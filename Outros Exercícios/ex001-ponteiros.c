#include <stdio.h>

int main()
{
    int valor;
    char c;
    char s[10];
    float num;
    double num_maior;
    int *ptvalor = &valor;
    char *ptc = &c;
    char *pts = s;
    float *ptnum = &num;
    double *ptnum_maior = &num_maior;

    printf("Insira um numero inteiro: ");
    scanf("%d", &valor);
    fflush(stdin);
    printf("Insira um caractere: ");
    scanf("%c", &c);
    fflush(stdin);
    printf("Insira uma string: ");
    fgets(s, 10, stdin);
    fflush(stdin);
    printf("Insira um numero float: ");
    scanf("%f", &num);
    fflush(stdin);
    printf("Insira um numero double: ");
    scanf("%lf", &num_maior);
    fflush(stdin);


    printf("Valores das variáveis: %d, %c, %s, %f, %lf\n", valor, c, s, num, num_maior);
    printf("Valores dos ponteiros: %d, %c, %s, %f, %lf\n", *ptvalor, *ptc, pts, *ptnum, *ptnum_maior);
    return 0;
}