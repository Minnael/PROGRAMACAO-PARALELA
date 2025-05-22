#include <iostream>   
#include <vector>     
#include <cstring> 
#include <iomanip>    
#include <mpi.h>      

using namespace std;  

constexpr int NUM_EXCHANGES = 1000;   // CONSTANTE DEFININDO O NÚMERO DE TROCAS DE MENSAGEM
 
int main(int argc, char *argv[]) {    // FUNÇÃO PRINCIPAL COM ARGUMENTOS DE LINHA DE COMANDO
    int rank, size;                   // VARIÁVEIS PARA ARMAZENAR O RANK DO PROCESSO E O NÚMERO TOTAL DE PROCESSOS
    int tag = 0;                      // TAG PARA IDENTIFICAR MENSAGENS (USADO NO MPI SEND/RECV)
    MPI_Status status;                // ESTRUTURA PARA ARMAZENAR O STATUS DAS MENSAGENS RECEBIDAS

    MPI_Init(&argc, &argv);                // INICIALIZA O AMBIENTE MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // OBTÉM O RANK (ID) DO PROCESSO ATUAL
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // OBTÉM O NÚMERO TOTAL DE PROCESSOS NA EXECUÇÃO

    if (size != 2) {                 // VERIFICA SE O NÚMERO DE PROCESSOS É EXATAMENTE 2
        MPI_Finalize();              // FINALIZA O AMBIENTE MPI
        return EXIT_FAILURE;         // ENCERRA O PROGRAMA COM CÓDIGO DE ERRO
    }

    vector<int> sizes = {8, 64, 512, 1024, 4096, 8192, 65536, 131072, 1048576};  // VETOR DE TAMANHOS DE MENSAGEM EM BYTES

    for (int msg_size : sizes) {                  // LOOP PARA CADA TAMANHO DE MENSAGEM
        vector<char> mensagem(msg_size, 'a');       
        double start_time = 0.0, end_time = 0.0;  

        if (rank == 0) {     
            start_time = MPI_Wtime();             
            for (int j = 0; j < NUM_EXCHANGES; j++) {               // REALIZA NUM_EXCHANGES TROCAS DE MENSAGENS
                MPI_Send(mensagem.data(), msg_size, MPI_CHAR, 1, tag, MPI_COMM_WORLD);  // ENVIA MENSAGEM PARA PROCESSO 1
                MPI_Recv(mensagem.data(), msg_size, MPI_CHAR, 1, tag, MPI_COMM_WORLD, &status); // RECEBE MENSAGEM DE VOLTA DO PROCESSO 1
            }
            end_time = MPI_Wtime();                                      

            cout << fixed << setprecision(12);
            cout << "TAMANHO: " << msg_size
                 << " bytes | TEMPO MEDIO (ida-volta): "
                 << (end_time - start_time) / NUM_EXCHANGES << " s\n"; 
        }
        else if (rank == 1) {         
            for (int j = 0; j < NUM_EXCHANGES; j++) {  // REALIZA NUM_EXCHANGES TROCAS DE MENSAGENS
                MPI_Recv(mensagem.data(), msg_size, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);  // RECEBE MENSAGEM DO PROCESSO 0
                MPI_Send(mensagem.data(), msg_size, MPI_CHAR, 0, tag, MPI_COMM_WORLD);  // ENVIA MENSAGEM DE VOLTA PARA O PROCESSO 0
            }
        }
    }
    MPI_Finalize();  // FINALIZA O AMBIENTE MPI

    return 0;        
}
