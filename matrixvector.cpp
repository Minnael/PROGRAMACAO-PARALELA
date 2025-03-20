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
    vector<int> resultado;

    if (variante) {
        auto inicio = high_resolution_clock::now();

        for (int i=0; i < matriz[0].size(); i++) {
            int number = 0;
            for (int j=0; j < vetor.size(); j++) {
                number = number + vetor[j] * matriz[j][i];
            }
            resultado.push_back(number);
        }

        auto fim = high_resolution_clock::now();
        auto duracao = duration_cast<microseconds>(fim - inicio);
        cout << "\nTempo de execução da multiplicação: " << duracao.count() << " microssegundos" << endl << endl;


    } else {
        auto inicio = high_resolution_clock::now();

        for (vector<int> vector : matriz){
            int number = 0;
            for (int i=0; i < vetor.size(); i++){
                number = number + vector[i] * vetor[i];
            }
            resultado.push_back(number);
        }

        auto fim = high_resolution_clock::now();
        auto duracao = duration_cast<microseconds>(fim - inicio);
        cout << "\nTempo de execução da multiplicação: " << duracao.count() << " microssegundos";
    }

    return resultado;
}

vector<vector<int>> matrizTransposta(vector<vector<int>> matriz, int linhas, int colunas) {
    vector<vector<int>> nova_matriz;

    for (int i=0; i < colunas; i++){
        vector<int> vetor;
        for (int j=0; j < linhas; j++) {
            vetor.push_back(matriz[j][i]);
        }
        nova_matriz.push_back(vetor);
    }

    return nova_matriz;
}


int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");
    srand(time(0));

    int linhas = rand() % (30 - 20 + 1) + 20, colunas = rand() % (30 - 20 + 1) + 20;
    cout << "LINHAS: " << linhas << endl;
    cout << "COLUNAS: " << colunas << endl << endl;

    vector<int> vetor(colunas, 0);
    vector<vector<int>> matriz(linhas, vector<int>(colunas, 0));

    // DEFININDO VETOR:
    for (int i=0; i < colunas; i++) {
        vetor[i] = rand() % 100;
    }

    // APRESENTANDO VETOR:
    cout << "SEGUE ABAIXO O VETOR: " << endl << endl;
    mostrarVetor(vetor);
    cout << endl;

    // DEFININDO MATRIZ:
    for (int i=0; i < linhas; i++){
        for (int j=0; j < colunas; j++) {
            matriz[i][j] = rand() % 100;
        }
    }

    // APRESENTANDO MATRIZ:
    cout << "SEGUE ABAIXO A MATRIZ: " << endl << endl;
    for (vector<int> vector : matriz) {
        mostrarVetor(vector);
    }
    cout << endl;

    // DEFININDO A MATRIZ TRANSPOSTA: 
    vector<vector<int>> transposta = matrizTransposta(matriz, linhas, colunas);

    // APRESENTANDO A MATRIZ TRANSPOSTA:
    cout << "SEGUE ABAIXO A TRANSPOSTA: " << endl << endl;
    for (vector<int> vector : transposta) {
        mostrarVetor(vector);
    }
    cout << endl;

    // MULTIPLICAÇÃO (MATRIX x VETOR) & (VETOR x MATRIX):
    vector<int> resultado = multiplicadorMatrizes(vetor, matriz, false);
    vector<int> resultado_transposta = multiplicadorMatrizes(vetor, transposta, true);


    // APRESENTAÇÃO DOS RESULTADOS FINAIS...
    mostrarVetor(resultado);
    mostrarVetor(resultado_transposta);

    return 0;
}