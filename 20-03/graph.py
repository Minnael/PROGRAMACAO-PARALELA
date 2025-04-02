import matplotlib.pyplot as plt

# Dados fornecidos
tamanhos = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200]
tempos_linhas_ns = [0, 0, 1045000, 1997000, 3001000, 5016000, 5033000, 7961000, 10000000, 12997000, 14995000, 18017000]
tempos_colunas_ns = [0, 0, 1968000, 1999000, 3000000, 5040000, 7000000, 8998000, 11998000, 17985000, 20007000, 21997000]

# Convertendo para milissegundos
tempos_linhas_ms = [t / 1e6 for t in tempos_linhas_ns]
tempos_colunas_ms = [t / 1e6 for t in tempos_colunas_ns]

# Criando o gráfico
plt.figure(figsize=(10, 6))
plt.plot(tamanhos, tempos_linhas_ms, marker='o', linestyle='-', label='Acesso por Linhas')
plt.plot(tamanhos, tempos_colunas_ms, marker='s', linestyle='-', label='Acesso por Colunas')

# Personalizando o gráfico
plt.xlabel("Tamanho da Matriz (NxN)")
plt.ylabel("Tempo (ms)")
plt.title("Tempo de Acesso à Matriz vs. Tamanho da Matriz")
plt.legend()
plt.grid(True)

# Exibindo o gráfico
plt.show()
