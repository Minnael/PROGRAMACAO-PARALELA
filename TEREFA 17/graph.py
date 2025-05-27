import matplotlib.pyplot as plt

# Dados
processes = [2, 4, 8, 16, 32]
times = [0.0940474, 0.0534772, 0.0439966, 0.0184532, 0.0120588]

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
