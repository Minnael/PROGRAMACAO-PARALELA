#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    int N = 100000000;
    int nthreads;
    double start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        nthreads = omp_get_num_threads();
    }

    int *counts = calloc(nthreads, sizeof(int));

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        unsigned int seed = time(NULL) ^ tid;

        #pragma omp for
        for (int i = 0; i < N; i++) {
            float x = (float)rand() / RAND_MAX;
            float y = (float)rand() / RAND_MAX;
            if (x * x + y * y <= 1.0f)
                counts[tid]++;
        }
    }

    int total_in = 0;
    for (int i = 0; i < nthreads; i++)
        total_in += counts[i];

    double pi = 4.0 * total_in / N;
    printf("PI = %f\n", pi);
    printf("Tempo: %f segundos\n", omp_get_wtime() - start);
    free(counts);
    return 0;
}
