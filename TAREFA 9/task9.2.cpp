#include <iostream>
#include <list>
#include <vector>
#include <random>
#include <omp.h>

using namespace std;

// LISTAS GLOBAIS PARA A PRIMEIRA PARTE
list<int> listaA;
list<int> listaB;

// FUNÇÃO PARA GERAR UM VALOR ALEATÓRIO
int gerarValor() {
    static thread_local mt19937 gen(random_device{}());
    uniform_int_distribution<> distrib(1, 1000);
    return distrib(gen);
}

// PARTE 1: DUAS LISTAS COM REGIÕES CRÍTICAS NOMEADAS
void insercaoComRegioesCriticas(int N) {
    #pragma omp parallel num_threads(2)
    {
        int id = omp_get_thread_num();
        for (int i = 0; i < N; ++i) {
            int valor = gerarValor();
            int destino = valor % 2;  // Simula escolha aleatória entre 0 e 1

            if (destino == 0) {
                #pragma omp critical(listaA)
                listaA.push_back(valor);
            } else {
                #pragma omp critical(listaB)
                listaB.push_back(valor);
            }
        }
    }

    cout << "\n[PARTE 1] INSERCAO COM 2 LISTAS FIXAS\n";
    cout << "TAMANHO DA LISTA A: " << listaA.size() << "\n";
    cout << "TAMANHO DA LISTA B: " << listaB.size() << "\n";
}

// PARTE 2: GENERALIZAÇÃO COM N LISTAS USANDO LOCKS EXPLÍCITOS
void insercaoGeneralizada(int numListas, int N, int numThreads) {
    vector<list<int>> listas(numListas);
    vector<omp_lock_t> locks(numListas);

    // Inicializa locks
    for (int i = 0; i < numListas; ++i) {
        omp_init_lock(&locks[i]);
    }

    #pragma omp parallel num_threads(numThreads)
    {
        int id = omp_get_thread_num();
        mt19937 gen(random_device{}() + id);
        uniform_int_distribution<> distLista(0, numListas - 1);
        uniform_int_distribution<> distValor(1, 1000);

        for (int i = 0; i < N; ++i) {
            int indice = distLista(gen);
            int valor = distValor(gen);

            omp_set_lock(&locks[indice]);
            listas[indice].push_back(valor);
            omp_unset_lock(&locks[indice]);
        }
    }

    cout << "\n[PARTE 2] INSERCAO GENERALIZADA COM " << numListas << " LISTAS\n";
    for (int i = 0; i < numListas; ++i) {
        cout << "TAMANHO DA LISTA " << i << ": " << listas[i].size() << "\n";
    }

    // Libera locks
    for (int i = 0; i < numListas; ++i) {
        omp_destroy_lock(&locks[i]);
    }
}

int main() {
    int N = 500000;

    // Parte 1: Duas listas com regiões críticas nomeadas
    insercaoComRegioesCriticas(N);

    // Parte 2: Generalização para múltiplas listas
    int numListas = 4;
    int numThreads = 4;
    insercaoGeneralizada(numListas, N, numThreads);

    return 0;
}
