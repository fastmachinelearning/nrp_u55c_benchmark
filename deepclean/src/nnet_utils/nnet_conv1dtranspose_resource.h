#ifndef NNET_CONV1DTRANSPOSE_RESOURCE_H_
#define NNET_CONV1DTRANSPOSE_RESOURCE_H_

#include "nnet_common.h"
#include "nnet_dense.h"

namespace nnet{

template<class data_T, class res_T, typename CONFIG_T>
void conv_1d_transpose_resource_cl(
    data_T data[CONFIG_T::in_width * CONFIG_T::n_chan],
    res_T res[CONFIG_T::out_width  * CONFIG_T::n_filt],
    typename CONFIG_T::weight_t weights[CONFIG_T::stride_width][
        CONFIG_T::trfilt_width * CONFIG_T::n_filt * CONFIG_T::n_chan
    ],
    typename CONFIG_T::bias_t   biases[CONFIG_T::n_filt]
)
{
    constexpr unsigned mult_n_in = CONFIG_T::trfilt_width * CONFIG_T::n_chan;
    constexpr unsigned mult_n_out = CONFIG_T::n_filt;
    constexpr unsigned block_factor = DIV_ROUNDUP(mult_n_in * mult_n_out, CONFIG_T::reuse_factor);
    constexpr unsigned multscale = block_factor / mult_n_out;

    assert((block_factor % mult_n_out == 0 || CONFIG_T::reuse_factor >= mult_n_in) && "The current Reuse Factor is not allowed");
    assert((CONFIG_T::reuse_factor <= CONFIG_T::trfilt_width * CONFIG_T::n_chan) && "This function is correct only for RF <= TRFILT_WIDTH * N_CHAN");

    data_T data_buf[CONFIG_T::n_pixels][mult_n_in];
    #pragma HLS ARRAY_PARTITION variable=data_buf complete dim=0
    #pragma HLS ARRAY_PARTITION variable=biases complete

    typename CONFIG_T::accum_t acc[CONFIG_T::n_pixels][mult_n_out][CONFIG_T::stride_width];
    #pragma HLS ARRAY_PARTITION variable=acc complete dim=0

    #pragma HLS ARRAY_RESHAPE variable=weights block factor=block_factor dim=2

    PartitionLoop:
    for (unsigned i_part = 0; i_part < CONFIG_T::n_partitions; i_part++) {
        CONFIG_T::template fill_buffer<data_T, CONFIG_T>::fill_buffer(data, data_buf, i_part);

        PixelInitAccumLoop:
        for (unsigned i_pxl = 0; i_pxl < CONFIG_T::n_pixels; i_pxl++) {
            #pragma HLS UNROLL

            InitAccumLoop:
            for (unsigned i_acc = 0; i_acc < mult_n_out; i_acc++) {
                #pragma HLS UNROLL

                InitStrideLoop:
                for (unsigned i_sw = 0; i_sw < CONFIG_T::stride_width; i_sw++) {
                    #pragma HLS UNROLL
                    acc[i_pxl][i_acc][i_sw] = (typename CONFIG_T::accum_t) biases[i_acc];
                }
            }
        }

        ReuseLoop:
        for (unsigned i_rf = 0; i_rf < CONFIG_T::reuse_factor; i_rf++) {
            #pragma HLS PIPELINE II=1 rewind

            unsigned i_w = i_rf;
            unsigned i_in = i_rf;
            unsigned i_out = 0;
            unsigned i_acc = 0;

            MultLoop:
            for (unsigned i_blk = 0; i_blk < block_factor; i_blk++) {
                #pragma HLS UNROLL

                PixelMultLoop:
                for (unsigned i_pxl = 0; i_pxl < CONFIG_T::n_pixels; i_pxl++) {
                    #pragma HLS UNROLL

                    StrideMultLoop:
                    for (unsigned i_sw = 0; i_sw < CONFIG_T::stride_width; i_sw++) {
                        #pragma HLS UNROLL

                        acc[i_pxl][i_out][i_sw] += static_cast<typename CONFIG_T::accum_t>(
                            CONFIG_T::mult_config::template product<data_T, typename CONFIG_T::mult_config::weight_t>::product(
                                data_buf[i_pxl][i_in], weights[i_sw][i_w]
                            )
                        );
                    }
                }

                // Increment i_w
                i_w += CONFIG_T::reuse_factor;
                // Increment i_in
                i_in += CONFIG_T::reuse_factor;
                if (i_in >= mult_n_in) {
                    i_in = i_rf;
                }
                // Increment i_out
                if (i_acc + 1 >= multscale) {
                    i_acc = 0;
                    i_out++;
                } else {
                    i_acc++;
                }
            }
        }


        PixelResultLoop:
        for (unsigned i_pxl = 0; i_pxl < CONFIG_T::n_pixels; i_pxl++) {
            #pragma HLS UNROLL

            StrideResultLoop:
            for (unsigned i_sw = 0; i_sw < CONFIG_T::stride_width; i_sw++) {
                #pragma HLS UNROLL

                unsigned output_index = i_pxl * CONFIG_T::n_partitions * CONFIG_T::stride_width + 
                    i_part * CONFIG_T::stride_width + i_sw;
                
                if (output_index >= CONFIG_T::pad_left && 
                    output_index < CONFIG_T::out_width + CONFIG_T::pad_left) {
                    ResultLoop:
                    for (unsigned i_res = 0; i_res < mult_n_out; i_res++) {
                        #pragma HLS UNROLL

                        res[(output_index-CONFIG_T::pad_left)*mult_n_out + i_res] = 
                            cast<data_T, res_T, typename CONFIG_T::mult_config>(acc[i_pxl][i_res][i_sw]);
                    }
                }
            }
        }
    }

}


}
#endif
