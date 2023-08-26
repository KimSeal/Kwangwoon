%%writefile Assignment3cuda.cu

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define WIDTH 5

__global__ void mulKernel(int* c, const int* a, const int* b) {
    int x = threadIdx.x;
    int y = threadIdx.y;
    int sum = 0;
    for (int i = 0; i < WIDTH; i++) {
        sum += a[y * WIDTH + i] * b[i * WIDTH + x];
    }
    c[WIDTH * y + x] = sum;

}

int main() {

    int a[WIDTH][WIDTH];
    int b[WIDTH][WIDTH];
    int c[WIDTH][WIDTH] = { 0 };
    for (int y = 0; y < WIDTH; y++) {
        for (int x = 0; x < WIDTH; x++) {
            a[y][x] = y * 10 + x;
            b[y][x] = (y * 10 + x);
        }
    }

    int* dev_a = 0;
    int* dev_b = 0;
    int* dev_c = 0;

    cudaMalloc((void**)&dev_a, WIDTH * WIDTH * sizeof(int));
    cudaMalloc((void**)&dev_b, WIDTH * WIDTH * sizeof(int));
    cudaMalloc((void**)&dev_c, WIDTH * WIDTH * sizeof(int));

    cudaMemcpy(dev_a, a, sizeof(int) * WIDTH * WIDTH, cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, sizeof(int) * WIDTH * WIDTH, cudaMemcpyHostToDevice);

    dim3 DimBlock(WIDTH, WIDTH);
    mulKernel << < 1, DimBlock >> > (dev_c, dev_a, dev_b); // launch test function
    cudaMemcpy(c, dev_c, sizeof(int) * WIDTH * WIDTH, cudaMemcpyDeviceToHost);

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("{%d} ", a[i][j]);    // print the results
        }
        for (int j = 0; j < WIDTH; j++) {
            printf("{%d} ", b[i][j]);    // print the results
        }
        for (int j = 0; j < WIDTH; j++) {
            printf("{%d} ", c[i][j]);    // print the results
        }
        printf("\n");
    }
    cudaFree(dev_a);    // free the device memory spaces 
    cudaFree(dev_b);    // free the device memory spaces 
    cudaFree(dev_c);    // free the device memory spaces 
    return 0;
}