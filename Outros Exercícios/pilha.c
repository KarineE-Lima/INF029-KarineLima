#include <stdio.h>
#include <stdlib.h>
#define TAM 10

typedef struct pilha
{
    int topo;
    int *elementos;
} Pilha;
void menu()
{
    printf("Escolha uma das Opções abaixo:\n");
    printf("1- Inserir elemento\n");
    printf("2- Remover elemento\n");
    printf("3- Imprimir pilha\n");
    printf("4- Sair\n");
}
void * criarPilha(Pilha *p)
{
    p->topo = -1;
    p->elementos = malloc(TAM * sizeof(int));
}
int pilha_cheia(Pilha *p)
{
    if (p->topo == TAM - 1)
        return 1;
    return 0;
}
int pilha_vazia(Pilha *p)
{
    if(p->topo == -1)
        return 1;
    return 0;
}
void empilhar(Pilha *p, int v)
{
    if (pilha_cheia(p))
    {
        printf("Pilha cheia!\n");
    } else
    {
        p->topo++;
        p->elementos[p->topo] = v;
    }
}
void desempilhar(Pilha *p)
{
    if(pilha_vazia(p))
    {
        printf("Pilha Vazia!\n");
    } else
    {
        p->topo--;
    }
}
void imprimirPilha(Pilha *p)
{
    if (pilha_vazia(p))
        printf("Pilha Vazia!\n");
    else
    {
        for (int i = 0; i <= p->topo; i++)
            printf("%d ", p->elementos[i]);
    }
}
int main()
{
    Pilha *p = malloc(sizeof(Pilha));
    criarPilha(p);
    int op, elem;
    do
    {
        menu();
        scanf("%d", &op);
        fflush(stdin);
        switch (op)
        {
            case 1:
                printf("Informe o elemento que você quer inserir: ");
                scanf("%d", &elem);
                fflush(stdin);
                empilhar(p, elem);
                break;
            case 2:
                desempilhar(p);
                break;
            case 3:
                imprimirPilha(p);
                break;
            case 4:
                printf("Saindo...");
                break;
            default: printf("Insira uma opção válida!\n");
        }
    }while(op != 4);
    free(p);
    return 0;
}
