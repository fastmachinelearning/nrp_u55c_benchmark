/**********
Copyright (c) 2018, Xilinx, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**********/

/*******************************************************************************
Description:
    HLS pragmas can be used to optimize the design : improve throughput, reduce latency and 
    device resource utilization of the resulting RTL code
    This is a wrapper to be used with an hls4ml project to enable proper handling by SDAccel
*******************************************************************************/

#define PROJ_HDR <MYPROJ.h>

#include PROJ_HDR
#include "kernel_params.h"



// SDAccel kernel must have one and only one s_axilite interface which will be used by host application to configure the kernel.
// Here bundle control is defined which is s_axilite interface and associated with all the arguments (in and out),
// control interface must also be associated with "return".
// All the global memory access arguments must be associated to one m_axi(AXI Master Interface). Here all two arguments(in, out) are 
// associated to bundle gmem which means that a AXI master interface named "gmem" will be created in Kernel and all these variables will be 
// accessing global memory through this interface.
// Multiple interfaces can also be created based on the requirements. For example when multiple memory accessing arguments need access to
// global memory simultaneously, user can create multiple master interfaces and can connect to different arguments.
extern "C" {
    void alveo_hls4ml(
     const bigdata_t *in, // Read-Only Vector
     bigdata_t *out       // Output Result
    )
{
 
    #pragma HLS INTERFACE m_axi port=in  offset=slave bundle=gmem0
    #pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem1
    #pragma HLS INTERFACE s_axilite port=in   bundle=control
    #pragma HLS INTERFACE s_axilite port=out  bundle=control
    #pragma HLS INTERFACE s_axilite port=return bundle=control
    #pragma HLS DATAFLOW

        
    bigdata_t in_buff[INPUT_STREAM_LEN];
    bigdata_t out_buf[OUT_STREAM_LEN];

    hls::stream<input_t> in_stream;
    hls::stream<result_t> out_stream;
    //these will get partitioned properly in the hls4ml code

    #pragma HLS STREAM   variable=in_stream  depth=8192
    #pragma HLS STREAM   variable=out_stream depth=8192

    //getting data from DRAM
    for (int i = 0; i < INPUT_STREAM_LEN; i++) {
        in_buff[i] = in[i];
    }

    //=============================================
    //input
    //=============================================
        
    for(unsigned i = 0; i < INPUT_STREAM_LEN / input_t::size; ++i) {
        input_t ctype;
        for(unsigned j = 0; j < input_t::size; j++) {
            bigdata_t in_val = in[i * input_t::size + j];
            ctype[j] = typename input_t::value_type(in_val);
        }
        in_stream.write(ctype);
    }
    hls4ml: MYPROJ(in_stream,out_stream);
      
    //=============================================
    //output
    //=============================================
    for(unsigned i1 = 0; i1 < OUT_STREAM_LEN / result_t::size; ++i1) {
        result_t ctype = out_stream.read();
        out_buf[i1]=bigdata_t(ctype[0]);
        for(unsigned j1 = 0; j1 < result_t::size; j1++) {
            out_buf[i1 * result_t::size + j1] = ctype[j1];
        }
    }
        
   for(int i2 = 0; i2 < OUT_STREAM_LEN; i2++) {
       out[i2]= out_buf[i2];
    }
}
}


    



