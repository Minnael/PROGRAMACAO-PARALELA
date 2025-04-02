#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

int main() {
    const size_t N = 100000000; // 100 milhões de elementos
    vector<double> a(N, 1.0), b(N, 2.0), c(N, 0.0);

    cout << "Threads, Tempo (ms)" << endl;
    
    for (int num_threads = 1; num_threads <= 16; num_threads *= 2) {
        omp_set_num_threads(num_threads);
        auto start = high_resolution_clock::now();
        
        #pragma omp parallel for
        for (size_t i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }
        
        auto end = high_resolution_clock::now();
        double duration = duration_cast<milliseconds>(end - start).count();
        
        cout << num_threads << ", " << duration << endl;
    }
    return 0;
}