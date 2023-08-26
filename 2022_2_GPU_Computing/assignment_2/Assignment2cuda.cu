%% writefile Assignment2cuda.cu
#include <stdlib.h>
#include <stdio.h>

__global__ void addKernel(int* d, const int* a, const int* b, const int* c) {
    int i = threadIdx.x;
    d[i] = a[i] + b[i] + c[i];
}

int main() {

    const int SIZE = 5;
    int a[SIZE] = { 0 };
    int b[SIZE] = { 0 };
    int c[SIZE] = { 0 };
    for (int i = 0; i < 5; i++) {
        a[i] = rand() / 4;
        b[i] = rand() / 4;
        c[i] = rand() / 4;
    }
    int d[SIZE] = { 0 };

    int* dev_a = 0;
    int* dev_b = 0;
    int* dev_c = 0;
    int* dev_d = 0;

    cudaMalloc((int**)&dev_a, SIZE * sizeof(int));
    cudaMalloc((int**)&dev_b, SIZE * sizeof(int));
    cudaMalloc((int**)&dev_c, SIZE * sizeof(int));
    cudaMalloc((int**)&dev_d, SIZE * sizeof(int));

    cudaMemcpy(dev_a, a, sizeof(int) * SIZE, cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, sizeof(int) * SIZE, cudaMemcpyHostToDevice);
    cudaMemcpy(dev_c, c, sizeof(int) * SIZE, cudaMemcpyHostToDevice);

    addKernel << < 1, SIZE >> > (dev_d, dev_a, dev_b, dev_c); // launch test function
    cudaMemcpy(d, dev_d, sizeof(int) * SIZE, cudaMemcpyDeviceToHost);

    for (int i = 0; i < SIZE; i++)
        printf("{%d} + {%d} + {%d} = {%d}\n", a[i], b[i], c[i], d[i]);    // print the results

    cudaFree(dev_a);    // free the device memory spaces 
    cudaFree(dev_b);    // free the device memory spaces 
    cudaFree(dev_c);    // free the device memory spaces 
    cudaFree(dev_d);    // free the device memory spaces 
    return 0;
}