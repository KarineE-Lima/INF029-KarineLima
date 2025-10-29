#include <stdio.h>
#define MAX 50


typedef struct pessoa {
    char nome[MAX];
    char data_nasc[11];
    char cpf[16];
    char sexo;
}pessoa;
int valida_nome(char *nome);
int validaSexo(char sexo);
int validaCPF(char *cpf);
pessoa cadastrar_cliente(pessoa *cliente);
void imprime_pessoa(pessoa *p);
int validaData(char *data_nasc);


int main() {
    pessoa cliente;
    cadastrar_cliente(&cliente);
    imprime_pessoa(&cliente);

    return 0;
}

int valida_nome(char *nome) {
    int i = 0;
    for(i = 0; nome[i] != '\n' && nome[i] != '\n'; i++);
    if (i > 20 || i < 3)
        return 0;
    return 1;
}
int validaSexo(char sexo) {
    if (sexo <= 'a' && sexo >= 'z') {
        sexo = sexo - 'a' + 'A';
    }
    if (sexo == 'F' || sexo == 'M' || sexo == 'O') {
        return 1;
    }
    return 0;
}
int pot(int num, int p) {
    int a = 1;
    for (int i = 1; i <= p; i++)
        a *= num;
    return a;
}
int validaCPF(char *cpf) {
    int i, j, k, num[11], soma1, soma2;
    for(i = 0; cpf[i] != '\n' && cpf[i] != '\0'; i++);
    if (i < 11 || i > 15) return 0;
    for (j = 0, k = 0; j < i; j++) {
        if (cpf[j] >= '0' && cpf[j] <= '9')
            num[k++] = cpf[j] - '0';
    }
    for (j = 0, k = 10, soma1 = 0; k >= 2; k--, j++)
        soma1 += num[j] * k;
    for (j = 0, k = 11, soma2 = 0; k >= 2; k--, j++)
        soma2 += num[j] * k;
    int dig1 = (soma1 % 11 == 0 || soma1 % 11 == 1)? 0 : 11 - (soma1 % 11);
    int dig2 = (soma2 % 11 == 0 || soma2 % 11 == 1)? 0 : 11 - (soma2 % 11);
    if (dig1 != num[9] || dig2 != num[10]) return 0;
    return 1;
}
int validaData(char *data_nasc) {
    int i, j, k, data[3];
    for(i = 0; data_nasc[i] != '\0' && data_nasc[i] != '\n'; i++);
    if (i > 10 || i < 6) return 0;
    for (k = 0, j = i - 1; k < 3; k++) {
        data[k] = 0;
        i = 0;
        while (data_nasc[j] >= '0' && data_nasc[j] <= '9') {
            data[k] += (data_nasc[j] - '0' ) * pot(10, i);
            j--;
            i++;
        }
        j--;
    }
    int dias_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if((data[0] % 4 == 0 && data[0] % 100 != 0) || (data[0] % 4 == 0 && data[0] % 400 == 0))
        dias_mes[1]++;

    if(data[0] < 1900 || data[0] > 2025)
        return 0;
    if(data[1] < 1 || data[1] > 12)
        return 0;
    if(data[2] < 1 || data[2] > dias_mes[data[1] - 1])
        return 0;
    return 1;
}
pessoa cadastrar_cliente(pessoa *cliente) {
    do {
        printf("Digite o nome:");
        fgets(cliente->nome, MAX, stdin);
        fflush(stdin);
        if (!valida_nome(cliente->nome))
            printf("Nome invalido!\n");
    }while (!valida_nome(cliente->nome));
   do {
        printf("Digite a data de nascimento[dd/mm/aaaa]:");
        fgets(cliente->data_nasc, 11, stdin);
        fflush(stdin);
       if (!validaData(cliente->data_nasc))
           printf("Data nascimento invalido!\n");

    } while (!validaData(cliente->data_nasc));
    do {
        printf("Digite o CPF:");
        fgets(cliente->cpf, 16, stdin);
        fflush(stdin);

        if (!validaCPF(cliente->cpf))
            printf("CPF invalido!\n");

    } while (!validaCPF(cliente->cpf));

    do {
        printf("Digite o sexo:");
        scanf("%c", &cliente->sexo);
        fflush(stdin);

        if (!validaSexo(cliente->sexo))
            printf("Sexo invalido!\n");

    } while (!validaSexo(cliente->sexo));
}
void imprime_pessoa(pessoa *p) {
    printf("Nome:%s", p->nome);
    printf("Data de nascimento: %s\n", p->data_nasc);
    printf("CPF: %s", p->cpf);
    printf("Sexo: %c\n", p->sexo);
    printf("\n");
}