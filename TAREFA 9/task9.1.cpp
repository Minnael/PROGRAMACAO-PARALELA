#include <iostream>
#include <list>
#include <mutex>
#include <thread>
#include <vector>
#include <random>

using namespace std;

// CRIÇÃO DAS LISTAS DE MANEIRA GLOBAL
list<int> listaA;
list<int> listaB;

// DEFINIÇÃO DE UM MUTEXT PARA CADA LISTA
mutex mutexA;
mutex mutexB;

void tarefa(int idThread, int N) {
    random_device rd; //GERA UMA SEMENTE RANDOM
    mt19937 gen(rd());
    uniform_int_distribution<> listaDistrib(0, 1); //ESCOLHE ENTRE LISTA 0 OU 1
    uniform_int_distribution<> valorDistrib(1, 1000); //ESCOLHE UM VALOR RANDOM DE 0 A 1000

    for (int i = 0; i < N; ++i) {
        int listaEscolhida = listaDistrib(gen); //LISTA ESCOLHIDA
        int valor = valorDistrib(gen); //VALOR ESCOLHIDO

        if (listaEscolhida == 0) {
            lock_guard<mutex> lock(mutexA); //PROTEGE O ACESSO A LISTA-A (REGIÃO CRÍTICA)
            listaA.push_back(valor);
        } else {
            lock_guard<mutex> lock(mutexB); //PROTEGE O ACESSO A LISTA-B (REGIÃO CRÍTICA)
            listaB.push_back(valor);
        }
    }
}

int main() {
    int N = 500000;
    thread thread1(tarefa, 1, N);
    thread thread2(tarefa, 2, N);

    thread1.join(); thread2.join();

    cout << "TAMANHO DA LISTA A: " << listaA.size() << "\n";
    cout << "TAMANHO DA LISTA B: " << listaB.size() << "\n";

    return 0;
}
