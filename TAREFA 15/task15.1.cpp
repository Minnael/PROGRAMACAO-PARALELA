#include <mpi.h>                     
#include <iostream>                  
#include <vector>                    

using namespace std;                 

// CONSTANTES
const int N = 10000000;                  // TAMANHO TOTAL DA BARRA DE CALOR
const int NUM_STEPS = 5000;         // NÚMERO TOTAL DE ITERAÇÕES (PASSOS DE TEMPO)
const double ALPHA = 0.01;          // COEFICIENTE DE DIFUSÃO TÉRMICA (DEFINE A VELOCIDADE DA DIFUSÃO)

// FUNÇÃO QUE TROCA OS VALORES DAS BORDAS ENTRE PROCESSOS VIZINHOS
void troca_bordas(vector<double>& u, int rank, int size, int local_n) {
    // SE NÃO FOR O PRIMEIRO PROCESSO, ENVIA SUA PRIMEIRA POSIÇÃO REAL PARA O PROCESSO À ESQUERDA
    if (rank > 0)
        MPI_Send(&u[1], 1, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD);

    // SE NÃO FOR O ÚLTIMO PROCESSO, ENVIA SUA ÚLTIMA POSIÇÃO REAL PARA O PROCESSO À DIREITA
    if (rank < size - 1)
        MPI_Send(&u[local_n], 1, MPI_DOUBLE, rank + 1, 1, MPI_COMM_WORLD);

    // SE NÃO FOR O PRIMEIRO PROCESSO, RECEBE UM VALOR PARA SUA CÉLULA FANTASMA À ESQUERDA
    if (rank > 0)
        MPI_Recv(&u[0], 1, MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // SE NÃO FOR O ÚLTIMO PROCESSO, RECEBE UM VALOR PARA SUA CÉLULA FANTASMA À DIREITA
    if (rank < size - 1)
        MPI_Recv(&u[local_n + 1], 1, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);                  // INICIALIZA O AMBIENTE MPI

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);    // OBTÉM O ID DO PROCESSO (RANK)
    MPI_Comm_size(MPI_COMM_WORLD, &size);    // OBTÉM O NÚMERO TOTAL DE PROCESSOS

    int local_n = N / size;                  // CADA PROCESSO TRABALHA COM UMA PARTE DA BARRA

    // CRIA DOIS VETORES DE TAMANHO local_n + 2 (INCLUINDO CÉLULAS FANTASMAS DOS DOIS LADOS)
    vector<double> u(local_n + 2, 0.0);       // VETOR ATUAL DE TEMPERATURAS
    vector<double> u_novo(local_n + 2, 0.0);  // VETOR PARA GUARDAR OS NOVOS VALORES

    // INSERE UM PICO DE CALOR NO MEIO DA BARRA GLOBAL (APENAS NO PROCESSO CENTRAL)
    if (rank == size / 2)
        u[local_n / 2] = 100.0;               // AQUECE UMA POSIÇÃO CENTRAL LOCAL DO PROCESSO DO MEIO

    double inicio = MPI_Wtime();             // MARCA O TEMPO DE INÍCIO DA SIMULAÇÃO

    // LOOP PRINCIPAL DE TEMPO (DIFUSÃO DE CALOR)
    for (int passo = 0; passo < NUM_STEPS; ++passo) {
        troca_bordas(u, rank, size, local_n);    // TROCA AS BORDAS COM OS VIZINHOS (COMUNICAÇÃO)

        // ATUALIZA AS POSIÇÕES INTERNAS DO VETOR USANDO O ESQUEMA DE DIFUSÃO
        for (int i = 1; i <= local_n; ++i)
            u_novo[i] = u[i] + ALPHA * (u[i - 1] - 2 * u[i] + u[i + 1]);  // CÁLCULO DA DIFUSÃO

        swap(u, u_novo);                      // TROCA OS VETORES PARA A PRÓXIMA ITERAÇÃO
    }

    double fim = MPI_Wtime();                // MARCA O TEMPO DE FIM DA SIMULAÇÃO

    // O PROCESSO 0 IMPRIME O TEMPO TOTAL DA SIMULAÇÃO
    if (rank == 0)
        cout << "TEMPO (MPI_Send/MPI_Recv): " << (fim - inicio) << " s" << endl;

    MPI_Finalize();                          // FINALIZA O AMBIENTE MPI
    return 0;                                // FIM DO PROGRAMA
}
