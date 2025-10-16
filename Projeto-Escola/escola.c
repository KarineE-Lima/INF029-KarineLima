#include <stdio.h>
#include "escola.h"

// ------- FUNÇÃO PRINCIPAL ---------
int main(){
	int opcao, op_aluno, op_prof, op_disciplina, op_relat;
	int qtd_aluno = 0, qtd_prof = 0, qtd_disciplina = 0;
	pessoa aluno[TAM];
	pessoa prof[TAM];
	pessoa geral[TAM + TAM];
	disciplina disc[TAM];
	char categoria[15];
	do{
		opcao = menu_geral();
		switch (opcao) {
			case 0:
				printf("Saindo...\n");
				for (int i = 0; i < qtd_disciplina; i++) {
					if (disc[i].alunos != NULL) {
						free(disc[i].alunos);
						disc[i].alunos = NULL;
					}
				}
				break;
			case 1:
				do {
					strcpy(categoria, "Alunos");
					gerar_linha();
					printf("Menu Aluno\n");
					unir_vetor(aluno, prof, geral, qtd_aluno, qtd_prof);
					op_aluno = menu_pessoa(categoria);
					switch (op_aluno) {
						case 0:
							printf("Saindo do menu aluno...\n");
							break;
						case 1:
							gerar_linha();
							printf("Cadastro Aluno\n");
							cadastrar_pessoa(&aluno[qtd_aluno], geral, &qtd_aluno, qtd_prof);
							break;
						case 2:
							gerar_linha();
							printf("Listar Aluno\n");
							listar_pessoa(aluno, qtd_aluno, categoria);
							break;
						case 3:
							gerar_linha();
							printf("Atualizar Aluno\n");
							atualizar_pessoa(aluno, qtd_aluno);
							break;
						case 4:
							gerar_linha();
							printf("Excluir Aluno\n");
							excluir_pessoa(aluno, &qtd_aluno, disc, qtd_disciplina);
							break;
						default: printf("Opção inválida!\n");
					}
				}while (op_aluno != 0);
				break;
			case 2:
				gerar_linha();
				printf("Menu Professor\n");
				do {
					strcpy(categoria, "Professores");
					unir_vetor(aluno, prof, geral, qtd_aluno, qtd_prof);
					op_prof = menu_pessoa(categoria);
					switch (op_prof) {
						case 0:
							printf("Saindo do menu professor...\n");
							break;
						case 1:
							gerar_linha();
							printf("Cadastro Professor\n");
							cadastrar_pessoa(&prof[qtd_prof], geral, &qtd_prof, qtd_aluno);
							break;
						case 2:
							gerar_linha();
							printf("Listar Professor\n");
							listar_pessoa(prof, qtd_prof, categoria);
							break;
						case 3:
							gerar_linha();
							printf("Atualizar Professor\n");
							atualizar_pessoa(prof, qtd_prof);
							break;
						case 4:
							gerar_linha();
							printf("Excluir Professor\n");
							excluir_pessoa(prof, &qtd_prof, disc, qtd_disciplina);
							break;
						default: printf("Opção inválida!\n");
					}
				} while (op_prof != 0);
				break;
			case 3:
				do {
					gerar_linha();
					printf("Menu Disciplina\n");
					op_disciplina = menu_disciplina();
					switch (op_disciplina) {
						case 0:
							printf("Saindo do menu disciplina...\n");
							break;
						case 1:
							gerar_linha();
							printf("Cadastro Disciplina\n");
							cadastrar_disciplina(&disc[qtd_disciplina], &qtd_disciplina, prof, qtd_prof);
							break;
						case 2:
							gerar_linha();
							printf("Listar Disciplina\n");
							listar_disciplina(disc, qtd_disciplina);
							break;
						case 3:
							gerar_linha();
							printf("Atualizar Disciplina\n");
							atualizar_disciplina(disc, qtd_disciplina, prof, qtd_prof);
							break;
						case 4:
							gerar_linha();
							printf("Excluir Disciplina\n");
							excluir_disciplina(disc, &qtd_disciplina, aluno, qtd_aluno);
							break;
						case 5:
							gerar_linha();
							printf("Incluir aluno\n");
							incluir_aluno(&disc, qtd_disciplina, &aluno, qtd_aluno);
							break;
						case 6:
							gerar_linha();
							printf("Excluir aluno\n");
							excluir_aluno(&disc, qtd_disciplina, &aluno, qtd_aluno);
							break;
						default: printf("Opção inválida!\n");
					}
				} while(op_disciplina != 0);
				break;
			case 4:
				unir_vetor(aluno, prof, geral, qtd_aluno, qtd_prof);
				do {
					gerar_linha();
					printf("Outros Relatórios\n");
					op_relat = menu_relatorio();
					switch (op_relat) {
						case 0:
							printf("Saindo do Menu Relatórios...\n");
							break;
						case 1:
							gerar_linha();
							printf("Aniversariantes do Mês\n");
							listar_aniversariantes(geral, qtd_aluno+qtd_prof);
							break;
						case 2:
							gerar_linha();
							printf("Buscar pessoas\n");
							buscar_por_nome(geral, qtd_aluno+qtd_prof);
							break;
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