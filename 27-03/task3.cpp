#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

#define N 100000000  // Tamanho do vetor (memory-bound)
#define ITER 10000000 // Iterações para cálculo de PI (compute-bound)

using namespace std;

// Função memory-bound: Soma de vetores
void memory_bound(int num_threads) {
    vector<double> A(N), B(N), C(N);
    
    // Inicializa os vetores
    #pragma omp parallel for num_threads(num_threads)
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
    cout << "Memory-bound (" << num_threads << " threads): " << (end - start) << " seconds\n";
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
    cout << "Compute-bound (" << num_threads << " threads): " << (end - start) << " seconds\n";
    
    return pi * 4;
}

int main() {
    vector<int> thread_counts = {1, 2, 4, 8, 16}; // Testando diferentes números de threads
    
    for (int threads : thread_counts) {
        memory_bound(threads);
        double pi_aprox = compute_bound(threads);
        cout << "Pi aproximado (" << threads << " threads): " << pi_aprox << endl;
        cout << "-----------------------------------" << endl;
    }
    
    return 0;
}
