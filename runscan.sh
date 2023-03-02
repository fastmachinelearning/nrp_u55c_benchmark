#!/bin/bash

NEVENTS=10000
PREFIX=scanlog_hbm

for NC in 1 2 3; do
#for NC in 4; do
#for NC in 1 2 3 4; do
    sed -i "s/define NUM_CU .*$/define NUM_CU ${NC}/g" src/host.cpp
    for NB in 1 2 4 8; do
    #for NB in 1; do
        sed -i "s/define NBUFFER .*$/define NBUFFER ${NB}/g" src/host.cpp
	echo "    NEVENTS = ${NEVENTS}" > ${PREFIX}/data_nevt${NEVENTS}_ncu${NC}_nbuf${NB}.txt
	echo "    NUM_CU = ${NC}" >> ${PREFIX}/data_nevt${NEVENTS}_ncu${NC}_nbuf${NB}.txt
	echo "    NBUFFER = ${NB}" >> ${PREFIX}/data_nevt${NEVENTS}_ncu${NC}_nbuf${NB}.txt
        LD_PRELOAD=/lib/x86_64-linux-gnu/libudev.so.1 make all TARGET=hw  DEVICE=xilinx_u55c_gen3x16_xdma_3_202210_1
        ./host build_dir.hw.xilinx_u55c_gen3x16_xdma_3_202210_1/alveo_hls4ml.xclbin ${NEVENTS} >> ${PREFIX}/data_nevt${NEVENTS}_ncu${NC}_nbuf${NB}.txt
    done
done

cat ${PREFIX}/* > scan_u55c_hbm.dat
