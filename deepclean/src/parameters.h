#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include "ap_int.h"
#include "ap_fixed.h"

#include "nnet_utils/nnet_helpers.h"
#include "nnet_utils/nnet_code_gen.h"
//hls-fpga-machine-learning insert includes
#include "nnet_utils/nnet_activation.h"
#include "nnet_utils/nnet_activation_stream.h"
#include "nnet_utils/nnet_batchnorm.h"
#include "nnet_utils/nnet_batchnorm_stream.h"
#include "nnet_utils/nnet_conv1d.h"
#include "nnet_utils/nnet_conv1d_stream.h"
#include "nnet_utils/nnet_conv1dtranspose.h"
#include "nnet_utils/nnet_conv1dtranspose_stream.h"
#include "nnet_utils/nnet_padding.h"
#include "nnet_utils/nnet_padding_stream.h"
 
//hls-fpga-machine-learning insert weights
#include "weights/w2.h"
#include "weights/b2.h"
#include "weights/w6.h"
#include "weights/b6.h"
#include "weights/w10.h"
#include "weights/b10.h"
#include "weights/w14.h"
#include "weights/b14.h"
#include "weights/w18.h"
#include "weights/b18.h"
#include "weights/w22.h"
#include "weights/b22.h"
#include "weights/s24.h"
#include "weights/b24.h"
#include "weights/w26.h"
#include "weights/b26.h"
#include "weights/s28.h"
#include "weights/b28.h"
#include "weights/w30.h"
#include "weights/b30.h"
#include "weights/s32.h"
#include "weights/b32.h"
#include "weights/w34.h"
#include "weights/b34.h"
#include "weights/s36.h"
#include "weights/b36.h"
#include "weights/w38.h"
#include "weights/b38.h"

//hls-fpga-machine-learning insert layer-config
// zp1d_input_conv
struct config40 : nnet::padding1d_config {
    static const unsigned in_width = 8192;
    static const unsigned n_chan = 21;
    static const unsigned out_width = 8198;
    static const unsigned pad_left = 3;
    static const unsigned pad_right = 3;
};

// input_conv
struct config2_mult : nnet::dense_config {
    static const unsigned n_in = 147;
    static const unsigned n_out = 21;
    static const unsigned reuse_factor = 21;
    static const unsigned strategy = nnet::resource;
    typedef model_default_t accum_t;
    typedef input_conv_bias_t bias_t;
    typedef input_conv_weight_t weight_t;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};

struct config2 : nnet::conv1d_config {
    static const unsigned pad_left = 0;
    static const unsigned pad_right = 0;
    static const unsigned in_width = 8198;
    static const unsigned n_chan = 21;
    static const unsigned filt_width = 7;
    static const unsigned kernel_size = filt_width;
    static const unsigned n_filt = 21;
    static const unsigned stride_width = 1;
    static const unsigned dilation = 1;
    static const unsigned out_width = 8192;
    static const unsigned reuse_factor = 21;
    static const unsigned n_zeros = 0;
    static const bool store_weights_in_bram = false;
    static const unsigned strategy = nnet::resource;
    static const nnet::conv_implementation implementation = nnet::conv_implementation::linebuffer;
    static const unsigned min_width = 13;
    static const ap_uint<filt_width> pixels[min_width];
    static const unsigned n_partitions = 8192;
    static const unsigned n_pixels = out_width / n_partitions;
    template<class data_T, class CONFIG_T>
    using fill_buffer = nnet::FillConv1DBuffer<data_T, CONFIG_T>;
    typedef model_default_t accum_t;
    typedef input_conv_bias_t bias_t;
    typedef input_conv_weight_t weight_t;
    typedef config2_mult mult_config;
};
const ap_uint<config2::filt_width> config2::pixels[] = {1,3,7,15,31,63,127,126,124,120,112,96,64};

// activation
struct tanh_config5 : nnet::activ_config {
    static const unsigned n_in = 172032;
    static const unsigned table_size = 1024;
    static const unsigned io_type = nnet::io_stream;
    static const unsigned reuse_factor = 256;
    typedef activationtable_t table_t;
};

// zp1d_conv_1
struct config41 : nnet::padding1d_config {
    static const unsigned in_width = 8192;
    static const unsigned n_chan = 21;
    static const unsigned out_width = 8197;
    static const unsigned pad_left = 2;
    static const unsigned pad_right = 3;
};

// conv_1
struct config6_mult : nnet::dense_config {
    static const unsigned n_in = 147;
    static const unsigned n_out = 8;
    static const unsigned reuse_factor = 21;
    static const unsigned strategy = nnet::resource;
    typedef model_default_t accum_t;
    typedef conv_1_bias_t bias_t;
    typedef conv_1_weight_t weight_t;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};

struct config6 : nnet::conv1d_config {
    static const unsigned pad_left = 0;
    static const unsigned pad_right = 0;
    static const unsigned in_width = 8197;
    static const unsigned n_chan = 21;
    static const unsigned filt_width = 7;
    static const unsigned kernel_size = filt_width;
    static const unsigned n_filt = 8;
    static const unsigned stride_width = 2;
    static const unsigned dilation = 1;
    static const unsigned out_width = 4096;
    static const unsigned reuse_factor = 21;
    static const unsigned n_zeros = 0;
    static const bool store_weights_in_bram = false;
    static const unsigned strategy = nnet::resource;
    static const nnet::conv_implementation implementation = nnet::conv_implementation::linebuffer;
    static const unsigned min_width = 13;
    static const ap_uint<filt_width> pixels[min_width];
    static const unsigned n_partitions = 4096;
    static const unsigned n_pixels = out_width / n_partitions;
    template<class data_T, class CONFIG_T>
    using fill_buffer = nnet::FillConv1DBuffer<data_T, CONFIG_T>;
    typedef model_default_t accum_t;
    typedef conv_1_bias_t bias_t;
    typedef conv_1_weight_t weight_t;
    typedef config6_mult mult_config;
};
const ap_uint<config6::filt_width> config6::pixels[] = {1,2,5,10,21,42,85,42,84,40,80,32,64};

// activation_1
struct tanh_config9 : nnet::activ_config {
    static const unsigned n_in = 32768;
    static const unsigned table_size = 1024;
    static const unsigned io_type = nnet::io_stream;
    static const unsigned reuse_factor = 256;
    typedef activation_1table_t table_t;
};

// zp1d_conv_2
struct config42 : nnet::padding1d_config {
    static const unsigned in_width = 4096;
    static const unsigned n_chan = 8;
    static const unsigned out_width = 4101;
    static const unsigned pad_left = 2;
    static const unsigned pad_right = 3;
};

// conv_2
struct config10_mult : nnet::dense_config {
    static const unsigned n_in = 56;
    static const unsigned n_out = 16;
    static const unsigned reuse_factor = 28;
    static const unsigned strategy = nnet::resource;
    typedef model_default_t accum_t;
    typedef conv_2_bias_t bias_t;
    typedef conv_2_weight_t weight_t;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};

struct config10 : nnet::conv1d_config {
    static const unsigned pad_left = 0;
    static const unsigned pad_right = 0;
    static const unsigned in_width = 4101;
    static const unsigned n_chan = 8;
    static const unsigned filt_width = 7;
    static const unsigned kernel_size = filt_width;
    static const unsigned n_filt = 16;
    static const unsigned stride_width = 2;
    static const unsigned dilation = 1;
    static const unsigned out_width = 2048;
    static const unsigned reuse_factor = 28;
    static const unsigned n_zeros = 0;
    static const bool store_weights_in_bram = false;
    static const unsigned strategy = nnet::resource;
    static const nnet::conv_implementation implementation = nnet::conv_implementation::linebuffer;
    static const unsigned min_width = 13;
    static const ap_uint<filt_width> pixels[min_width];
    static const unsigned n_partitions = 2048;
    static const unsigned n_pixels = out_width / n_partitions;
    template<class data_T, class CONFIG_T>
    using fill_buffer = nnet::FillConv1DBuffer<data_T, CONFIG_T>;
    typedef model_default_t accum_t;
    typedef conv_2_bias_t bias_t;
    typedef conv_2_weight_t weight_t;
    typedef config10_mult mult_config;
};
const ap_uint<config10::filt_width> config10::pixels[] = {1,2,5,10,21,42,85,42,84,40,80,32,64};

// activation_2
struct tanh_config13 : nnet::activ_config {
    static const unsigned n_in = 32768;
    static const unsigned table_size = 1024;
    static const unsigned io_type = nnet::io_stream;
    static const unsigned reuse_factor = 256;
    typedef activation_2table_t table_t;
};

// zp1d_conv_3
struct config43 : nnet::padding1d_config {
    static const unsigned in_width = 2048;
    static const unsigned n_chan = 16;
    static const unsigned out_width = 2053;
    static const unsigned pad_left = 2;
    static const unsigned pad_right = 3;
};

// conv_3
struct config14_mult : nnet::dense_config {
    static const unsigned n_in = 112;
    static const unsigned n_out = 32;
    static const unsigned reuse_factor = 56;
    static const unsigned strategy = nnet::resource;
    typedef model_default_t accum_t;
    typedef conv_3_bias_t bias_t;
    typedef conv_3_weight_t weight_t;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};

struct config14 : nnet::conv1d_config {
    static const unsigned pad_left = 0;
    static const unsigned pad_right = 0;
    static const unsigned in_width = 2053;
    static const unsigned n_chan = 16;
    static const unsigned filt_width = 7;
    static const unsigned kernel_size = filt_width;
    static const unsigned n_filt = 32;
    static const unsigned stride_width = 2;
    static const unsigned dilation = 1;
    static const unsigned out_width = 1024;
    static const unsigned reuse_factor = 56;
    static const unsigned n_zeros = 0;
    static const bool store_weights_in_bram = false;
    static const unsigned strategy = nnet::resource;
    static const nnet::conv_implementation implementation = nnet::conv_implementation::linebuffer;
    static const unsigned min_width = 13;
    static const ap_uint<filt_width> pixels[min_width];
    static const unsigned n_partitions = 1024;
    static const unsigned n_pixels = out_width / n_partitions;
    template<class data_T, class CONFIG_T>
    using fill_buffer = nnet::FillConv1DBuffer<data_T, CONFIG_T>;
    typedef model_default_t accum_t;
    typedef conv_3_bias_t bias_t;
    typedef conv_3_weight_t weight_t;
    typedef config14_mult mult_config;
};
const ap_uint<config14::filt_width> config14::pixels[] = {1,2,5,10,21,42,85,42,84,40,80,32,64};

// activation_3
struct tanh_config17 : nnet::activ_config {
    static const unsigned n_in = 32768;
    static const unsigned table_size = 1024;
    static const unsigned io_type = nnet::io_stream;
    static const unsigned reuse_factor = 256;
    typedef activation_3table_t table_t;
};

// zp1d_conv_4
struct config44 : nnet::padding1d_config {
    static const unsigned in_width = 1024;
    static const unsigned n_chan = 32;
    static const unsigned out_width = 1029;
    static const unsigned pad_left = 2;
    static const unsigned pad_right = 3;
};

// conv_4
struct config18_mult : nnet::dense_config {
    static const unsigned n_in = 224;
    static const unsigned n_out = 64;
    static const unsigned reuse_factor = 224;
    static const unsigned strategy = nnet::resource;
    typedef model_default_t accum_t;
    typedef conv_4_bias_t bias_t;
    typedef conv_4_weight_t weight_t;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};

struct config18 : nnet::conv1d_config {
    static const unsigned pad_left = 0;
    static const unsigned pad_right = 0;
    static const unsigned in_width = 1029;
    static const unsigned n_chan = 32;
    static const unsigned filt_width = 7;
    static const unsigned kernel_size = filt_width;
    static const unsigned n_filt = 64;
    static const unsigned stride_width = 2;
    static const unsigned dilation = 1;
    static const unsigned out_width = 512;
    static const unsigned reuse_factor = 224;
    static const unsigned n_zeros = 0;
    static const bool store_weights_in_bram = false;
    static const unsigned strategy = nnet::resource;
    static const nnet::conv_implementation implementation = nnet::conv_implementation::linebuffer;
    static const unsigned min_width = 13;
    static const ap_uint<filt_width> pixels[min_width];
    static const unsigned n_partitions = 512;
    static const unsigned n_pixels = out_width / n_partitions;
    template<class data_T, class CONFIG_T>
    using fill_buffer = nnet::FillConv1DBuffer<data_T, CONFIG_T>;
    typedef model_default_t accum_t;
    typedef conv_4_bias_t bias_t;
    typedef conv_4_weight_t weight_t;
    typedef config18_mult mult_config;
};
const ap_uint<config18::filt_width> config18::pixels[] = {1,2,5,10,21,42,85,42,84,40,80,32,64};

// activation_4
struct tanh_config21 : nnet::activ_config {
    static const unsigned n_in = 32768;
    static const unsigned table_size = 1024;
    static const unsigned io_type = nnet::io_stream;
    static const unsigned reuse_factor = 256;
    typedef activation_4table_t table_t;
};

// zp1d_convtr_1
struct config46 : nnet::padding1d_config {
    static const unsigned in_width = 512;
    static const unsigned n_chan = 64;
    static const unsigned out_width = 517;
    static const unsigned pad_left = 3;
    static const unsigned pad_right = 2;
};

// convtr_1
struct config22_mult : nnet::dense_config {
    static const unsigned n_in = 256;
    static const unsigned n_out = 32;
    static const unsigned reuse_factor = 256;
    static const unsigned strategy = nnet::resource;
    typedef model_default_t accum_t;
    typedef convtr_1_bias_t bias_t;
    typedef convtr_1_weight_t weight_t;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};

struct config22 : nnet::conv1dtranspose_config {
    static const unsigned pad_left = 8;
    static const unsigned pad_right = 3;
    static const unsigned in_width = 517;
    static const unsigned n_chan = 64;
    static const unsigned filt_width = 7;
    static const unsigned kernel_size = filt_width;
    static const unsigned n_filt = 32;
    static const unsigned stride_width = 2;
    static const unsigned dilation = 1;
    static const unsigned out_width = 1024;
    static const unsigned reuse_factor = 256;
    static const unsigned n_zeros = 2048;
    static const unsigned trfilt_width = 4;
    static const bool store_weights_in_bram = false;
    static const unsigned strategy = nnet::resource;
    static const nnet::conv_implementation implementation = nnet::conv_implementation::linebuffer;
    static const unsigned min_width = 7;
    static const ap_uint<trfilt_width> pixels[min_width];
    static const unsigned n_partitions = 513;
    static const unsigned proc_width = 513;
    static const unsigned n_pixels = proc_width / n_partitions;
    template<class data_T, class CONFIG_T>
    using fill_buffer = nnet::FillConv1DBuffer<data_T, CONFIG_T>;
    typedef model_default_t accum_t;
    typedef convtr_1_bias_t bias_t;
    typedef convtr_1_weight_t weight_t;
    typedef config22_mult mult_config;
};
const ap_uint<config22::trfilt_width> config22::pixels[] = {1,3,7,15,14,12,8};

// batch_normalization_5
struct config24 : nnet::batchnorm_config {
    static const unsigned n_in = N_OUTPUTS_22*N_FILT_22;
    static const unsigned n_filt = 32;
    static const unsigned n_scale_bias = (n_filt == -1) ? n_in : n_filt;
    static const unsigned io_type = nnet::io_stream;
    static const unsigned reuse_factor = 256;
    static const bool store_weights_in_bram = false;
    typedef batch_normalization_5_bias_t bias_t;
    typedef batch_normalization_5_scale_t scale_t;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};

// activation_5
struct tanh_config25 : nnet::activ_config {
    static const unsigned n_in = 32768;
    static const unsigned table_size = 1024;
    static const unsigned io_type = nnet::io_stream;
    static const unsigned reuse_factor = 256;
    typedef activation_5table_t table_t;
};

// zp1d_convtr_2
struct config47 : nnet::padding1d_config {
    static const unsigned in_width = 1024;
    static const unsigned n_chan = 32;
    static const unsigned out_width = 1029;
    static const unsigned pad_left = 3;
    static const unsigned pad_right = 2;
};

// convtr_2
struct config26_mult : nnet::dense_config {
    static const unsigned n_in = 128;
    static const unsigned n_out = 16;
    static const unsigned reuse_factor = 64;
    static const unsigned strategy = nnet::resource;
    typedef model_default_t accum_t;
    typedef convtr_2_bias_t bias_t;
    typedef convtr_2_weight_t weight_t;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};

struct config26 : nnet::conv1dtranspose_config {
    static const unsigned pad_left = 8;
    static const unsigned pad_right = 3;
    static const unsigned in_width = 1029;
    static const unsigned n_chan = 32;
    static const unsigned filt_width = 7;
    static const unsigned kernel_size = filt_width;
    static const unsigned n_filt = 16;
    static const unsigned stride_width = 2;
    static const unsigned dilation = 1;
    static const unsigned out_width = 2048;
    static const unsigned reuse_factor = 64;
    static const unsigned n_zeros = 512;
    static const unsigned trfilt_width = 4;
    static const bool store_weights_in_bram = false;
    static const unsigned strategy = nnet::resource;
    static const nnet::conv_implementation implementation = nnet::conv_implementation::linebuffer;
    static const unsigned min_width = 7;
    static const ap_uint<trfilt_width> pixels[min_width];
    static const unsigned n_partitions = 1025;
    static const unsigned proc_width = 1025;
    static const unsigned n_pixels = proc_width / n_partitions;
    template<class data_T, class CONFIG_T>
    using fill_buffer = nnet::FillConv1DBuffer<data_T, CONFIG_T>;
    typedef model_default_t accum_t;
    typedef convtr_2_bias_t bias_t;
    typedef convtr_2_weight_t weight_t;
    typedef config26_mult mult_config;
};
const ap_uint<config26::trfilt_width> config26::pixels[] = {1,3,7,15,14,12,8};

// batch_normalization_6
struct config28 : nnet::batchnorm_config {
    static const unsigned n_in = N_OUTPUTS_26*N_FILT_26;
    static const unsigned n_filt = 16;
    static const unsigned n_scale_bias = (n_filt == -1) ? n_in : n_filt;
    static const unsigned io_type = nnet::io_stream;
    static const unsigned reuse_factor = 256;
    static const bool store_weights_in_bram = false;
    typedef batch_normalization_6_bias_t bias_t;
    typedef batch_normalization_6_scale_t scale_t;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};

// activation_6
struct tanh_config29 : nnet::activ_config {
    static const unsigned n_in = 32768;
    static const unsigned table_size = 1024;
    static const unsigned io_type = nnet::io_stream;
    static const unsigned reuse_factor = 256;
    typedef activation_6table_t table_t;
};

// zp1d_convtr_3
struct config48 : nnet::padding1d_config {
    static const unsigned in_width = 2048;
    static const unsigned n_chan = 16;
    static const unsigned out_width = 2053;
    static const unsigned pad_left = 3;
    static const unsigned pad_right = 2;
};

// convtr_3
struct config30_mult : nnet::dense_config {
    static const unsigned n_in = 64;
    static const unsigned n_out = 8;
    static const unsigned reuse_factor = 32;
    static const unsigned strategy = nnet::resource;
    typedef model_default_t accum_t;
    typedef convtr_3_bias_t bias_t;
    typedef convtr_3_weight_t weight_t;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};

struct config30 : nnet::conv1dtranspose_config {
    static const unsigned pad_left = 8;
    static const unsigned pad_right = 3;
    static const unsigned in_width = 2053;
    static const unsigned n_chan = 16;
    static const unsigned filt_width = 7;
    static const unsigned kernel_size = filt_width;
    static const unsigned n_filt = 8;
    static const unsigned stride_width = 2;
    static const unsigned dilation = 1;
    static const unsigned out_width = 4096;
    static const unsigned reuse_factor = 32;
    static const unsigned n_zeros = 128;
    static const unsigned trfilt_width = 4;
    static const bool store_weights_in_bram = false;
    static const unsigned strategy = nnet::resource;
    static const nnet::conv_implementation implementation = nnet::conv_implementation::linebuffer;
    static const unsigned min_width = 7;
    static const ap_uint<trfilt_width> pixels[min_width];
    static const unsigned n_partitions = 2049;
    static const unsigned proc_width = 2049;
    static const unsigned n_pixels = proc_width / n_partitions;
    template<class data_T, class CONFIG_T>
    using fill_buffer = nnet::FillConv1DBuffer<data_T, CONFIG_T>;
    typedef model_default_t accum_t;
    typedef convtr_3_bias_t bias_t;
    typedef convtr_3_weight_t weight_t;
    typedef config30_mult mult_config;
};
const ap_uint<config30::trfilt_width> config30::pixels[] = {1,3,7,15,14,12,8};

// batch_normalization_7
struct config32 : nnet::batchnorm_config {
    static const unsigned n_in = N_OUTPUTS_30*N_FILT_30;
    static const unsigned n_filt = 8;
    static const unsigned n_scale_bias = (n_filt == -1) ? n_in : n_filt;
    static const unsigned io_type = nnet::io_stream;
    static const unsigned reuse_factor = 256;
    static const bool store_weights_in_bram = false;
    typedef batch_normalization_7_bias_t bias_t;
    typedef batch_normalization_7_scale_t scale_t;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};

// activation_7
struct tanh_config33 : nnet::activ_config {
    static const unsigned n_in = 32768;
    static const unsigned table_size = 1024;
    static const unsigned io_type = nnet::io_stream;
    static const unsigned reuse_factor = 256;
    typedef activation_7table_t table_t;
};

// zp1d_convtr_4
struct config49 : nnet::padding1d_config {
    static const unsigned in_width = 4096;
    static const unsigned n_chan = 8;
    static const unsigned out_width = 4101;
    static const unsigned pad_left = 3;
    static const unsigned pad_right = 2;
};

// convtr_4
struct config34_mult : nnet::dense_config {
    static const unsigned n_in = 32;
    static const unsigned n_out = 21;
    static const unsigned reuse_factor = 16;
    static const unsigned strategy = nnet::resource;
    typedef model_default_t accum_t;
    typedef convtr_4_bias_t bias_t;
    typedef convtr_4_weight_t weight_t;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};

struct config34 : nnet::conv1dtranspose_config {
    static const unsigned pad_left = 8;
    static const unsigned pad_right = 3;
    static const unsigned in_width = 4101;
    static const unsigned n_chan = 8;
    static const unsigned filt_width = 7;
    static const unsigned kernel_size = filt_width;
    static const unsigned n_filt = 21;
    static const unsigned stride_width = 2;
    static const unsigned dilation = 1;
    static const unsigned out_width = 8192;
    static const unsigned reuse_factor = 16;
    static const unsigned n_zeros = 168;
    static const unsigned trfilt_width = 4;
    static const bool store_weights_in_bram = false;
    static const unsigned strategy = nnet::resource;
    static const nnet::conv_implementation implementation = nnet::conv_implementation::linebuffer;
    static const unsigned min_width = 7;
    static const ap_uint<trfilt_width> pixels[min_width];
    static const unsigned n_partitions = 4097;
    static const unsigned proc_width = 4097;
    static const unsigned n_pixels = proc_width / n_partitions;
    template<class data_T, class CONFIG_T>
    using fill_buffer = nnet::FillConv1DBuffer<data_T, CONFIG_T>;
    typedef model_default_t accum_t;
    typedef convtr_4_bias_t bias_t;
    typedef convtr_4_weight_t weight_t;
    typedef config34_mult mult_config;
};
const ap_uint<config34::trfilt_width> config34::pixels[] = {1,3,7,15,14,12,8};

// batch_normalization_8
struct config36 : nnet::batchnorm_config {
    static const unsigned n_in = N_OUTPUTS_34*N_FILT_34;
    static const unsigned n_filt = 21;
    static const unsigned n_scale_bias = (n_filt == -1) ? n_in : n_filt;
    static const unsigned io_type = nnet::io_stream;
    static const unsigned reuse_factor = 256;
    static const bool store_weights_in_bram = false;
    typedef batch_normalization_8_bias_t bias_t;
    typedef batch_normalization_8_scale_t scale_t;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};

// activation_8
struct tanh_config37 : nnet::activ_config {
    static const unsigned n_in = 172032;
    static const unsigned table_size = 1024;
    static const unsigned io_type = nnet::io_stream;
    static const unsigned reuse_factor = 256;
    typedef activation_8table_t table_t;
};

// zp1d_output_conv
struct config45 : nnet::padding1d_config {
    static const unsigned in_width = 8192;
    static const unsigned n_chan = 21;
    static const unsigned out_width = 8198;
    static const unsigned pad_left = 3;
    static const unsigned pad_right = 3;
};

// output_conv
struct config38_mult : nnet::dense_config {
    static const unsigned n_in = 147;
    static const unsigned n_out = 1;
    static const unsigned reuse_factor = 21;
    static const unsigned strategy = nnet::resource;
    typedef model_default_t accum_t;
    typedef output_conv_bias_t bias_t;
    typedef output_conv_weight_t weight_t;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};

struct config38 : nnet::conv1d_config {
    static const unsigned pad_left = 0;
    static const unsigned pad_right = 0;
    static const unsigned in_width = 8198;
    static const unsigned n_chan = 21;
    static const unsigned filt_width = 7;
    static const unsigned kernel_size = filt_width;
    static const unsigned n_filt = 1;
    static const unsigned stride_width = 1;
    static const unsigned dilation = 1;
    static const unsigned out_width = 8192;
    static const unsigned reuse_factor = 21;
    static const unsigned n_zeros = 0;
    static const bool store_weights_in_bram = false;
    static const unsigned strategy = nnet::resource;
    static const nnet::conv_implementation implementation = nnet::conv_implementation::linebuffer;
    static const unsigned min_width = 13;
    static const ap_uint<filt_width> pixels[min_width];
    static const unsigned n_partitions = 8192;
    static const unsigned n_pixels = out_width / n_partitions;
    template<class data_T, class CONFIG_T>
    using fill_buffer = nnet::FillConv1DBuffer<data_T, CONFIG_T>;
    typedef model_default_t accum_t;
    typedef output_conv_bias_t bias_t;
    typedef output_conv_weight_t weight_t;
    typedef config38_mult mult_config;
};
const ap_uint<config38::filt_width> config38::pixels[] = {1,3,7,15,31,63,127,126,124,120,112,96,64};


#endif
