import pandas as pd
from tabulate import tabulate

# Tempos de execução medidos para diferentes quantidades de threads
tempos = [22.5946, 11.3268, 5.86234, 3.18854, 1.77848, 0.926311]

threads = [1, 2, 4, 8, 16, 32]

# Tempo da execução sequencial (com 1 thread)
T1 = tempos[0]

# -------------------------------
# Cálculo do Speedup Forte
# Fórmula: S(p) = T(1) / T(p)
# Onde:
#   - T(1) é o tempo com 1 thread (sequencial)
#   - T(p) é o tempo com p threads
# -------------------------------
speedups = [T1 / t for t in tempos]

# -------------------------------
# Cálculo da Eficiência Forte
# Fórmula: E(p) = S(p) / p
#          E(p)% = (T(1) / (p * T(p))) * 100
# Onde:
#   - S(p) é o speedup com p threads
#   - p é o número de threads
# -------------------------------
eficiencias = [s / p for s, p in zip(speedups, threads)]

# Criação da tabela de resultados numéricos
df = pd.DataFrame({
    'Threads': threads,
    'Tempo (s)': [round(t, 5) for t in tempos],
    'Speedup': [round(s, 2) for s in speedups],
    'Eficiência (%)': [round(e * 100, 2) for e in eficiencias]  # Eficiência em porcentagem
})

# Formatação dos valores como strings centralizadas para exibição tabular
df_formatado = pd.DataFrame({
    'Threads': [f'{p:^7}' for p in df['Threads']],
    'Tempo (s)': [f'{t:^10.5f}' for t in df['Tempo (s)']],
    'Speedup': [f'{s:^8.2f}' for s in df['Speedup']],
    'Eficiência (%)': [f'{e:^14.2f}' for e in df['Eficiência (%)']]
})

# Impressão da tabela formatada
print(tabulate(df_formatado, headers="keys", tablefmt="fancy_grid", showindex=False))

import matplotlib.pyplot as plt

# Plot do Speedup vs Threads
plt.figure(figsize=(12, 5))

plt.subplot(1, 2, 1)
plt.plot(threads, speedups, marker='s', markerfacecolor='black', markeredgecolor='black', linestyle='-', color='blue', label='Speedup')
plt.title('Speedup vs Threads')
plt.xlabel('Número de Threads')
plt.ylabel('Speedup')
plt.xticks(threads)
plt.grid(True)
plt.legend()

# Plot da Eficiência vs Threads
plt.subplot(1, 2, 2)
plt.plot(threads, [e * 100 for e in eficiencias], marker='s', markerfacecolor='black', markeredgecolor='black', linestyle='-', color='red', label='Eficiência (%)')
plt.title('Eficiência vs Threads')
plt.xlabel('Número de Threads')
plt.ylabel('Eficiência (%)')
plt.xticks(threads)
plt.ylim(74, 102)  # Limite superior um pouco acima de 100% para visualização
plt.grid(True)
plt.legend()

plt.tight_layout()
plt.show()

