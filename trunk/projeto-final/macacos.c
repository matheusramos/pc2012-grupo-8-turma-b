#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"miscelanea.h"
//#include<mpi.h>
//#include<omp.h>

int main(int argc, char **argv)
{	
	registro *menor, *maior;
	long int t_menor=0, t_maior=0, posicao=0;
	char *palavra;
	short int t_palavra=0, flag_achou=0;
	unsigned long int conta_aleat =1;/* Variavel criada para que o processo nao gere a mesma letra aleatoria dentro do intervalo de tempo de segundo*/ 
	int id=0, p=0; 

	/*MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);*/

	recuperarVetorRegistro(&menor,&t_menor,T_STR_MENOR,"menor.dat");
	recuperarVetorRegistro(&maior,&t_maior,T_STR_MAIOR,"maior.dat");

	imprimirVetorRegistro(menor, t_menor);

	palavra = (char *) malloc((T_STR_MENOR+1)*sizeof(char)); //só tem o tamanho da palavra menor, que vão ser o tamanho máximo gerado.

	while(t_palavra < T_STR_MENOR)
	{
		palavra[t_palavra++] = gerarCaractere(id,conta_aleat++); //gera caractere aleatório
		palavra[t_palavra] = '\0'; //marca o fim da string

		printf("%s\n",palavra);
		fflush(stdout);

		posicao = buscarPalavraMenor(menor,palavra,t_menor,&flag_achou); //procura a palavra no vetor de palavras menores

		if(flag_achou)
		{
			printf("Achou a palavra %s\n",palavra);
			fflush(stdout);
			menor[posicao].flag_achado = 1;
			if (t_palavra > 1) //só procura no vetor de maiores se o length for maior do que 1
			{
				//PROCURA NO VETOR MAIOR
			}
			t_palavra = 0;
			break;
		}
		else
		{
			/*verifica os dois vizinhos*/
			if (posicao > 0 && posicao+1 < t_menor)
			{
				/* se nenhum vizinho apresenta a estrutura*/
				if (strncmp(menor[posicao+1].palavra,palavra,strlen(palavra)) != 0 &&
						strncmp(menor[posicao-1].palavra,palavra,strlen(palavra)) != 0 &&
						strncmp(menor[posicao].palavra,palavra,strlen(palavra)) != 0)
					palavra[--t_palavra]='\0';
			}
			/*verifica o valor e o vizinho da direita*/
			else if(posicao==0)
			{
				if (strncmp(menor[posicao+1].palavra,palavra,strlen(palavra))!=0 &&
						strncmp(menor[posicao].palavra,palavra,strlen(palavra))!=0)
					palavra[--t_palavra]='\0';
			}
			/*verifica o valor e o vizinho da esquerda*/
			else
			{
				if (strncmp(menor[posicao-1].palavra,palavra,strlen(palavra)) != 0 &&
						strncmp(menor[posicao].palavra,palavra,strlen(palavra)) != 0)
					palavra[--t_palavra]='\0';
			}
		}

	}

	/*char *vetor[5];
	vetor[0]="carol";
	vetor[1]="fabio";
	vetor[2]="isa";
	vetor[3]="tsu";
	vetor[4]="vanes";
		

	for(i=0;i<8;++i)
		gerarPalavra(id,&contAleat,vetor,5);
		*/
		
	free(palavra);
	desalocarVetorRegistro(&menor,t_menor);
	desalocarVetorRegistro(&maior,t_maior);

	//MPI_Finalize();
	
	return EXIT_SUCCESS;
}
