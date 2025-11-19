#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 10

typedef struct bat{
    char tabuleiro[DIM][DIM];
    char jogada[DIM][DIM];
}batalha;

int qtd_barco_tam4 = 1;
int qtd_barco_tam3 = 1;
int qtd_barco_tam1 = 3;

/*
 * [V] Criar a função imprime_jogo
 * [V] Criar a função add_barco
 * [V] Criar a função valida_posição
 * [V] Criar a função converte_posição
 * [V] Criar a função ganha_jogo
 * [V] Criar uma cópia de cada matriz sem os barcos, mas com as jogadas certas e erradas - dentro da struct
 * [V] Criar a função atira (ou deixa no main) - se atirar certo pode atirar de novo, caso contrário,
 * passa para outro jogador - usar a valida posição para validar a jogada
 * [V] Criar o espaço para jogador1 e jogador2
 */
void imprime_jogo(char jogo[DIM][DIM]);
void add_barco(char jogo[DIM][DIM]);
int valida_posicao(char *pos, char jogo[DIM][DIM], int tam);
void converte_posicao(char *pos, int *ini, int *fim, int tam);
int ganha_jogo(char jogo[DIM][DIM]);
void atira(char jogoT[DIM][DIM], char jogoA[DIM][DIM]);
void limpatela();
void limpa_buffer();

int main() {
    batalha jogador1;
    batalha jogador2;

    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            jogador1.tabuleiro[i][j] = ' ';
            jogador1.jogada[i][j] = ' ';
            jogador2.tabuleiro[i][j] = ' ';
            jogador2.jogada[i][j] = ' ';
        }
    }
    printf("------------- Vez do jogador 1 ----------------\n");

    imprime_jogo(jogador1.tabuleiro);
    add_barco(jogador1.tabuleiro);

    limpatela();

    printf("------------- Vez do jogador 2 ----------------\n");

    imprime_jogo(jogador2.tabuleiro);
    add_barco(jogador2.tabuleiro);

    limpatela();

    while (!ganha_jogo(jogador1.tabuleiro) && !ganha_jogo(jogador2.tabuleiro)) {

        printf("------------- Vez do jogador 1 ----------------\n");

        printf("Seu tabuleiro: \n");
        imprime_jogo(jogador1.tabuleiro);

        atira(jogador2.tabuleiro, jogador1.jogada);

        limpatela();

        if (ganha_jogo(jogador2.tabuleiro)){
            printf("Jogador 1 venceu!\n");
            imprime_jogo(jogador1.tabuleiro);
            imprime_jogo(jogador2.tabuleiro);
            break;
        }

        printf("------------- Vez do jogador 2 ----------------\n");

        printf("Seu tabuleiro: \n");
        imprime_jogo(jogador2.tabuleiro);

        atira(jogador1.tabuleiro, jogador2.jogada);

        limpatela();

        if (ganha_jogo(jogador1.tabuleiro))
        {
            printf("Jogador 2 venceu!\n");
            imprime_jogo(jogador1.tabuleiro);
            imprime_jogo(jogador2.tabuleiro);
            break;
        }

    }
    printf("Enter para Finalizar...\n");
    while ((getchar()) != '\n');

    return 0;
}
void imprime_jogo(char jogo[DIM][DIM]) {
    int i, j, k;

    for (i = 0; i < DIM; i++) {

        if (i == 0) {
            for (k = 0; k < DIM; k++)
                printf("   %d", k + 1);
            printf("\n");
        }

        for (j = 0; j < DIM; j++) {
            if (j == 0)
                printf("%c ", i + 'A');

            printf("| %c ", jogo[i][j]);

            if (j == DIM - 1)
                printf("|");

        }
        printf("\n");
    }
}
void add_barco(char jogo[DIM][DIM]) {
    /*
     * Solicita a posição inicial e final do barco
     * Chama a posição valida para validar
     * Se válido, chama a função converte para coverter as posições
     * Se não, avisa ao usuário e solicita novamente
     */

    char posicoes[8];
    int pi[2], pf[2];
    int i, j;

    do {
        printf("Insira a posição inicial e final do barco de tamanho 4: ");
        fgets(posicoes, 8, stdin);
        limpa_buffer();

        if (!valida_posicao(posicoes, jogo, 4))
            printf("Insira uma posição válida!\n");
        if (valida_posicao(posicoes, jogo, 4) == 2)
            printf("Posição já ocupada!\n");

    } while (!valida_posicao(posicoes, jogo, 4) || valida_posicao(posicoes, jogo, 4) == 2);

    converte_posicao(posicoes, pi, pf, 4);
    for (i = pi[0]; i <= pf[0]; i++) {
        for (j = pi[1]; j <= pf[1]; j++) {
            jogo[i][j] = 'N';
        }
    }
    imprime_jogo(jogo);
    do {
        printf("Insira a posição inicial e final do barco de tamanho 3: ");
        fgets(posicoes, 8, stdin);
        limpa_buffer();

        if (!valida_posicao(posicoes, jogo, 3))
            printf("Insira uma posição válida!\n");
        if (valida_posicao(posicoes, jogo, 3) == 2)
            printf("Posição já ocupada!\n");
    } while (!valida_posicao(posicoes, jogo, 3) || valida_posicao(posicoes, jogo, 3) == 2);

    converte_posicao(posicoes, pi, pf, 3);
    for (i = pi[0]; i <= pf[0]; i++) {
        for (j = pi[1]; j <= pf[1]; j++) {
            jogo[i][j] = 'N';
        }
    }
    imprime_jogo(jogo);

    for (int k = 0; k < qtd_barco_tam1; k++) {
        do {
            printf("Insira a posição do barco de tamanho 1: ");
            fgets(posicoes, 8, stdin);
            limpa_buffer();

            if (!valida_posicao(posicoes, jogo, 1))
                printf("Insira uma posição válida!\n");

            if (valida_posicao(posicoes, jogo, 1) == 2)
                printf("Posição já ocupada!\n");

        } while (!valida_posicao(posicoes, jogo, 1) || valida_posicao(posicoes, jogo, 1) == 2);

        converte_posicao(posicoes, pi, pf, 1);

        for (i = pi[0]; i <= pf[0]; i++) {
            for (j = pi[1]; j <= pf[1]; j++) {
                jogo[i][j] = 'N';
            }
        }
        imprime_jogo(jogo);
    }
}
int valida_posicao(char *pos, char jogo[DIM][DIM], int tam) {
    /*Criar função valida posição
     * recebe a posição, o tabuleiro e o tamanho do barco
     * valida o valor da posição
     * vê se a distância é o tamanho dos barcos -1
     * verifica se a posição está ocupada
     * 0 - se posição inválida, 1 - se posição vazia, 2 - se posição preenchida por barco, 3 - se estiver atingida
     */
    int pi[2], pf[2];

    if ((strlen(pos) < 2 || strlen(pos) > 4) && tam == 1) return 0;

    int i = 0, j = 0;
    converte_posicao(pos, pi, pf, tam);


    if ((pi[0] < 0 || pi[0] > 9) || (pi[1] < 0 || pi[1] > 9)) return 0;

    if ((pf[0] < 0 || pf[0] > 9) || (pf[1] < 0 || pf[1] > 9)) return 0;

    if (pi[0] != pf[0] && pi[1] != pf[1]) return 0;

    if ((pi[0] == pf[0] && pf[1] - pi[1] != tam - 1) || (pi[1] == pf[1] && pf[0] - pi[0] != tam - 1)) return 0;

    for (i = pi[0]; i <= pf[0]; i++) {
        for (j = pi[1]; j <= pf[1]; j++) {
            if (jogo[i][j] == 'N') return 2;
            if (jogo[i][j] == 'X' || jogo[i][j] == 'O') return 3;
        }
    }
    return 1;

}
void converte_posicao(char *pos, int *ini, int *fim, int tam) {
    /*
     * recebe a posicao, dois vetores e o tamanho do barco
     * converte para um vetor com as posições reais da matriz
     */
    int i = 0, j = 0;
    ini[j++] = pos[i++] - 'A';
    ini[j] = 0;

    while (pos[i] != ' ' && pos[i] != '\0' && pos[i] != '\n')
        ini[j] = (ini[j] * 10) + (pos[i++] - '0');

    ini[j] -= 1;

    if (tam > 1) {
        i++;
        j = 0;

        fim[j++] = pos[i++] - 'A';
        fim[j] = 0;
        while (pos[i] != ' ' && pos[i] != '\0' && pos[i] != '\n')
            fim[j] = (fim[j] * 10) + (pos[i++] - '0');

        fim[j] -= 1;

    } else {
        fim[0] = ini[0];
        fim[1] = ini[1];
    }

}
int ganha_jogo(char jogo[DIM][DIM]) {
    /*
     * se houver algum navio ele retorna 0, senão ele retorna 1
     */
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if (jogo[i][j] == 'N')
                return 0;
        }
    }
    return 1;
}
void atira(char jogoT[DIM][DIM], char jogoA[DIM][DIM]) {
    /*
     * recebe o jogo do adversário e a tabela de jogadas do jogador atual
     * solicita ao usuário a posição que ele quer atirar
     * chama a valida posição para informar se a posição existe, está ocupada ou se tem barco
     * imprime O se acertou
     * imprime X se não acertou
     */
    char posicao[4];
    int ini[2], fim[2];
    do {
        printf("Insira a posição que você quer atirar: ");
        fgets(posicao, 4, stdin);
        //fflush(stdin);
        limpa_buffer();
        if (!valida_posicao(posicao, jogoT, 1))
            printf("Insira uma posição válida!\n");

        if (valida_posicao(posicao, jogoT, 1) == 3)
            printf("Posição já escolhida!\n");

        if (valida_posicao(posicao, jogoT, 1) == 2) {
            converte_posicao(posicao, ini, fim, 1);
            jogoT[ini[0]][ini[1]] = 'O';
            jogoA[ini[0]][ini[1]] = 'O';
            imprime_jogo(jogoA);
        }
        if (ganha_jogo(jogoT))
            break;
        
    } while ((!valida_posicao(posicao, jogoT, 1) || valida_posicao(posicao, jogoT, 1) == 3
        || valida_posicao(posicao, jogoT, 1) == 2));
    if (valida_posicao(posicao, jogoT, 1) == 1) {
            converte_posicao(posicao, ini, fim, 1);
            jogoT[ini[0]][ini[1]] = 'X';
            jogoA[ini[0]][ini[1]] = 'X';
            imprime_jogo(jogoA);
        }

}
void limpatela()
{
    printf("Enter para continuar...\n");
    while ((getchar()) != '\n');
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void limpa_buffer()
{
#ifdef _WIN32
    fflush(stdin);
#else
    int c;
    while ((c = getchar()) != EOF && c != '\n');
#endif

}
