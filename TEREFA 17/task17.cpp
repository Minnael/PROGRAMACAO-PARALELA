#include <mpi.h> 
#include <iostream> 
#include <vector> 
#include <cstdlib> 
#include <ctime> 

using namespace std; 

void fill_matrix(vector<float>& A, int M, int N) { // FUNÇÃO PARA PREENCHER A MATRIZ COM VALORES ALEATÓRIOS
    for (int i = 0; i < M * N; ++i)               // PERCORRE TODOS OS ELEMENTOS DA MATRIZ
        A[i] = static_cast<float>(rand()) / RAND_MAX; // ATRIBUI VALOR ALEATÓRIO NORMALIZADO
}

void fill_vector(vector<float>& x, int N) { // FUNÇÃO PARA PREENCHER O VETOR x COM VALORES ALEATÓRIOS
    for (int i = 0; i < N; ++i)              // PERCORRE TODOS OS ELEMENTOS DO VETOR
        x[i] = static_cast<float>(rand()) / RAND_MAX; // ATRIBUI VALOR ALEATÓRIO NORMALIZADO
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv); // INICIALIZA O MPI

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // OBTÉM O RANK DO PROCESSO ATUAL
    MPI_Comm_size(MPI_COMM_WORLD, &size); // OBTÉM O NÚMERO TOTAL DE PROCESSOS

    int M = 12800, N = 1000; // TAMANHOS PADRÃO PARA MATRIZ E VETOR
    if (argc >= 3) {
        M = atoi(argv[1]); // LÊ O VALOR DE M DA LINHA DE COMANDO
        N = atoi(argv[2]); // LÊ O VALOR DE N DA LINHA DE COMANDO
    }

    if (N % size != 0) { // VERIFICA SE N É DIVISÍVEL PELO NÚMERO DE PROCESSOS
        if (rank == 0)
            cerr << "ERROR: N must be divisible by number of processes." << endl; // MENSAGEM DE ERRO
        MPI_Finalize(); // FINALIZA O MPI
        return 1; // ENCERRA O PROGRAMA COM ERRO
    }

    int local_N = N / size; // NÚMERO DE COLUNAS POR PROCESSO
    vector<float> A, x, local_A(M * local_N), local_x(local_N), y(M), local_y(M, 0.0f); // DECLARA VETORES

    if (rank == 0) {
        A.resize(M * N); // ALOCA TAMANHO PARA MATRIZ A
        x.resize(N); // ALOCA TAMANHO PARA VETOR x
        fill_matrix(A, M, N); // PREENCHE MATRIZ COM VALORES ALEATÓRIOS
        fill_vector(x, N); // PREENCHE VETOR COM VALORES ALEATÓRIOS
    } else {
        x.resize(N); // ALOCA VETOR x PARA RECEBER A PARTE DE x VIA SCATTER
    }

    double start_time = MPI_Wtime(); // MARCA TEMPO DE INÍCIO

    MPI_Datatype column_type, resized_type; // VARIÁVEIS PARA TIPOS DERIVADOS
    MPI_Type_vector(M, local_N, N, MPI_FLOAT, &column_type); // CRIA TIPO DERIVADO PARA BLOCO DE COLUNAS
    MPI_Type_create_resized(column_type, 0, local_N * sizeof(float), &resized_type); // AJUSTA DESLOCAMENTO PARA USO COM SCATTER
    MPI_Type_commit(&resized_type); // COMMITA O TIPO PARA USO

    MPI_Scatter(A.data(), 1, resized_type, local_A.data(), M * local_N, MPI_FLOAT, 0, MPI_COMM_WORLD); // DISTRIBUI AS COLUNAS DA MATRIZ A

    MPI_Scatter(x.data(), local_N, MPI_FLOAT, local_x.data(), local_N, MPI_FLOAT, 0, MPI_COMM_WORLD); // DISTRIBUI AS PARTES DO VETOR x

    for (int i = 0; i < M; ++i) { // CALCULA CONTRIBUIÇÃO PARCIAL PARA CADA LINHA
        for (int j = 0; j < local_N; ++j)
            local_y[i] += local_A[i * local_N + j] * local_x[j]; // SOMA PRODUTOS DAS COLUNAS DE A COM ELEMENTOS DE x
    }
    MPI_Reduce(local_y.data(), y.data(), M, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD); // SOMA AS CONTRIBUIÇÕES PARCIAIS PARA y

    double end_time = MPI_Wtime(); // MARCA TEMPO DE TÉRMINO

    if (rank == 0) {
        cout << "EXECUTION TIME: " << (end_time - start_time) << " SECONDS" << endl; // EXIBE TEMPO TOTAL
        /*
        cout << "RESULT VECTOR y:\n"; // DESCOMENTAR PARA MOSTRAR RESULTADO FINAL
        for (int i = 0; i < M; ++i)
            cout << y[i] << " ";
        cout << endl;
        */
    }

    MPI_Type_free(&column_type); // LIBERA O TIPO DERIVADO ORIGINAL
    MPI_Type_free(&resized_type); // LIBERA O TIPO REDIMENSIONADO

    MPI_Finalize(); 

    return 0; 
}
