import pandas as pd
from tabulate import tabulate
import matplotlib.pyplot as plt

# Tempos de execução com carga proporcional ao número de threads (weak scaling)
tempos = [2.23079, 2.30793, 2.47061, 2.82158, 3.04468, 3.1183]
threads = [1, 2, 4, 8, 16, 32]

# Assumindo 1 milhão de iterações por thread
iteracoes_por_thread = 500
iteracoes_totais = [p * iteracoes_por_thread for p in threads]

# Tempo com 1 thread (base para weak scaling)
T1 = tempos[0]

# Cálculo do Speedup Fraco: T1 / Tp
speedups_weak = [T1 / t for t in tempos]

# Eficiência Fraca: E(p) = S(p) / p
eficiencias_weak = [s / p for s, p in zip(speedups_weak, threads)]

# Tabela de resultados
df_weak = pd.DataFrame({
    'Threads': threads,
    'Iterações Totais': iteracoes_totais,
    'Tempo (s)': [round(t, 5) for t in tempos],
    'Speedup Fraco': [round(s, 2) for s in speedups_weak],
    'Eficiência Fraca (%)': [round(e * 100, 2) for e in eficiencias_weak]
})

# Formatação tabular
df_formatado = pd.DataFrame({
    'Threads': [f'{p:^7}' for p in df_weak['Threads']],
    'Iterações Totais': [f'{it:^18}' for it in df_weak['Iterações Totais']],
    'Tempo (s)': [f'{t:^10.5f}' for t in df_weak['Tempo (s)']],
    'Speedup Fraco': [f'{s:^14.2f}' for s in df_weak['Speedup Fraco']],
    'Eficiência Fraca (%)': [f'{e:^18.2f}' for e in df_weak['Eficiência Fraca (%)']]
})

print(tabulate(df_formatado, headers="keys", tablefmt="fancy_grid", showindex=False))

# Gráficos
plt.figure(figsize=(12, 5))

# Speedup Fraco
plt.subplot(1, 2, 1)
plt.plot(threads, speedups_weak, marker='o', color='black', label='Speedup Fraco')
plt.title('Speedup vs Threads')
plt.xlabel('THREADS')
plt.ylabel('SPEEDUP')
plt.grid(True)
plt.legend()

# Eficiência Fraca
plt.subplot(1, 2, 2)
plt.plot(threads, [e * 100 for e in eficiencias_weak], marker='o', color='red', label='Eficiência Fraca (%)')
plt.title('Eficiência vs Threads (Escalabilidade Fraca)')
plt.xlabel('THREADS')
plt.ylabel('EFICIÊNCIA (%)')
plt.xticks(threads)
plt.ylim(-1, 120)
plt.grid(True)
plt.legend()

plt.tight_layout()
plt.show()

