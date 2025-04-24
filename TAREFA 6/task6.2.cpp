#include <iostream>
#include <iomanip>  
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

int main() {
    // Número de pontos a serem gerados
    const int totalPontos = 10000000;
    int hit = 0;

    // Inicializa a semente do gerador de números aleatórios
    srand(static_cast<unsigned>(time(nullptr)));        

    #pragma omp parallel for
    for (int i = 0; i < totalPontos; ++i) {
        // Gera coordenadas (x, y) entre 0 e 1
        double x = static_cast<double>(rand()) / RAND_MAX;
        double y = static_cast<double>(rand()) / RAND_MAX;

        // Verifica se o ponto está dentro do quarto de círculo
        if (x * x + y * y <= 1.0) {
            ++hit;
        }
    }

    // Estimativa de pi usando a razão de pontos dentro do círculo
    double pi = 4.0 * hit / totalPontos;

    // Exibe pi com 9 casas decimais
    cout << fixed << setprecision(9);
    cout << "Estimativa de pi: " << pi << endl;

    return 0;
}
