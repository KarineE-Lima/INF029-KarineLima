#include <stdio.h>
#define DIM 10

typedef struct bat{
    char tabuleiro[DIM][DIM];
    char barco4[4];
    char barco3[3];
    char barco1[1];
}batalha;

int qtd_barco_tam4 = 1;
int qtd_barco_tam3 = 1;
int qtd_barco_tam1 = 3;

void imprime_jogo(char jogo[DIM][DIM]);

int main() {
    batalha jogador1;
    batalha jogador2;
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            jogador1.tabuleiro[i][j] = ' ';
            jogador2.tabuleiro[i][j] = ' ';
        }
    }
    imprime_jogo(jogador1.tabuleiro);

    return 0;
}
void imprime_jogo(char jogo[DIM][DIM]) {
    int i, j, k;

    for (i = 0; i < DIM; i++) {

        if (i == 0) {
            for (k = 0; k < DIM; k++)
                printf("  %d ", k + 1);
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