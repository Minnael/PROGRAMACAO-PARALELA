import matplotlib.pyplot as plt

# Dados fornecidos (memory-bound)
threads = list(range(1, 33))
tempos_ms = [
    739, 450, 367, 305, 272, 220, 195, 213,
    216, 222, 203, 250, 214, 213, 199, 184,
    200, 198, 189, 194, 198, 197, 203, 199,
    190, 196, 204, 198, 189, 192, 193, 194
]

# Criação do gráfico
plt.figure(figsize=(10, 5))

# Barras vermelhas
plt.bar(threads, tempos_ms, color='red', label='Tempo de execução (ms)')

# Linha sobre os topos das barras
plt.plot(threads, tempos_ms, color='black', linewidth=2, marker='o', label='Tendência')

# Personalização
plt.title('Tempo de Execução vs Número de Threads (Memory-bound)', fontsize=13)
plt.xlabel('Número de Threads', fontsize=13)
plt.ylabel('Tempo de Execução (ms)', fontsize=13)
plt.xticks(threads, fontsize=10)
plt.yticks(fontsize=10)
plt.grid(axis='y', linestyle='--', alpha=0.6)
plt.legend(fontsize=12)
plt.tight_layout()

# Exibição
plt.show()
