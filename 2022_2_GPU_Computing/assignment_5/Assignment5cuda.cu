%%writefile Assignment5cuda.cu

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <chrono>         //header to calculate time
#include <iostream>

#define GRIDSIZE 16*1024 //16K
#define BLOCKSIZE 1024   //1K
#define TOTALSIZE (GRIDSIZE * BLOCKSIZE)

void genData(float* ptr, unsigned int size) { //put values
    while (size--) {
        *ptr++ = (float)(rand() % 1000) / 1000.0F;
    }
}

void adjDiff(float* dst, const float* src, unsigned int size) {  //function to calculate delay
    for (int i = 1; i < size; i++) {
        dst[i] = src[i] - src[i - 1];
    }
}

__global__ void adjDiff2(float* result, const float* input) {  //function to calculate delay
    unsigned int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i > 0) {
        float x_i = input[i];
        float x_i_m1 = input[i - 1];
        result[i] = x_i - x_i_m1;
    }
}

__global__ void adjDiff3(float* result, float* input) {  //function to calculate delay
    __shared__ float s_data[BLOCKSIZE];
    unsigned int tx = threadIdx.x;
    unsigned int i = blockIdx.x * blockDim.x + threadIdx.x;
    s_data[tx] = input[i];
    __syncthreads();
    if (tx > 0) {
        result[i] = s_data[tx] - s_data[tx - 1];
    }
    else if (i > 0) {
        result[i] = s_data[tx] - input[i - 1];
    }
}

int main(void) {
    ////////////////////////////5-1(HOST version)
    float* pSource = NULL;   //variable array to genData & adjDiff function
    float* pResult = NULL;
    int i;

    pSource = (float*)malloc(TOTALSIZE * sizeof(float)); //put space to save
    pResult = (float*)malloc(TOTALSIZE * sizeof(float));

    genData(pSource, TOTALSIZE);  //generate input source data
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now(); //take start time
    pResult[0] = 0.0F;                                                              //exceptional case for i=0
    adjDiff(pResult, pSource, TOTALSIZE);
    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();   //take end time
    std::chrono::nanoseconds duration_micro = end - start;
    printf("elapsed time = %lld usec \n", duration_micro / 1000);
    //print sample cases
    i = 1;
    printf("i=%d: %f=%f-%f\n", i, pResult[i], pSource[i], pSource[i - 1]);
    i = TOTALSIZE - 1;
    printf("i=%d: %f=%f-%f\n", i, pResult[i], pSource[i], pSource[i - 1]);
    i = TOTALSIZE / 2;
    printf("i=%d: %f=%f-%f\n\n", i, pResult[i], pSource[i], pSource[i - 1]);
    //free the memory
    free(pSource);
    free(pResult);
    //////////////////////////////////////5-2(CUDA global memory version)
    float* pSource2 = NULL;   //variable array to genData & adjDiff function
    float* pResult2 = NULL;
    int i2;

    pSource2 = (float*)malloc(TOTALSIZE * sizeof(float)); //put space to save
    pResult2 = (float*)malloc(TOTALSIZE * sizeof(float));

    genData(pSource2, TOTALSIZE);  //generate input source data

    float* pSourceDev2 = NULL;
    float* pResultDev2 = NULL;

    pResult2[0] = 0.0F;                                                              //exceptional case for i=0

    cudaMalloc((void**)&pSourceDev2, TOTALSIZE * sizeof(float));
    cudaMalloc((void**)&pResultDev2, TOTALSIZE * sizeof(float));

    //CUDA launch the kernel adjDiff
    cudaMemcpy(pSourceDev2, pSource2, TOTALSIZE * sizeof(float), cudaMemcpyHostToDevice);
    std::chrono::system_clock::time_point start2 = std::chrono::system_clock::now(); //take start time

    dim3 dimGrid2(GRIDSIZE, 1, 1);
    dim3 dimBlock2(BLOCKSIZE, 1, 1);
    adjDiff2 << <dimGrid2, dimBlock2 >> > (pResultDev2, pSourceDev2);

    std::chrono::system_clock::time_point end2 = std::chrono::system_clock::now();   //take end time
    cudaMemcpy(pResult2, pResultDev2, TOTALSIZE * sizeof(float), cudaMemcpyDeviceToHost);
    std::chrono::nanoseconds duration_micro2 = end2 - start2;
    printf("elapsed time = %lld usec \n", duration_micro2 / 1000);
    //print sample cases
    i2 = 1;
    printf("i=%d: %f=%f-%f\n", i2, pResult2[i2], pSource2[i2], pSource2[i2 - 1]);
    i2 = TOTALSIZE - 1;
    printf("i=%d: %f=%f-%f\n", i2, pResult2[i2], pSource2[i2], pSource2[i2 - 1]);
    i2 = TOTALSIZE / 2;
    printf("i=%d: %f=%f-%f\n\n", i2, pResult2[i2], pSource2[i2], pSource2[i2 - 1]);
    //free the memory
    free(pSource2);
    free(pResult2);
    cudaFree(pSourceDev2);
    cudaFree(pResultDev2);
    cudaDeviceSynchronize();
    /////////////////////5-3(CUDA Shared memory version)
    float* pSource3 = NULL;   //variable array to genData & adjDiff function
    float* pResult3 = NULL;
    int i3;

    pSource3 = (float*)malloc(TOTALSIZE * sizeof(float)); //put space to save
    pResult3 = (float*)malloc(TOTALSIZE * sizeof(float));

    genData(pSource3, TOTALSIZE);  //generate input source data

    float* pSourceDev3 = NULL;
    float* pResultDev3 = NULL;

    pResult3[0] = 0.0F;                                                              //exceptional case for i=0

    cudaMalloc((void**)&pSourceDev3, TOTALSIZE * sizeof(float));
    cudaMalloc((void**)&pResultDev3, TOTALSIZE * sizeof(float));

    //CUDA launch the kernel adjDiff
    cudaMemcpy(pSourceDev3, pSource3, TOTALSIZE * sizeof(float), cudaMemcpyHostToDevice);
    std::chrono::system_clock::time_point start3 = std::chrono::system_clock::now(); //take start time

    dim3 dimGrid3(GRIDSIZE, 1, 1);
    dim3 dimBlock3(BLOCKSIZE, 1, 1);
    adjDiff3 << <dimGrid3, dimBlock3 >> > (pResultDev3, pSourceDev3);

    std::chrono::system_clock::time_point end3 = std::chrono::system_clock::now();   //take end time
    cudaMemcpy(pResult3, pResultDev3, TOTALSIZE * sizeof(float), cudaMemcpyDeviceToHost);
    std::chrono::nanoseconds duration_micro3 = end3 - start3;
    printf("elapsed time = %lld usec \n", duration_micro3 / 1000);
    //print sample cases
    i3 = 1;
    printf("i=%d: %f=%f-%f\n", i3, pResult3[i3], pSource3[i3], pSource3[i3 - 1]);
    i3 = TOTALSIZE - 1;
    printf("i=%d: %f=%f-%f\n", i3, pResult3[i3], pSource3[i3], pSource3[i3 - 1]);
    i3 = TOTALSIZE / 2;
    printf("i=%d: %f=%f-%f\n", i3, pResult3[i3], pSource3[i3], pSource3[i3 - 1]);
    //free the memory
    free(pSource3);
    free(pResult3);
    cudaFree(pSourceDev3);
    cudaFree(pResultDev3);
    cudaDeviceSynchronize();
    return 0;
}