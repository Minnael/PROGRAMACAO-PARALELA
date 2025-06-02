import matplotlib.pyplot as plt

# Dados
processes = [2, 4, 8, 16, 32]
times = [0.105585, 0.0632338, 0.0359643, 0.0299001, 0.0359585]

plt.figure(figsize=(10,6))
plt.plot(processes, times, marker='o', linestyle='-', color='red')

plt.title('TEMPO DE EXECUÇÃO X NÚMERO DE PROCESSOS\nM=12800, N=1000', fontsize=14)
plt.xlabel('NÚMERO DE PROCESSOS', fontsize=12, fontweight='bold')
plt.ylabel('TEMPO (SEGUNDOS)', fontsize=12, fontweight='bold')

plt.xticks(processes, fontsize=12, fontweight='bold')
plt.yticks(fontsize=12, fontweight='bold')
plt.grid(True, linestyle='--', alpha=0.7)

plt.tight_layout()
plt.show()
