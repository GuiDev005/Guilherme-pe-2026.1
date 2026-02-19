#include <stdio.h>

double calcularIMC(double p, double a){
    return p / (a*a);
}
int main(){
    double peso, altura, imc;
    printf("Digite seu peso.");
    scanf("%lf", &peso);
    printf("Digite sua altura.");
    scanf("%lf", &altura);
    imc = calcularIMC(peso, altura);
    printf("Seu IMC é: %.2lf\n", imc);
    return 0;
}