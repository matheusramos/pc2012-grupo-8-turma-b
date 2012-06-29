#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<mpi.h>

/*
 * Funcao que busca uma palavra no vetor de palavras menores.
 * Se a palavra é encontrada, a variável achou passa a ser 1, e retorna-se a posicao
 * dessa palavra no vetor. Se a palavra não for encontrada, achou tem valor 0, e retorna -
 * se a posicao onde a busca parou, que é a posicao da palavra do vetor mais proxima da
 * palavra desejada.
 */

int buscarPalavraMenor (char **vetor, char *palavra, long int tamanho, int *achou)
{
	int inf=0, pos=tamanho-1, meio=0;
	(*achou)=0;

	/*Faz a busca binaria para ver se existe a palavra*/
	while(inf<pos)
	{
		meio=(inf+pos)/2;
		int comp=strcmp(vetor[meio],palavra);

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
	if(strcmp(vetor[meio],palavra)==0)
		(*achou)=1;

	return meio;
}

char gerarCaractere (int id, int contAleat)
{
	unsigned int i=time(NULL);
	unsigned int iProc;	

	iProc = i*(id+1)*(contAleat+1);
	
	return rand_r(&iProc)%26+97;
}

void gerarPalavra (int id, long unsigned int *contAleat, char **vetor_menor, int i_menor)
{	
	char *palavra= malloc(6*sizeof(char));
	char caracter;
	int tamanho = 0;
	int achou;
	int posicao;

	while(tamanho<5)
	{
		caracter = gerarCaractere(id,*contAleat);
		(*contAleat)++;
		palavra[tamanho]=caracter;
		palavra[tamanho+1]='\0';
		++tamanho;
		printf("%s\n",palavra);
		
		posicao = buscarPalavraMenor(vetor_menor,palavra,i_menor,&achou);
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
				if(strncmp(vetor_menor[posicao+1],palavra,strlen(palavra))!=0 &&
					strncmp(vetor_menor[posicao-1],palavra,strlen(palavra))!=0 &&
					strncmp(vetor_menor[posicao],palavra,strlen(palavra))!=0)
				{
					palavra[tamanho-1]='\0';
					--tamanho;

				}

			}
			/*verifica o valor e o vizinho da direita*/
			else if(posicao==0)
			{
				if(strncmp(vetor_menor[posicao+1],palavra,strlen(palavra))!=0 &&
					strncmp(vetor_menor[posicao],palavra,strlen(palavra))!=0)
				{
					palavra[tamanho-1]='\0';
					--tamanho;

				}

			}
			/*verifica o valor e o vizinho da esquerda*/
			else
			{
				if(strncmp(vetor_menor[posicao-1],palavra,strlen(palavra))!=0 &&
					strncmp(vetor_menor[posicao],palavra,strlen(palavra))!=0)
				{
					palavra[tamanho-1]='\0';
					--tamanho;

				}


			}

		}
	}

}

int main(int argc, char **argv)
{
	int i,id, p; 
	unsigned long int contAleat =1;/* Variavel criada para que o processo nao gere a mesma letra aleatoria dentro do intervalo de tempo de segundo*/ 
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	char *vetor[5];
	vetor[0]="carol";
	vetor[1]="fabio";
	vetor[2]="isa";
	vetor[3]="tsu";
	vetor[4]="vanes";
		

	for(i=0;i<8;++i)
		gerarPalavra(id,&contAleat,vetor,5);
		

	MPI_Finalize();
	
	return EXIT_SUCCESS;
}










