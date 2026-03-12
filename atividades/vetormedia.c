#include <stdio.h>

int main(){

    double nota, media = 0, nota1[30], nota2[30], MediaAluno[30];

    int ContVetor = 0, i = 1;
    
    while(i < 31){

        printf("Digite a nota 1 do %d° aluno :", i);
        if (scanf("%lf", &nota) == 0 || nota < 0){
            printf("Nota inválida!");
            while(getchar() != '\n');
            continue;
        }
        else {
            nota1[ContVetor] = nota;
        }
        printf("Digite a nota 2 do %d° aluno :", i);
        if (scanf("%lf", &nota) == 0 || nota < 0){
            printf("Nota inválida, digite novamente!");
            while(getchar() != '\n');
            while (1){
                printf("Digite a nota 2 do %d° aluno :", i);
                if (scanf("%lf", &nota) == 0 || nota < 0){
                    printf("Nota inválida, digite novamente!");
                    while(getchar() != '\n');
                    continue;
                }
                else{
                    nota2[ContVetor] = nota;
                    break;
                }
            }
        }
        else{
            nota2[ContVetor] = nota;
        }
        MediaAluno[ContVetor] = ((nota1[ContVetor] * 2) + (nota2[ContVetor] * 3)) / 5 ;
        media += MediaAluno[ContVetor];
        i += 1;
        ContVetor += 1;
    }

    ContVetor = 0;
    i = 1;
    media =  media / 30;
    printf("A média geral da turma foi de %.2lf\n", media);
    while(i < 31){
        if (MediaAluno[ContVetor] > media){
            printf("O %d° aluno teve nota 1: %.2lf e nota 2: %.2lf e média: %.2lf e ficou acima da média da turma!\n", i, nota1[ContVetor], nota2[ContVetor], MediaAluno[ContVetor]);
        }
      
        i += 1;
        ContVetor += 1;
       }
    return 0;
}