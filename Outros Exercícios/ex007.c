#include <stdio.h>
#define MAX 50

void Ler3palavras(char p[3][MAX]){
    for(int i = 0; i < 3; i++) {
        fgets(p[i], MAX, stdin);
        fflush(stdin);
    }
}
int main(){
    char palavras[3][MAX];
    Ler3palavras(palavras);
    for(int i = 0; i < 3; i++)
        puts(palavras[i]);

    return 0;
}