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

        for (int j=0; j < vetor.size(); j++) {
            for (int i=0; i < vetor.size(); i++) {
                resultado[j] = resultado[j] + vetor[i] * matriz[j][i];
            }
        }
        
        auto end = high_resolution_clock::now();
        cout << "Case 02: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    } else {
        auto start = high_resolution_clock::now();

        for (int i=0; i < vetor.size(); i++){
            for (int j=0; j < vetor.size(); j++){
                resultado[i] = resultado[i] + matriz[i][j] * vetor[j];
            }
        }

        auto end = high_resolution_clock::now();
        cout << "Case 01: " << duration_cast<milliseconds>(end - start).count() << " ms\n";
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

    int max = 3, min = 3;
    int linhas = rand() % (max - min + 1) + min, colunas = rand() % (max - min + 1) + min;

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
    auto start = high_resolution_clock::now();

    vector<vector<int>> transposta = matrizTransposta(matriz, linhas, colunas);
    
    auto end = high_resolution_clock::now();
    cout << "Case 02: " << duration_cast<milliseconds>(end - start).count() << " ms\n";


    /* APRESENTANDO A MATRIZ TRANSPOSTA:
    cout << "SEGUE ABAIXO A TRANSPOSTA: " << endl << endl;
    for (vector<int> vector : transposta) {
        mostrarVetor(vector);
    }
    cout << endl;
    */
    

    // MULTIPLICACAO (MATRIX x VETOR) & (VETOR x MATRIX):
    vector<int> resultado = multiplicadorMatrizes(vetor, matriz, false);
    vector<int> resultado_transposta = multiplicadorMatrizes(vetor, matriz, true);

    // ESPACO OCUPADO PELAS MATRIZES...
    size_t tamanho_matriz = 0;

    for (const auto& linha : matriz) {
        tamanho_matriz += sizeof(linha) + (linha.size() * sizeof(int));
    }

    cout << "Tamanho total da matriz: " << tamanho_matriz << " bytes" << endl;

    // APRESENTACAO DOS RESULTADOS FINAIS...
    mostrarVetor(resultado);
    mostrarVetor(resultado_transposta);


    return 0;
}