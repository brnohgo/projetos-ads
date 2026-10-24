#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_TEXTO 500

void limpar_linha(void) { int c; while ((c = getchar()) != '\n' && c != EOF) {} }
void cifra_cesar(const char *origem, char *destino, int deslocamento) {
    deslocamento = ((deslocamento % 26) + 26) % 26;
    for (size_t i = 0; origem[i] != '\0'; i++) {
        unsigned char c = (unsigned char)origem[i];
        if (c >= 'A' && c <= 'Z') destino[i] = (char)('A' + (c - 'A' + deslocamento) % 26);
        else if (c >= 'a' && c <= 'z') destino[i] = (char)('a' + (c - 'a' + deslocamento) % 26);
        else destino[i] = (char)c;
    }
    destino[strlen(origem)] = '\0';
}
void executar_cifra(void) {
    char texto[MAX_TEXTO], resultado[MAX_TEXTO]; int deslocamento, opcao;
    printf("\n1 - Codificar\n2 - Decodificar\nEscolha: ");
    if (scanf("%d", &opcao) != 1 || (opcao != 1 && opcao != 2)) { puts("Opcao invalida."); limpar_linha(); return; }
    printf("Deslocamento (numero inteiro): ");
    if (scanf("%d", &deslocamento) != 1) { puts("Numero invalido."); limpar_linha(); return; }
    limpar_linha(); printf("Digite a mensagem: ");
    if (!fgets(texto, sizeof texto, stdin)) return;
    texto[strcspn(texto, "\n")] = '\0';
    cifra_cesar(texto, resultado, opcao == 1 ? deslocamento : -deslocamento);
    printf("Resultado: %s\n", resultado);
}
void executar_pa(void) {
    long long primeiro, razao, n;
    printf("Primeiro termo: "); if (scanf("%lld", &primeiro) != 1) { puts("Valor invalido."); limpar_linha(); return; }
    printf("Razao: "); if (scanf("%lld", &razao) != 1) { puts("Valor invalido."); limpar_linha(); return; }
    printf("Quantidade de termos (1 a 1000000): "); if (scanf("%lld", &n) != 1 || n < 1 || n > 1000000) { puts("Quantidade invalida."); limpar_linha(); return; }
    printf("PA: "); for (long long i=0; i<n; i++) printf("%lld%s", primeiro + i * razao, i + 1 == n ? "\n" : ", ");
    printf("Soma dos %lld termos: %lld\n", n, n * (2 * primeiro + (n - 1) * razao) / 2);
}
int main(void) {
    int opcao;
    do {
        puts("\n=== ESTUDOS EM C: CRIPTOGRAFIA E PA ===");
        puts("1. Cifra de Cesar\n2. Progressao aritmetica e soma\n0. Sair");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) { puts("Entrada invalida."); limpar_linha(); continue; }
        switch (opcao) { case 1: executar_cifra(); break; case 2: executar_pa(); break; case 0: puts("Programa encerrado."); break; default: puts("Opcao inexistente."); }
    } while (opcao != 0);
    return 0;
}
