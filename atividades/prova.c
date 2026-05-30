#include <stdio.h>
#include <string.h>

#define TAM 100

struct Categoria {
    int codigo;
    char nome[50];
};

struct Produto {
    int codigo;
    char titulo[100];
    char descricao[256];
    int categoria;
    int preco;
};

// Q1
void cadastrarCategoria(struct Categoria v[], int *qtd) {
    if (*qtd >= TAM) {
        printf("Vetor cheio.\n");
        return;
    }

    struct Categoria c;
    int codigoValido = 0;

    while (!codigoValido) {
        printf("Digite o codigo: ");
        scanf("%d", &c.codigo);

        codigoValido = 1;

        for (int i = 0; i < *qtd; i++) {
            if (v[i].codigo == c.codigo) {
                printf("Ja existe categoria com esse codigo.\n");
                codigoValido = 0;
                break;
            }
        }
    }

    printf("Digite o nome: ");
    scanf("%s", c.nome);

    v[*qtd] = c;
    (*qtd)++;
}

// Q2
void imprimirCategorias(struct Categoria v[], int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("%d - %s\n", v[i].codigo, v[i].nome);
    }
}

// Q3
void imprimirProdutos(struct Produto vp[], int qtdProdutos,
                      struct Categoria vc[], int qtdCategorias) {
    for (int i = 0; i < qtdProdutos; i++) {
        char nomeCategoria[50] = "Desconhecida";

        for (int j = 0; j < qtdCategorias; j++) {
            if (vp[i].categoria == vc[j].codigo) {
                strcpy(nomeCategoria, vc[j].nome);
                break;
            }
        }

        double preco = (double) vp[i].preco / 100.0;

        printf("Codigo: %d\n", vp[i].codigo);
        printf("Titulo: %s\n", vp[i].titulo);
        printf("Descricao: %s\n", vp[i].descricao);
        printf("Categoria: %s\n", nomeCategoria);
        printf("Preco: R$ %.2f\n\n", preco);
    }
}

// Q4
void selectionSortPorDescricao(struct Produto v[], int qtd) {
    int i, j, minIdx;
    struct Produto temp;

    for (i = 0; i < qtd - 1; i++) {
        minIdx = i;

        for (j = i + 1; j < qtd; j++) {
            if (strcmp(v[j].descricao, v[minIdx].descricao) < 0) {
                minIdx = j;
            }
        }

        temp = v[i];
        v[i] = v[minIdx];
        v[minIdx] = temp;
    }
}

// Q5
int buscaBinariaPorDescricao(struct Produto v[], int qtd, char *x) {
    int inicio = 0, fim = qtd - 1, meio, comp;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comp = strcmp(v[meio].descricao, x);

        if (comp == 0) {
            return meio;
        } else if (comp > 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
    return -1;
}