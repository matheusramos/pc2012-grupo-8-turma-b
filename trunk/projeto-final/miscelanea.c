#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include"miscelanea.h"

/**
 * Alocar o vetor de strings.
 *
 * @param ***vetor: endereco do vetor de registros
 * @param *tamanho: o endereco do inteiro que contém o tamanho do vetor de registros
 * @param tamanho_string: o tamanho das novas strings que serão alocadas
 */
void alocarVetorRegistro(registro **vetor,long int *tamanho, int tamanho_string)
{
	register long int i=0;
	*vetor = (registro *) malloc((*tamanho)*sizeof(registro));
	for(i=0; i<*tamanho; i++)
	{
		(*vetor)[i].palavra[0] = '\0';
		(*vetor)[i].flag_achado = 0;
	}
}

/**
 * Realocar o vetor de registros para um novo tamanho, caso o tamanho antigo não seja suficiente.
 *
 * @param ***vetor: endereco do vetor de registros
 * @param *tamanho: o endereco tamanho antigo do vetor de registros
 * @param tamanho_string: o tamanho das novas strings que serão alocadas
 */
void realocarVetorRegistro(registro **vetor,long int *tamanho, int tamanho_string)
{
	register long int i=0;
	long int ultima_posicao;
	ultima_posicao = *tamanho;

	*tamanho += TAMANHO_ADICIONAL;

	*vetor = (registro *) realloc(*vetor,(*tamanho)*sizeof(registro));

	for(i=ultima_posicao; i<*tamanho; i++)
	{
		(*vetor)[i].palavra[0] = '\0';
		(*vetor)[i].flag_achado = 0;
	}
}

void desalocarVetorRegistro(registro **vetor, int tamanho)
{
	free(*vetor);
}

void strToLower(char *str)
{
	register short int i=0;

	for(i=0; i<strlen(str); i++)
		str[i] = tolower(str[i]);

}

/**
 * Grava o conteúdo do vetor em um arquivo.
 * 
 * @param vetor: ponteiro para o vetor que terá o conteúdo armazenado.
 * @param tamanho: tamanho do vetor.
 * @param nome: nome do arquivo que será salvo.
 *
 */
void gravarVetorRegistro(registro *vetor,long int tamanho, char *nome)
{
	FILE *p;
	p = fopen(nome,"wb");

	if (p == NULL)
	{
		fprintf(stderr,"Erro ao tentar criar o arquivo %s\n",nome);
		exit(EXIT_FAILURE);
	}
	fwrite(&tamanho,1,sizeof(long int),p);
	fwrite(vetor,tamanho,sizeof(registro),p); //escrever o vetor no arquivo

	fclose(p);
}

/**
 * Recupera o vetor do arquivo do binário.
 *
 * @param vetor: Endereço do vetor de strings que receberá o conteúdo do arquivo, não deve estar alocado.
 * @param tamanho: Endereço da variável inteira que irá guardar o tamanho do vetor.
 * @param tamanho_string: tamanho das strings que serão alocadas no vetor.
 * @param nome: string contendo o nome do arquivo que será aberto.
 *
 */
void recuperarVetorRegistro(registro **vetor, long int *tamanho, int tamanho_string, char *nome)
{
	FILE *p;
	p = fopen(nome,"rb");

	if (p == NULL)
	{
		fprintf(stderr,"Erro ao tentar abrir o arquivo %s\n",nome);
		exit(EXIT_FAILURE);
	}

	fread(tamanho,1,sizeof(long int),p);
	alocarVetorRegistro(vetor,tamanho,tamanho_string);
	fread(*vetor,*tamanho,sizeof(registro),p); //escrever o vetor no arquivo
	fclose(p);
}

/**
 * Imprime as palavras do vetor de registros.
 *
 * @param vetor: ponteiro para o vetor de registros.
 * @param tamanho: quantidade de palavras no vetor.
 */
void imprimirVetorRegistro(registro *vetor, long int tamanho)
{
	register int i=0;

	for(i=0; i<tamanho; i++)
		printf("%d - %s\n",i,vetor[i].palavra);
	fflush(stdout);
}

/*
 * Funcao que busca uma palavra no vetor de palavras menores.
 * Se a palavra é encontrada, a variável achou passa a ser 1, e retorna-se a posicao
 * dessa palavra no vetor. Se a palavra não for encontrada, achou tem valor 0, e retorna -
 * se a posicao onde a busca parou, que é a posicao da palavra do vetor mais proxima da
 * palavra desejada.
 */

int buscarPalavraMenor (registro *registro, char *palavra, long int tamanho, short int *achou)
{
	int inf=0, pos=tamanho-1, meio=0;

	if (tamanho == 0) return -1; //vetor vazio

	*achou = 0;

	/*Faz a busca binaria para ver se existe a palavra*/
	while(inf<pos)
	{
		meio=(inf+pos)/2;
		int comp=strcmp(registro[meio].palavra,palavra);

		/*Achou a palavra deve sair*/
		if(comp==0)
			break;
		else if (comp<0)
			inf = meio+1;
		else
		{
			/*para evitar que pos fique -1*/
			if(meio==0)
				pos =0;
			else
				pos = meio-1;
		}			
	}
	meio=(inf+pos)/2;

	/*verifica-se se achou a palavra*/
	if (strcmp(registro[meio].palavra,palavra)==0 && !registro[meio].flag_achado) //verifica se achou a palavra
		*achou = 1;

	return meio;
}

char gerarCaractere (int id, unsigned long int contAleat)
{
	unsigned int i=time(NULL);
	unsigned int iProc;	

	iProc = i*(id+1)*(contAleat+1);
	
	return rand_r(&iProc)%26+97;
}

void gerarPalavra (int id, long unsigned int *contAleat, registro *registro, int i_menor)
{	
	char *palavra= malloc(6*sizeof(char));
	char caracter;
	int tamanho = 0;
	short int achou;
	int posicao;

	while(tamanho<5)
	{
		caracter = gerarCaractere(id,*contAleat);
		(*contAleat)++;
		palavra[tamanho]=caracter;
		palavra[tamanho+1]='\0';
		++tamanho;
		printf("%s\n",palavra);
		
		posicao = buscarPalavraMenor(registro,palavra,i_menor,&achou);
		if(achou==1)
		{
			printf("Achouuuuu");
			printf(" %s\n",palavra);
			break;	
		}
		
		else
		{
			/*verifica se as palavras vizinhas apresentam a mesma estrutura.
			Exemplo:  gerou 'fa', mas nao tem e tem 'far' como um dos vizinhos entao continua, 
			senão retira-se a ultima letra e tenta de novo. 
			
			Com isso se gerarmos como primeira letra 'k' e não houver o 'k' e nenhuma 
			palavra que comece com 'k', ele exclui essa letra e começa de novo*/

			
			//TODO: depois, em vez de olhar a posicao atual e os vizinhos diretos, tem que fazer
			//uma funcao que pegue o primeiro vizinho da direita nao achado, e o primeiro vizinho da
			//esquerda nao achado


			/*verifica os dois vizinhos*/
			if(posicao>0 && posicao+1<i_menor)
			{
				/* se nenhum vizinho apresenta a estrutura*/
				if(strncmp(registro[posicao+1].palavra,palavra,strlen(palavra))!=0 &&
					strncmp(registro[posicao-1].palavra,palavra,strlen(palavra))!=0 &&
					strncmp(registro[posicao].palavra,palavra,strlen(palavra))!=0)
				{
					palavra[tamanho-1]='\0';
					--tamanho;
				}
			}
			/*verifica o valor e o vizinho da direita*/
			else if(posicao==0)
			{
				if(strncmp(registro[posicao+1].palavra,palavra,strlen(palavra))!=0 &&
					strncmp(registro[posicao].palavra,palavra,strlen(palavra))!=0)
				{
					palavra[tamanho-1]='\0';
					--tamanho;
				}
			}
			/*verifica o valor e o vizinho da esquerda*/
			else
			{
				if(strncmp(registro[posicao-1].palavra,palavra,strlen(palavra))!=0 &&
					strncmp(registro[posicao].palavra,palavra,strlen(palavra))!=0)
				{
					palavra[tamanho-1]='\0';
					--tamanho;
				}
			}
		}
	}

}

