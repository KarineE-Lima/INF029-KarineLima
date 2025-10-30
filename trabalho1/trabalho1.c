// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Karine Evelin Sousa da Cruz Lima
//  email: karine.elima73@gmail.com
//  Matrícula: 20251160002
//  Semestre: 2025.2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include "trabalho1.h"
#include <stdlib.h>
#include <stdio.h>

DataQuebrada quebraData(char data[]);
int bissexto(int ano);
void tratarString(char *texto);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
    int datavalida = 1;
    DataQuebrada data_div = quebraData(data);

    if (!data_div.valido) datavalida = 0;

    int dias_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(bissexto(data_div.iAno))
        dias_mes[1]++;

    if(data_div.iAno < 100)
        data_div.iAno += (data_div.iAno > 25)? 1900 : 2000;

    if(data_div.iAno < 1900 || data_div.iAno > 2025)
        datavalida = 0;
    if(data_div.iMes < 1 || data_div.iMes > 12)
        datavalida = 0;
    if(data_div.iDia < 1 || data_div.iDia > dias_mes[data_div.iMes - 1])
        datavalida = 0;

    return datavalida;
}



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{

    //calcule os dados e armazene nas três variáveis a seguir
    DiasMesesAnos dma;
    int dias_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int dias_t = 0;
    DataQuebrada dataI = quebraData(datainicial);
    DataQuebrada dataF = quebraData(datafinal);


    if (q1(datainicial) == 0){
      dma.retorno = 2;
      return dma;
    }else if (q1(datafinal) == 0){
      dma.retorno = 3;
      return dma;
    }else{
        if (dataI.iAno > dataF.iAno) {
            dma.retorno = 4;
            return dma;
        }
        if (dataI.iAno == dataF.iAno && dataI.iMes > dataF.iMes) {
            dma.retorno = 4;
            return dma;
        }
        if (dataI.iAno == dataF.iAno && dataI.iMes == dataF.iMes && dataI.iDia > dataF.iDia) {
            dma.retorno = 4;
            return dma;
        }

        //calcule a distancia entre as datas

        dma.qtdAnos = dataF.iAno - dataI.iAno;
        if (dataI.iMes > dataF.iMes || (dataI.iMes == dataF.iMes && dataI.iDia > dataF.iDia))
            dma.qtdAnos--;
        dataI.iAno += dma.qtdAnos;

        dma.qtdMeses = 0;


        int m_i = (dataI.iMes >= dataF.iMes && dataI.iDia != dataF.iDia) ? dataI.iMes - 12 : dataI.iMes;
        int m_f = dataF.iMes;

        while (m_i < m_f) {
            dma.qtdMeses++;
            m_i++;
        }
        if (dataI.iDia > dataF.iDia) {
            dma.qtdMeses--;
        }
        if(dma.qtdMeses >= 12) {
            dma.qtdMeses -= 12;
            dma.qtdAnos++;
        }
        dataI.iMes += dma.qtdMeses;

        if (dataI.iMes > 12) {
            dataI.iMes -= 12;
            dataI.iAno++;
        }

        dias_mes[1] = (bissexto(dataF.iAno))? 29 : 28;
        dma.qtdDias = (dias_mes[dataI.iMes-1] - dataI.iDia) + dataF.iDia;
        dma.qtdDias += (bissexto(dataI.iAno) && !bissexto(dataF.iAno)) ? 1 : 0;
        dma.qtdDias -= (dma.qtdDias >= dias_mes[dataI.iMes - 1])? dias_mes[dataI.iMes - 1] : 0;


      //se tudo der certo
      dma.retorno = 1;
      return dma;
      
    }
    
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0, i;
    char txt_copia[256];
    for (i = 0; texto[i] != '\0'; i++)
        txt_copia[i] = texto[i];
    tratarString(txt_copia);
    char c_copia = c;
    tratarString(c_copia);
    if (!isCaseSensitive) {
        c_copia = (c_copia >= 'A' && c_copia <= 'Z') ? c_copia - 'A' + 'a' : c_copia;
        for (i = 0; txt_copia[i] != '\0'; i++)
            txt_copia[i] = (txt_copia[i] >= 'A' && txt_copia[i] <= 'Z') ? txt_copia[i] - 'A' + 'a' : txt_copia[i];
    }
    for(int i = 0; txt_copia[i]; i++){
        if(txt_copia[i] == c_copia)
            qtdOcorrencias++;
    }
    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = 0;
    int i, j, k, tam;
    tratarString(strTexto);
    tratarString(strBusca);
    for (tam = 0; strBusca[tam]; tam++);
    for (i = 0, k = 0; strTexto[i] != '\0'; i++) {
        for (j = 0; strBusca[j] != '\0'; j++) {
            if (strTexto[i + j] != strBusca[j]) {
                break;
            }
        }

        if (tam == j) {
            posicoes[k++] = i + 1;
            posicoes[k++] = i + tam;
            qtdOcorrencias++;
            i++;
        }
    }
    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
    long long int invertido = 0;
    while (num > 0) {
        invertido = invertido * 10 + (num % 10);
        num = num / 10;
    }
    num = invertido;
    return num;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias = 0;
    int i, j;
    char num_base[10], num_busca[10];
    numerobase = q5(numerobase);
    numerobusca = q5(numerobusca);
    // covertendo para char
    for (i = 0; numerobase > 0; i++) {
        num_base[i] = (numerobase % 10) + '0';
        numerobase /= 10;
    }
    num_base[i] = '\0';

    for (i = 0; numerobusca > 0; i++){
        num_busca[i] = (numerobusca % 10) + '0';
        numerobusca /= 10;
    }
    num_busca[i] = '\0';

    int tam = i;
    // buscando ocorrencias
    for (i = 0; num_base[i] != '\0'; i++) {
        for (j = 0; num_busca[j] != '\0'; j++) {
            if (num_base[i + j] != num_busca[j])
                break;
        }
        if (tam == j) {
            qtdOcorrencias++;
            i += tam - 1;
        }
    }
    return qtdOcorrencias;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

 int q7(char matriz[8][10], char palavra[5])
 {
    int achou = 0;
    int i, j, k, tam_p;
    char invertido[5];
    for (tam_p = 0; palavra[tam_p]; tam_p++);
    for (i = tam_p - 1, j = 0; i >= 0; i--, j++) {
        invertido[j] = palavra[i];
    }
    // sentido horizontal para frente e para trás
    for (i = 0; i < 8 && !achou; i++) {
        for (j = 0; j < 10 - tam_p + 1 && !achou; j++) {
            for (k = 0; k < tam_p; k++) {
                if (matriz[i][j + k] != palavra[k] && matriz[i][j + k] != invertido[k]) {
                    break;
                }
            }
            if (k == tam_p)
                achou = 1;
        }
    }
    // sentido vertical para cima e para baixo
    for (i = 0; i < 10 - tam_p + 1 && !achou; i++) {
        for (j = 0; j < 8 && !achou; j++) {
            for (k = 0; k < tam_p; k++) {
                if (matriz[j + k][i] != palavra[k] && matriz[j + k][i] != invertido[k]) {
                    break;
                }
            }
            if (k == tam_p)
                achou = 1;
        }
    }
    // diagonal
    for (int l = 0; l < 8; l++) {
        for (int c = 0; c < 10; c++) {
            for (i = l; i < 8 && !achou; i++) {
                for (j = c; j < 10 && !achou; j++) {
                    for (k = 0; k < tam_p && j + k < 10; k++) {
                        if (matriz[i + k][j + k] != palavra[k] && matriz[i + k][j + k] != invertido[k])
                            break;
                    }
                    if (k == tam_p)
                        achou = 1;
                }
            }
        }
    }
    for (int l = 0; l < 8 && !achou; l++) {
        for (int c = tam_p - 1; c < 10 && !achou; c++) {
            for (i = l; i < 8 && !achou && j >= 0; i++) {
                for (j = c; j < 10 && !achou; j++) {
                    for (k = 0; k < tam_p && j - k > 0; k++) {
                        if (matriz[i + k][j - k] != palavra[k] && matriz[i + k][j - k] != invertido[k])
                            break;
                    }
                    if (k == tam_p)
                        achou = 1;
                }
            }
        }
    }
     return achou;
 }



DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i;

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}
int bissexto(int ano) {
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 4 == 0 && ano % 400 == 0)) {
        return 1;
    }
    return 0;
}
void tratarString(char *texto) {
    int i, j, tam;
    char com_acento[] = "ÄÁÂÀÃäáâàãÉÊËÈéêëèÍÎÏÌíîïìÖÓÔÒÕöóôòõÜÚÛÙüúûù";
    char sem_acento[] = "AAAAAAAAAAaaaaaaaaaaEEEEEEEEeeeeeeeeIIIIIIIIiiiiiiiiOOOOOOOOOOooooooooooUUUUUUUUuuuuuuuu";
    for(tam = 0; texto[tam] != '\0'; tam++);
    for(i = 0; texto[i] != '\0'; i++){
        for(j = 0; com_acento[j] != '\0'; j++) {
            if(texto[i] == com_acento[j] && texto[i+1] == com_acento[j+1]) {
                texto[i] = sem_acento[j];
                for (int k = i + 1; k < tam - 1; k++) {
                    texto[k] = texto[k+1];
                }
                texto[tam - 1] = '\0';
                tam--;
                break;
            }
        }
    }
}


