#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int chave;
    struct no *prox;
}No;

typedef struct No
{
    No *Cabeca;
}Lista;
void menu()
{
    printf("Escolha uma das opções:\n");
    printf("1- Inserir elemento\n");
    printf("2- Remover elemento\n");
    printf("3- Imprimir lista\n");
    printf("4- Sair\n");
}

No* criarNo(int valor)
{
    No *novo = (No*)malloc(sizeof(No));
    novo->chave = valor;
    novo->prox = NULL;
    return novo;
}
Lista *criarLista()
{
    Lista *novo = (Lista*)malloc(sizeof(Lista));
    novo->Cabeca = NULL;

}
void inserirNo(Lista *l, No *n)
{
    No *novo = criarNo(n->chave);
    if (l->Cabeca == NULL || l->Cabeca->chave >= novo->chave)
    {
        novo->prox = l->Cabeca;
        l->Cabeca = novo;
    } else
    {
        No *aux = l->Cabeca;

        while (aux->prox != NULL && aux->prox->chave < n->chave)
            aux = aux->prox;
        if (aux->prox == NULL)
            aux->prox = n;
        else
        {
            novo->prox = aux->prox;
            aux->prox = novo;

        }


    }
}
void Remover(Lista *l, int elem)
{
    if (l->Cabeca != NULL)
    {
        No *remove = l->Cabeca;
        No *aux;
        while (remove->prox != NULL && remove->chave != elem)
        {
            aux = remove;
            remove = remove->prox;
        }
        if (remove == l->Cabeca && elem == l->Cabeca->chave)
        {
            l->Cabeca = l->Cabeca->prox;
        } else if (elem == remove->chave)
        {
            aux->prox = remove->prox;
        }
        else
            printf("Elemento não encontrado!\n");
    }
}
void imprimirLista(Lista *l)
{
    No *aux = l->Cabeca;
    printf("\n");
    while (aux != NULL)
    {
        printf("%d -> ", aux->chave);
        aux = aux->prox;
    }
    printf("NULL\n");

}
int main()
{
    Lista *lista;
    lista = criarLista();
    int op, elemi, elemex;
    do
    {
        menu();
        scanf("%d", &op);
        switch (op)
        {
            case 1:
                printf("Inserir elemento\n");
                printf("Informe o elemento que você quer inserir:");
                scanf("%d", &elemi);
                fflush(stdin);
                inserirNo(lista, criarNo(elemi));
                break;
            case 2:
                printf("Remover elemento\n");
                if (lista->Cabeca == NULL)
                {
                    printf("Lista vazia!\n");
                } else
                {
                    printf("Informe o elemento que você quer excluir:");
                    scanf("%d", &elemex);
                    fflush(stdin);
                    Remover(lista, elemex);
                }
                break;
            case 3:
                printf("Imprimir lista\n");
                imprimirLista(lista);
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default: printf("Opção inválida!\n");
        }

    }while (op != 4);

}