import matplotlib.pyplot as plt

def scientific_label(num):
    # Formata o número em notação científica do tipo "1.0x10^6"
    base, exponent = f"{num:.1e}".split("e")
    exponent = exponent.replace("+", "")
    return f"{base}x10^{int(exponent)}"

def main():
    # Dados fornecidos
    iteracoes = [
        1000000, 3000000, 5000000, 7000000, 10000000,
        20000000, 30000000, 40000000, 50000000, 75000000,
        100000000, 200000000, 300000000, 400000000, 500000000,
        750000000, 1000000000, 1250000000, 1500000000, 1750000000, 2000000000
    ]
    
    erro_absoluto = [
        0.000001000000019, 0.000000333333420, 0.000000200000013, 0.000000142857193,
        0.000000100000002, 0.000000049999976, 0.000000033333160, 0.000000024999329,
        0.000000019999542, 0.000000013333398, 0.000000010000467, 0.000000005000385,
        0.000000003333770, 0.000000002500735, 0.000000002000535, 0.000000001334657,
        0.000000001001743, 0.000000000750154, 0.000000000320593, 0.000000000650555,
        0.000000004915388
    ]
    
    # Geração dos labels em notação científica customizada
    labels_iteracoes = [scientific_label(it) for it in iteracoes]
    
    # Criação do gráfico de barras
    plt.figure(figsize=(10, 5))
    plt.bar(labels_iteracoes, erro_absoluto, color='red')
    
    # Configurações do gráfico
    plt.xlabel("Número de Iterações")
    plt.ylabel("Erro Absoluto")
    plt.title("Relação entre Número de Iterações e Erro Absoluto")
    
    # Aplicando escala logarítmica no eixo y para melhor visualização dos erros
    plt.yscale("log")
    
    plt.xticks(rotation=45)
    plt.grid(axis='y', linestyle="--", linewidth=0.5, alpha=0.7)
    plt.tight_layout()
    
    # Exibindo o gráfico
    plt.show()

if __name__ == "__main__":
    main()
