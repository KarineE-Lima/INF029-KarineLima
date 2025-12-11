#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"
typedef struct
{
    int *valores;
    int qtd;
    int tamanho;
}Ponto;

Ponto vetorPrincipal[TAM];

int valida_posicao(int pos)
{
    if (pos < 1 || pos > TAM)
        return 0;
    return 1;
}
int tem_estrutura(int pos)
{
    if (vetorPrincipal[pos].valores == NULL)
        return 0;
    return 1;
}
int estrutura_vaga(Ponto *p)
{
    if (p->qtd == p->tamanho)
        return 0;
    return 1;

}
int BuscaValor(int posicao, int valor)
{
    for (int i = 0; i < vetorPrincipal[posicao].qtd; i++)
    {
        if (vetorPrincipal[posicao].valores[i] == valor)
            return i;

    }
    return -1;
}
int get_qtd(Ponto *vet){
    int tam = 0;
    for(int i = 0; i < TAM; i++){
        tam += vet[i].qtd;
    }
    return tam;
}
void ordena_vetor(int vet[], int tam)
{
    int i, j, aux;
    for (i = 1; i < tam; i++)
    {
        aux = vet[i];
        j = i - 1;
        while (vet[j] > aux && j >= 0)
        {
            vet[j + 1] = vet[j];
            j--;
        }
        vet[j + 1] = aux;
    }
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    posicao--;

    // se posição é um valor válido {entre 1 e 10}
    if (!valida_posicao(posicao+1))
        return POSICAO_INVALIDA;
    // a posicao pode já existir estrutura auxiliar
    if (tem_estrutura(posicao))
        return JA_TEM_ESTRUTURA_AUXILIAR;
    // o tamanho nao pode ser menor que 1
    if (tamanho < 1)
        return TAMANHO_INVALIDO;

    // o tamanho ser muito grande
    Ponto *p = malloc(tamanho * sizeof(Ponto));
    if (p == NULL)
        return SEM_ESPACO_DE_MEMORIA;
    free(p);

    // deu tudo certo, crie
    vetorPrincipal[posicao].valores = malloc(tamanho * sizeof(int));
    vetorPrincipal[posicao].qtd = 0;
    vetorPrincipal[posicao].tamanho = tamanho;

    return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    int retorno = 0;

    if (!valida_posicao(posicao))
        retorno = POSICAO_INVALIDA;
    else
    {
        posicao--;
        // testar se existe a estrutura auxiliar
        if (tem_estrutura(posicao))
        {
            if (estrutura_vaga(&vetorPrincipal[posicao]))
            {
                //insere
                vetorPrincipal[posicao].valores[vetorPrincipal[posicao].qtd] = valor;
                vetorPrincipal[posicao].qtd++;
                retorno = SUCESSO;
            }
            else
                retorno = SEM_ESPACO;

        }
        else
        {
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }

    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    int retorno = SUCESSO;
    posicao--;
    if (!valida_posicao(posicao + 1))
        retorno = POSICAO_INVALIDA;
    else if (!tem_estrutura(posicao))
        retorno = SEM_ESTRUTURA_AUXILIAR;
    else if (!(vetorPrincipal[posicao].qtd))
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    else
        vetorPrincipal[posicao].qtd--;
    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    int retorno = SUCESSO;
    posicao--;
    int pos = BuscaValor(posicao, valor);
    if (!valida_posicao(posicao + 1))
        retorno = POSICAO_INVALIDA;
    else if (!tem_estrutura(posicao))
        retorno = SEM_ESTRUTURA_AUXILIAR;
    else if (!vetorPrincipal[posicao].qtd)
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    else if (pos < 0)
        retorno = NUMERO_INEXISTENTE;
    else
    {
        for (int i = pos; i < vetorPrincipal[posicao].qtd-1; i++)
        {
            vetorPrincipal[posicao].valores[i] = vetorPrincipal[posicao].valores[i + 1];
        }
        vetorPrincipal[posicao].qtd--;
    }
    return retorno;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > 10)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{

    int retorno = 0;
    posicao--;
    if (!valida_posicao(posicao + 1))
        retorno = POSICAO_INVALIDA;
    else if (!tem_estrutura(posicao))
        retorno = SEM_ESTRUTURA_AUXILIAR;
    else
    {
        for (int i = 0; i < vetorPrincipal[posicao].qtd; i++)
            vetorAux[i] = vetorPrincipal[posicao].valores[i];
        retorno = SUCESSO;
    }

    return retorno;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{

    int retorno = 0;

    retorno = getDadosEstruturaAuxiliar(posicao, vetorAux);
    if (retorno == SUCESSO)
        ordena_vetor(vetorAux, vetorPrincipal[posicao-1].qtd);
    
    return retorno;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{

    int retorno = 0;
    int tam = 0;
    int k = 0;
    for (int i = 0; i < TAM; i++)
    {
        if (tem_estrutura(i) && vetorPrincipal[i].qtd > 0)
        {
            tam+= vetorPrincipal[i].qtd;
            for (int j = 0; j < vetorPrincipal[i].qtd; j++)
                vetorAux[k++] = vetorPrincipal[i].valores[j];

        }
    }
    if (tam)
        retorno = SUCESSO;
    else
        retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    return retorno;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{

    int retorno = 0;
    retorno = getDadosDeTodasEstruturasAuxiliares(vetorAux);
    ordena_vetor(vetorAux, get_qtd(vetorPrincipal));
    return retorno;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    posicao--;
    if (!valida_posicao(posicao + 1))
        return POSICAO_INVALIDA;
    if (!tem_estrutura(posicao))
        return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[posicao].tamanho + novoTamanho <= 0)
        return NOVO_TAMANHO_INVALIDO;

    // testando alocação
    vetorPrincipal[posicao].tamanho += novoTamanho;
    vetorPrincipal[posicao].valores = realloc(vetorPrincipal[posicao].valores, vetorPrincipal[posicao].tamanho);

    if (vetorPrincipal[posicao].valores == NULL)
        return SEM_ESPACO_DE_MEMORIA;

    if (vetorPrincipal[posicao].tamanho < vetorPrincipal[posicao].qtd)
        vetorPrincipal[posicao].qtd = vetorPrincipal[posicao].tamanho;
    return SUCESSO;

}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{

    int retorno = 0;
    posicao--;
    if (!valida_posicao(posicao + 1))
        retorno = POSICAO_INVALIDA;
    else if (!tem_estrutura(posicao))
        retorno = SEM_ESTRUTURA_AUXILIAR;
    else if (!vetorPrincipal[posicao].qtd)
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    else
        retorno = vetorPrincipal[posicao].qtd;

    return retorno;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
void Inserir(No *inicio, int valor){
    No *novo = (No*) malloc(sizeof(No));
    novo->conteudo = valor;
    novo->prox = NULL;

    if(inicio->prox == NULL){
        inicio->prox = novo;
    }else{

        No *aux = inicio->prox;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = novo;
    }
}
No *montarListaEncadeadaComCabecote()
{
    No *inicioLista = (No*) malloc(sizeof(No));
    inicioLista->prox = NULL;
    int tamanho = get_qtd(vetorPrincipal);
    int *todos = malloc(tamanho * sizeof(int));
    int retorno = getDadosDeTodasEstruturasAuxiliares(todos);
    for (int i = 0; i < tamanho; i++)
    {
        Inserir(inicioLista, todos[i]);
    }
    free(todos);
    if (retorno == SUCESSO)
        return inicioLista;

    return NULL;
}

/*
Objetivo: retorna os números da lista encadeada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    No *aux = inicio->prox;
    int j = 0;
    while (aux != NULL)
    {
        vetorAux[j++] = aux->conteudo;
        aux = aux->prox;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    No *aux = *inicio;
    No *prox;
    while(aux != NULL)
    {
        prox = aux->prox;
        free(aux);
        aux = prox;
    }
    *inicio = NULL;

}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar()
{
    for (int i = 0; i < TAM; i++)
    {
        vetorPrincipal[i].valores = NULL;
        vetorPrincipal[i].qtd = 0;
        vetorPrincipal[i].tamanho = 0;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
    for (int i = 0; i < TAM; i++)
    {
        if (vetorPrincipal[i].valores != NULL)
        {
            free(vetorPrincipal[i].valores);
            vetorPrincipal[i].valores = NULL;
            vetorPrincipal[i].tamanho = 0;
            vetorPrincipal[i].qtd = 0;
        }
    }
}
