#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 100000000  // Tamanho do vetor (memory-bound)
#define ITER 10000000 // Iterações para cálculo de PI (compute-bound)

// Função memory-bound: Soma de vetores
void memory_bound(int num_threads) {
    double *A = (double *)malloc(N * sizeof(double));
    double *B = (double *)malloc(N * sizeof(double));
    double *C = (double *)malloc(N * sizeof(double));
    
    // Inicializa os vetores
    for (int i = 0; i < N; i++) {
        A[i] = i * 1.0;
        B[i] = (N - i) * 1.0;
    }
    
    double start = omp_get_wtime();
    
    #pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
    }
    
    double end = omp_get_wtime();
    printf("Memory-bound (%d threads): %.6f seconds\n", num_threads, end - start);
    
    free(A); free(B); free(C);
}

// Função compute-bound: Aproximação de Pi com a série de Leibniz
double compute_bound(int num_threads) {
    double pi = 0.0;
    
    double start = omp_get_wtime();
    
    #pragma omp parallel for reduction(+:pi) num_threads(num_threads)
    for (int i = 0; i < ITER; i++) {
        double termo = pow(-1, i) / (2 * i + 1);
        pi += termo;
    }
    
    double end = omp_get_wtime();
    printf("Compute-bound (%d threads): %.6f seconds\n", num_threads, end - start);
    
    return pi * 4;
}

int main() {
    int thread_counts[] = {1, 2, 4, 8, 16}; // Testando diferentes números de threads
    
    for (int i = 0; i < 5; i++) {
        int threads = thread_counts[i];
        memory_bound(threads);
        double pi_aprox = compute_bound(threads);
        printf("Pi aproximado (%d threads): %.15f\n", threads, pi_aprox);
        printf("-----------------------------------\n");
    }
    
    return 0;
}