/*
 * SIDER FIXADORES - Atividade Avaliativa 04
 * Sistema de loja e gerenciamento de produtos em linguagem C.
 * Usa struct, ponteiros, arquivos texto e Bubble Sort.
 * Compilar: gcc -std=c11 -Wall -Wextra SIDER_FIXADORES_ENTREGA_FINAL.c -o sider_fixadores.exe
 */
/* stdio.h: printf, fgets, fopen, fprintf e fclose (tela e arquivos). */
/* Inclui a biblioteca stdio.h usada pelas funcoes do programa. */
#include <stdio.h>
/* stdlib.h: exit, usado quando a entrada termina. */
/* Inclui a biblioteca stdlib.h usada pelas funcoes do programa. */
#include <stdlib.h>
/* string.h: strlen, strcmp, memcpy, strchr e strcspn (textos e vetores). */
/* Inclui a biblioteca string.h usada pelas funcoes do programa. */
#include <string.h>
/* ctype.h: tolower, para comparar nomes sem diferenciar maiusculas. */
/* Inclui a biblioteca ctype.h usada pelas funcoes do programa. */
#include <ctype.h>

/* Define a constante MAX_PRODUTOS usada para padronizar limites ou nomes de arquivos. */
#define MAX_PRODUTOS 500
/* Define a constante TAM_NOME usada para padronizar limites ou nomes de arquivos. */
#define TAM_NOME 60
/* Define a constante TAM_CATEGORIA usada para padronizar limites ou nomes de arquivos. */
#define TAM_CATEGORIA 40
/* Define a constante TAM_FORNECEDOR usada para padronizar limites ou nomes de arquivos. */
#define TAM_FORNECEDOR 60
/* Define a constante ARQUIVO usada para padronizar limites ou nomes de arquivos. */
#define ARQUIVO "produtos.txt"
/* Define a constante ARQUIVO_ID usada para padronizar limites ou nomes de arquivos. */
#define ARQUIVO_ID "ultimo_id.txt"
/* Define a constante TEMPORARIO usada para padronizar limites ou nomes de arquivos. */
#define TEMPORARIO "produtos.tmp"
/* Define a constante CSV usada para padronizar limites ou nomes de arquivos. */
#define CSV "produtos.csv"

/* Cada Produto e um registro com as seis colunas da tabela do enunciado.
   O vetor Produto lista[] guarda ate MAX_PRODUTOS registros na memoria. */
typedef struct {
    int id;                         /* Identificador numerico automatico. */
    char nome[TAM_NOME];            /* Nome do produto, como Parafuso Sextavado M8. */
    char categoria[TAM_CATEGORIA];  /* Tipo: Parafusos, Porcas, Arruelas etc. */
    double preco;                   /* Valor unitario em reais, com casas decimais. */
    int quantidade;                 /* Quantidade disponivel em estoque. */
    char fornecedor[TAM_FORNECEDOR];/* Nome do fornecedor do produto. */
} Produto;

/* Remove a quebra de linha que fgets pode guardar. */
/* Inicia a funcao retirarQuebra, que executa uma tarefa do sistema. */
void retirarQuebra(char *texto) {
    /* Substitui a quebra de linha pelo fim da string em C. */
    texto[strcspn(texto, "\n")] = '\0';
/* Encerra este bloco de instrucoes. */
}

/* Le uma linha com seguranca, inclusive quando o usuario digita demais. */
/* Inicia a funcao lerTexto, que executa uma tarefa do sistema. */
void lerTexto(const char *mensagem, char *destino, size_t tamanho) {
    /* Cria uma variavel inteira para guardar o resultado desta etapa. */
    int c;
    /* Inicia um bloco que sera repetido pelo menos uma vez. */
    do {
        /* Mostra na tela os valores indicados, respeitando o formato definido. */
        printf("%s", mensagem);
        /* Testa esta condicao para decidir se a operacao pode continuar. */
        if (!fgets(destino, (int)tamanho, stdin)) {
            /* Apresenta esta mensagem ao usuario no terminal. */
            puts("Entrada encerrada.");
            /* Encerra o programa porque a entrada nao esta mais disponivel. */
            exit(0);
        /* Encerra este bloco de instrucoes. */
        }
        /* Testa esta condicao para decidir se a operacao pode continuar. */
        if (!strchr(destino, '\n')) {
            /* Descarta caracteres restantes e avisa quando a entrada ultrapassa o limite. */
            int excedeu = 0;
            while ((c = getchar()) != '\n' && c != EOF) excedeu = 1;
            if (excedeu) {
                puts("Texto muito longo para este campo. Digite um texto menor.");
                continue;
            }
        /* Encerra este bloco de instrucoes. */
        }
        /* Remove a quebra de linha que pode ter sido guardada pelo fgets. */
        retirarQuebra(destino);
        /* Testa esta condicao para decidir se a operacao pode continuar. */
        if (strlen(destino) == 0) puts("O campo nao pode ficar vazio.");
        /* Testa esta segunda condicao caso a anterior nao seja verdadeira. */
        else if (strchr(destino, '|') || strchr(destino, ';') || strchr(destino, '"'))
            /* Apresenta esta mensagem ao usuario no terminal. */
            puts("Nao use os caracteres |, ; ou aspas.");
        /* Executa a alternativa quando a verificacao anterior nao foi atendida. */
        else return;
    /* Repete a leitura ate receber um valor valido. */
    } while (1);
/* Encerra este bloco de instrucoes. */
}

/* Le um numero inteiro e rejeita letras ou entradas incompletas. */
/* Inicia a funcao lerInteiro, que executa uma tarefa do sistema. */
int lerInteiro(const char *mensagem, int minimo, int maximo) {
    /* Reserva espaco para armazenar o texto informado pelo usuario. */
    char linha[100], extra;
    /* Cria uma variavel inteira para guardar o resultado desta etapa. */
    int valor;
    /* Repete a verificacao enquanto a condicao continuar verdadeira. */
    while (1) {
        /* Le o texto digitado, respeitando o tamanho maximo do campo. */
        lerTexto(mensagem, linha, sizeof(linha));
        /* Testa esta condicao para decidir se a operacao pode continuar. */
        if (sscanf(linha, " %d %c", &valor, &extra) == 1 && valor >= minimo && valor <= maximo)
            /* Devolve este valor para a funcao que fez a chamada. */
            return valor;
        /* Mostra na tela os valores indicados, respeitando o formato definido. */
        printf("Digite um numero inteiro entre %d e %d.\n", minimo, maximo);
    /* Encerra este bloco de instrucoes. */
    }
/* Encerra este bloco de instrucoes. */
}

/* Le precos com ponto ou virgula decimal. */
/* Inicia a funcao lerPreco, que executa uma tarefa do sistema. */
double lerPreco(const char *mensagem) {
    /* Reserva espaco para armazenar o texto informado pelo usuario. */
    char linha[100], extra;
    /* Cria uma variavel decimal para guardar o preco ou total da compra. */
    double valor;
    /* Repete a verificacao enquanto a condicao continuar verdadeira. */
    while (1) {
        /* Le o texto digitado, respeitando o tamanho maximo do campo. */
        lerTexto(mensagem, linha, sizeof(linha));
        /* Repete a instrucao para percorrer os produtos ou caracteres necessarios. */
        for (size_t i = 0; linha[i]; i++) if (linha[i] == ',') linha[i] = '.';
        /* Testa esta condicao para decidir se a operacao pode continuar. */
        if (sscanf(linha, " %lf %c", &valor, &extra) == 1 && valor >= 0 && valor <= 100000000)
            /* Devolve este valor para a funcao que fez a chamada. */
            return valor;
        /* Apresenta esta mensagem ao usuario no terminal. */
        puts("Digite um preco valido, como 2.50 ou 2,50.");
    /* Encerra este bloco de instrucoes. */
    }
/* Encerra este bloco de instrucoes. */
}

/* Compara textos sem diferenciar letras maiusculas de minusculas. */
/* Inicia a funcao compararTexto, que executa uma tarefa do sistema. */
int compararTexto(const char *a, const char *b) {
    /* Repete a verificacao enquanto a condicao continuar verdadeira. */
    while (*a && *b) {
        /* Cria uma variavel inteira para guardar o resultado desta etapa. */
        int diferenca = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        /* Testa esta condicao para decidir se a operacao pode continuar. */
        if (diferenca) return diferenca;
        /* Avanca para o proximo caractere dos dois textos comparados. */
        a++; b++;
    /* Encerra este bloco de instrucoes. */
    }
    /* Devolve este valor para a funcao que fez a chamada. */
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
/* Encerra este bloco de instrucoes. */
}

/* Busca uma palavra ou parte dela, ignorando maiusculas/minusculas. */
/* Inicia a funcao contemTexto, que executa uma tarefa do sistema. */
int contemTexto(const char *texto, const char *busca) {
    /* Repete a instrucao para percorrer os produtos ou caracteres necessarios. */
    for (size_t i = 0; texto[i]; i++) {
        /* Executa esta instrucao como parte da operacao atual. */
        size_t j = 0;
        /* Repete a verificacao enquanto a condicao continuar verdadeira. */
        while (busca[j] && texto[i + j] &&
               /* Continua a expressao iniciada na linha anterior. */
               tolower((unsigned char)texto[i + j]) == tolower((unsigned char)busca[j])) j++;
        /* Testa esta condicao para decidir se a operacao pode continuar. */
        if (!busca[j]) return 1;
    /* Encerra este bloco de instrucoes. */
    }
    /* Devolve este valor para a funcao que fez a chamada. */
    return 0;
/* Encerra este bloco de instrucoes. */
}

/* Procura um produto pelo ID e devolve sua posicao, ou -1. */
/* Inicia a funcao indicePorId, que executa uma tarefa do sistema. */
int indicePorId(const Produto *lista, int total, int id) {
    /* Repete a instrucao para percorrer os produtos ou caracteres necessarios. */
    for (int i = 0; i < total; i++) if (lista[i].id == id) return i;
    /* Informa que nenhum produto possui o ID procurado. */
    return -1;
/* Encerra este bloco de instrucoes. */
}

/* Impede nomes duplicados; ignorarId permite manter o nome ao alterar. */
/* Inicia a funcao nomeExiste, que executa uma tarefa do sistema. */
int nomeExiste(const Produto *lista, int total, const char *nome, int ignorarId) {
    /* Repete a instrucao para percorrer os produtos ou caracteres necessarios. */
    for (int i = 0; i < total; i++)
        /* Testa esta condicao para decidir se a operacao pode continuar. */
        if (lista[i].id != ignorarId && compararTexto(lista[i].nome, nome) == 0) return 1;
    /* Devolve este valor para a funcao que fez a chamada. */
    return 0;
/* Encerra este bloco de instrucoes. */
}

/* Consulta o maior ID do estoque e o contador persistente.
   Assim, excluir o ultimo produto nao libera seu numero para reutilizacao. */
int recuperarUltimoId(const Produto *lista, int total) {
    int maior = 0, salvo = 0;
    for (int i = 0; i < total; i++)
        if (lista[i].id > maior) maior = lista[i].id;
    FILE *arquivo = fopen(ARQUIVO_ID, "r");
    if (arquivo) {
        if (fscanf(arquivo, "%d", &salvo) == 1 && salvo > maior) maior = salvo;
        fclose(arquivo);
    }
    return maior;
}

/* Grava o maior ID utilizado, mesmo se o produto for excluido depois.
   A troca do arquivo temporario evita gravacoes parcialmente escritas. */
int registrarUltimoId(int id) {
    FILE *arquivo = fopen("ultimo_id.tmp", "w");
    if (!arquivo) return 0;
    int escreveu = fprintf(arquivo, "%d\n", id) >= 0;
    int fechou = fclose(arquivo) == 0;
    if (!escreveu || !fechou) {
        remove("ultimo_id.tmp");
        return 0;
    }
    if (rename("ultimo_id.tmp", ARQUIVO_ID) == 0) return 1;
    /* No Windows, o destino existente pode impedir rename. */
    /* Apaga o arquivo temporario que nao sera mais utilizado. */
    remove("ultimo_id.bak");
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (rename(ARQUIVO_ID, "ultimo_id.bak") != 0) {
        /* Apaga o arquivo temporario que nao sera mais utilizado. */
        remove("ultimo_id.tmp"); return 0;
    /* Encerra este bloco de instrucoes. */
    }
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (rename("ultimo_id.tmp", ARQUIVO_ID) == 0) {
        /* Apaga o arquivo temporario que nao sera mais utilizado. */
        remove("ultimo_id.bak"); return 1;
    /* Encerra este bloco de instrucoes. */
    }
    /* Renomeia o arquivo indicado para concluir ou restaurar a gravacao. */
    rename("ultimo_id.bak", ARQUIVO_ID);
    /* Apaga o arquivo temporario que nao sera mais utilizado. */
    remove("ultimo_id.tmp");
    /* Devolve este valor para a funcao que fez a chamada. */
    return 0;
/* Encerra este bloco de instrucoes. */
}

/* Le o arquivo de texto; cada produto ocupa uma linha separada por |. */
/* Inicia a funcao carregar, que executa uma tarefa do sistema. */
int carregar(Produto *lista) {
    /* Abre um arquivo e guarda sua referencia para leitura ou gravacao. */
    FILE *arquivo = fopen(ARQUIVO, "r");
    /* Reserva espaco para armazenar o texto informado pelo usuario. */
    char linha[400];
    /* Inicia em zero a quantidade de produtos encontrados no arquivo. */
    int total = 0;
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (!arquivo) return 0; /* Primeira execucao: ainda nao existe arquivo. */
    /* Repete a verificacao enquanto a condicao continuar verdadeira. */
    while (total < MAX_PRODUTOS && fgets(linha, sizeof(linha), arquivo)) {
        /* Cria um registro do tipo Produto para guardar os dados desta etapa. */
        Produto p;
        /* Testa esta condicao para decidir se a operacao pode continuar. */
        if (sscanf(linha, "%d|%59[^|]|%39[^|]|%lf|%d|%59[^\n]",
                   /* Continua a expressao iniciada na linha anterior. */
                   &p.id, p.nome, p.categoria, &p.preco, &p.quantidade, p.fornecedor) == 6 &&
            /* Executa esta instrucao como parte da operacao atual. */
            p.id > 0 && p.preco >= 0 && p.quantidade >= 0 &&
            /* Executa esta instrucao como parte da operacao atual. */
            indicePorId(lista, total, p.id) == -1 &&
            /* Executa esta instrucao como parte da operacao atual. */
            !nomeExiste(lista, total, p.nome, -1)) {
            /* Atualiza este produto na posicao indicada do vetor. */
            lista[total++] = p;
        /* Encerra este bloco de instrucoes. */
        }
    /* Encerra este bloco de instrucoes. */
    }
    /* Fecha o arquivo depois da leitura ou gravacao. */
    fclose(arquivo);
    /* Devolve a quantidade de produtos carregados do arquivo. */
    return total;
/* Encerra este bloco de instrucoes. */
}

/* Salva em arquivo temporario e so depois substitui o original. */
/* Inicia a funcao salvar, que executa uma tarefa do sistema. */
int salvar(const Produto *lista, int total) {
    /* Abre um arquivo e guarda sua referencia para leitura ou gravacao. */
    FILE *arquivo = fopen(TEMPORARIO, "w");
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (!arquivo) { perror("Erro ao criar arquivo temporario"); return 0; }
    /* Repete a instrucao para percorrer os produtos ou caracteres necessarios. */
    for (int i = 0; i < total; i++) {
        /* Cria um ponteiro de leitura para o produto nesta posicao. */
        const Produto *p = &lista[i];
        /* Testa esta condicao para decidir se a operacao pode continuar. */
        if (fprintf(arquivo, "%d|%s|%s|%.2f|%d|%s\n", p->id, p->nome,
                    /* Atribui ou atualiza este valor para manter os dados do produto corretos. */
                    p->categoria, p->preco, p->quantidade, p->fornecedor) < 0) {
            /* Fecha o arquivo depois da leitura ou gravacao. */
            fclose(arquivo); remove(TEMPORARIO); return 0;
        /* Encerra este bloco de instrucoes. */
        }
    /* Encerra este bloco de instrucoes. */
    }
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (fclose(arquivo) != 0) { remove(TEMPORARIO); return 0; }
    /* Em Windows, renomear sobre um arquivo existente pode falhar.
       Nesse caso fazemos uma copia de seguranca antes de substituir. */
    if (rename(TEMPORARIO, ARQUIVO) == 0) return 1;
    remove("produtos.bak");
    if (rename(ARQUIVO, "produtos.bak") != 0) {
        remove(TEMPORARIO); return 0;
    }
    if (rename(TEMPORARIO, ARQUIVO) == 0) {
        remove("produtos.bak"); return 1;
    }
    rename("produtos.bak", ARQUIVO);
    remove(TEMPORARIO);
    return 0;
}

/* Mostra a tabela com as mesmas seis colunas do exemplo do Blackboard.
   %-Ns alinha textos a esquerda e %f imprime precos com duas casas. */
void cabecalho(void) {
    puts("---------------------------------------------------------------------------------------------------------------");
    printf("%-4s | %-27s | %-17s | %10s | %5s | %-25s\n",
           "ID", "PRODUTO", "CATEGORIA", "PRECO", "QTD", "FORNECEDOR");
    puts("---------------------------------------------------------------------------------------------------------------");
}
void linhaProduto(const Produto *p) {
    printf("%-4d | %-27.27s | %-17.17s | R$ %7.2f | %5d | %-25.25s\n",
           p->id, p->nome, p->categoria, p->preco, p->quantidade, p->fornecedor);
}
void listar(const Produto *lista, int total) {
    if (total == 0) { puts("Nenhum produto cadastrado."); return; }
    cabecalho();
    for (int i = 0; i < total; i++) linhaProduto(&lista[i]);
    puts("---------------------------------------------------------------------------------------------------------------");
    printf("Total: %d produto(s).\n", total);
}

/* Solicita todos os dados de um produto. */
/* Inicia a funcao preencher, que executa uma tarefa do sistema. */
void preencher(Produto *p) {
    /* Le o texto digitado, respeitando o tamanho maximo do campo. */
    lerTexto("Nome: ", p->nome, sizeof(p->nome));
    /* Le o texto digitado, respeitando o tamanho maximo do campo. */
    lerTexto("Categoria: ", p->categoria, sizeof(p->categoria));
    /* Atribui ou atualiza este valor para manter os dados do produto corretos. */
    p->preco = lerPreco("Preco (R$): ");
    /* Atribui ou atualiza este valor para manter os dados do produto corretos. */
    p->quantidade = lerInteiro("Quantidade: ", 0, 1000000);
    /* Le o texto digitado, respeitando o tamanho maximo do campo. */
    lerTexto("Fornecedor: ", p->fornecedor, sizeof(p->fornecedor));
/* Encerra este bloco de instrucoes. */
}

/* Cadastra e grava, mantendo os dados anteriores se a gravacao falhar.
   int *total e int *ultimoId sao ponteiros: permitem atualizar os valores
   originais recebidos de main, usando *total e *ultimoId. */
void inserir(Produto *lista, int *total, int *ultimoId) {
    if (*total >= MAX_PRODUTOS) { puts("Limite de produtos atingido."); return; }
    Produto novo;
    if (*ultimoId >= 2000000000) { puts("Limite de IDs atingido."); return; }
    novo.id = *ultimoId + 1;
    preencher(&novo);
    if (nomeExiste(lista, *total, novo.nome, -1)) {
        puts("Ja existe um produto com esse nome. Cadastro cancelado."); return;
    }
    /* Reserva o ID antes de salvar o produto para impedir sua reutilizacao. */
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (!registrarUltimoId(novo.id)) {
        /* Apresenta esta mensagem ao usuario no terminal. */
        puts("Erro ao registrar ID. Cadastro cancelado."); return;
    /* Encerra este bloco de instrucoes. */
    }
    *ultimoId = novo.id;
    /* Atualiza este produto na posicao indicada do vetor. */
    lista[*total] = novo;
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (salvar(lista, *total + 1)) {
        /* Executa esta instrucao como parte da operacao atual. */
        (*total)++; *ultimoId = novo.id;
        /* Mostra na tela os valores indicados, respeitando o formato definido. */
        printf("Produto cadastrado! ID automatico: %d\n", novo.id);
    /* Executa a alternativa caso a condicao anterior seja falsa. */
    } else puts("Erro ao salvar. Cadastro nao realizado.");
/* Encerra este bloco de instrucoes. */
}

/* Altera o registro encontrado pelo ID. */
/* Inicia a funcao alterar, que executa uma tarefa do sistema. */
void alterar(Produto *lista, int total) {
    /* Cria uma variavel inteira para guardar o resultado desta etapa. */
    int id = lerInteiro("ID do produto a alterar: ", 1, 2000000000);
    /* Cria uma variavel inteira para guardar o resultado desta etapa. */
    int pos = indicePorId(lista, total, id);
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (pos < 0) { puts("ID nao encontrado."); return; }
    /* Guarda uma copia do registro para desfazer alteracoes se necessario. */
    Produto anterior = lista[pos];
    /* Mostra os dados do produto na linha da tabela. */
    linhaProduto(&anterior);
    /* Apresenta esta mensagem ao usuario no terminal. */
    puts("Digite os novos dados:");
    /* Copia os dados atuais antes de pedir as alteracoes. */
    Produto novo = anterior;
    /* Solicita os campos do produto para cadastro ou alteracao. */
    preencher(&novo);
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (nomeExiste(lista, total, novo.nome, id)) {
        /* Apresenta esta mensagem ao usuario no terminal. */
        puts("Ja existe outro produto com esse nome."); return;
    /* Encerra este bloco de instrucoes. */
    }
    /* Atualiza este produto na posicao indicada do vetor. */
    lista[pos] = novo;
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (salvar(lista, total)) puts("Produto alterado com sucesso.");
    /* Executa a alternativa quando a verificacao anterior nao foi atendida. */
    else { lista[pos] = anterior; puts("Erro ao salvar. Alteracao cancelada."); }
/* Encerra este bloco de instrucoes. */
}

/* Exclui do vetor e do arquivo, apos confirmacao.
   O ponteiro int *total permite diminuir a contagem original apos salvar. */
void excluir(Produto *lista, int *total) {
    int id = lerInteiro("ID do produto a excluir: ", 1, 2000000000);
    int pos = indicePorId(lista, *total, id);
    if (pos < 0) { puts("ID nao encontrado."); return; }
    linhaProduto(&lista[pos]);
    int confirma = lerInteiro("Confirmar exclusao? (1=Sim, 2=Nao): ", 1, 2);
    if (confirma != 1) { puts("Exclusao cancelada."); return; }
    Produto excluido = lista[pos];
    for (int i = pos; i < *total - 1; i++) lista[i] = lista[i + 1];
    if (salvar(lista, *total - 1)) { (*total)--; puts("Produto excluido."); }
    else {
        for (int i = *total - 1; i > pos; i--) lista[i] = lista[i - 1];
        lista[pos] = excluido;
        puts("Erro ao salvar. Exclusao cancelada.");
    }
}

/* Busca por nome ou categoria, aceitando parte do texto. */
/* Inicia a funcao buscar, que executa uma tarefa do sistema. */
void buscar(const Produto *lista, int total) {
    /* Cria uma variavel inteira para guardar o resultado desta etapa. */
    int opcao = lerInteiro("Buscar por 1-Nome ou 2-Categoria: ", 1, 2);
    /* Reserva espaco para armazenar o texto informado pelo usuario. */
    char termo[80];
    /* Le o texto digitado, respeitando o tamanho maximo do campo. */
    lerTexto("Digite o termo: ", termo, sizeof(termo));
    /* Cria uma variavel inteira para guardar o resultado desta etapa. */
    int encontrados = 0;
    /* Repete a instrucao para percorrer os produtos ou caracteres necessarios. */
    for (int i = 0; i < total; i++) {
        /* Escolhe o texto que sera usado na pesquisa. */
        const char *campo = opcao == 1 ? lista[i].nome : lista[i].categoria;
        /* Testa esta condicao para decidir se a operacao pode continuar. */
        if (contemTexto(campo, termo)) {
            /* Testa esta condicao para decidir se a operacao pode continuar. */
            if (encontrados == 0) cabecalho();
            /* Mostra os dados do produto na linha da tabela. */
            linhaProduto(&lista[i]);
            /* Conta mais um produto encontrado na pesquisa. */
            encontrados++;
        /* Encerra este bloco de instrucoes. */
        }
    /* Encerra este bloco de instrucoes. */
    }
    /* Mostra na tela os valores indicados, respeitando o formato definido. */
    printf("Resultado: %d produto(s) encontrado(s).\n", encontrados);
/* Encerra este bloco de instrucoes. */
}

/* Bubble Sort: compara vizinhos e troca quando estao fora de ordem.
   O laco externo controla as passagens; o interno compara cada par vizinho.
   O campo houveTroca permite parar quando a lista ja esta ordenada.
   A ordenacao e feita em copia, sem modificar o arquivo original. */
void ordenar(const Produto *lista, int total) {
    if (total == 0) { puts("Nenhum produto para ordenar."); return; }
    puts("1 - Nome (A-Z)\n2 - Nome (Z-A)\n3 - Preco (menor-maior)\n4 - Preco (maior-menor)");
    int modo = lerInteiro("Escolha: ", 1, 4);
    Produto copia[MAX_PRODUTOS];
    memcpy(copia, lista, (size_t)total * sizeof(Produto));
    for (int i = 0; i < total - 1; i++) {
        int houveTroca = 0;
        for (int j = 0; j < total - 1 - i; j++) {
            int trocar = 0;
            if (modo == 1) trocar = compararTexto(copia[j].nome, copia[j + 1].nome) > 0;
            if (modo == 2) trocar = compararTexto(copia[j].nome, copia[j + 1].nome) < 0;
            if (modo == 3) trocar = copia[j].preco > copia[j + 1].preco;
            if (modo == 4) trocar = copia[j].preco < copia[j + 1].preco;
            if (trocar) {
                Produto aux = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = aux;
                houveTroca = 1;
            }
        }
        if (!houveTroca) break;
    }
    listar(copia, total);
    puts("Ordenacao apenas na tela; o arquivo original nao foi alterado.");
}

/* Coloca aspas em campos CSV e duplica aspas internas, conforme o formato CSV. */
/* Inicia a funcao escreverCampoCSV, que executa uma tarefa do sistema. */
void escreverCampoCSV(FILE *arquivo, const char *texto) {
    /* Grava este caractere no arquivo CSV. */
    fputc('"', arquivo);
    /* Repete a instrucao para percorrer os produtos ou caracteres necessarios. */
    for (const char *letra = texto; *letra; letra++) {
        /* Testa esta condicao para decidir se a operacao pode continuar. */
        if (*letra == '"') fputc('"', arquivo);
        /* Grava este caractere no arquivo CSV. */
        fputc(*letra, arquivo);
    /* Encerra este bloco de instrucoes. */
    }
    /* Grava este caractere no arquivo CSV. */
    fputc('"', arquivo);
/* Encerra este bloco de instrucoes. */
}

/* Exporta seis colunas separadas por virgulas, conforme o enunciado. */
/* Inicia a funcao exportarCSV, que executa uma tarefa do sistema. */
void exportarCSV(const Produto *lista, int total) {
    /* Abre um arquivo e guarda sua referencia para leitura ou gravacao. */
    FILE *arquivo = fopen(CSV, "w");
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (!arquivo) { perror("Erro ao exportar CSV"); return; }
    /* Cria uma variavel inteira para guardar o resultado desta etapa. */
    int ok = fprintf(arquivo, "ID,Produto,Categoria,Preco (R$),Quantidade,Fornecedor\n") >= 0;
    /* Repete a instrucao para percorrer os produtos ou caracteres necessarios. */
    for (int i = 0; i < total && ok; i++) {
        /* Cria um ponteiro de leitura para o produto nesta posicao. */
        const Produto *p = &lista[i];
        /* Testa esta condicao para decidir se a operacao pode continuar. */
        if (fprintf(arquivo, "%d,", p->id) < 0) ok = 0;
        /* Grava este campo entre aspas para preservar o formato CSV. */
        escreverCampoCSV(arquivo, p->nome);
        /* Testa esta condicao para decidir se a operacao pode continuar. */
        if (fputc(',', arquivo) == EOF) ok = 0;
        /* Grava este campo entre aspas para preservar o formato CSV. */
        escreverCampoCSV(arquivo, p->categoria);
        /* Testa esta condicao para decidir se a operacao pode continuar. */
        if (fprintf(arquivo, ",%.2f,%d,", p->preco, p->quantidade) < 0) ok = 0;
        /* Grava este campo entre aspas para preservar o formato CSV. */
        escreverCampoCSV(arquivo, p->fornecedor);
        /* Testa esta condicao para decidir se a operacao pode continuar. */
        if (fputc('\n', arquivo) == EOF) ok = 0;
        /* Testa esta condicao para decidir se a operacao pode continuar. */
        if (ferror(arquivo)) ok = 0;
    /* Encerra este bloco de instrucoes. */
    }
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (fclose(arquivo) != 0) ok = 0;
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (ok) printf("Exportado: %s\n", CSV);
    /* Executa a alternativa quando a verificacao anterior nao foi atendida. */
    else { remove(CSV); puts("Erro ao finalizar a exportacao."); }
/* Encerra este bloco de instrucoes. */
}

/* Cria exemplos apenas na primeira execucao, para facilitar a apresentacao. */
/* Inicia a funcao criarExemplos, que executa uma tarefa do sistema. */
void criarExemplos(Produto *lista, int *total, int *ultimoId) {
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (*total != 0) { puts("Ja existem produtos cadastrados."); return; }
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (*ultimoId > 2000000000 - 5) { puts("Limite de IDs atingido."); return; }
    /* Cria um registro do tipo Produto para guardar os dados desta etapa. */
    Produto exemplos[] = {
        /* Executa esta instrucao como parte da operacao atual. */
        {1, "Parafuso Sextavado M8", "Parafusos", 2.50, 150, "Metal Brasil"},
        /* Executa esta instrucao como parte da operacao atual. */
        {2, "Porca Sextavada M10", "Porcas", 1.20, 300, "Fixadores Sul"},
        /* Executa esta instrucao como parte da operacao atual. */
        {3, "Arruela Lisa M8", "Arruelas", 0.50, 500, "Metal Brasil"},
        /* Executa esta instrucao como parte da operacao atual. */
        {4, "Parafuso Allen M6", "Parafusos", 3.80, 100, "Aco Forte"},
        /* Executa esta instrucao como parte da operacao atual. */
        {5, "Bucha Nylon 8mm", "Buchas", 0.75, 400, "Fixadores Sul"}
    /* Encerra o bloco de instrucoes anterior. */
    };
    /* Cria uma variavel inteira para guardar o resultado desta etapa. */
    int n = (int)(sizeof(exemplos) / sizeof(exemplos[0]));
    /* Repete a instrucao para percorrer os produtos ou caracteres necessarios. */
    for (int i = 0; i < n; i++) exemplos[i].id = *ultimoId + i + 1;
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (!registrarUltimoId(*ultimoId + n)) {
        /* Apresenta esta mensagem ao usuario no terminal. */
        puts("Erro ao registrar IDs dos exemplos."); return;
    /* Encerra este bloco de instrucoes. */
    }
    *ultimoId += n;
    /* Copia os registros de exemplo para o vetor principal. */
    memcpy(lista, exemplos, sizeof(exemplos));
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (salvar(lista, n)) {
        *total = n;
        /* Apresenta esta mensagem ao usuario no terminal. */
        puts("Cinco produtos de exemplo cadastrados com sucesso.");
    /* Executa a alternativa caso a condicao anterior seja falsa. */
    } else puts("Nao foi possivel salvar os exemplos.");
/* Encerra este bloco de instrucoes. */
}

/* Simula uma venda para o cliente, atualizando o estoque no arquivo.
   O pagamento nao e processado: a compra e uma simulacao de caixa. */
void realizarCompra(Produto *lista, int total) {
    /* Mostra os itens disponiveis antes de pedir o ID escolhido. */
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (total == 0) { puts("Loja sem produtos cadastrados."); return; }
    /* Apresenta esta mensagem ao usuario no terminal. */
    puts("\n========== LOJA SIDER FIXADORES ==========");
    /* Mostra a lista de produtos disponiveis. */
    listar(lista, total);
    /* O ID identifica o produto mesmo quando a tabela muda de ordem. */
    /* Cria uma variavel inteira para guardar o resultado desta etapa. */
    int id = lerInteiro("ID do produto (0 para cancelar): ", 0, 2000000000);
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (id == 0) { puts("Compra cancelada."); return; }
    /* Cria uma variavel inteira para guardar o resultado desta etapa. */
    int pos = indicePorId(lista, total, id);
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (pos < 0) { puts("Produto nao encontrado."); return; }
    /* Cria um registro do tipo Produto para guardar os dados desta etapa. */
    Produto *produto = &lista[pos];
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (produto->quantidade <= 0) { puts("Produto sem estoque."); return; }
    /* Mostra na tela os valores indicados, respeitando o formato definido. */
    printf("Produto: %s | Preco: R$ %.2f | Disponivel: %d\n",
           /* Atribui ou atualiza este valor para manter os dados do produto corretos. */
           produto->nome, produto->preco, produto->quantidade);
    /* A quantidade aceita vai de 1 ate o estoque atual. */
    /* Cria uma variavel inteira para guardar o resultado desta etapa. */
    int quantidade = lerInteiro("Quantidade desejada: ", 1, produto->quantidade);
    /* Calcula o valor da compra multiplicando preco por quantidade. */
    double totalCompra = produto->preco * quantidade;
    /* Mostra na tela os valores indicados, respeitando o formato definido. */
    printf("\nRESUMO DA COMPRA\n%s\n%d x R$ %.2f = R$ %.2f\n",
           /* Atribui ou atualiza este valor para manter os dados do produto corretos. */
           produto->nome, quantidade, produto->preco, totalCompra);
    /* Cria uma variavel inteira para guardar o resultado desta etapa. */
    int confirmar = lerInteiro("Confirmar compra? (1=Sim, 2=Nao): ", 1, 2);
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (confirmar != 1) { puts("Compra cancelada. Estoque mantido."); return; }
    /* Guarda o valor anterior para restaurar caso falhe a gravacao. */
    /* Guarda o estoque original para desfazer a compra se nao salvar. */
    int estoqueAnterior = produto->quantidade;
    /* Atribui ou atualiza este valor para manter os dados do produto corretos. */
    produto->quantidade -= quantidade;
    /* Testa esta condicao para decidir se a operacao pode continuar. */
    if (salvar(lista, total)) {
        /* Apresenta esta mensagem ao usuario no terminal. */
        puts("Compra realizada com sucesso!");
        /* Mostra na tela os valores indicados, respeitando o formato definido. */
        printf("Total: R$ %.2f | Estoque restante: %d\n",
               /* Atribui ou atualiza este valor para manter os dados do produto corretos. */
               totalCompra, produto->quantidade);
    /* Se a operacao anterior falhou, executa a alternativa. */
    } else {
        /* Atribui ou atualiza este valor para manter os dados do produto corretos. */
        produto->quantidade = estoqueAnterior;
        /* Apresenta esta mensagem ao usuario no terminal. */
        puts("Nao foi possivel salvar a compra. Estoque restaurado.");
    /* Encerra este bloco de instrucoes. */
    }
/* Encerra este bloco de instrucoes. */
}

/* Menu principal: do/while repete as opcoes; switch/case chama a funcao
   correspondente; break impede que outro caso seja executado. */
int main(void) {
    Produto lista[MAX_PRODUTOS]; /* Vetor de estruturas: banco de dados em memoria. */
    int total = carregar(lista); /* Recupera os registros de produtos.txt. */
    int ultimoId = recuperarUltimoId(lista, total); /* Contador preservado entre execucoes. */
    int opcao;
    do {
        puts("\n========== SIDER FIXADORES ==========");
        puts("   GERENCIAMENTO DE PRODUTOS");
        puts("1 - Cadastrar produto");
        puts("2 - Listar produtos");
        puts("3 - Alterar produto");
        puts("4 - Excluir produto");
        puts("5 - Buscar produto");
        puts("6 - Ordenar produtos");
        puts("7 - Exportar para CSV");
        puts("8 - Cadastrar produtos de exemplo");
        /* Permite ao cliente comprar e desconta a quantidade vendida. */
        /* Apresenta esta mensagem ao usuario no terminal. */
        puts("9 - Realizar compra (cliente)");
        /* Apresenta esta mensagem ao usuario no terminal. */
        puts("0 - Sair");
        /* Le a opcao do menu escolhida pelo usuario. */
        opcao = lerInteiro("Escolha uma opcao: ", 0, 9);
        /* Escolhe a acao do menu conforme o numero informado. */
        switch (opcao) {
            /* Quando o usuario escolhe 1, executa a funcao indicada e retorna ao menu. */
            case 1: inserir(lista, &total, &ultimoId); break;
            /* Quando o usuario escolhe 2, executa a funcao indicada e retorna ao menu. */
            case 2: listar(lista, total); break;
            /* Quando o usuario escolhe 3, executa a funcao indicada e retorna ao menu. */
            case 3: alterar(lista, total); break;
            /* Quando o usuario escolhe 4, executa a funcao indicada e retorna ao menu. */
            case 4: excluir(lista, &total); break;
            /* Quando o usuario escolhe 5, executa a funcao indicada e retorna ao menu. */
            case 5: buscar(lista, total); break;
            /* Quando o usuario escolhe 6, executa a funcao indicada e retorna ao menu. */
            case 6: ordenar(lista, total); break;
            /* Quando o usuario escolhe 7, executa a funcao indicada e retorna ao menu. */
            case 7: exportarCSV(lista, total); break;
            /* Quando o usuario escolhe 8, executa a funcao indicada e retorna ao menu. */
            case 8: criarExemplos(lista, &total, &ultimoId); break;
            /* Registra a venda e persiste o estoque atualizado. */
            /* Quando o usuario escolhe 9, executa a funcao indicada e retorna ao menu. */
            case 9: realizarCompra(lista, total); break;
            /* Quando o usuario escolhe 0, executa a funcao indicada e retorna ao menu. */
            case 0: puts("Obrigado por usar o SIDER FIXADORES!"); break;
        /* Encerra este bloco de instrucoes. */
        }
    /* Repete o menu ate o usuario escolher a opcao zero. */
    } while (opcao != 0); /* Encerra somente quando o usuario digita zero. */
    /* Devolve este valor para a funcao que fez a chamada. */
    return 0;
/* Encerra este bloco de instrucoes. */
}
