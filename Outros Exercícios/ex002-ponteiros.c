#include <stdio.h>
void troca(int *num1, int *num2)
{
    int aux = *num1;
    *num1 = *num2;
    *num2 = aux;
}
void ordena(int *vet, int tam)
{
    for (int i = 1; i < tam; i++)
    {
        int chave = vet[i];
        int j = i - 1;
        while (j >= 0 && vet[j] > chave)
        {
            vet[j + 1] = vet[j];
            j--;
        }
        vet[j + 1] = chave;

    }
}
int main()
{
    int valor1, valor2;
    int vetor[5];
    printf("Insira o valor 1: ");
    scanf("%d",&valor1);
    printf("Insira o valor 2: ");
    scanf("%d",&valor2);
    printf("Antes da troca:\nValor 1: %d e Valor 2: %d\n", valor1, valor2);
    troca(&valor1, &valor2);
    printf("Depois da troca:\nValor 1: %d e Valor 2: %d\n", valor1, valor2);

    for (int i = 0; i < 5; i++)
    {
        printf("Insira o valor: ");
        scanf("%d",&vetor[i]);
    }
    ordena(vetor, 5);
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", vetor[i]);
    }
    return 0;
}