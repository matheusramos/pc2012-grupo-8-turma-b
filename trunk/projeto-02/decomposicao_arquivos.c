#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NUM_PROCESSORS 8 /*somente para a versão sequencial, simula o nro de processadores*/

/**
 * Verifica o caractere c é um separador ou EOF.
 */
int isSeparador(char c, char separador[])
{
	if (strchr(separador,c) == NULL || c == EOF)
		return 0;
	else
		return 1;
}

/**
 * Funcao que recebe o byte em que começa a partição e o que termina e copia
 * os dados para a string particão.
 */
void montarParticao(FILE *arq, char **particao, int byte_inicio, int byte_fim)
{
	*particao = (char *) malloc( (byte_fim-byte_inicio+1)*sizeof(char)); /*Aloca exatamente o tamanho necessário para a particao +1 para o \0*/

	/*Leitura dos dados*/
	fseek(arq,byte_inicio,SEEK_SET);
	fread(*particao,sizeof(char),byte_fim-byte_inicio,arq);

	(*particao)[byte_fim-byte_inicio] = '\0';
}

/**
 * Função que irá buscar um separador no stream apartir do offset
 * o retorno é o offset do ultimo caractere antes do separador
 * ou o EOF.
 */
int buscarNaoSeparador(FILE *arq, int offset, char separador[])
{
	char c = 0;

	fseek(arq,offset,SEEK_SET);

	do
	{
		c = fgetc(arq);
	}
	while(isSeparador(c,separador));
	
	if (c == EOF)
		return ftell(arq);
	else
		return (ftell(arq)-1);
}

/**
 * Regras para separadores:
 * argc = 0 -> separadores: espaço, \n\r (ARQUIVO PEQUENO)
 * argc = 1 -> separadores: \n\r (ARQUIVO GRANDE)
 */
int main(int argc, char *argv[])
{
	FILE *arq = NULL;
	long int tamanho_bytes = 0;
	char *particao_texto[NUM_PROCESSORS], separador[4];
	register int i=0;
	int byte_inicio=0, byte_fim=0;

	FILE *particao_teste[NUM_PROCESSORS];
	char name[10];
	
	/*Definição dos separadores*/
	separador[0]='\n';
	separador[1]='\r';
	if (argc == 0)
	{
		separador[2]=' ';
	}
	separador[3]='\0';
	
	printf("Arquivo: %s\n",argv[2]);
	printf("Tipo arquivo = %d\n",atoi(argv[1]));

	arq = fopen(argv[2],"r+"); /*Abre o arquivo*/
	if (arq == NULL) /*Verifica se o arquivo existe*/
		return EXIT_FAILURE;

	/* 
	 * Calcula tamanho do arquivo - o ftell() para streams texto pode não voltar o tamanho do arquivo
	 * caso não funcione procurar pela função stat.
	 */
	fseek(arq,0,SEEK_END);
	tamanho_bytes = ftell(arq);
	fseek(arq,0,SEEK_SET);
	tamanho_bytes -= ftell(arq);
	
	/* 
	 * Aqui o arquivo vai ser divido em partes, o critério de divisão é o tamanho do arquivo e a ocorrência
	 * de um separador para que um palíndromo não seja cortado em dois pedaços.
	 */
	for(i=0; i<NUM_PROCESSORS; i++)
	{
		/*Calcula o byte de início da partição, corre o stream até achar um separador*/
		byte_inicio = (int)(tamanho_bytes*((float)i/(float)NUM_PROCESSORS)); 
		byte_inicio = buscarNaoSeparador(arq,byte_inicio, separador);
		/*Calcula o byte final da partição, corre o stram até achado um separador ou EOF*/
		byte_fim = (int)(tamanho_bytes*((float)(i+1)/(float)NUM_PROCESSORS));
		byte_fim = buscarNaoSeparador(arq,byte_fim, separador);

		/*Impressão para checagem*/
		/*
		printf("%d\n",(int)(tamanho_bytes*((float)i/(float)NUM_PROCESSORS)));
		printf("Byte inicial=%d, byte final=%d\n",byte_inicio,byte_fim);
		*/

		/*Transfere a partição para uma string*/
		montarParticao(arq,&particao_texto[i],byte_inicio,byte_fim);
	}
	
	/*Faz arquivos para teste*/
	for(i=0; i<NUM_PROCESSORS; i++)
	{
		sprintf(name,"teste_%d",i);
		particao_teste[i] = fopen(name,"w+");
		fseek(particao_teste[i],0,SEEK_SET);
		fputs(particao_texto[i],particao_teste[i]);
		fclose(particao_teste[i]);
	}

	if (!fclose(arq)) /*Tenta fechar o ponteiro do arquivo*/ 
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}
