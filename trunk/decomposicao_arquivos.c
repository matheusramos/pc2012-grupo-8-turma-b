#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NUM_PROCESSORS 8 /*somente para a versão sequencial, simula o nro de processadores*/

int isSeparador(char c, char separador[])
{
	if (strchr(separador,c) == NULL)
		return 0;
	else
		return 1;
}

/**
 * Regras para separadores:
 * argc = 0 -> separadores: espaço, \n\r (ARQUIVO PEQUENO)
 * argc = 1 -> separadores: \n\r (ARQUIVO GRANDE)
 */
int main(int argc, char **argv)
{
	FILE *arq = NULL;
	long int tamanho_bytes = 0;
	char *particao_texto[NUM_PROCESSORS], c = 0, separador[4];
	int flag_saida = 0, flag_separador = 0;
	register int i=0;
	int bloco_inicio=0, bloco_fim=0;

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
	for(i=1; i<=NUM_PROCESSORS; i++)
	{
		flag_separador = 0;
		flag_saida = 0;
		fseek(arq,i*(tamanho_bytes/NUM_PROCESSORS),SEEK_SET);

		do
		{
			c = fgetc(arq);
			
			/*TODO o fread avanca o nro de bytes que ele le,devo dar um fseek, depois um fread,  epossivelmente um fseek para colocar no lugar certo novamente*/
			
			if (isSeparador(c,separador)) /*acha o primeiro separador e marca a flag para consumir os seguintes*/ 
			{
				/*Achou o bloco_fimd e uma partição, monta a partição*/
				if(flag_separador == 0)
				{
					bloco_fim = ftell(arq)-1; /**/
					particao_texto[i-1] = (char *) malloc( (bloco_fim-bloco_inicio+1)*sizeof(char));

					/*Leitura dos dados*/
					fseek(arq,bloco_inicio,SEEK_SET);
					fread(particao_texto[i-1],sizeof(char),bloco_fim-bloco_inicio,arq);

					particao_texto[i-1][bloco_fim-bloco_inicio-1] = '\0';
					printf("Byte inicial=%d, byte final=%d\n",bloco_inicio,bloco_fim);
	
					flag_separador=1;
				}
			}
			else if(flag_separador == 1)
			{
				flag_saida = 1;
				bloco_inicio = ftell(arq); /* Seta o início da partição de dados */
			}
		}while(!flag_saida);

		
		printf("Separação em %ld\n",ftell(arq));
	}
	
	for(i=0; i<NUM_PROCESSORS; i++)
	{
		sprintf(name,"teste %d",i);
		particao_teste[i] = fopen(name,"w+");
		fseek(particao_teste[i],0,SEEK_SET);
		fputs(particao_texto[i],particao_teste[i]);
		fclose(particao_teste[i]);
	}

	if (!fclose(arq)) /*Tenta fechar o ponteiro do arquivo*/ 
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}
