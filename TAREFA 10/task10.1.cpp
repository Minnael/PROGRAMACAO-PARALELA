#include <iostream>
#include <random>
#include <omp.h>
#include <ctime>

using namespace std;

int main() {
    int N = 100000000;
    int total_in = 0;
    double start = omp_get_wtime();

    #pragma omp parallel
    {
        int in = 0;
        mt19937 rng(time(nullptr) + omp_get_thread_num());
        uniform_real_distribution<float> dist(0.0f, 1.0f);

        #pragma omp for
        for (int i = 0; i < N; i++) {
            float x = dist(rng);
            float y = dist(rng);
            if (x * x + y * y <= 1.0f)
                in++;
        }

        #pragma omp critical
        {
            total_in += in;
        }
    }

    double pi = 4.0 * total_in / N;
    double end = omp_get_wtime();

    cout << "[critical + <random>] PI = " << pi << endl;
    cout << "[critical + <random>] Tempo: " << end - start << " segundos" << endl;
    return 0;
}
