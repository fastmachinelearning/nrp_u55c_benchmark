#ifndef DEFINES_H_
#define DEFINES_H_

#include "ap_int.h"
#include "ap_fixed.h"
#include "nnet_utils/nnet_types.h"
#include <cstddef>
#include <cstdio>

//hls-fpga-machine-learning insert numbers
#define N_INPUT_1_1 8192
#define N_INPUT_2_1 21
#define OUT_WIDTH_40 8198
#define N_CHAN_40 21
#define N_OUTPUTS_2 8192
#define N_FILT_2 21
#define OUT_WIDTH_41 8197
#define N_CHAN_41 21
#define N_OUTPUTS_6 4096
#define N_FILT_6 8
#define OUT_WIDTH_42 4101
#define N_CHAN_42 8
#define N_OUTPUTS_10 2048
#define N_FILT_10 16
#define OUT_WIDTH_43 2053
#define N_CHAN_43 16
#define N_OUTPUTS_14 1024
#define N_FILT_14 32
#define OUT_WIDTH_44 1029
#define N_CHAN_44 32
#define N_OUTPUTS_18 512
#define N_FILT_18 64
#define OUT_WIDTH_46 517
#define N_CHAN_46 64
#define N_OUTPUTS_22 1024
#define N_FILT_22 32
#define OUT_WIDTH_47 1029
#define N_CHAN_47 32
#define N_OUTPUTS_26 2048
#define N_FILT_26 16
#define OUT_WIDTH_48 2053
#define N_CHAN_48 16
#define N_OUTPUTS_30 4096
#define N_FILT_30 8
#define OUT_WIDTH_49 4101
#define N_CHAN_49 8
#define N_OUTPUTS_34 8192
#define N_FILT_34 21
#define OUT_WIDTH_45 8198
#define N_CHAN_45 21
#define N_OUTPUTS_38 8192
#define N_FILT_38 1

//hls-fpga-machine-learning insert layer-precision
typedef ap_fixed<16,2> model_default_t;
typedef nnet::array<ap_fixed<16,2>, 21*1> input_t;
typedef nnet::array<ap_fixed<16,2>, 21*1> layer40_t;
typedef nnet::array<ap_fixed<16,2>, 21*1> layer2_t;
typedef ap_fixed<16,2> input_conv_weight_t;
typedef ap_fixed<16,2> input_conv_bias_t;
typedef ap_fixed<16,2> activation_default_t;
typedef ap_fixed<16,2> activationtable_t;
typedef nnet::array<ap_fixed<16,2>, 21*1> layer5_t;
typedef nnet::array<ap_fixed<16,2>, 21*1> layer41_t;
typedef nnet::array<ap_fixed<16,2>, 8*1> layer6_t;
typedef ap_fixed<16,2> conv_1_weight_t;
typedef ap_fixed<16,2> conv_1_bias_t;
typedef ap_fixed<16,2> activation_1_default_t;
typedef ap_fixed<16,2> activation_1table_t;
typedef nnet::array<ap_fixed<16,2>, 8*1> layer9_t;
typedef nnet::array<ap_fixed<16,2>, 8*1> layer42_t;
typedef nnet::array<ap_fixed<16,2>, 16*1> layer10_t;
typedef ap_fixed<16,2> conv_2_weight_t;
typedef ap_fixed<16,2> conv_2_bias_t;
typedef ap_fixed<16,2> activation_2_default_t;
typedef ap_fixed<16,2> activation_2table_t;
typedef nnet::array<ap_fixed<16,2>, 16*1> layer13_t;
typedef nnet::array<ap_fixed<16,2>, 16*1> layer43_t;
typedef nnet::array<ap_fixed<16,2>, 32*1> layer14_t;
typedef ap_fixed<16,2> conv_3_weight_t;
typedef ap_fixed<16,2> conv_3_bias_t;
typedef ap_fixed<16,2> activation_3_default_t;
typedef ap_fixed<16,2> activation_3table_t;
typedef nnet::array<ap_fixed<16,2>, 32*1> layer17_t;
typedef nnet::array<ap_fixed<16,2>, 32*1> layer44_t;
typedef nnet::array<ap_fixed<16,2>, 64*1> layer18_t;
typedef ap_fixed<16,2> conv_4_weight_t;
typedef ap_fixed<16,2> conv_4_bias_t;
typedef ap_fixed<16,2> activation_4_default_t;
typedef ap_fixed<16,2> activation_4table_t;
typedef nnet::array<ap_fixed<16,2>, 64*1> layer21_t;
typedef nnet::array<ap_fixed<16,2>, 64*1> layer46_t;
typedef nnet::array<ap_fixed<16,2>, 32*1> layer22_t;
typedef ap_fixed<16,2> convtr_1_weight_t;
typedef ap_fixed<16,2> convtr_1_bias_t;
typedef nnet::array<ap_fixed<16,2>, 32*1> layer24_t;
typedef ap_fixed<16,2> batch_normalization_5_scale_t;
typedef ap_fixed<16,2> batch_normalization_5_bias_t;
typedef ap_fixed<16,2> activation_5_default_t;
typedef ap_fixed<16,2> activation_5table_t;
typedef nnet::array<ap_fixed<16,2>, 32*1> layer25_t;
typedef nnet::array<ap_fixed<16,2>, 32*1> layer47_t;
typedef nnet::array<ap_fixed<16,2>, 16*1> layer26_t;
typedef ap_fixed<16,2> convtr_2_weight_t;
typedef ap_fixed<16,2> convtr_2_bias_t;
typedef nnet::array<ap_fixed<16,2>, 16*1> layer28_t;
typedef ap_fixed<16,2> batch_normalization_6_scale_t;
typedef ap_fixed<16,2> batch_normalization_6_bias_t;
typedef ap_fixed<16,2> activation_6_default_t;
typedef ap_fixed<16,2> activation_6table_t;
typedef nnet::array<ap_fixed<16,2>, 16*1> layer29_t;
typedef nnet::array<ap_fixed<16,2>, 16*1> layer48_t;
typedef nnet::array<ap_fixed<16,2>, 8*1> layer30_t;
typedef ap_fixed<16,2> convtr_3_weight_t;
typedef ap_fixed<16,2> convtr_3_bias_t;
typedef nnet::array<ap_fixed<16,2>, 8*1> layer32_t;
typedef ap_fixed<16,2> batch_normalization_7_scale_t;
typedef ap_fixed<16,2> batch_normalization_7_bias_t;
typedef ap_fixed<16,2> activation_7_default_t;
typedef ap_fixed<16,2> activation_7table_t;
typedef nnet::array<ap_fixed<16,2>, 8*1> layer33_t;
typedef nnet::array<ap_fixed<16,2>, 8*1> layer49_t;
typedef nnet::array<ap_fixed<16,2>, 21*1> layer34_t;
typedef ap_fixed<16,2> convtr_4_weight_t;
typedef ap_fixed<16,2> convtr_4_bias_t;
typedef nnet::array<ap_fixed<16,2>, 21*1> layer36_t;
typedef ap_fixed<16,2> batch_normalization_8_scale_t;
typedef ap_fixed<16,2> batch_normalization_8_bias_t;
typedef ap_fixed<16,2> activation_8_default_t;
typedef ap_fixed<16,2> activation_8table_t;
typedef nnet::array<ap_fixed<16,2>, 21*1> layer37_t;
typedef nnet::array<ap_fixed<16,2>, 21*1> layer45_t;
typedef nnet::array<ap_fixed<16,2>, 1*1> result_t;
typedef ap_fixed<16,2> output_conv_weight_t;
typedef ap_fixed<16,2> output_conv_bias_t;

#endif
