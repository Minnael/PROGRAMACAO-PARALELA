import matplotlib.pyplot as plt

# Dados fornecidos
numeros = [5000, 10000, 50000, 100000, 500000, 1000000, 2000000, 3000000, 4000000, 5000000]

tempos = [
    0.002029500, 0.000204200, 0.000978500, 0.002407400, 0.018011300,
    0.045368900, 0.117165300, 0.203664000, 0.290933400, 0.398610300
]

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
