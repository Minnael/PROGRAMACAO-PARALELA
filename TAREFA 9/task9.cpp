#include <iostream>
#include <list>
#include <mutex>
#include <thread>
#include <vector>
#include <random>

// Duas listas globais
std::list<int> listaA;
std::list<int> listaB;

// Mutexes específicos para cada lista
std::mutex mutexA;
std::mutex mutexB;

void tarefa(int id, int numInsercoes) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> listaDistrib(0, 1);
    std::uniform_int_distribution<> valorDistrib(1, 1000);

    for (int i = 0; i < numInsercoes; ++i) {
        int listaEscolhida = listaDistrib(gen);
        int valor = valorDistrib(gen);

        if (listaEscolhida == 0) {
            std::lock_guard<std::mutex> lock(mutexA); // Região crítica nomeada para listaA
            listaA.push_back(valor);
        } else {
            std::lock_guard<std::mutex> lock(mutexB); // Região crítica nomeada para listaB
            listaB.push_back(valor);
        }
    }
}

int main() {
    int N = 55;
    std::thread t1(tarefa, 1, N);
    std::thread t2(tarefa, 2, N);

    t1.join();
    t2.join();

    std::cout << "Tamanho da lista A: " << listaA.size() << "\n";
    std::cout << "Tamanho da lista B: " << listaB.size() << "\n";

    return 0;
}
