#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

int main() {
    vector<int> testes = {300000000};

    for (int N : testes) {
        vector<int> vec(N);
    
        // INICIALIZAÇÃO COM CÁLCULO SIMPLES
        auto start = high_resolution_clock::now();
        for (int i = 0; i < N; ++i) {
            vec[i] = i * 3 + 7;
        }
        auto end = high_resolution_clock::now();
        cout << "INICIALIZACAO: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

        // SOMA ACUMULATIVA COM DEPENDÊNCIA 
        start = high_resolution_clock::now();
        long long sum = 0;
        for (int i = 0; i < N; ++i) {
            sum += vec[i];
        }
        end = high_resolution_clock::now();
        cout << "COM DEPENDENCIA -> " << "RESULTADO: " << sum << " / "<< "TEMPO: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

        // SOMA COM MÚLTIPLAS VARIÁVEIS PARA QUEBRAR DEPENDÊNCIAS
        start = high_resolution_clock::now();
        long long sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
        for (int i = 0; i + 3 < N; i += 4) {
            sum1 += vec[i];
            sum2 += vec[i + 1];
            sum3 += vec[i + 2];
            sum4 += vec[i + 3];
        }

        // Adiciona elementos restantes se N não for múltiplo de 4
        long long totalSum = sum1 + sum2 + sum3 + sum4;
        for (int i = (N / 4) * 4; i < N; ++i) {
            totalSum += vec[i];
        }

        end = high_resolution_clock::now();
        cout << "SEM DEPENDENCIA -> "<< "RESULTADO: " << totalSum << " / " << "TEMPO: " << duration_cast<milliseconds>(end - start).count() << " ms\n";
    }

    return 0;
}
