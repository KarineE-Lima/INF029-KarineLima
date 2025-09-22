#include <stdio.h>
#define TAM 3

typedef struct carro{
	int ano, chassi;
	float preco;
} tipo_carro;

void listar_carros(tipo_carro lista[TAM], int qtd);
void cadastrar(tipo_carro lista[TAM], int qtd);
void editar(tipo_carro lista[TAM], int qtd);
void excluir(tipo_carro lista[TAM], int qtd);
int menu();

int main(){
	tipo_carro carros[TAM];
	int i = 0; 
	int opcao, selec, j, terminar;
	
	do{
		opcao = menu();
		switch(opcao){
			case 0: printf("Saindo...\n"); break;
			case 1: 
				if(i == TAM){
					printf("Lista de carros cheia, exclua algum.");
				} else {
					cadastrar(carros, i);
					i++;
				}
				break;
			case 2: 
				if(i == 0){
					printf("Lista de carros vazia.");
				} else {
					printf("-----Listando Carros-------\n"); 
					listar_carros(carros, i);
				}
				break;
			case 3: 
				if(i == 0){
					printf("Não há carros para atualizar.");
				} else {
					printf("-----Atualizar Carro-------\n"); 
					listar_carros(carros, i);
					editar(carros, i);
				}
				break;
			case 4: 
				if(i == 0){
					printf("Não há carros para excluir.");
				} else {
					printf("-----Excluir Carro-------\n"); 
					listar_carros(carros, i);
					excluir(carros, i);
					i--;
				}
				break;
			default: 
				printf("Insira uma opção válida!!\n"); 
				break;
		}
	} while(opcao != 0);
	return 0;
}

int menu(){
	int opcao;
	printf("\n----------------OPÇÕES--------------:\n");
	printf("0 - SAIR\n");
	printf("1 - CADASTRAR\n");
	printf("2 - LISTAR\n");
	printf("3 - ATUALIZAR\n");
	printf("4 - EXCLUIR\n");
	scanf("%d", &opcao);
	system("cls");
	return opcao;
}
void excluir(tipo_carro lista[TAM], int qtd){
	int terminar = 0, selec, j;
	while(terminar == 0){
		printf("Insira o carro que você quer excluir: ");
		scanf("%d", &selec);
		if(selec >= qtd || selec < 0){
			printf("Insira um carro existente.\n");
		} else {
			for(j = selec; j < qtd; j++){
				lista[j].ano = lista[j+1].ano;
				lista[j].chassi = lista[j+1].chassi;
				lista[j].preco = lista[j+1].preco;
			}
			terminar = 1;
		}
	}	
}
void editar(tipo_carro lista[TAM], int qtd){
	int terminar = 0, selec;
	while(terminar == 0){
		printf("Insira o carro que você quer atualizar: ");
		scanf("%d", &selec);
		if(selec >= qtd || selec < 0){
			printf("Insira um carro existente.\n");
		} else {
			printf("Insira o novo ano do carro %d: ", selec);
			scanf("%d", &lista[selec].ano);
			printf("Insira o novo preço do carro %d: ", selec);
			scanf("%f", &lista[selec].preco);
			terminar = 1;
		}
	}
}
void listar_carros(tipo_carro lista[TAM], int qtd){
	int j;
	for(j = 0; j < qtd; j++){
		printf("\nCarro %d:\n", j);
		printf("Ano: %d \nChassi: %d\nValor: R$%.2f\n", lista[j].ano, lista[j].chassi, lista[j].preco);
	}
}
void cadastrar(tipo_carro lista[TAM], int qtd){
	printf("-----Cadastrar Carro-------\n"); 
	printf("Insira o ano do carro: ");
	scanf("%d", &lista[qtd].ano);
	printf("Insira o chassi do carro: ");
	scanf("%d", &lista[qtd].chassi);
	printf("Insira o valor do carro: ");
	scanf("%f", &lista[qtd].preco);
}
