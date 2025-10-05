#include <stdio.h>
#include <string.h>
#define TAM 3
#define MAX_N 50
#define CPF 16
#define LISTA_CHEIA 1
#define LISTA_VAZIA 0

typedef struct data{
	int dia, mes, ano;
} data;

typedef struct pessoa{
	int matricula;
	char nome[MAX_N];
	char sexo;
	data data_nascimento;
	char cpf[CPF];
	int qtd_displinas;
} pessoa;

typedef struct disciplina{
	char nome[MAX_N];
	int codigo;
	int semestre;
	int vagas;
	pessoa professor;
	pessoa alunos[TAM];
} disciplina;

int menu_geral();
int menu_pessoa(char c[15]);
int menu_disciplina();
void cadastrar_pessoa(pessoa *a, int *qtd);
void listar_pessoa(pessoa a[TAM], int qtd, char c[MAX_N]);
int buscar_pessoa(pessoa a[TAM], int qtd, int mat_busc);
void atualizar_pessoa(pessoa a[TAM], int qtd);
void excluir_pessoa(pessoa a[TAM], int *qtd);

int main(){
	int opcao, op_aluno, op_prof, op_disciplina, qtd_aluno = 0, qtd_prof = 0, qtd_disciplina = 0;
	pessoa aluno[TAM];
	pessoa prof[TAM];
	char categoria[15];
	do{
		opcao = menu_geral();
		switch (opcao) {
			case 0:
				printf("Saindo...\n");
				break;
			case 1:
				do {
					strcpy(categoria, "Alunos");
					printf("Menu Aluno\n");
					op_aluno = menu_pessoa(categoria);
					switch (op_aluno) {
						case 0:
							printf("Saindo do menu aluno...\n");
							break;
						case 1:
							printf("Cadastro Aluno\n");
							cadastrar_pessoa(&aluno[qtd_aluno], &qtd_aluno);
							break;
						case 2:
							printf("Listar Aluno\n");
							listar_pessoa(aluno, qtd_aluno, categoria);
							break;
						case 3:
							printf("Atualizar Aluno\n");
							atualizar_pessoa(aluno, qtd_aluno);
							break;
						case 4:
							printf("Excluir Aluno\n");
							excluir_pessoa(aluno, &qtd_aluno);
							break;
						default: printf("Opção inválida!\n");
					}
				}while (op_aluno != 0);
				break;
			case 2:
				printf("Menu Professor\n");
				do {
					strcpy(categoria, "Professores");
					op_prof = menu_pessoa(categoria);
					switch (op_prof) {
						case 0: printf("Saindo do menu professor...\n"); break;
						case 1:
							printf("Cadastro Professor\n");
							cadastrar_pessoa(&prof[qtd_prof], &qtd_prof);
							break;
						case 2:
							printf("Listar Professor\n");
							listar_pessoa(prof, qtd_prof, categoria);
							break;
						case 3:
							printf("Atualizar Professor\n");
							atualizar_pessoa(prof, qtd_prof);
							break;
						case 4:
							printf("Excluir Professor\n");
							excluir_pessoa(prof, &qtd_prof);
							break;
						default: printf("Opção inválida!\n");
					}
				} while (op_prof != 0);
				break;
			case 3:
				do {
					printf("Menu Disciplina\n");
					op_disciplina = menu_disciplina();
					switch (op_disciplina) {
						case 0: printf("Saindo do menu disciplina...\n"); break;
						case 1: printf("Cadastro Disciplina\n"); break;
						case 2: printf("Listar Disciplina\n"); break;
						case 3: printf("Listar Disciplina(Aluno + Dados)\n"); break;
						case 4: printf("Incluir aluno\n"); break;
						case 5: printf("Excluir aluno\n"); break;
						default: printf("Opção inválida!\n");
					}
				} while(op_disciplina != 0);
				break;
			default:
				printf("Opção inválida!\n");
		}
	} while (opcao != 0);
	return 0;
}
// Indica se a lista está cheia ou vazia
int tam_lista(int qtd) {
	if (qtd == TAM)
		return LISTA_CHEIA;
	if (qtd == 0)
		return LISTA_VAZIA;
	return 2;
}
int menu_geral(){
	int opcao;
	printf("Insira as opções:\n");
	printf("0 - SAIR\n");
	printf("1 - Módulo Aluno\n");
	printf("2 - Módulo Professor\n");
	printf("3 - Módulo Disciplina\n");
	scanf("%d", &opcao);
	return opcao;
}
int menu_pessoa(char c[15]){
	int opcao;
	printf("0 - SAIR\n");
	printf("1 - Incluir %s\n", c);
	printf("2 - Listar %s\n", c);
	printf("3 - Atualizar %s\n", c);
	printf("4 - Excluir %s\n", c);
	scanf("%d", &opcao);
	return opcao;
}
int menu_disciplina(){
	int opcao;
	printf("0 - SAIR\n");
	printf("1 - Cadastrar Disciplina\n");
	printf("2 - Listar Disciplinas\n");
	printf("3 - Listar uma Disciplina(dados + alunos)\n");
	printf("4 - Inserir aluno\n");
	printf("5 - Excluir aluno\n");

	scanf("%d", &opcao);
	return opcao;
}
void cadastrar_pessoa(pessoa *a, int *qtd){
	if (tam_lista(*qtd) == LISTA_CHEIA) {
		printf("Lista cheia!\n");
	} else {
		printf("Insira a matrícula: ");
		scanf("%d", &(a->matricula));
		fflush(stdin);
		printf("Insira o nome: ");
		fgets(a->nome, MAX_N, stdin);
		fflush(stdin);
		printf("Insira o sexo[F/M/O]: ");
		scanf("%c", &(a->sexo));
		fflush(stdin);
		printf("Insira a data de nascimento: ");
		scanf("%d %d %d", &(a->data_nascimento.dia), &(a->data_nascimento.mes), &(a->data_nascimento.ano));
		fflush(stdin);
		printf("Insira o CPF: ");
		fgets(a->cpf, CPF, stdin);
		fflush(stdin);
		printf("\nUsuário cadastrado com sucesso!\n");
		*qtd = *qtd + 1;
	}
}
int menu_listar(char c[MAX_N]) {
	int opcao;
	printf("1 - Listar todos os %s\n", c);
	printf("2 - Listar %s ordenados por nome\n", c);
	printf("3 - Listar %s ordenados por data de nascimento\n", c);
	printf("4 - Listar %s por sexo\n", c);
	scanf("%d", &opcao);
	fflush(stdin);
	return opcao;
}
void imprimir_pessoa(pessoa a[TAM], int qtd) {
	for (int i = 0; i < qtd; i++) {
		printf("Matricula: %d\n", a[i].matricula);
		printf("Nome: %s", a[i].nome);
		printf("Sexo: %c\n", a[i].sexo);
		printf("Data de nascimento: %02d/%02d/%02d\n", a[i].data_nascimento.dia, a[i].data_nascimento.mes, a[i].data_nascimento.ano);
		printf("CPF: %s\n", a[i].cpf);
	}
}

void listar_pessoa(pessoa a[TAM], int qtd, char c[MAX_N]) {
	int op_lista;
	if (tam_lista(qtd) == LISTA_VAZIA) {
		printf("Lista Vazia!\n");
	} else {
		do {
			op_lista = menu_listar(c);
			switch (op_lista) {
				case 1:
					printf("Listar todos os %s\n", c);
					imprimir_pessoa(a, qtd);
					break;
				case 2:
					printf("Listar %s ordenados por nome\n", c);
					imprimir_pessoa(a, qtd);
					break;
				case 3:
					printf("Listar %s ordenados por data de nascimento\n", c);
					imprimir_pessoa(a, qtd);
					break;
				case 4:
					printf("Listar %s por sexo [M/F/O]\n", c);
					break;
				default: printf("Opção inválida!\n");
			}
		} while (op_lista < 1 || op_lista > 4);
	}

}
// retorna a posição da pessoa no vetor, se não achar, retorna -1:
int buscar_pessoa(pessoa a[TAM], int qtd, int mat_busc){
	for (int i = 0; i < qtd; i++) {
		if (mat_busc == a[i].matricula) {
			return i;
		}
	}
	return -1;
}
void atualizar_pessoa(pessoa a[TAM], int qtd) {
	int pos, opcao, matricula;
	char nome[MAX_N];
	if (tam_lista(qtd) == LISTA_VAZIA) {
		printf("Lista Vazia!\n");
	} else {
		do {
			printf("Insira a matrícula: ");
			scanf("%d", &matricula);
			pos = buscar_pessoa(a, qtd, matricula);
			if (pos < 0) {
				printf("Matrícula não encontrada.\n");
			} else {
				printf("Selecione o dado a ser alterado:\n");
				printf("1 - Matrícula\n");
				printf("2 - Nome\n");
				printf("3 - Sexo\n");
				printf("4 - Data de Nascimento\n");
				printf("5 - CPF\n");
				scanf("%d", &opcao);
				fflush(stdin);
				switch (opcao) {
					case 1:
						printf("Insira a nova matrícula: ");
						scanf("%d", &a[pos].matricula);
						fflush(stdin);
						break;
					case 2:
						printf("Insira o novo nome: ");
						fgets(nome, MAX_N, stdin);
						fflush(stdin);
						strcpy(a[pos].nome, nome);
						break;
					case 3:
						printf("Insira o sexo: ");
						scanf("%c", &a[pos].sexo);
						fflush(stdin);
						break;
					case 4:
						printf("Insira a data de nascimento: ");
						scanf("%d %d %d", &a[pos].data_nascimento.dia, &a[pos].data_nascimento.mes, &a[pos].data_nascimento.ano);
						fflush(stdin);
						break;
					case 5:
						printf("Insira o CPF: ");
						fgets(a[pos].cpf, CPF, stdin);
						fflush(stdin);
						break;
					default: printf("Opção inválida!\n");
				}
			}
		} while (pos < 0 && (opcao < 1 || opcao > 5));
		printf("\nDados alterados com sucesso!\n");
	}

}
// exclui usuario a partir da matrícula
void excluir_pessoa(pessoa a[TAM], int *qtd) {
	int pos, matricula;
	if (tam_lista(*qtd) == LISTA_VAZIA) {
		printf("Lista Vazia!\n");
	} else {
		do {
			printf("Insira a matrícula: ");
			scanf("%d", &matricula);
			pos = buscar_pessoa(a, *qtd, matricula);
			if (pos < 0) {
				printf("Matrícula não encontrada.\n");
			} else {
				for (int i = pos; i < *qtd - 1; i++) {
					a[i].matricula = a[i + 1].matricula;
					strcpy(a[i].nome, a[i + 1].nome);
					a[i].sexo = a[i + 1].sexo;
					a[i].data_nascimento.dia = a[i + 1].data_nascimento.dia;
					a[i].data_nascimento.mes = a[i + 1].data_nascimento.mes;
					a[i].data_nascimento.ano = a[i + 1].data_nascimento.ano;
					strcpy(a[i].cpf, a[i + 1].cpf);
				}
				printf("\nMatrícula Excluída com sucesso!\n");
			}
		} while (pos < 0);
		*qtd = *qtd - 1;
	}
}