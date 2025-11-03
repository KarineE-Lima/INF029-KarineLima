#include <stdio.h>

void imprime_jogo(char jogo[3][3]);
int valida_posicao (char jogo[3][3], char posicao[]);
int ganha_jogo(char jogo[3][3]);

int main() {
    char jogo[3][3];
    char posicao[3];
    char jogador;
    int i, j, round = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            jogo[i][j] = ' ';
        }
    }

    while (!ganha_jogo(jogo) && round < 9) {
        imprime_jogo(jogo);
        jogador = (round % 2 == 0)? 'X' : 'O';

        do {
            printf("Informe a posição: ");
            fgets(posicao, 3, stdin);
            fflush(stdin);

            if (!valida_posicao(jogo, posicao))
                printf("Insira uma posição válida!\n");

            if (valida_posicao(jogo, posicao) == 2)
                printf("Essa posição já foi preenchida!\n");

        } while (!valida_posicao(jogo, posicao) || valida_posicao(jogo, posicao) == 2);

        int linha = posicao[0] - 'A';
        int coluna = posicao[1] - '0' - 1;

        jogo[linha][coluna] = jogador;

        round++;

        if (ganha_jogo(jogo) == 1) {
            imprime_jogo(jogo);
            printf("Jogador 1 venceu!\n");
        }

        if (ganha_jogo(jogo) == 2) {
            imprime_jogo(jogo);
            printf("Jogador 2 venceu!\n");
        }

        if (!ganha_jogo(jogo) && round == 9) {
            imprime_jogo(jogo);
            printf("Empate!\n");
        }

    }

    return 0;
}

void imprime_jogo(char jogo[3][3]) {
    int i, j, k;
    char linha;
    for (i = 0, linha = 'A'; i < 3; i++, linha++) {
        if (i == 0) {
            for (k = 0; k < 3; k++) {
                printf("    %d", k + 1);
            }
            printf("\n");
        }
        for (j = 0; j < 3; j++) {
            if (j == 0)
                printf("%c ", linha);
            printf("| %c ", jogo[i][j]);
            if (j == 2)
                printf("|");
        }

        printf("\n  ");
        if (i < 2) {
            for (k = 0; k < 6; k++)
                printf(" -");
        }

        printf("\n");
    }
}
int valida_posicao (char jogo[3][3], char *posicao) {
    if (posicao[0] < 'A' || posicao[0] > 'C') return 0;
    if (posicao[1] < '1' || posicao[1] > '3') return 0;
    if (jogo[posicao[0] - 'A'][posicao[1] - '0' - 1] != ' ') return 2;
    return 1;
}
int ganha_jogo(char jogo[3][3]) {
    int i, j, k;
    char jogador1[] = {'X', 'X', 'X'};
    char jogador2[] = {'O', 'O', 'O'};
    for (i = 0; i < 3; i++) {
        // Jogador 1
        // Horizontal
        for (j = 0; jogo[i][j] == jogador1[j]; j++);
        if (j == 3)
            return 1;
        // Vertical
        for (j = 0; jogo[j][i] == jogador1[j]; j++);
        if (j == 3)
            return 1;
        // Diagonal principal
        for (j = 0;jogo[j][j] == jogador1[j] && j < 3; j++);
        if (j == 3)
            return 1;
        // Diagonal secundária
        for (j = 0;jogo[j][2-j] == jogador1[j] && j < 3; j++);
        if (j == 3)
            return 1;
        // Jogador 2
        // Horizontal
        for (k = 0; jogo[i][k] == jogador2[k]; k++);
        if (k == 3)
            return 2;
        // Vertical
        for (k = 0; jogo[k][i] == jogador2[k]; k++);
        if (k == 3)
            return 2;
        // Diagonal principal
        for (k = 0; jogo[k][k] == jogador2[k] && k < 3; k++);
        if (k == 3)
            return 2;
        // Diagonal secundária
        for (k = 0; jogo[k][2-k] == jogador2[k] && k < 3; k++);
        if (k == 3)
            return 2;
    }
    return 0;
}