#include <mpi.h>
#include <iostream>
#include <vector>

using namespace std;

// CONSTANTES
const int N = 1000;            // TAMANHO TOTAL DA BARRA
const int NUM_STEPS = 5000;    // NÚMERO DE PASSOS DE TEMPO
const double ALPHA = 0.01;     // COEFICIENTE DE DIFUSÃO

// FUNÇÃO PARA TROCAR BORDAS USANDO MPI_Send / MPI_Recv
void troca_bordas(vector<double>& u, int rank, int size, int local_n) {
    // ENVIA E RECEBE COMUNICAÇÃO BLOQUEANTE
    if (rank > 0)
        MPI_Send(&u[1], 1, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD);
    if (rank < size - 1)
        MPI_Send(&u[local_n], 1, MPI_DOUBLE, rank + 1, 1, MPI_COMM_WORLD);
    if (rank > 0)
        MPI_Recv(&u[0], 1, MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    if (rank < size - 1)
        MPI_Recv(&u[local_n + 1], 1, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_n = N / size;

    // VETORES DE TEMPERATURA COM CÉLULAS FANTASMAS
    vector<double> u(local_n + 2, 0.0);
    vector<double> u_novo(local_n + 2, 0.0);

    // CONDIÇÃO INICIAL: PICO DE CALOR NO CENTRO DA BARRA
    if (rank == size / 2)
        u[local_n / 2] = 100.0;

    double inicio = MPI_Wtime();

    // LOOP PRINCIPAL DE TEMPO
    for (int passo = 0; passo < NUM_STEPS; ++passo) {
        troca_bordas(u, rank, size, local_n);

        // ATUALIZA OS VALORES INTERNOS
        for (int i = 1; i <= local_n; ++i)
            u_novo[i] = u[i] + ALPHA * (u[i - 1] - 2 * u[i] + u[i + 1]);

        swap(u, u_novo);
    }

    double fim = MPI_Wtime();

    // IMPRESSÃO DO TEMPO TOTAL
    if (rank == 0)
        cout << "TEMPO (MPI_Send/MPI_Recv): " << (fim - inicio) << " s" << endl;

    MPI_Finalize();
    return 0;
}
