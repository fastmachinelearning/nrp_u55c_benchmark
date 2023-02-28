#ifndef NNET_CONV1D_STREAM_H_
#define NNET_CONV1D_STREAM_H_

#include "nnet_common.h"
#include "nnet_conv_stream.h"
#include "hls_stream.h"

namespace nnet {

template<class data_T, typename CONFIG_T>
void compute_scaled_indices_1d(
    const unsigned w_idx,
    ap_uint<CONFIG_T::filt_width> *pixel_idx
) {
    unsigned wp_idx = w_idx * (data_T::size / CONFIG_T::n_chan);

    ComputeIndex: for (unsigned p = 0; p < data_T::size / CONFIG_T::n_chan; p++) {
        #pragma HLS UNROLL

        unsigned sw_idx = scale_index<CONFIG_T::filt_width, CONFIG_T::stride_width, CONFIG_T::in_width>(wp_idx + p);
        pixel_idx[p] = CONFIG_T::pixels[sw_idx];
    }
}

template<class data_T, class res_T, typename CONFIG_T>
void conv_1d_encoded_cl(
    hls::stream<data_T> &data,
    hls::stream<res_T>  &res,
    typename CONFIG_T::weight_t weights[CONFIG_T::filt_width * CONFIG_T::n_chan * CONFIG_T::n_filt],
    typename CONFIG_T::bias_t   biases[CONFIG_T::n_filt])
{
    assert(CONFIG_T::pad_left == 0 && CONFIG_T::pad_right == 0);

    hls::stream<typename data_T::value_type> data_window[CONFIG_T::filt_width * CONFIG_T::n_chan];
    const int win_depth = CONFIG_T::out_width;
    for (unsigned i_out = 0; i_out < CONFIG_T::filt_width * CONFIG_T::n_chan; i_out++) {
        #pragma HLS STREAM variable=data_window[i_out] depth=win_depth
    }

    #pragma HLS ARRAY_PARTITION variable=CONFIG_T::pixels complete

    res_T res_pack;
    #pragma HLS DATA_PACK variable=res_pack
    unsigned outputs_ready = 0;

    ap_uint<CONFIG_T::filt_width> pixel_idx[data_T::size / CONFIG_T::n_chan];
    #pragma HLS ARRAY_PARTITION variable=pixel_idx complete

    ReadInputWidth: for (unsigned i_iw = 0; i_iw < CONFIG_T::in_width / (data_T::size / CONFIG_T::n_chan); i_iw++) {
        #pragma HLS LOOP_FLATTEN
        if (CONFIG_T::strategy == nnet::latency && data_T::size / CONFIG_T::n_chan == 1) {
            #pragma HLS PIPELINE II=CONFIG_T::reuse_factor
        }
        compute_scaled_indices_1d<data_T, CONFIG_T>(i_iw, pixel_idx);
        compute_output_encoded<data_T, res_T, CONFIG_T>(data.read(), data_window, res, res_pack, outputs_ready, weights, biases, pixel_idx);
    }
}

template<class data_T, class res_T, typename CONFIG_T>
void conv_1d_buffer_cl(
    hls::stream<data_T> &data,
    hls::stream<res_T>  &res,
    typename CONFIG_T::weight_t weights[CONFIG_T::filt_width * CONFIG_T::n_chan * CONFIG_T::n_filt],
    typename CONFIG_T::bias_t   biases[CONFIG_T::n_filt])
{
    assert(CONFIG_T::pad_left == 0 && CONFIG_T::pad_right == 0);

    ReadInputWidth: for (unsigned i_iw = 0; i_iw < CONFIG_T::in_width; i_iw++) {
        #pragma HLS LOOP_FLATTEN
        if (CONFIG_T::strategy == nnet::latency) {
            #pragma HLS PIPELINE II=CONFIG_T::reuse_factor
        }
        compute_output_buffer_1d<data_T, res_T, CONFIG_T>(data.read(), res, weights, biases);
    }
}

template<class data_T, class res_T, typename CONFIG_T>
void conv_1d_cl(
    hls::stream<data_T> &data,
    hls::stream<res_T>  &res,
    typename CONFIG_T::weight_t weights[CONFIG_T::filt_width * CONFIG_T::n_chan * CONFIG_T::n_filt],
    typename CONFIG_T::bias_t   biases[CONFIG_T::n_filt])
{
    #pragma HLS inline region
    switch(CONFIG_T::implementation){
        case conv_implementation::linebuffer:
            conv_1d_buffer_cl<data_T, res_T, CONFIG_T>(data, res, weights, biases);
            break;
        case conv_implementation::encoded:
            conv_1d_encoded_cl<data_T, res_T, CONFIG_T>(data, res, weights, biases);
            break;
    }  
}

}




}

template<class data_T,typename CONFIG_T>
void cnnshift_arr(
    const data_T data[CONFIG_T::n_chan],
    data_T kernel_window[(CONFIG_T::filt_width)*(CONFIG_T::n_chan)]
) {
    #pragma HLS inline
    #pragma HLS PIPELINE II = 1
    
    // Shift kernel_window by one step to the left (manual shift operation)
    static const int filt_width = CONFIG_T::filt_width - 1;
    KernelShiftWidth: for (int i_iw = 0; i_iw < filt_width; i_iw++) {
        #pragma HLS UNROLL
        KernelShiftChannel: for (unsigned i_ic = 0; i_ic < CONFIG_T::n_chan; i_ic++) {
            // Shift every element in kernel_window to the left
            kernel_window[i_iw * CONFIG_T::n_chan + i_ic] = kernel_window[(i_iw + 1) * CONFIG_T::n_chan + i_ic];
        }
    }

    // Insert shift_buffer column into right-most column of kernel
    static const int lastheight = (CONFIG_T::filt_width - 1) * CONFIG_T::n_chan;
    KernelPushChannel: for (int i_ic = 0; i_ic < CONFIG_T::n_chan; i_ic++) {
        #pragma HLS UNROLL
        kernel_window[lastheight + i_ic] = data[i_ic];
    }
}


template<class data_T, class res_T, typename CONFIG_T>
void conv_1d_large_cl_nopad_pad_ss(
         hls::stream<data_T> &data,
         hls::stream<res_T>  &res,
         typename CONFIG_T::weight_t weights[CONFIG_T::filt_width * CONFIG_T::n_chan * CONFIG_T::n_filt],
         typename CONFIG_T::bias_t   biases[CONFIG_T::n_filt]               
                ) {

    assert(CONFIG_T::pad_top == 0 && CONFIG_T::pad_right == 0);
    std::cout  << "USE CONV1D LARGE"<< std::endl;

    data_T tmpdata[CONFIG_T::n_chan];
    #pragma HLS ARRAY_RESHAPE variable=tmpdata complete

    static data_T layer_in[CONFIG_T::filt_width*CONFIG_T::n_chan];
    #pragma HLS ARRAY_RESHAPE variable=layer_in complete

    //typename res_T::value_type layer_reluout[CONFIG_T::n_filt];
    //#pragma HLS ARRAY_RESHAPE variable=layer_reluout complete dim=0

    res_T layer_out[CONFIG_T::n_filt];
    #pragma HLS ARRAY_RESHAPE variable=layer_out complete dim=0

    res_T res_pack;
    #pragma HLS DATA_PACK variable=res_pack



    // Thresholds
    const static int lShiftX = CONFIG_T::filt_width - 1;

    // Counters
    static int pX = 0; // Pixel X
    static int sX = 0; // Stride X

    for (unsigned i = 0; i < CONFIG_T::in_width; i++) {

        for(int i1 = 0; i1 < CONFIG_T::n_chan; i1++) { 
          #pragma HLS UNROLL
          tmpdata[i1] = data.read();
        }
        cnnshift_arr<data_T,CONFIG_T>(tmpdata,layer_in);

        // Check to see if we have a full kernel
        if ( (sX - lShiftX) == 0 && pX > lShiftX - 1) {

            // Dense multiply
            #pragma HLS INLINE region
            if (CONFIG_T::strategy == nnet::latency) {
                nnet::dense_latency<data_T,res_T, typename CONFIG_T::mult_config>(layer_in, layer_out, weights, biases);

            } else {
                nnet::dense_resource<data_T,res_T, typename CONFIG_T::mult_config>(layer_in, layer_out, weights, biases);
            }
            // Pack output
            CastLoop: for (unsigned i_ic = 0; i_ic < CONFIG_T::n_filt; i_ic++) {
                #pragma HLS UNROLL
                res_pack = layer_out[i_ic];
                res.write(res_pack);
            }

            // Write output to stream when output ready

        }

        // Counter Housekeeping
        if (pX + 1 == CONFIG_T::in_width)  // Includes padding, end of line (padded)
        {
            pX = 0; 
            sX = 0;

        } else {
            pX = pX + 1;
            // Update stride (threshold) ? subtract stride : increment stride
            sX = ((sX - lShiftX) == 0) ? sX - CONFIG_T::stride_width + 1 : sX + 1; 
        }
    }
}


template<class data_T, class res_T, typename CONFIG_T>
void conv_1d_cl_ss(
    hls::stream<data_T> &data,
    hls::stream<res_T>  &res,
    typename CONFIG_T::weight_t weights[CONFIG_T::filt_width * CONFIG_T::n_chan * CONFIG_T::n_filt],
    typename CONFIG_T::bias_t   biases[CONFIG_T::n_filt])
{
    #pragma HLS inline region
    switch(CONFIG_T::implementation){
        case nnet::conv_implementation::linebuffer:
            conv_1d_large_cl_nopad_pad_ss<data_T, res_T, CONFIG_T>(data, res, weights, biases);
            break;
        case nnet::conv_implementation::encoded:
            conv_1d_large_cl_nopad_pad_ss<data_T, res_T, CONFIG_T>(data, res, weights, biases);
            break;
    }  
}

#endif

