#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    struct No *prox;
    struct No *ant;
    int chave;
}No;

typedef struct Lista
{
    No *cabeca;
}Lista;

No* criarNo(int valor)
{
    No* novo;
    novo = malloc(sizeof(No));
    novo->chave = valor;
    novo->prox = NULL;
    novo->ant = NULL;
}
Lista* criarLista()
{
    Lista* novo;
    novo = (Lista*) malloc(sizeof(Lista));
    novo->cabeca = NULL;
}


void Inserir(Lista * l, int valor)
{
    No * novo = criarNo(valor);
    if (l->cabeca == NULL || l->cabeca->chave > valor)
    {
        novo->prox = l->cabeca;
        l->cabeca = novo;
    } else
    {
        No *aux = l->cabeca;
        while (aux->prox != NULL && aux->prox->chave < valor)
        {
            aux = aux->prox;
        }
        if (aux->prox == NULL)
        {
            novo->ant = aux;
            aux->prox = novo;
        }
        else
        {
            novo->prox = aux->prox;
            aux->prox = novo;
        }
    }
}
void imprimirLista(Lista *l)
{
    No *aux = l->cabeca;
    printf("\nNULL->");
    while (aux != NULL)
    {
        printf("%d -> ", aux->chave);
        aux = aux->prox;
    }
    printf("NULL\n");
}
int main()
{
    Lista *lista = criarLista();
    Inserir(lista, 5);
    Inserir(lista, 3);
    Inserir(lista, 8);
    Inserir(lista, 4);
    Inserir(lista, 2);
    imprimirLista(lista);
}