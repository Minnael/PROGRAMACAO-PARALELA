#include <mpi.h>
#include <iostream>
#include <vector>

using namespace std;

const int N = 1000;
const int NUM_STEPS = 5000;
const double ALPHA = 0.01;

// TROCA NÃO BLOQUEANTE COM MPI_Isend / Irecv
void troca_bordas_nb(vector<double>& u, int rank, int size, int local_n) {
    MPI_Request reqs[4];

    if (rank > 0)
        MPI_Irecv(&u[0], 1, MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD, &reqs[0]);
    if (rank < size - 1)
        MPI_Irecv(&u[local_n + 1], 1, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD, &reqs[1]);
    if (rank > 0)
        MPI_Isend(&u[1], 1, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, &reqs[2]);
    if (rank < size - 1)
        MPI_Isend(&u[local_n], 1, MPI_DOUBLE, rank + 1, 1, MPI_COMM_WORLD, &reqs[3]);

    // ESPERA ATÉ QUE TODAS AS COMUNICAÇÕES SEJAM COMPLETADAS
    if (rank > 0) MPI_Wait(&reqs[0], MPI_STATUS_IGNORE);
    if (rank < size - 1) MPI_Wait(&reqs[1], MPI_STATUS_IGNORE);
    if (rank > 0) MPI_Wait(&reqs[2], MPI_STATUS_IGNORE);
    if (rank < size - 1) MPI_Wait(&reqs[3], MPI_STATUS_IGNORE);
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
        troca_bordas_nb(u, rank, size, local_n);

        for (int i = 1; i <= local_n; ++i)
            u_novo[i] = u[i] + ALPHA * (u[i - 1] - 2 * u[i] + u[i + 1]);

        swap(u, u_novo);
    }

    double fim = MPI_Wtime();

    if (rank == 0)
        cout << "TEMPO (MPI_Isend/MPI_Irecv): " << (fim - inicio) << " s" << endl;

    MPI_Finalize();
    return 0;
}
