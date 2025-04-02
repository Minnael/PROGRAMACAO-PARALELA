#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Função para calcular pi usando a fórmula de Machin
double calcularPi(int iteracoes) {
    double pi = 0.0;
    for (int i = 0; i < iteracoes; ++i) {
        pi += (pow(-1, i) / (2 * i + 1)) * pow(5, -2 * i - 1) * 16;
        pi -= (pow(-1, i) / (2 * i + 1)) * pow(239, -2 * i - 1) * 4;
    }
    return pi;
}

int main() {
    const double PI_REAL = M_PI; // Valor real de pi
    int iteracoes[] = {10, 100, 1000, 10000, 100000, 1000000};

    cout << fixed << setprecision(20); // Configura precisão máxima disponível

    cout << "Iterações | Aproximação de PI         | Erro Absoluto            | Tempo de Execução (ms)\n";
    cout << "-------------------------------------------------------------------------------\n";

    for (int iter : iteracoes) {
        auto inicio = high_resolution_clock::now();
        double pi_aproximado = calcularPi(iter);
        auto fim = high_resolution_clock::now();

        auto duracao = duration_cast<milliseconds>(fim - inicio);
        double erro = fabs(PI_REAL - pi_aproximado);

        cout << iter << " | " << pi_aproximado << " | " << erro << " | " << duracao.count() << " ms\n";
    }

    return 0;
}
