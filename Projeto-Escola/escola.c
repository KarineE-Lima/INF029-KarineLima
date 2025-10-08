#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define TAM 3
#define MAX_N 50
#define CPF 16
#define LISTA_CHEIA 1
#define LISTA_VAZIA 0
// ------ STRUCTS ---------
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

// --------- PROTÓTIPO DAS FUNÇÕES -----------

// Funções Menu
int menu_geral();
int menu_pessoa(char c[15]);
int menu_disciplina();
int menu_relatorio();

// Funções CRUD
void cadastrar_pessoa(pessoa *a, pessoa lista[TAM],int *qtd);
void listar_pessoa(pessoa a[TAM], int qtd, char c[MAX_N]);
int buscar_pessoa(pessoa a[TAM], int qtd, int mat_busc);
void atualizar_pessoa(pessoa a[TAM], int qtd);
void excluir_pessoa(pessoa a[TAM], int *qtd);
void cadastrar_disciplina(disciplina *d, int *qtd, pessoa prof[TAM], int qtd_p);

// Funções de validação
int validar_matricula(int matricula, pessoa lista[TAM], int qtd);
char validar_genero();
int validar_data(data d);
int validar_cpf(char cpf[CPF]);

int main(){
	int opcao, op_aluno, op_prof, op_disciplina, op_relat, qtd_aluno = 0, qtd_prof = 0, qtd_disciplina = 0;
	pessoa aluno[TAM];
	pessoa prof[TAM];
	disciplina disc[TAM];
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
							cadastrar_pessoa(&aluno[qtd_aluno], aluno, &qtd_aluno);
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
						case 0:
							printf("Saindo do menu professor...\n");
							break;
						case 1:
							printf("Cadastro Professor\n");
							cadastrar_pessoa(&prof[qtd_prof], prof, &qtd_prof);
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
						case 0:
							printf("Saindo do menu disciplina...\n");
							break;
						case 1:
							printf("Cadastro Disciplina\n");
							cadastrar_disciplina(&disc[qtd_disciplina], &qtd_disciplina, prof, qtd_prof);
							break;
						case 2: printf("Listar Disciplina\n"); break;
						case 3: printf("Atualizar Disciplina\n"); break;
						case 4: printf("Excluir Disciplina\n"); break;
						case 5: printf("Incluir aluno\n"); break;
						case 6: printf("Excluir aluno\n"); break;
						default: printf("Opção inválida!\n");
					}
				} while(op_disciplina != 0);
				break;
			case 4:
				do {
					printf("Outros Relatórios\n");
					op_relat = menu_relatorio();
					switch (op_relat) {
						case 0: printf("Saindo do menu relatorio...\n"); break;
						case 1: printf("Aniversariantes do Mês\n"); break;
						case 2: printf("Buscar pessoas\n"); break;
						default: printf("Opção Inválida!\n");
					}
				} while (op_relat != 0);
				break;
			default:
				printf("Opção inválida!\n");
		}
	} while (opcao != 0);
	return 0;
}
// Transforma as letras da string em minusculo
void minusculo(char *c, int tam){
	for(int i = 0; i < tam; i++){
		c[i] = tolower(c[i]);
	}
}

// Indica se a lista está cheia ou vazia
int tam_lista(int qtd) {
	if (qtd == TAM)
		return LISTA_CHEIA;
	if (qtd == 0)
		return LISTA_VAZIA;
	return 2;
}

// ---------- MENUS ----------
int menu_geral(){
	int opcao;
	printf("Insira as opções:\n");
	printf("0 - SAIR\n");
	printf("1 - Menu Aluno\n");
	printf("2 - Menu Professor\n");
	printf("3 - Menu Disciplina\n");
	printf("4 - Outros Relatórios\n");
	scanf("%d", &opcao);
	return opcao;
}

int menu_pessoa(char c[15]){
	int opcao;
	printf("0 - SAIR\n");
	printf("1 - Cadastrar %s\n", c);
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
	printf("3 - Atualizar Disciplina\n");
	printf("4 - Excluir Disciplina\n");
	printf("5 - Incluir aluno\n");
	printf("6 - Excluir aluno\n");

	scanf("%d", &opcao);
	fflush(stdin);
	return opcao;
}

int menu_relatorio() {
	int opcao;
	printf("0 - SAIR\n");
	printf("1 - Lista de Aniversariantes do mês\n");
	printf("2 - Buscar pessoas\n");
	scanf("%d", &opcao);
	fflush(stdin);
	return opcao;
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

// ---------- FUNÇÕES DE VALIDAÇÃO ----------

// Matrícula única
int validar_matricula(int matricula, pessoa lista[TAM], int qtd) {
	for (int i = 0; i < qtd; i++) {
		if (lista[i].matricula == matricula) {
			return 0;
		}
	}
	return 1;
}

// Gênero (F/M/O)
char validar_genero() {
	char sexo;
	do {
		printf("Insira o sexo [F/M/O]: ");
		scanf(" %c", &sexo);
		fflush(stdin);

		if (sexo >= 'a' && sexo <= 'z') {
			sexo -= 32;
		}

		if (sexo != 'F' && sexo != 'M' && sexo != 'O') {
			printf("Opção inválida! Use apenas F (Feminino), M (Masculino) ou O (Outro).\n");
		}
	} while (sexo != 'F' && sexo != 'M' && sexo != 'O');
	return sexo;
}

// Data de nascimento válida
int validar_data(data d) {
	int dias_mes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

	if ((d.ano % 4 == 0 && d.ano % 100 != 0) || (d.ano % 400 == 0)) {
		dias_mes[2] = 29;
	}

	if (d.mes < 1 || d.mes > 12) return 0;
	if (d.dia < 1 || d.dia > dias_mes[d.mes]) return 0;
	if (d.ano < 1900 || d.ano > 2025) return 0;

	return 1;
}

// CPF válido
int validar_cpf(char cpf[CPF]) {
	int i, j, soma, resto;
	int digitos[11], qtd = 0;

	for (i = 0; cpf[i] != '\0' && qtd < 11; i++) {
		if (cpf[i] >= '0' && cpf[i] <= '9') {
			digitos[qtd++] = cpf[i] - '0';
		}
	}

	if (qtd != 11) return 0;

	int iguais = 1;
	for (i = 1; i < 11; i++) {
		if (digitos[i] != digitos[0]) {
			iguais = 0;
			break;
		}
	}
	if (iguais) return 0;

	soma = 0;
	for (i = 0, j = 10; i < 9; i++, j--) soma += digitos[i] * j;
	resto = soma % 11;
	int digito1 = (resto < 2) ? 0 : 11 - resto;
	if (digito1 != digitos[9]) return 0;

	soma = 0;
	for (i = 0, j = 11; i < 10; i++, j--) soma += digitos[i] * j;
	resto = soma % 11;
	int digito2 = (resto < 2) ? 0 : 11 - resto;
	if (digito2 != digitos[10]) return 0;

	return 1;
}

// ---------- FUNÇÕES CRUD -------------

void cadastrar_pessoa(pessoa *a, pessoa lista[TAM],int *qtd){
	if (tam_lista(*qtd) == LISTA_CHEIA) {
		printf("Lista cheia!\n");
	} else {
		do {
			printf("Insira a matrícula: ");
			scanf("%d", &(a->matricula));
			fflush(stdin);
			if (!validar_matricula(a->matricula, lista, *qtd)) {
				printf("Matrícula já cadastrada! Digite novamente.\n");
			}
		} while (!validar_matricula(a->matricula, lista, *qtd));

		printf("Insira o nome: ");
		fgets(a->nome, MAX_N, stdin);
		fflush(stdin);

		a->sexo = validar_genero();

		do {
			printf("Insira a data de nascimento (dd mm aaaa): ");
			scanf("%d %d %d", &(a->data_nascimento.dia), &(a->data_nascimento.mes), &(a->data_nascimento.ano));
			fflush(stdin);
			if (!validar_data(a->data_nascimento)) {
				printf("Data inválida! Digite novamente.\n");
			}
		} while (!validar_data(a->data_nascimento));

		do {
			printf("Insira o CPF: ");
			fgets(a->cpf, CPF, stdin);
			fflush(stdin);
			if (!validar_cpf(a->cpf)) {
				printf("CPF inválido! Digite novamente.\n");
			}
		} while (!validar_cpf(a->cpf));

		printf("\nCadastro realizado com sucesso!\n");
		*qtd = *qtd + 1;
	}
}

void cadastrar_disciplina(disciplina *d, int *qtd, pessoa prof[TAM], int qtd_p) {
	int mat_prof, pos;
	if (tam_lista(*qtd) == LISTA_CHEIA) {
		printf("Lista de disciplinas cheia!\n");
	} else {
		printf("Insira o nome da disciplina: ");
		fgets(d->nome, MAX_N, stdin);
		fflush(stdin);

		printf("Insira o codigo da disciplina: ");
		scanf("%d", &(d->codigo));
		fflush(stdin);

		printf("Insira o semestre: ");
		scanf("%d", &(d->semestre));
		fflush(stdin);

		printf("Insira a quantidade de vagas: ");
		scanf("%d", &(d->vagas));
		fflush(stdin);
		do {
			printf("Insira a matrícula do professor: ");
			scanf("%d", &mat_prof);
			fflush(stdin);
			pos = buscar_pessoa(prof, qtd_p, mat_prof);
			if (pos < 0)
				printf("Não foi possível achar o professor!");
			else
				strcpy(d->professor.nome, prof[pos].nome);
		} while (pos < 0);
		*qtd = *qtd + 1;
		printf("Disciplina cadastrada com sucesso!\n");
	}
}

// faz a troca de pessoa
void troca(pessoa *a, pessoa *b){
	pessoa aux;
	// passando dados de a p/ aux
	aux.matricula = a->matricula;
	strcpy(aux.nome, a->nome);
	aux.sexo = a->sexo;
	aux.data_nascimento.dia = a->data_nascimento.dia;
	aux.data_nascimento.mes = a->data_nascimento.mes;
	aux.data_nascimento.ano = a->data_nascimento.ano;
	strcpy(aux.cpf, a->cpf);
	// passando dados de b p/ a
	a->matricula = b->matricula;
	strcpy(a->nome, b->nome);
	a->sexo = b->sexo;
	a->data_nascimento.dia = b->data_nascimento.dia;
	a->data_nascimento.mes = b->data_nascimento.mes;
	a->data_nascimento.ano = b->data_nascimento.ano;
	strcpy(a->cpf, b->cpf);
	// passando dados de aux p/ b
	b->matricula = aux.matricula;
	strcpy(b->nome, aux.nome);
	b->sexo = aux.sexo;
	b->data_nascimento.dia = aux.data_nascimento.dia;
	b->data_nascimento.mes = aux.data_nascimento.mes;
	b->data_nascimento.ano = aux.data_nascimento.ano;
	strcpy(b->cpf, aux.cpf);
}

//todas a funções de listar pessoa
void imprimir_pessoa(pessoa a[TAM], int qtd, int ini) {
	for (int i = ini; i < qtd; i++) {
		printf("Matricula: %d\n", a[i].matricula);
		printf("Nome: %s", a[i].nome);
		printf("Sexo: %c\n", a[i].sexo);
		printf("Data de nascimento: %02d/%02d/%02d\n", a[i].data_nascimento.dia, a[i].data_nascimento.mes, a[i].data_nascimento.ano);
		printf("CPF: %s\n", a[i].cpf);
	}
}
//lista professor/aluno por ordem alfabética
void ord_por_nome(pessoa a[TAM], int qtd) {
	// ordena por nome com o selection sort
	char menor[MAX_N];
	char minusc[MAX_N];
	int k;
	for(int i = 0; i < qtd - 1; i++){
		strcpy(menor, a[i].nome);
		minusculo(menor, strlen(menor));
		int pos = i;
		for(int j = i + 1; j < qtd; j++){
			strcpy(minusc, a[j].nome);
			minusculo(minusc, strlen(minusc));
			k = 0;
			while(minusc[k] == menor[k])
				k++;
			if(menor[k] > minusc[k]){
				strcpy(menor, minusc);
				pos = j;
			}
		}
		troca(&a[i], &a[pos]);
	}
	imprimir_pessoa(a, qtd, 0);
}
//lista professor/aluno por data de nascimento(mais antigo -> mais atual)
void ord_por_data(pessoa a[TAM], int qtd) {
	data menor;
	for (int i = 0; i < qtd; i++) {
		menor.ano = a[i].data_nascimento.ano;
		menor.mes = a[i].data_nascimento.mes;
		menor.dia = a[i].data_nascimento.dia;
		int pos = i;
		for(int j = i + 1; j < qtd; j++) {
			if(menor.ano == a[j].data_nascimento.ano) {
				if(menor.mes == a[j].data_nascimento.mes) {
					if(menor.dia > a[j].data_nascimento.dia) {
						menor.ano = a[j].data_nascimento.ano;
						menor.mes = a[j].data_nascimento.mes;
						menor.dia = a[j].data_nascimento.dia;
						pos = j;
					}
				} else if(menor.mes > a[j].data_nascimento.mes) {
					menor.ano = a[j].data_nascimento.ano;
					menor.mes = a[j].data_nascimento.mes;
					menor.dia = a[j].data_nascimento.dia;
					pos = j;
				}
			} else if(menor.ano > a[j].data_nascimento.ano) {
				menor.ano = a[j].data_nascimento.ano;
				menor.mes = a[j].data_nascimento.mes;
				menor.dia = a[j].data_nascimento.dia;
				pos = j;
			}
		}
		troca(&a[i], &a[pos]);
	}
	imprimir_pessoa(a, qtd, 0);
}
//lista professor/aluno por sexo selecionado pelo usuario
void filtrar_sexo(pessoa a[TAM], int qtd, char c[MAX_N]){
	char busc_sex;
	int achou;
	do{
		printf("\nInsira o sexo que você quer listar[F/M/O]: ");
		scanf("%c", &busc_sex);
		fflush(stdin);
		busc_sex = toupper(busc_sex);
		if(busc_sex == 'F' || busc_sex == 'M' || busc_sex == 'O'){
			achou = 0;
			for(int i = 0; i < qtd; i++){
				if(a[i].sexo == busc_sex){
					imprimir_pessoa(a, i+1, i);
					achou++;
				}
			}
			if(achou == 0){
				printf("Não foram encontrados %s com o sexo digitado.\n", c);
			}
		} else {
			printf("Opção Inválida!\n");
		}
	} while(busc_sex != 'F' && busc_sex != 'M' && busc_sex != 'O');
}
// modulo de listar
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
					imprimir_pessoa(a, qtd, 0);
					break;
				case 2:
					printf("Listar %s ordenados por nome\n", c);
					ord_por_nome(a, qtd);
					break;
				case 3:
					printf("Listar %s ordenados por data de nascimento\n", c);
					ord_por_data(a, qtd);
					break;
				case 4:
					printf("Listar %s por sexo [M/F/O]\n", c);
					filtrar_sexo(a, qtd, c);
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

// atualiza professor/aluno a partir da matricula
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
// exclui professor/aluno a partir da matrícula
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