import matplotlib.pyplot as plt

# Dados fornecidos
tamanhos = [8, 64, 512, 1024, 4096, 8192, 65536, 131072, 1048576]  # em bytes
tempos = [
    0.000020981021,
    0.000000352592,
    0.000001512440,
    0.000000907705,
    0.000002637904,
    0.000001967965,
    0.000009439237,
    0.000018293484,
    0.000141443389
]  # em segundos

# Criar o gráfico
plt.figure(figsize=(8, 4))
plt.plot(tamanhos, tempos, marker='o', linestyle='-', color='red')
plt.xscale('log')
plt.yscale('log')
plt.xlabel('Tamanho da Mensagem (bytes)')
plt.ylabel('Tempo Médio Ida-Volta (s)')
plt.title('Tempo de Comunicação MPI em Função do Tamanho da Mensagem')
plt.grid(True, which="both", ls="--", linewidth=0.5)
plt.tight_layout()

plt.show()
