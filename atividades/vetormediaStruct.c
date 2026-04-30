#include <stdio.h>

#define NUM_ALUNOS 30

typedef struct {
    double nota1;
    double nota2;
    double media;
} Aluno;

double lerNota(int aluno, int numNota) {
    double nota;
    while (1) {
        printf("Digite a nota %d do %d° aluno: ", numNota, aluno);
        if (scanf("%lf", &nota) == 0 || nota < 0) {
            printf("Nota inválida, digite novamente!\n");
            while (getchar() != '\n');
        } else {
            return nota;
        }
    }
}

void lerNotas(Aluno turma[]) {
    for (int i = 0; i < NUM_ALUNOS; i++) {
        turma[i].nota1 = lerNota(i + 1, 1);
        turma[i].nota2 = lerNota(i + 1, 2);
    }
}

void calcularMedias(Aluno turma[]) {
    for (int i = 0; i < NUM_ALUNOS; i++) {
        turma[i].media = (turma[i].nota1 * 2 + turma[i].nota2 * 3) / 5.0;
    }
}

double calcularMediaTurma(Aluno turma[]) {
    double soma = 0;
    for (int i = 0; i < NUM_ALUNOS; i++) {
        soma += turma[i].media;
    }
    return soma / NUM_ALUNOS;
}

void imprimirAcimaMedia(Aluno turma[], double mediaTurma) {
    printf("\nA média geral da turma foi de %.2lf\n\n", mediaTurma);
    for (int i = 0; i < NUM_ALUNOS; i++) {
        if (turma[i].media > mediaTurma) {
            printf("O %d° aluno teve nota 1: %.2lf, nota 2: %.2lf e média: %.2lf — acima da média da turma!\n",
                   i + 1, turma[i].nota1, turma[i].nota2, turma[i].media);
        }
    }
}

int main() {
    Aluno turma[NUM_ALUNOS];

    lerNotas(turma);
    calcularMedias(turma);
    double mediaTurma = calcularMediaTurma(turma);
    imprimirAcimaMedia(turma, mediaTurma);

    return 0;
}