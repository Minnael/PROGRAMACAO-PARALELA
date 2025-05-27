#include <mpi.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// FUNÇÃO PARA PREENCHER A MATRIZ COM VALORES ALEATÓRIOS
void fill_matrix(vector<float>& A, int M, int N) {
    for (int i = 0; i < M * N; ++i)
        A[i] = static_cast<float>(rand()) / RAND_MAX;
}

// FUNÇÃO PARA PREENCHER O VETOR x COM VALORES ALEATÓRIOS
void fill_vector(vector<float>& x, int N) {
    for (int i = 0; i < N; ++i)
        x[i] = static_cast<float>(rand()) / RAND_MAX;
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv); // INICIALIZA O MPI

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // OBTÉM O RANK DO PROCESSO ATUAL
    MPI_Comm_size(MPI_COMM_WORLD, &size); // OBTÉM O NÚMERO TOTAL DE PROCESSOS

    
    int M = 12800, N = 1000; // DEFINE TAMANHOS PADRÃO DA MATRIZ E DO VETOR
    if (argc >= 3) {
        M = atoi(argv[1]);  // NÚMERO DE LINHAS
        N = atoi(argv[2]);  // NÚMERO DE COLUNAS / TAMANHO DO VETOR x
    }

    // GARANTE QUE O NÚMERO DE LINHAS SEJA DIVISÍVEL PELO NÚMERO DE PROCESSOS
    if (M % size != 0) {
        if (rank == 0)
            cerr << "ERROR: M MUST BE DIVISIBLE BY NUMBER OF PROCESSES." << endl;
        MPI_Finalize();
        return 1;
    }

    int local_M = M / size; // NÚMERO DE LINHAS POR PROCESSO
    vector<float> A, x(N), y(M), local_A(local_M * N), local_y(local_M); // DECLARA VETORES E MATRIZES

    // PROCESSO 0 GERA MATRIZ A E VETOR x
    if (rank == 0) {
        A.resize(M * N);
        fill_matrix(A, M, N);
        fill_vector(x, N);
    }

    double start_time = MPI_Wtime(); // INÍCIO DA MEDIÇÃO DO TEMPO

    // DISTRIBUI AS LINHAS DA MATRIZ A ENTRE OSPROCES SOS
    MPI_Scatter(A.data(), local_M * N, MPI_FLOAT, local_A.data(), local_M * N, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(x.data(), N, MPI_FLOAT, 0, MPI_COMM_WORLD); // TODOS OS PROCESSOS RECEBEM O VETOR x

    // CADA PROCESSO CALCULA SUA PARTE DO RESULTADO y
    for (int i = 0; i < local_M; ++i) {
        local_y[i] = 0.0f;
        for (int j = 0; j < N; ++j)
            local_y[i] += local_A[i * N + j] * x[j];
    }

    // REUNE TODAS AS PARTES DO VETOR y NO PROCESSO 0
    MPI_Gather(local_y.data(), local_M, MPI_FLOAT, y.data(), local_M, MPI_FLOAT, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime(); // FIM DA MEDIÇÃO DO TEMPO

    // PROCESSO 0 EXIBE O TEMPO DE EXECUÇÃO
    if (rank == 0) {
        cout << "EXECUTION TIME: " << (end_time - start_time) << " SECONDS" << endl;

        // DESCOMENTE PARA EXIBIR O RESULTADO y
        /*
        cout << "RESULT VECTOR y:\n";
        for (int i = 0; i < M; ++i)
            cout << y[i] << " ";
        cout << endl;
        */
    }

    MPI_Finalize(); // FINALIZA O MPI

    return 0;
}
