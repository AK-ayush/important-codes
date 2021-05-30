#include <cuda_runtime.h>
#include <stdio.h>

#define CHECK(call)                                                         \
{                                                                           \
    const cudaError_t error = call;                                         \    
    if (error != cudaSuccess){                                              \
        printf("Error: %s:%d, ", __FILE__, __LINE__);                       \        
        printf("code:%d, reason: %s\n", error, cudaGetErrorString(error));  \
        exit(-10 * error);                                                            \
    }                                                                       \
}                                                                           \

void checkResult(float *hostRef, float *gpuRef, const int N){
    double epsilon = 1.0E-8;
    bool match = true;

    for(int i = 0; i < N; i++){
        if(abs(hostRef[i] - gpuRef[i]) > epsilon) {
            match = false;
            printf("Arrays do not match!\n");
            printf("host %5.2f gpu %5.2f at current %d\n", hostRef[i], gpuRef[i], i);
            break;
        }
    }
    if(match) printf("Arrays match\n");
}

void initialData(float *ip, int size){
    // generate different seed for random number
    time_t t;
    srand((unsigned) time(&t));

    for(int i = 0; i < size; i++){
        ip[i] = (float)(rand() & 0xFF) / 10.0f;
    }
}

void sumArraysOnHost(float *A, float *B, float *C, const int N){
    for(int i = 0; i < N; i++){
        C[i] = A[i] + B[i];
    }
}

__global__ sumArraysOnGPU(float *A, float *B, float *C, const int N){
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    if (i < N){
        C[i] = A[i] + B[i];
    } 
}

int main(int argc, char **argv) {
    printf("%s Starting...\n", argv[0]);

    
    int dev = 0;
    // get device properties
    cudaDeviceProp deviceProp;
    CHECK(cudaGetDeviceProperties(&deviceProp, dev));
    printf("using device %d: %s\n", dev, deviceProp.name);

    // set up device
    CHECK(cudaSetDevice(dev));

    // set up data size of vectors
    int nElem = 1<<24;  
    printf("Vector size %d\n", nElem);

    // malloc host memory
    size_t nBytes = nElem * sizeof(float);

    float *h_A, *h_B, *hostRef, *gpuRef;

    h_A     = (float *)malloc(nBytes);
    h_B     = (float *)malloc(nBytes);
    hostRef = (float *)malloc(nBytes);
    gpuRef  = (float *)malloc(nBytes);

    // initialize data on host side
    initialData(h_A, nElem);
    initialData(h_B, nElem);

    // initializing with 0    
    memset(hostRef, 0, nElem);
    memset(gpuRef, 0, nElem);

    // malloc device global memory
    float *d_A, *d_B, *d_C;
    cudaMalloc((void**)&d_A, nBytes);
    cudaMalloc((void**)&d_B, nBytes);
    cudaMalloc((void**)&d_C, nBytes);

    // transfer data from host to devie memory
    cudaMemcpy(d_A, h_A, nBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, nBytes, cudaMemcpyHostToDevice);

    // invoke kernel at the host side
    dim3 block (256);
    dim3 grid  ((nElem + block.x - 1)/block.x);

    sumArraysOnGPU <<< grid, block >>> (d_A, d_B, d_C, N);
    printf("Execution Configuration <<< %d, %d >>> \n", grid.x, block.x);

    // copy kernel result back to host side
    cudaMemcpy(gpuRef, d_A, nBytes, cudaMemcpyDeviceToHost);

    // add vectors on host to compare the result
    sumArraysOnHost(h_A, h_B, hostRef, nElem);
    
    // check results
    checkResult(hostRef, gpuRef, nElem);
    
    // free device gloabl memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    // free host memory
    free(h_A);
    free(h_B);
    free(hostRef);
    free(gpuRef);
     
    return(0); 
}


/* Summing Matrices with a 2D Grid and 2D Blocks
 // Launch Configurations

dim3 block(32, 32);
dim3 grid((nCols + block.x - 1)/block.x, nRows + block.y - 1)/block.y);
*/
__global__ void sumMatrixOnGPU2D(float *MatA, float *MatB, float *MatC, int nRows, int nCols){
    unsigned int ix = threadIdx.x + blockDim.x * blockIdx.x;
    unsigned int iy = threadIdx.y + blockDim.y * blockIdx.y;
    unsigned int idx = iy*nCols + ix;

    if(ix < nCols && iy < nRows){
        MatC[idx] = MatA[idx] + MatB[idx];
    }
}


/* Summing Matrices with a 1D Grid and 1D Blocks
// Launch Configurations

dim3 block(32,1);
dim3 grid((nCols + block.x - 1)/block.x, 1);
*/

__global__ void sumMatrixOnGPU1D(float *MatA, float *MatB, float *MatC, int nRows, int nCols){
    unsigned int ix = threadIdx.x + blockDim.x * blockIdx.x;
    if(ix < nCols){
        for( int iy = 0; iy < nRows; iy++) {
            unsigned int idx = iy*nCols + ix;
            MatC[idx] = MatA[idx] + MatB[idx];
        }
    }
}


/* Summing Matrices with a 2D Grid and 1D Blocks
// Launch Configuration 

dim3 block(32);
dim3 grid((nCols + block.x -1) /block.x, nRows);
*/

__global__ void sumMatrixOnGPUMix(float *MatA, float *MatB, float *MatC, int nRows, int nCols){
    unsigned int ix = threadIdx.x + blockDim.x * blockIdx.x;
    unsigned int iy = blockIdx.y;
    unsigned int idx = iy * nCols + ix;
    if (ix < nCols){
        MatC[idx] = MatA[idx] + MatB[idx];
    }
}


/*

$ nvcc sumArraysOnGPU.cu  -o addvector
$ ./addvector

** Timing with CPU Timer **
#include <sys/time.h>

double iStart, iElaps;
iStart = cpuSecond();
// some operation or function call
iElaps = cpuSecond() - iStart();

printf("Time Elapsed %f\n", iElaps);

** Timing with `nvprof`
$ nvprof --help
$ nvprof ./addvector

*/