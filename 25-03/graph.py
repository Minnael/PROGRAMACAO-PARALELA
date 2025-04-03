import matplotlib.pyplot as plt
import numpy as np

# Dados sem os dois primeiros elementos
tamanhos = [10**6, 10**7, 10**8, 2*10**8, 3*10**8, 4*10**8]

tempos_O0 = {
    "Inicializacao": [9, 62, 581, 656, 984, 1357],
    "Com Dependencia": [10, 63, 639, 731, 1101, 1523],
    "Sem Dependencia": [11, 57, 560, 653, 972, 1296]
}

tempos_O2 = {
    "Inicializacao": [2, 15, 66, 117, 119, 160],
    "Com Dependencia": [2, 20, 98, 192, 172, 228],
    "Sem Dependencia": [4, 21, 164, 317, 294, 384]
}

tempos_O3 = {
    "Inicializacao": [1, 17, 66, 121, 119, 159],
    "Com Dependencia": [2, 26, 98, 193, 174, 229],
    "Sem Dependencia": [3, 44, 162, 312, 288, 395]
}

def format_label(value):
    base = value // (10 ** int(np.log10(value)))
    exp = int(np.log10(value))
    return f'${base} \tx 10^{{{exp}}}$'

def plot_bar_chart(tamanhos, tempos, title):
    x = np.arange(len(tamanhos))
    width = 0.2  # Reduzindo a largura das barras
    
    fig, ax = plt.subplots(figsize=(7, 4.5))  # Reduzindo o tamanho do gráfico
    ax.bar(x - width, tempos["Inicializacao"], width, label="Inicializacao", color='#E6A117')  # Amarelo queimado vivo
    ax.bar(x, tempos["Com Dependencia"], width, label="Com Dependencia", color='#FF6700')  # Laranja queimado vivo
    ax.bar(x + width, tempos["Sem Dependencia"], width, label="Sem Dependencia", color='#D40000')  # Vermelho vivo
    
    ax.set_xlabel("Tamanho do Vetor")
    ax.set_ylabel("Tempo (ms)")
    ax.set_title(title)
    ax.set_xticks(x)
    ax.set_xticklabels([format_label(t) for t in tamanhos])
    ax.legend()
    ax.grid(axis='y', linestyle='--', alpha=0.7)
    
    plt.show()

plot_bar_chart(tamanhos, tempos_O0, "Desempenho com Otimizacao O0")
plot_bar_chart(tamanhos, tempos_O2, "Desempenho com Otimizacao O2")
plot_bar_chart(tamanhos, tempos_O3, "Desempenho com Otimizacao O3")
