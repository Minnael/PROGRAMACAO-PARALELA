#include <mpi.h>
#include <iostream>
#include <vector>

using namespace std;

const int N = 10000000;
const int NUM_STEPS = 5000;
const double ALPHA = 0.01;

void troca_bordas_overlap(vector<double>& u, vector<double>& u_novo, int rank, int size, int local_n) {
    MPI_Request reqs[4];                                        // DECLARAÇÃO DO VETOR DE REQUISIÇÕES PARA COMUNICAÇÃO ASSÍNCRONA

    if (rank > 0)
        MPI_Irecv(&u[0], 1, MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD, &reqs[0]);   // INICIA RECEPÇÃO NÃO BLOQUEANTE DA BORDA ESQUERDA DO PROCESSO ANTERIOR
    if (rank < size - 1)
        MPI_Irecv(&u[local_n + 1], 1, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD, &reqs[1]); // INICIA RECEPÇÃO NÃO BLOQUEANTE DA BORDA DIREITA DO PROCESSO SEGUINTE

    if (rank > 0)
        MPI_Isend(&u[1], 1, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, &reqs[2]);   // INICIA ENVIO NÃO BLOQUEANTE DA BORDA ESQUERDA PARA PROCESSO ANTERIOR
    if (rank < size - 1)
        MPI_Isend(&u[local_n], 1, MPI_DOUBLE, rank + 1, 1, MPI_COMM_WORLD, &reqs[3]); // INICIA ENVIO NÃO BLOQUEANTE DA BORDA DIREITA PARA PROCESSO SEGUINTE

    for (int i = 2; i <= local_n - 1; ++i) // LOOP PARA ATUALIZAÇÃO DOS PONTOS INTERNOS, EXCLUINDO AS BORDAS
        // CÁLCULO DA DIFUSÃO TÉRMICA NOS PONTOS INTERNOS, SEM DEPENDER DAS BORDAS
        u_novo[i] = u[i] + ALPHA * (u[i - 1] - 2 * u[i] + u[i + 1]); 

    if (rank > 0)
        MPI_Wait(&reqs[0], MPI_STATUS_IGNORE); // ESPERA A CONCLUSÃO DA RECEPÇÃO DA BORDA ESQUERDA ANTES DE ATUALIZAR ESTE VALOR
    if (rank < size - 1)
        MPI_Wait(&reqs[1], MPI_STATUS_IGNORE); // ESPERA A CONCLUSÃO DA RECEPÇÃO DA BORDA DIREITA ANTES DE ATUALIZAR ESTE VALOR

    if (rank > 0)
        u_novo[1] = u[1] + ALPHA * (u[0] - 2 * u[1] + u[2]);// ATUALIZA A BORDA ESQUERDA USANDO O VALOR RECEBIDO NA CÉLULA FANTASMA
    if (rank < size - 1)
        // ATUALIZA A BORDA DIREITA USANDO O VALOR RECEBIDO NA CÉLULA FANTASMA
        u_novo[local_n] = u[local_n] + ALPHA * (u[local_n - 1] - 2 * u[local_n] + u[local_n + 1]); 

    if (rank > 0)
        MPI_Wait(&reqs[2], MPI_STATUS_IGNORE); // ESPERA A FINALIZAÇÃO DO ENVIO DA BORDA ESQUERDA PARA PROCESSO ANTERIOR
    if (rank < size - 1)
        MPI_Wait(&reqs[3], MPI_STATUS_IGNORE); // ESPERA A FINALIZAÇÃO DO ENVIO DA BORDA DIREITA PARA PROCESSO SEGUINTE
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
