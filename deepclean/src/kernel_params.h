#include "ap_fixed.h"
#include "defines.h"


//===============
//Input
//===============

//Input has 21 channels with each channel 8192
#define INPUT_STREAM_LEN  8192

//===============
//Output
//=============== 
#define OUT_STREAM_LEN 256    

typedef ap_uint<512>    bigdata_t;
