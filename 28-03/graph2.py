import matplotlib.pyplot as plt

# Dados fornecidos (memory-bound)
threads = list(range(1, 33))
tempos_ms = [
    6582, 3465, 2228, 1726, 1557, 1429, 1354, 1273,
    1246, 1216, 1213, 1220, 1197, 1192, 1236, 1213,
    1397, 1237, 1240, 1216, 1226, 1205, 1356, 1522,
    1480, 1525, 1559, 1538, 1595, 1568, 1535, 1588
]

# Criação do gráfico
plt.figure(figsize=(10, 5))

# Barras vermelhas
plt.bar(threads, tempos_ms, color='red', label='Tempo de execução (ms)')

# Linha sobre os topos das barras
plt.plot(threads, tempos_ms, color='black', linewidth=2, marker='o', label='Tendência')

# Personalização
plt.title('Tempo de Execução vs Número de Threads (CPU-bound)', fontsize=13)
plt.xlabel('Número de Threads', fontsize=13)
plt.ylabel('Tempo de Execução (ms)', fontsize=13)
plt.xticks(threads, fontsize=10)
plt.yticks(fontsize=10)
plt.grid(axis='y', linestyle='--', alpha=0.6)
plt.legend(fontsize=12)
plt.tight_layout()

# Exibição
plt.show()
