import matplotlib.pyplot as plt

def main():
    # Dados fornecidos
    iteracoes = [
        1000000, 3000000, 5000000, 7000000, 10000000,
        20000000, 30000000, 40000000, 50000000, 75000000,
        100000000, 200000000, 300000000, 400000000, 500000000,
        750000000, 1000000000, 1250000000, 1500000000, 1750000000, 2000000000
    ]

    tempo_ms = [
        2, 8, 13, 19, 28, 55, 78, 105, 122, 181,
        237, 476, 702, 928, 1162, 1729, 2350, 3028, 3425, 4009, 4582
    ]

    # Criação do gráfico
    plt.figure(figsize=(10, 5))
    plt.plot(iteracoes, tempo_ms, marker='o', linestyle='-', color='b', label="Tempo (ms)")

    # Aplicando escala logarítmica no eixo x
    plt.xscale("log")

    # Configurações do gráfico
    plt.xlabel("Número de Iterações (escala log)")
    plt.ylabel("Tempo (ms)")
    plt.title("Relação entre Número de Iterações e Tempo de Execução")
    plt.legend()
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)

    # Exibindo o gráfico
    plt.show()

if __name__ == "__main__":
    main()
