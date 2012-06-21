#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<mpi.h>

/*
 *
 *
 */

int buscaPalavraMenor (char **vetor, char *palavra, long int tamanho, int *achou)
{

	int inf=0,pos=tamanho-1;
	int meio=0;
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
	if(strcmp(vetor[meio],palavra)==0)
		(*achou)=1;

	return meio;
}

char geraCaracter (int id, int contAleat)
{

	unsigned int i=time(NULL);
	unsigned int iProc;	

	iProc = i*(id+1)*(contAleat+1);
	
	return rand_r(&iProc)%26+97;
	

}

void geraPalavra (int id, long unsigned int *contAleat, char **vetor_menor, int i_menor)
{	
	char *palavra= malloc(6*sizeof(char));
	char caracter;
	int tamanho = 0;
	int achou;
	int posicao;

	while(tamanho<5)
	{
		caracter = geraCaracter(id,*contAleat);
		(*contAleat)++;
		palavra[tamanho]=caracter;
		palavra[tamanho+1]='\0';
		++tamanho;
		printf("%s\n",palavra);
		
		posicao = buscaPalavraMenor(vetor_menor,palavra,i_menor,&achou);
		if(achou==1)
		{
			printf("Achouuuuu");
			printf(" %s\n",palavra);
			break;	
		}
		
		/*else VOU FAZER ISSO
		{
			//se a palavra da frente não apresenta a mesma estrutura, gerou 'abap', mas nao tem e tem //'abal', retira-se a ultima letra e tenta de novo
			if(strncmp(vetor_menor[posicao],palavra,strlen(palavra))!=0 && )
			{
				palavra[tamanho-1]='\0';
				--tamanho;
			
			}

		}*/
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
	vetor[0]="ab";
	vetor[1]="fg";
	vetor[2]="lm";
	vetor[3]="ln";
	vetor[4]="tv";
		

	for(i=1;i<5;++i)
		geraPalavra(id,&contAleat,vetor,5);
		

	MPI_Finalize();
	
	return EXIT_SUCCESS;
}










