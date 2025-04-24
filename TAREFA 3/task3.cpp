#include <iostream>           
#include <iomanip>              
#include <cmath>                
#include <chrono>              

using namespace std;
using namespace chrono;

// FUNÇÃO QUE CALCULA A APROXIMAÇÃO DE π USANDO A SÉRIE DE LEIBNIZ
double calcularPiLeibniz(int iteracoes) {
    double pi = 0.0;  
    for (int i = 0; i < iteracoes; i++) {
        double termo;
        if (i % 2 == 0) {
            termo = 1.0 / (2 * i + 1);  //TERMO POSITIVO SE 'i' FOR PAR
        } else {
            termo = -1.0 / (2 * i + 1); //TERMO NEGATIVO SE 'i' FOR ÍMPAR
        }
        pi = pi + termo;  
    }
    return pi * 4;  
}

int main() {
    const double pi_real = M_PI; // VALOR REAL DE π DEFINIDO NA BIBLIOTECA CMATH
    int iteracoes_lista[] = {
        1000000, 3000000, 5000000, 7000000, 10000000,  
        20000000, 30000000, 40000000, 50000000, 75000000,  
        100000000, 200000000, 300000000, 400000000, 500000000,  
        750000000, 1000000000, 1250000000, 1500000000, 1750000000, 2000000000
    };


    // DEFINE A PRECISÃO DAS CASAS DECIMAIS PARA A SAÍDA
    cout << fixed << setprecision(15);

    // LINHA SUPERIOR DA TABELA
    cout << "+" << string(12, '-') 
         << "+" << string(25, '-') 
         << "+" << string(25, '-') 
         << "+" << string(15, '-') << "+\n";

    // CABEÇALHO DAS COLUNAS
    cout << "|" << setw(12) << "ITERACOES"
         << "|" << setw(25) << "PI APROXIMADO"
         << "|" << setw(25) << "ERRO ABSOLUTO"
         << "|" << setw(15) << "TEMPO (MS)" << "|\n";

    // LINHA DE SEPARAÇÃO
    cout << "+" << string(12, '-') 
         << "+" << string(25, '-') 
         << "+" << string(25, '-') 
         << "+" << string(15, '-') << "+\n";

    // LINHAS COM OS RESULTADOS
    for (int iteracoes : iteracoes_lista) {
        auto inicio = high_resolution_clock::now();

        double pi_aproximado = calcularPiLeibniz(iteracoes); // CALCULA π COM O NÚMERO ATUAL DE ITERAÇÕES

        auto fim = high_resolution_clock::now();

        auto duracao = duration_cast<milliseconds>(fim - inicio).count();

        double erro = abs(pi_real - pi_aproximado);

        cout << "|" << setw(12) << iteracoes
             << "|" << setw(25) << pi_aproximado
             << "|" << setw(25) << erro
             << "|" << setw(15) << duracao << "|\n";
    }

    // LINHA INFERIOR DA TABELA
    cout << "+" << string(12, '-') 
         << "+" << string(25, '-') 
         << "+" << string(25, '-') 
         << "+" << string(15, '-') << "+\n";

    return 0; 
}
