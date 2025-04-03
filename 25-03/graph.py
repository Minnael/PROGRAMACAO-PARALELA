import matplotlib.pyplot as plt
import numpy as np

# Novos dados
tamanhos = [10**6, 10**7, 10**8, 2*10**8, 3*10**8]

tempos_O0 = {
    "Inicializacao": [2, 24, 231, 574, 704],
    "Com Dependencia": [3, 24, 249, 603, 763],
    "Sem Dependencia": [2, 25, 200, 433, 619]
}

tempos_O2 = {
    "Inicializacao": [0, 3, 34, 68, 96],
    "Com Dependencia": [0, 5, 35, 70, 102],
    "Sem Dependencia": [1, 5, 36, 72, 104]
}

tempos_O3 = {
    "Inicializacao": [0, 3, 33, 65, 98],
    "Com Dependencia": [0, 4, 34, 69, 101],
    "Sem Dependencia": [0, 5, 35, 73, 104]
}

def format_label(value):
    base = value // (10 ** int(np.log10(value)))
    exp = int(np.log10(value))
    return f'${base} \tx 10^{{{exp}}}$'

def plot_bar_chart(tamanhos, tempos, title):
    x = np.arange(len(tamanhos))
    width = 0.2  # Largura das barras
    
    fig, ax = plt.subplots(figsize=(7, 4.5))
    ax.bar(x - width, tempos["Inicializacao"], width, label="Inicializacao", color='#E6A117')
    ax.bar(x, tempos["Com Dependencia"], width, label="Com Dependencia", color='#FF6700')
    ax.bar(x + width, tempos["Sem Dependencia"], width, label="Sem Dependencia", color='#D40000')
    
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
