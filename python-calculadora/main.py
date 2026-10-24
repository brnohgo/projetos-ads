def ler_numero(rotulo: str) -> float:
    while True:
        try:
            return float(input(rotulo).replace(',', '.'))
        except ValueError:
            print('Valor inválido. Digite um número, por exemplo 12 ou 3,5.')

def main() -> None:
    operacoes = {'1': ('adição', lambda a, b: a + b), '2': ('subtração', lambda a, b: a - b), '3': ('multiplicação', lambda a, b: a * b), '4': ('divisão', lambda a, b: a / b)}
    while True:
        print('\n=== CALCULADORA ===\n1. Adição\n2. Subtração\n3. Multiplicação\n4. Divisão\n0. Sair')
        escolha = input('Escolha: ').strip()
        if escolha == '0':
            print('Até mais!')
            break
        if escolha not in operacoes:
            print('Opção inválida.')
            continue
        a = ler_numero('Primeiro número: ')
        b = ler_numero('Segundo número: ')
        nome, funcao = operacoes[escolha]
        if escolha == '4' and b == 0:
            print('Não é possível dividir por zero.')
            continue
        print(f'Resultado da {nome}: {funcao(a, b):g}')

if __name__ == '__main__':
    main()
