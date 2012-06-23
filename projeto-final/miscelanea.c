#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
		(*vetor)[i].palavra = (char *) malloc((tamanho_string+1)*sizeof(char));
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
		(*vetor)[i].palavra = (char *) malloc((tamanho_string+1)*sizeof(char));
		(*vetor)[i].flag_achado = 0;
	}
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
}

