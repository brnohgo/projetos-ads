#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void mostrar(int v[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");
}

int salvar(const char *nome, int v[], int n) {
    FILE *f = fopen(nome, "w");
    if (!f) { printf("Erro ao abrir %s.\n", nome); return 0; }
    for (int i = 0; i < n; i++) fprintf(f, "%d\n", v[i]);
    fclose(f);
    return 1;
}

int ler(int v[]) {
    FILE *f = fopen("dados.txt", "r");
    if (!f) { printf("Crie os dados primeiro (opcao 1).\n"); return 0; }
    int n = 0;
    while (n < MAX && fscanf(f, "%d", &v[n]) == 1) n++;
    fclose(f);
    return n;
}

void trocar(int *a, int *b) { int t = *a; *a = *b; *b = t; }

void bubble(int v[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (v[j] > v[j + 1]) trocar(&v[j], &v[j + 1]);
}

void insertion(int v[], int n) {
    for (int i = 1; i < n; i++) {
        int atual = v[i], j = i - 1;
        while (j >= 0 && v[j] > atual) { v[j + 1] = v[j]; j--; }
        v[j + 1] = atual;
    }
}

void selection(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) if (v[j] < v[menor]) menor = j;
        trocar(&v[i], &v[menor]);
    }
}

void merge(int v[], int aux[], int ini, int meio, int fim) {
    int i = ini, j = meio + 1, k = ini;
    while (i <= meio && j <= fim)
        aux[k++] = (v[i] <= v[j]) ? v[i++] : v[j++];
    while (i <= meio) aux[k++] = v[i++];
    while (j <= fim) aux[k++] = v[j++];
    for (i = ini; i <= fim; i++) v[i] = aux[i];
}

void mergeSort(int v[], int aux[], int ini, int fim) {
    if (ini >= fim) return;
    int meio = ini + (fim - ini) / 2;
    mergeSort(v, aux, ini, meio);
    mergeSort(v, aux, meio + 1, fim);
    merge(v, aux, ini, meio, fim);
}

void quickSort(int v[], int ini, int fim) {
    int i = ini, j = fim, pivo = v[ini + (fim - ini) / 2];
    while (i <= j) {
        while (v[i] < pivo) i++;
        while (v[j] > pivo) j--;
        if (i <= j) { trocar(&v[i], &v[j]); i++; j--; }
    }
    if (ini < j) quickSort(v, ini, j);
    if (i < fim) quickSort(v, i, fim);
}

int ordenar(int v[], int n, int metodo) {
    int aux[MAX];
    switch (metodo) {
        case 1: bubble(v, n); break;
        case 2: insertion(v, n); break;
        case 3: selection(v, n); break;
        case 4: mergeSort(v, aux, 0, n - 1); break;
        case 5: quickSort(v, 0, n - 1); break;
        default: printf("Metodo invalido.\n"); return 0;
    }
    return 1;
}

int escolherMetodo(void) {
    int metodo;
    printf("\n1 - Bubble Sort\n2 - Insertion Sort\n3 - Selection Sort\n");
    printf("4 - Merge Sort\n5 - Quick Sort\nEscolha: ");
    if (scanf("%d", &metodo) != 1) return 0;
    return metodo;
}

int main(void) {
    int v[MAX], n = 0, opcao, metodo;
    do {
        printf("\n=== ATIVIDADE AVALIATIVA 03 ===\n");
        printf("1 - Criar dados.txt\n2 - Ler dados.txt\n");
        printf("3 - Ordenar e salvar ordenado.txt\n");
        printf("4 - Alterar um valor e ordenar novamente\n0 - Sair\nOpcao: ");
        if (scanf("%d", &opcao) != 1) { printf("Entrada invalida.\n"); return 1; }
        switch (opcao) {
            case 1:
                printf("Quantos numeros (1 a %d)? ", MAX);
                if (scanf("%d", &n) != 1 || n < 1 || n > MAX) { printf("Quantidade invalida.\n"); return 1; }
                for (int i = 0; i < n; i++) {
                    printf("Numero %d: ", i + 1);
                    if (scanf("%d", &v[i]) != 1) { printf("Numero invalido.\n"); return 1; }
                }
                if (salvar("dados.txt", v, n)) printf("Arquivo dados.txt criado!\n");
                break;
            case 2:
                n = ler(v);
                if (n > 0) { printf("Dados originais: "); mostrar(v, n); }
                break;
            case 3:
                n = ler(v);
                if (n == 0) break;
                metodo = escolherMetodo();
                if (ordenar(v, n, metodo)) {
                    printf("Dados ordenados: "); mostrar(v, n);
                    if (salvar("ordenado.txt", v, n)) printf("Arquivo ordenado.txt salvo!\n");
                }
                break;
            case 4: {
                n = ler(v);
                if (n == 0) break;
                printf("Dados atuais: "); mostrar(v, n);
                int posicao, novo;
                printf("Posicao para alterar (1 a %d): ", n);
                if (scanf("%d", &posicao) != 1 || posicao < 1 || posicao > n) {
                    printf("Posicao invalida.\n"); break;
                }
                printf("Novo valor: ");
                if (scanf("%d", &novo) != 1) { printf("Valor invalido.\n"); return 1; }
                v[posicao - 1] = novo;
                if (!salvar("dados.txt", v, n)) break;
                metodo = escolherMetodo();
                if (ordenar(v, n, metodo)) {
                    printf("Nova ordem: "); mostrar(v, n);
                    if (salvar("ordenado.txt", v, n)) printf("Arquivos atualizados!\n");
                }
                break;
            }
            case 0: printf("Programa encerrado.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
    return 0;
}
