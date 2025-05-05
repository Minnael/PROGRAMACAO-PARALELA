<img src="./ms2ex21g.png"
style="width:2.07292in;height:0.85417in" />

> UNIVERSIDADE FEDERAL DO RIO GRANDE DO NORTE DEPARTAMENTO DE ENGENHARIA
> DE COMPUTAÇÃO E AUTOMAÇÃO DCA3703 - PROGRAMAÇÃO PARALELA
>
> **MEMÓRIA** **CACHE**
>
> DISCENTE: MINNAEL CAMPELO DE OLIVEIRA
>
> DOCENTE: SAMUEL XAVIER DE SOUZA
>
> NATAL/RN
>
> 2025

**1.** **PROBLEMÁTICA**

A eficiência da multiplicação de matriz por vetor (MxV) é diretamente
influenciada pelo padrão de acesso à memória, especialmente devido à
hierarquia de cache dos processadores modernos. Dependendo de como os
elementos da matriz são acessados — linha por linha ou coluna por coluna
— o tempo de execução pode variar significativamente.

Este estudo investiga duas abordagens para a multiplicação MxV:

> 1\. **Acesso** **por** **Linhas**: a matriz é percorrida linha por
> linha (linha externa, coluna interna).
>
> 2\. **Acesso** **por** **Colunas**: a matriz é percorrida coluna por
> coluna (coluna externa, linha interna).

Espera-se que o acesso por linhas seja mais eficiente devido à
**localidade** **espacial**, pois os elementos armazenados
sequencialmente na memória são carregados em blocos para a cache. Já o
acesso por colunas pode resultar em acessos menos eficientes, pois
envolve saltos na memória que podem aumentar as falhas de cache e,
consequentemente, o tempo de execução.

O objetivo deste experimento é identificar a partir de que tamanho de
matriz ocorre uma diferença significativa de desempenho entre os dois
métodos e relacionar essa diferença com os princípios de funcionamento
da cache, analisando como a organização da memória afeta a eficiência
computacional.

**2.** **DESENVOLVIMENTO**

**2.1.** **LINGUAGENS** **E** **BIBLIOTECAS**

O código foi implementado em **C++**, uma linguagem de programação
amplamente utilizada em tarefas que exigem alto desempenho e controle
sobre os recursos de hardware. Sua eficiência na manipulação de memória
e otimização de tempo de execução torna-a uma escolha ideal para
operações matemáticas intensivas, como a multiplicação de matrizes. O
C++ permite uma maior flexibilidade no gerenciamento de memória,
essencial para este tipo de análise, onde o acesso eficiente à memória
pode impactar significativamente o desempenho.

O código desenvolvido visa realizar a multiplicação de uma matriz por um
vetor de duas formas distintas, com o objetivo de medir o impacto do
padrão de acesso à memória no tempo de execução. O código foi
implementado em **C++** utilizando a biblioteca \<chrono\> para medir o
tempo de execução, e a estrutura de dados \<vector\> foi escolhida para
armazenar tanto a matriz quanto o vetor.

**2.2** **ESTRUTURA** **PRINCIPAL** **DO** **CÓDIGO**

O código segue estruturado nas seguintes partes fundamentais: Definição
e Inicialização de Dados, Multiplicação da Matriz pelo Vetor, Cálculo do
Tempo de Execução. No entanto, para uma melhor avaliação o código
completo está disponível no
<u>[**GITHUB**](https://github.com/Minnael/PROGRAMACAO-PARALELA/tree/master/20-03).</u>

**2.2.1.** **DEFINIÇÃO** **E** **INICIALIZAÇÃO** **DE**
**DADOS**<img src="./gubvm2cf.png"
style="width:5.09375in;height:1.375in" /><img src="./sf2zemt3.png"
style="width:6.69792in;height:1.04167in" />

A primeira parte do código se dedica a configurar o vetor e a matriz,
ambos de tamanhos variáveis, de acordo com os valores definidos no vetor
testes. Este vetor contém os tamanhos das matrizes que serão testadas,
variando de 100 a 1200 elementos em incrementos de 100.

Para cada valor presente em testes, o código gera uma matriz quadrada de
tamanho NxN, onde N é o valor do teste atual. A matriz é preenchida com
valores fixos (100, no caso), assim como o vetor. A alocação de memória
é feita utilizando o tipo vector\<int\> para o vetor e
vector\<vector\<int\>\> para a matriz.

**2.2.2.** **MULTIPLICAÇÃO** **DA** **MATRIZ** **PELO** **VETOR**

O cálculo da multiplicação é feito dentro da função
multiplicadorMatrizes(). Nessa função, a multiplicação é implementada de
duas maneiras, controladas pelo parâmetro variante:

> ● **Acesso** **por** **Linhas** **(Linha** **Externa,** **Coluna**
> **Interna)**: Neste padrão, as linhas da matriz são percorridas
> primeiro, e para cada linha, percorre-se a coluna correspondente.
>
> ● **Acesso** **por** **Colunas** **(Coluna** **Externa,** **Linha**
> **Interna)**: Nesse padrão, as colunas são percorridas primeiro, o que
> pode resultar em um acesso menos eficiente devido ao layout de
> memória.
>
> Figura 01 - Multiplicação por linhas.

A escolha entre um acesso ou outro é feita através da variável variante,
que é passada como argumento para a função. Se a variante for falsa, a
multiplicação é feita com acesso por linhas. Caso contrário, o acesso é
feito por colunas.

**3.** **CÁLCULO** **DO** **TEMPO** **DE** **EXECUÇÃO**

O tempo de execução de cada versão da multiplicação (por linhas e por
colunas) é medido com a ajuda da biblioteca \<chrono\>. O
high_resolution_clock::now() é utilizado para capturar o momento de
início e de término de cada operação, e a diferença entre esses tempos é
convertida para **nanosegundos**.

> Figura 02 - Medição do tempo de execução de uma determinada
> multiplicação.

**3.** **CONCLUSÃO**<img src="./fwmvegz4.png"
style="width:6.22917in;height:3.71875in" />

**3.1** **RESULTADOS** **ESPERADOS**

Com base na explicação do que foi pedido, espera-se que o tempo de
execução da multiplicação de matriz por vetor seja mais eficiente para o
caso de acesso por linhas, devido à melhor utilização da localidade
espacial da memória. Em contrastes, o acesso por colunas pode resultar
em maior número de falhas de cache e, portanto, maior tempo de execução.

**3.2** **ANÁLISE** **DE** **DESEMPENHO**

O desempenho do código foi analisado observando os tempos de execução
para diferentes tamanhos de matrizes. Espera-se que, à medida que o
tamanho da matriz aumenta, as diferenças entre os dois tipos de acesso
se tornem mais evidentes, especialmente em matrizes maiores, quando as
falhas de cache se tornam mais frequentes. A análise gráfica dessas
medições segue abaixo e permite identificar em que ponto o desempenho se
desvia significativamente entre as duas abordagens.

> Figura 03 - Gráfico responsável pela comparação de acesso.

Em conclusão, os resultados obtidos por meio das medições de tempo de
execução, apresentados no gráfico gerado em Python, confirmaram as
expectativas iniciais. O gráfico evidenciou que o acesso por linhas,
devido à melhor utilização da localidade espacial da memória, resultou
em tempos de execução mais rápidos em comparação com o acesso por
colunas, especialmente conforme o tamanho da matriz aumentou. Esses
resultados validam a teoria de que o padrão de acesso à memória tem um
impacto significativo no desempenho, especialmente em operações com
grandes matrizes, corroborando a análise teórica realizada.
