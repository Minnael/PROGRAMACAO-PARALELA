#include <iostream>
#include <string>
#include <omp.h>

using namespace std;

// Definição do nó da lista encadeada
struct Node {
    string filename;
    Node* next;
    Node(const string& name) : filename(name), next(nullptr) {}
};

int main() {
    // 1) Construir a lista encadeada com arquivos fictícios
    const int N = 8;
    Node* head = new Node("file1.txt");
    Node* tail = head;
    for (int i = 2; i <= N; ++i) {
        tail->next = new Node("file" + to_string(i) + ".txt");
        tail = tail->next;
    }

    // 2) Região paralela para criação e execução de tarefas
    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            Node* p = head;
            while (p) {
                #pragma omp task firstprivate(p)
                {
                    int tid = omp_get_thread_num();
                    cout << "Thread " << tid
                         << " processou " << p->filename << endl;
                }
                p = p->next;
            }
            #pragma omp taskwait
        }
    }

    // 3) Liberar memória
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }

    return 0;
}