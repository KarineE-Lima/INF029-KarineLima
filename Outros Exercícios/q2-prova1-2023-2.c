#include <stdio.h>
#define MAX 16
#define QTD_E 4
#define QTD_S 3

typedef struct v{
    int retorno;
    int entrada[QTD_E];
    int saida[QTD_S];
} varetas;

void menu(void)
{
    printf("Escolha: \n");
    printf("1 - Verificar varetas\n");
    printf("2 - Sair\n");
}
int triangulo(int a, int b, int c)
{
    if (a > b + c || b > a + c || c > a + b)
        return 0;
    return 1;
}
varetas validaEntrada(char *E)
{
    varetas v;
    int i, j;
    for (i = 0; i < QTD_E; i++)
        v.entrada[i] = 0;
    for (i = 0, j = 0; i < QTD_E; i++){
        while (E[j] != '\n' && E[j] != '-' && E[j] != '\0'){
            if ((E[j] < '0' || E[j] > '9') && E[j] != '-' && E[j] != '\0' && E[j] != '\n'){
                v.retorno = 0;
                return v;
            }
            v.entrada[i] = (v.entrada[i] * 10) + (E[j] - '0');
            j++;
        }
        j++;
        if (v.entrada[i] < 1 || v.entrada[i] > 100){
            v.retorno = 0;
            return v;
        }
    }
    v.retorno = 1;
    return v;
}
varetas verificaVaretas(varetas v)
{
    if (triangulo(v.entrada[0], v.entrada[1], v.entrada[2])){
        v.saida[0] = v.entrada[0];
        v.saida[1] = v.entrada[1];
        v.saida[2] = v.entrada[2];
        v.retorno = 1;
        return v;
    }
    if (triangulo(v.entrada[1], v.entrada[2], v.entrada[3]))
    {
        v.saida[0] = v.entrada[1];
        v.saida[1] = v.entrada[2];
        v.saida[2] = v.entrada[3];
        v.retorno = 1;
        return v;
    }
    if (triangulo(v.entrada[2], v.entrada[3], v.entrada[0]))
    {
        v.saida[0] = v.entrada[2];
        v.saida[1] = v.entrada[3];
        v.saida[2] = v.entrada[0];
        v.retorno = 1;
        return v;
    }
    if (triangulo(v.entrada[3], v.entrada[0], v.entrada[1]))
    {
        v.saida[0] = v.entrada[3];
        v.saida[1] = v.entrada[0];
        v.saida[2] = v.entrada[1];
        v.retorno = 1;
        return v;
    }
    v.retorno = 0;
    return v;
}
int main(void)
{
    char Entrada[MAX];
    varetas vareta;
    int op;
    do
    {
        menu();
        scanf("%d", &op);
        fflush(stdin);
        switch (op)
        {
            case 1:
            do
            {
                printf("Insira o valor das varetas: ");
                fgets(Entrada, MAX, stdin);
                fflush(stdin);
                vareta = validaEntrada(Entrada);
                if (!vareta.retorno)
                    printf("Entrada Inválida!\n");
            }while (!vareta.retorno);
            vareta = verificaVaretas(vareta);
            if (!vareta.retorno)
            {
                printf("Varetas não forma triângulo\n");
            } else
            {
                printf("Conjunto de três varetas forma triÂngulo: ");
                for (int i = 0; i < QTD_S; i++)
                {
                    printf("%d ", vareta.saida[i]);
                }
            }
            break;
            case 2: break;
            default: printf("Operação Inválida!\n");
        }

    }while (op != 2);

}