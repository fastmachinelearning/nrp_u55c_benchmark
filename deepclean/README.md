# DeepClean on NRP U55Cs

Setup tools, licenses, check connection to FPGA card

Check out packages
```bash
# check out VitisAccel project
git clone https://github.com/fastmachinelearning/nrp_u55c_benchmark
```
Compile VitisAccel project
```bash
cd nrp_u55c_benchmark/deepclean
LD_PRELOAD=/lib/x86_64-linux-gnu/libudev.so.1 make all TARGET=hw  DEVICE=xilinx_u55c_gen3x16_xdma_3_202210_1
```

Run project
```bash
./host build_dir.hw.xilinx_u55c_gen3x16_xdma_3_202210_1/alveo_hls4ml.xclbin 1000
```
