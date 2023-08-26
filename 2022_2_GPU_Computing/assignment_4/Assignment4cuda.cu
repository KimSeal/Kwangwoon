%% writefile Assignment4cuda.cu

#include <stdio.h>
#include <stdlib.h>
#include <iostream>



__global__ void mulKernel(int* c, const int* a, const int* b, const int WIDTH) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    int sum = 0;
    for (int i = 0; i < WIDTH; i++) {
        sum += a[y * WIDTH + i] * b[i * WIDTH + x];
    }
    c[WIDTH * y + x] = sum;

}

int main() {
    const int WIDTH = 16;
    const int TILE_WIDTH = 8;

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

    dim3 dimGrid(WIDTH / TILE_WIDTH, WIDTH / TILE_WIDTH, 1);
    dim3 DimBlock(TILE_WIDTH, TILE_WIDTH, 1);

    mulKernel << < dimGrid, DimBlock >> > (dev_c, dev_a, dev_b, WIDTH); // launch test function
    cudaMemcpy(c, dev_c, sizeof(int) * WIDTH * WIDTH, cudaMemcpyDeviceToHost);

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("[%6d] ", a[i][j]);    // print the results
            if (j % TILE_WIDTH == (TILE_WIDTH - 1)) {
                printf("   ");
            }
        }
        printf(" || ");
        for (int j = 0; j < WIDTH; j++) {
            printf("[%6d] ", b[i][j]);    // print the results
            if (j % TILE_WIDTH == (TILE_WIDTH - 1)) {
                printf("   ");
            }
        }
        printf(" || ");
        for (int j = 0; j < WIDTH; j++) {
            printf("[%6d] ", c[i][j]);    // print the results
            if (j % TILE_WIDTH == (TILE_WIDTH - 1)) {
                printf("   ");
            }
        }
        printf("\n");
        if (i % TILE_WIDTH == (TILE_WIDTH - 1)) {
            printf("\n");
        }
    }
    cudaFree(dev_a);    // free the device memory spaces 
    cudaFree(dev_b);    // free the device memory spaces 
    cudaFree(dev_c);    // free the device memory spaces 
    return 0;
}