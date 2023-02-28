//
//    rfnoc-hls-neuralnet: Vivado HLS code for neural-net building blocks
//
//    Copyright (C) 2017 EJ Kreinar
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include <iostream>

#include "myproject.h"
#include "parameters.h"

void myproject(
    hls::stream<input_t> &input_conv_input,
    hls::stream<result_t> &layer38_out

) {

    #pragma HLS INTERFACE axis port=input_conv_input,layer38_out 
    #pragma HLS DATAFLOW


#ifndef __SYNTHESIS__
    static bool loaded_weights = false;
    if (!loaded_weights) {
        //hls-fpga-machine-learning insert load weights
        nnet::load_weights_from_txt<input_conv_weight_t, 3087>(w2, "w2.txt");
        nnet::load_weights_from_txt<input_conv_bias_t, 21>(b2, "b2.txt");
        nnet::load_weights_from_txt<conv_1_weight_t, 1176>(w6, "w6.txt");
        nnet::load_weights_from_txt<conv_1_bias_t, 8>(b6, "b6.txt");
        nnet::load_weights_from_txt<conv_2_weight_t, 896>(w10, "w10.txt");
        nnet::load_weights_from_txt<conv_2_bias_t, 16>(b10, "b10.txt");
        nnet::load_weights_from_txt<conv_3_weight_t, 3584>(w14, "w14.txt");
        nnet::load_weights_from_txt<conv_3_bias_t, 32>(b14, "b14.txt");
        nnet::load_weights_from_txt<conv_4_weight_t, 14336>(w18, "w18.txt");
        nnet::load_weights_from_txt<conv_4_bias_t, 64>(b18, "b18.txt");
        nnet::load_weights_from_txt<convtr_1_weight_t, 2, 8192>(w22, "w22.txt");
        nnet::load_weights_from_txt<convtr_1_bias_t, 32>(b22, "b22.txt");
        nnet::load_weights_from_txt<batch_normalization_5_scale_t, 32>(s24, "s24.txt");
        nnet::load_weights_from_txt<batch_normalization_5_bias_t, 32>(b24, "b24.txt");
        nnet::load_weights_from_txt<convtr_2_weight_t, 2, 2048>(w26, "w26.txt");
        nnet::load_weights_from_txt<convtr_2_bias_t, 16>(b26, "b26.txt");
        nnet::load_weights_from_txt<batch_normalization_6_scale_t, 16>(s28, "s28.txt");
        nnet::load_weights_from_txt<batch_normalization_6_bias_t, 16>(b28, "b28.txt");
        nnet::load_weights_from_txt<convtr_3_weight_t, 2, 512>(w30, "w30.txt");
        nnet::load_weights_from_txt<convtr_3_bias_t, 8>(b30, "b30.txt");
        nnet::load_weights_from_txt<batch_normalization_7_scale_t, 8>(s32, "s32.txt");
        nnet::load_weights_from_txt<batch_normalization_7_bias_t, 8>(b32, "b32.txt");
        nnet::load_weights_from_txt<convtr_4_weight_t, 2, 672>(w34, "w34.txt");
        nnet::load_weights_from_txt<convtr_4_bias_t, 21>(b34, "b34.txt");
        nnet::load_weights_from_txt<batch_normalization_8_scale_t, 21>(s36, "s36.txt");
        nnet::load_weights_from_txt<batch_normalization_8_bias_t, 21>(b36, "b36.txt");
        nnet::load_weights_from_txt<output_conv_weight_t, 147>(w38, "w38.txt");
        nnet::load_weights_from_txt<output_conv_bias_t, 1>(b38, "b38.txt");
        loaded_weights = true;
    }
#endif

    // ****************************************
    // NETWORK INSTANTIATION
    // ****************************************

    //hls-fpga-machine-learning insert layers

    hls::stream<layer40_t> layer40_out("layer40_out");
    #pragma HLS STREAM variable=layer40_out depth=8198
    nnet::zeropad1d_cl<input_t, layer40_t, config40>(input_conv_input, layer40_out); // zp1d_input_conv

    hls::stream<layer2_t> layer2_out("layer2_out");
    #pragma HLS STREAM variable=layer2_out depth=8192
    nnet::conv_1d_cl<layer40_t, layer2_t, config2>(layer40_out, layer2_out, w2, b2); // input_conv

    hls::stream<layer5_t> layer5_out("layer5_out");
    #pragma HLS STREAM variable=layer5_out depth=8192
    nnet::tanh<layer2_t, layer5_t, tanh_config5>(layer2_out, layer5_out); // activation

    hls::stream<layer41_t> layer41_out("layer41_out");
    #pragma HLS STREAM variable=layer41_out depth=8197
    nnet::zeropad1d_cl<layer5_t, layer41_t, config41>(layer5_out, layer41_out); // zp1d_conv_1

    hls::stream<layer6_t> layer6_out("layer6_out");
    #pragma HLS STREAM variable=layer6_out depth=4096
    nnet::conv_1d_cl<layer41_t, layer6_t, config6>(layer41_out, layer6_out, w6, b6); // conv_1

    hls::stream<layer9_t> layer9_out("layer9_out");
    #pragma HLS STREAM variable=layer9_out depth=4096
    nnet::tanh<layer6_t, layer9_t, tanh_config9>(layer6_out, layer9_out); // activation_1

    hls::stream<layer42_t> layer42_out("layer42_out");
    #pragma HLS STREAM variable=layer42_out depth=4101
    nnet::zeropad1d_cl<layer9_t, layer42_t, config42>(layer9_out, layer42_out); // zp1d_conv_2

    hls::stream<layer10_t> layer10_out("layer10_out");
    #pragma HLS STREAM variable=layer10_out depth=2048
    nnet::conv_1d_cl<layer42_t, layer10_t, config10>(layer42_out, layer10_out, w10, b10); // conv_2

    hls::stream<layer13_t> layer13_out("layer13_out");
    #pragma HLS STREAM variable=layer13_out depth=2048
    nnet::tanh<layer10_t, layer13_t, tanh_config13>(layer10_out, layer13_out); // activation_2

    hls::stream<layer43_t> layer43_out("layer43_out");
    #pragma HLS STREAM variable=layer43_out depth=2053
    nnet::zeropad1d_cl<layer13_t, layer43_t, config43>(layer13_out, layer43_out); // zp1d_conv_3

    hls::stream<layer14_t> layer14_out("layer14_out");
    #pragma HLS STREAM variable=layer14_out depth=1024
    nnet::conv_1d_cl<layer43_t, layer14_t, config14>(layer43_out, layer14_out, w14, b14); // conv_3

    hls::stream<layer17_t> layer17_out("layer17_out");
    #pragma HLS STREAM variable=layer17_out depth=1024
    nnet::tanh<layer14_t, layer17_t, tanh_config17>(layer14_out, layer17_out); // activation_3

    hls::stream<layer44_t> layer44_out("layer44_out");
    #pragma HLS STREAM variable=layer44_out depth=1029
    nnet::zeropad1d_cl<layer17_t, layer44_t, config44>(layer17_out, layer44_out); // zp1d_conv_4

    hls::stream<layer18_t> layer18_out("layer18_out");
    #pragma HLS STREAM variable=layer18_out depth=512
    nnet::conv_1d_cl<layer44_t, layer18_t, config18>(layer44_out, layer18_out, w18, b18); // conv_4

    hls::stream<layer21_t> layer21_out("layer21_out");
    #pragma HLS STREAM variable=layer21_out depth=512
    nnet::tanh<layer18_t, layer21_t, tanh_config21>(layer18_out, layer21_out); // activation_4

    hls::stream<layer46_t> layer46_out("layer46_out");
    #pragma HLS STREAM variable=layer46_out depth=517
    nnet::zeropad1d_cl<layer21_t, layer46_t, config46>(layer21_out, layer46_out); // zp1d_convtr_1

    hls::stream<layer22_t> layer22_out("layer22_out");
    #pragma HLS STREAM variable=layer22_out depth=1024
    nnet::conv_1d_transpose_cl<layer46_t, layer22_t, config22>(layer46_out, layer22_out, w22, b22); // convtr_1

    hls::stream<layer24_t> layer24_out("layer24_out");
    #pragma HLS STREAM variable=layer24_out depth=1024
    nnet::normalize<layer22_t, layer24_t, config24>(layer22_out, layer24_out, s24, b24); // batch_normalization_5

    hls::stream<layer25_t> layer25_out("layer25_out");
    #pragma HLS STREAM variable=layer25_out depth=1024
    nnet::tanh<layer24_t, layer25_t, tanh_config25>(layer24_out, layer25_out); // activation_5

    hls::stream<layer47_t> layer47_out("layer47_out");
    #pragma HLS STREAM variable=layer47_out depth=1029
    nnet::zeropad1d_cl<layer25_t, layer47_t, config47>(layer25_out, layer47_out); // zp1d_convtr_2

    hls::stream<layer26_t> layer26_out("layer26_out");
    #pragma HLS STREAM variable=layer26_out depth=2048
    nnet::conv_1d_transpose_cl<layer47_t, layer26_t, config26>(layer47_out, layer26_out, w26, b26); // convtr_2

    hls::stream<layer28_t> layer28_out("layer28_out");
    #pragma HLS STREAM variable=layer28_out depth=2048
    nnet::normalize<layer26_t, layer28_t, config28>(layer26_out, layer28_out, s28, b28); // batch_normalization_6

    hls::stream<layer29_t> layer29_out("layer29_out");
    #pragma HLS STREAM variable=layer29_out depth=2048
    nnet::tanh<layer28_t, layer29_t, tanh_config29>(layer28_out, layer29_out); // activation_6

    hls::stream<layer48_t> layer48_out("layer48_out");
    #pragma HLS STREAM variable=layer48_out depth=2053
    nnet::zeropad1d_cl<layer29_t, layer48_t, config48>(layer29_out, layer48_out); // zp1d_convtr_3

    hls::stream<layer30_t> layer30_out("layer30_out");
    #pragma HLS STREAM variable=layer30_out depth=4096
    nnet::conv_1d_transpose_cl<layer48_t, layer30_t, config30>(layer48_out, layer30_out, w30, b30); // convtr_3

    hls::stream<layer32_t> layer32_out("layer32_out");
    #pragma HLS STREAM variable=layer32_out depth=4096
    nnet::normalize<layer30_t, layer32_t, config32>(layer30_out, layer32_out, s32, b32); // batch_normalization_7

    hls::stream<layer33_t> layer33_out("layer33_out");
    #pragma HLS STREAM variable=layer33_out depth=4096
    nnet::tanh<layer32_t, layer33_t, tanh_config33>(layer32_out, layer33_out); // activation_7

    hls::stream<layer49_t> layer49_out("layer49_out");
    #pragma HLS STREAM variable=layer49_out depth=4101
    nnet::zeropad1d_cl<layer33_t, layer49_t, config49>(layer33_out, layer49_out); // zp1d_convtr_4

    hls::stream<layer34_t> layer34_out("layer34_out");
    #pragma HLS STREAM variable=layer34_out depth=8192
    nnet::conv_1d_transpose_cl<layer49_t, layer34_t, config34>(layer49_out, layer34_out, w34, b34); // convtr_4

    hls::stream<layer36_t> layer36_out("layer36_out");
    #pragma HLS STREAM variable=layer36_out depth=8192
    nnet::normalize<layer34_t, layer36_t, config36>(layer34_out, layer36_out, s36, b36); // batch_normalization_8

    hls::stream<layer37_t> layer37_out("layer37_out");
    #pragma HLS STREAM variable=layer37_out depth=8192
    nnet::tanh<layer36_t, layer37_t, tanh_config37>(layer36_out, layer37_out); // activation_8

    hls::stream<layer45_t> layer45_out("layer45_out");
    #pragma HLS STREAM variable=layer45_out depth=8198
    nnet::zeropad1d_cl<layer37_t, layer45_t, config45>(layer37_out, layer45_out); // zp1d_output_conv

    nnet::conv_1d_cl<layer45_t, result_t, config38>(layer45_out, layer38_out, w38, b38); // output_conv

}
