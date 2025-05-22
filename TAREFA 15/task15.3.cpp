#include <mpi.h>
#include <iostream>
#include <vector>

using namespace std;

const int N = 1000;
const int NUM_STEPS = 5000;
const double ALPHA = 0.01;

// TROCA COM MPI_Test PARA SOBREPOSIÇÃO DE COMPUTAÇÃO E COMUNICAÇÃO
void troca_bordas_overlap(vector<double>& u, vector<double>& u_novo, int rank, int size, int local_n) {
    MPI_Request reqs[4];
    bool recv_ok[2] = {false, false};

    // INICIA RECEBIMENTOS
    if (rank > 0)
        MPI_Irecv(&u[0], 1, MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD, &reqs[0]);
    if (rank < size - 1)
        MPI_Irecv(&u[local_n + 1], 1, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD, &reqs[1]);

    // INICIA ENVIO
    if (rank > 0)
        MPI_Isend(&u[1], 1, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, &reqs[2]);
    if (rank < size - 1)
        MPI_Isend(&u[local_n], 1, MPI_DOUBLE, rank + 1, 1, MPI_COMM_WORLD, &reqs[3]);

    // CÁLCULO DOS PONTOS INTERNOS
    for (int i = 2; i <= local_n - 1; ++i)
        u_novo[i] = u[i] + ALPHA * (u[i - 1] - 2 * u[i] + u[i + 1]);

    // TESTA SE RECEBIMENTOS TERMINARAM
    if (rank > 0) while (!recv_ok[0]) MPI_Test(&reqs[0], &recv_ok[0], MPI_STATUS_IGNORE);
    if (rank < size - 1) while (!recv_ok[1]) MPI_Test(&reqs[1], &recv_ok[1], MPI_STATUS_IGNORE);

    // CÁLCULO DAS BORDAS APÓS RECEBER
    u_novo[1] = u[1] + ALPHA * (u[0] - 2 * u[1] + u[2]);
    u_novo[local_n] = u[local_n] + ALPHA * (u[local_n - 1] - 2 * u[local_n] + u[local_n + 1]);

    // AGUARDA FIM DOS ENVIOS
    MPI_Waitall(4, reqs, MPI_STATUSES_IGNORE);
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_n = N / size;

    vector<double> u(local_n + 2, 0.0);
    vector<double> u_novo(local_n + 2, 0.0);

    if (rank == size / 2)
        u[local_n / 2] = 100.0;

    double inicio = MPI_Wtime();

    for (int passo = 0; passo < NUM_STEPS; ++passo) {
        troca_bordas_overlap(u, u_novo, rank, size, local_n);
        swap(u, u_novo);
    }

    double fim = MPI_Wtime();

    if (rank == 0)
        cout << "TEMPO (MPI_Test + SOBREPOSIÇÃO): " << (fim - inicio) << " s" << endl;

    MPI_Finalize();
    return 0;
}
