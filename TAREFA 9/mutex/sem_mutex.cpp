#include <iostream>
#include <thread>

int contador = 0;

void incrementa() {
    for (int i = 0; i < 10000000; ++i) {
        contador++;  // <-- acesso concorrente, perigoso!
    }
}

int main() {
    std::thread t1(incrementa);
    std::thread t2(incrementa);

    t1.join();
    t2.join();

    std::cout << "Contador: " << contador << std::endl;
    return 0;
}
