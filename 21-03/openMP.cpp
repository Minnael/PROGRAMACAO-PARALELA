#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <chrono>
#include <iomanip>

using namespace std;


int main() {
    srand(time(NULL));

    // Gerar tamanho aleatório para o vetor
    int size = 300000;
    int vetor[size];

    // Preencher o vetor com valores aleatórios de 0 a 9
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        vetor[i] = rand() % (9 + 1);
    }

    // Número a ser contado
    int n;
    cout << "Digite o numero que deseja contar: ";
    cin >> n;

    // Contar a quantidade de ocorrências de 'n' usando OpenMP
    int count_parallel = 0;

    // Usando chrono para medir o tempo do cálculo paralelo
    auto inicio = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for 
    for (int i = 0; i < size; i++) {
        if (vetor[i] == n) {
            count_parallel++;
        }
    }

    auto fim = std::chrono::high_resolution_clock::now();
    auto duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - inicio);
    cout << "\nTempo de execucao da multiplicacao (paralelo): " << duracao.count() << " microssegundos" << endl << endl;

    // Contar a quantidade de ocorrências de 'n' usando loop sequencial
    int count_sequential = 0;

    // Usando chrono para medir o tempo do cálculo sequencial
    auto inicio_sequencial = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < size; i++) {
        if (vetor[i] == n) {
            count_sequential++;
        }
    }

    auto fim_sequencial = std::chrono::high_resolution_clock::now();
    auto duracao_sequencial = std::chrono::duration_cast<std::chrono::microseconds>(fim_sequencial - inicio_sequencial);
    cout << "Tempo de execucao da multiplicacao (sequencial): " << duracao_sequencial.count() << " microssegundos" << endl << endl;

    // Exibir o número de ocorrências encontrados
    cout << "O NUMERO " << n << " APARECE " << count_parallel << " VEZES NO VETOR (paralelo)" << endl;
    cout << "O NUMERO " << n << " APARECE " << count_sequential << " VEZES NO VETOR (sequencial)" << endl;

    return 0;
}
