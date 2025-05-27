#include <mpi.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void fill_matrix(vector<float>& A, int M, int N) {
    for (int i = 0; i < M * N; ++i)
        A[i] = static_cast<float>(rand()) / RAND_MAX;
}

void fill_vector(vector<float>& x, int N) {
    for (int i = 0; i < N; ++i)
        x[i] = static_cast<float>(rand()) / RAND_MAX;
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int M = 12800, N = 1000;
    if (argc >= 3) {
        M = atoi(argv[1]);
        N = atoi(argv[2]);
    }

    if (N % size != 0) {
        if (rank == 0)
            cerr << "ERROR: N must be divisible by number of processes." << endl;
        MPI_Finalize();
        return 1;
    }

    int local_N = N / size;
    vector<float> A, x, local_A(M * local_N), local_x(local_N), y(M), local_y(M, 0.0f);

    if (rank == 0) {
        A.resize(M * N);
        x.resize(N);
        fill_matrix(A, M, N);
        fill_vector(x, N);
    } else {
        x.resize(N); // Necessário para MPI_Scatter (recebe só parte em local_x)
    }

    double start_time = MPI_Wtime();

    // Criar tipo derivado para coluna
    MPI_Datatype column_type, resized_type;
    MPI_Type_vector(M, local_N, N, MPI_FLOAT, &column_type);
    MPI_Type_create_resized(column_type, 0, local_N * sizeof(float), &resized_type);
    MPI_Type_commit(&resized_type);

    // Distribuir colunas da matriz A entre os processos
    MPI_Scatter(A.data(), 1, resized_type, local_A.data(), M * local_N, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Distribuir partes correspondentes do vetor x
    MPI_Scatter(x.data(), local_N, MPI_FLOAT, local_x.data(), local_N, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Cada processo calcula sua contribuição para y
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < local_N; ++j)
            local_y[i] += local_A[i * local_N + j] * local_x[j];
    }

    // Somar as contribuições parciais no processo 0
    MPI_Reduce(local_y.data(), y.data(), M, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    if (rank == 0) {
        cout << "EXECUTION TIME: " << (end_time - start_time) << " SECONDS" << endl;
        /*
        cout << "RESULT VECTOR y:\n";
        for (int i = 0; i < M; ++i)
            cout << y[i] << " ";
        cout << endl;
        */
    }

    MPI_Type_free(&column_type);
    MPI_Type_free(&resized_type);
    MPI_Finalize();

    return 0;
}
