#include <stdio.h>

int entradaTamanho(void);
void preencherVetor(int v[], int tamanho);
void imprimirVetor(int vetor[],int tamanho);
int consulta(int vetor[],int tamanho);
int remover(int vetor[], int tamanho);
int inserir(int vetor[], int tamanho);
void barra();

int main(){
    int tamanho = entradaTamanho(), tam_max = 50;
    int vetor[tam_max];
    preencherVetor(vetor, tamanho);
    
    while(1){
        int opcao;
        printf("1.Imprimir vetor\n");
        printf("2.Consultar vetor\n");
        printf("3.Remover Elemento do vetor\n");
        printf("4.inserir elemento no vetor\n");
        printf("Digite sua opção:\n");
        scanf("%d", &opcao);
        if (opcao == 1){
            barra();
            imprimirVetor(vetor, tamanho);
            barra();
        }else if(opcao == 2){
            barra();
            int pos = consulta(vetor, tamanho);
            if (pos != -1){
            printf("A posição é a %d°\n", pos + 1);
            barra();
        }else{
            printf("não encontrado\n");
            barra();
        }

        }else if (opcao == 3){
            barra();
            tamanho = remover(vetor, tamanho);
            barra();
        }else if(opcao == 4){
            barra();
            tamanho = inserir(vetor, tamanho);
            barra();
        }else {
            break;
        }
    }
    return 0;
}

int entradaTamanho(void){
    int n;
    while (1){
    printf("Digite o Tamanho máximo do vetor (O valor tem que estar entre 3 e 50): \n");
    if (scanf("%d", &n) == 1 && n >= 3 && n <= 50){
        return n;
    } else{
        printf("Valor inválido!\n");
        while(getchar() != '\n');
    }
    }

}

void preencherVetor(int v[], int tamanho){
    int numero;
    for(int i = 0; i < tamanho; i++){
        printf("Digite o numero para a posição %d°\n", i + 1);
        if (scanf("%d", &numero) == 1){
            int j = i - 1;
            while (j >= 0 && v[j] > numero) {
                v[j + 1] = v[j];
                j--;
            }
            v[j + 1] = numero;
        } else{
            printf("Entrada inválida");
            while(getchar() != '\n');
            i--;
        }
    }
}

void imprimirVetor(int vetor[],int tamanho){
    for(int i = 0; i < tamanho; i++) {
        printf("%d\n", vetor[i]);
    }
}

int consulta(int vetor[],int tamanho){
    int valor, inicio = 0, fim = tamanho - 1, meio;
    printf("Digite o valor que procura:");
    if (scanf("%d", &valor) == 1){
        while(inicio <= fim){
           meio = (inicio + fim) / 2;
           if (valor > vetor[meio]){
                inicio = meio + 1;
           } else if(valor < vetor[meio]){
                fim = meio - 1;
           }else{
            return meio;
           }
        }
        
        return -1;
    }
    return -1;
}

int remover(int vetor[], int tamanho) {
    int indice = consulta(vetor, tamanho);
    if (indice == -1) {
        printf("Elemento não encontrado!\n");
        return tamanho;
    }
    for (int i = indice; i < tamanho - 1; i++) {
        vetor[i] = vetor[i + 1];
    }
    (tamanho)--;
    printf("Elemento removido com sucesso!\n");
    return tamanho;
}

int inserir(int vetor[], int tamanho) {
    if (tamanho >= 50) {
        printf("Vetor cheio!\n");
        return tamanho;
    }
    int numero;
    printf("Digite o valor a inserir: ");
    if (scanf("%d", &numero) != 1) return tamanho;

    int j = tamanho - 1;
    while (j >= 0 && vetor[j] > numero) {
        vetor[j + 1] = vetor[j];
        j--;
    }
    vetor[j + 1] = numero;
    (tamanho)++;
    printf("Elemento inserido com sucesso!\n");
    return tamanho;
}

void barra(){
    printf("--------------------------------------------\n");
    printf("                                             \n");

}