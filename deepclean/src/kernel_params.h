#include "ap_fixed.h"
#include "defines.h"


//===============
//Input
//===============

//Input has 21 channels with each channel 8192
#define INPUT_STREAM_LEN  (N_INPUT_1_1*N_INPUT_2_1)

//===============
//Output
//===============
#define OUT_STREAM_LEN N_OUTPUTS_38  

typedef ap_fixed<16,6> bigdata_t;