import matplotlib.pyplot as plt
import numpy as np

# Estilo moderno
plt.style.use('seaborn-v0_8-whitegrid')

# Dados
numeros = [5000, 10000, 50000, 100000, 500000, 1000000, 2000000, 3000000, 4000000, 5000000]
tempos_threads = [
    0.002029500, 0.000204200, 0.000978500, 0.002407400, 0.018011300,
    0.045368900, 0.117165300, 0.203664000, 0.290933400, 0.398610300
]
tempos_sequencial = [
    0.000320900, 0.000682700, 0.004489900, 0.010252000, 0.080973000,
    0.193479700, 0.486627600, 0.822329700, 1.233193500, 1.653367400
]

# Configurações
bar_width = 0.4
indices = np.arange(len(numeros))

fig, ax = plt.subplots(figsize=(12, 7))

# Cores
cor_threads = '#e63946'   # vermelho moderno
cor_sequencial = '#457b9d'  # azul moderno

# Barras
bars1 = ax.bar(indices, tempos_threads, width=bar_width, color=cor_threads, label='Com Threads (OpenMP)')
bars2 = ax.bar(indices + bar_width, tempos_sequencial, width=bar_width, color=cor_sequencial, label='Sequencial')

# Adicionar valores no topo das barras
def add_labels(bars):
    for bar in bars:
        height = bar.get_height()
        ax.annotate(f'{height:.3f}s',
                    xy=(bar.get_x() + bar.get_width() / 2, height),
                    xytext=(0, 5),
                    textcoords="offset points",
                    ha='center', va='bottom',
                    fontsize=9)

add_labels(bars1)
add_labels(bars2)

# Ajustes visuais
ax.set_title('Comparação de Tempo de Execução: Paralelo vs Sequencial', fontsize=17, weight='bold')
ax.set_xlabel('N (limite superior para verificação de primos)', fontsize=13)
ax.set_ylabel('Tempo de execução (segundos)', fontsize=13)
ax.set_xticks(indices + bar_width / 2)
ax.set_xticklabels([f'{n:,}'.replace(",", ".") for n in numeros], rotation=0)

# Legenda com fonte maior
ax.legend(fontsize=13, loc='upper left')

# Remover bordas superiores e direitas
ax.spines['right'].set_visible(False)
ax.spines['top'].set_visible(False)

plt.tight_layout()
plt.show()
