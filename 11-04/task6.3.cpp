#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
#include <omp.h>

using namespace std;

int main() {
    const int totalPontos = 1000000000;
    int hit = 0;

    #pragma omp parallel default(none) shared(totalPontos, hit)
    {
        // Criador de números aleatórios por thread
        std::mt19937 rng(time(nullptr) + omp_get_thread_num());
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        int local_hit = 0;

        #pragma omp for
        for (int i = 0; i < totalPontos; ++i) {
            double x = dist(rng);
            double y = dist(rng);

            if (x * x + y * y <= 1.0) {
                ++local_hit;
            }
        }

        #pragma omp atomic
        hit += local_hit;
    }

    double pi = 4.0 * hit / totalPontos;

    cout << fixed << setprecision(9);
    cout << "Estimativa de pi: " << pi << endl;

    return 0;
}
