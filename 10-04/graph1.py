import matplotlib.pyplot as plt

# Dados fornecidos
numeros = [5000, 10000, 50000, 100000, 500000, 1000000, 2000000, 3000000, 4000000, 5000000]
tempos = [0.000320900, 0.000682700, 0.004489900, 0.010252000, 0.080973000,
          0.193479700, 0.486627600, 0.822329700, 1.233193500, 1.653367400]

# Gráfico de barras
plt.figure(figsize=(9, 6))
plt.bar([str(n) for n in numeros], tempos, color='red')
plt.title('Tempo de Execução x Número N', fontsize=14)
plt.xlabel('N (limite superior para verificação de primos)', fontsize=10)
plt.ylabel('Tempo de execução (segundos)', fontsize=10)
plt.xticks(rotation=0)
plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()

# Exibir gráfico
plt.show()
