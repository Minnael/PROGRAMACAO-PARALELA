#include <iostream>
#include <thread>
#include <mutex>

int contador = 0;
std::mutex mtx;

void incrementa() {
    for (int i = 0; i < 10000000; ++i) {
        std::lock_guard<std::mutex> lock(mtx); // protege o acesso
        contador++;
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
