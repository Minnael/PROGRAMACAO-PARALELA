#include <iostream>
#include <locale.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace chrono;


void mostrarVetor(vector<int> vetor){
    cout << "[ ";
    for (int number : vetor) {
        cout << setw(3) << number << "  ";
    }
    cout << "]" << endl;
}

vector<int> multiplicadorMatrizes(vector<int> vetor, vector<vector<int>> matriz, bool variante) {
    vector<int> resultado(vetor.size(), 0);

    if (variante) {
        auto start = high_resolution_clock::now();

        for (int j = 0; j < vetor.size(); j++) {
            for (int i = 0; i < vetor.size(); i++) {
                resultado[i] += matriz[i][j] * vetor[j];
            }
        }

        auto end = high_resolution_clock::now();
        cout << "Case 02 (Colunas): " << duration_cast<nanoseconds>(end - start).count() << " nano segundos\n";

    } else {
        auto start = high_resolution_clock::now();

        for (int i = 0; i < vetor.size(); i++) {
            for (int j = 0; j < vetor.size(); j++) {
                resultado[i] += matriz[i][j] * vetor[j];
            }
        }

        auto end = high_resolution_clock::now();
        cout << "Case 01 (Linhas): " << duration_cast<nanoseconds>(end - start).count() << " nano segundos\n";
    }

    return resultado;
}


int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");
    srand(time(0));

    vector<int> testes = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200};

    for (int teste : testes) {
        int max = teste, min = teste;
        int linhas = rand() % (max - min + 1) + min, colunas = rand() % (max - min + 1) + min;

        vector<int> vetor(colunas, 0);
        vector<vector<int>> matriz(linhas, vector<int>(colunas, 0));

        // DEFININDO VETOR: 
        for (int i=0; i < colunas; i++) {
            vetor[i] = 100;
        }

        // DEFININDO MATRIZ:
        for (int i=0; i < linhas; i++){
            for (int j=0; j < colunas; j++) {
                matriz[i][j] = 100;
            }
        }

        /* APRESENTANDO VETOR:
        cout << "SEGUE ABAIXO O VETOR: " << endl << endl;
        mostrarVetor(vetor);
        cout << endl;

        // APRESENTANDO MATRIZ:
        cout << "SEGUE ABAIXO A MATRIZ: " << endl << endl;
        for (vector<int> vector : matriz) {
            mostrarVetor(vector);
        }
        cout << endl;
        */
        

        // MULTIPLICACAO (MATRIX x VETOR) & (VETOR x MATRIX):
        vector<int> resultadoVxM = multiplicadorMatrizes(vetor, matriz, false);
        vector<int> resultadoMxV = multiplicadorMatrizes(vetor, matriz, true);

        // ESPACO OCUPADO PELAS MATRIZES...
        size_t tamanho_matriz = 0;

        for (const auto& linha : matriz) {
            tamanho_matriz += sizeof(linha) + (linha.size() * sizeof(int));
        }

        cout << "MATRIZ: " << teste  << "x" << teste << " " << tamanho_matriz << " bytes" << endl;

        // APRESENTACAO DOS RESULTADOS FINAIS...
        //mostrarVetor(resultadoMxV);
        //mostrarVetor(resultadoVxM);
    }

    return 0;
}