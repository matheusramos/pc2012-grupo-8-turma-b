#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#define MAXLENGTH 200

typedef struct
{
	int last_index;
	int last_prime;
	int max_len;
	int *prime_list;
}primos;

void realoca (primos **p, int novo_tamanho)
{
	int i,*realocado;
	realocado = realloc ((*p)->prime_list, novo_tamanho * sizeof(int));
	(*p)->prime_list = realocado;
	
}

int crivo(primos *list, int valor)
{ 

	int i,j;
	int *vetor,prime;

	//temos que calcular mais primos
	if(valor > (list->last_prime))
	{
		int tamanho = valor - (list->last_prime);

		vetor = malloc(tamanho*sizeof(int));
	
		//preenche o vetor
		#pragma omp parallel for
		for(i=0;i<tamanho;i++)
				vetor[i]=(list->last_prime)+i+1;
	
				
		for(i=0;i<=(list->last_index);++i)
		{
			prime = list->prime_list[i];
			
			#pragma omp parallel for
			for(j=0;j<tamanho;++j)
			{
				//se eh multiplo
				if(vetor[j]%prime==0)
					vetor[j]=-1;
					
			}
			//jah percorreu toda a lista inicial de primos, eh hora de add mais algum primo
			if(i==(list->last_index))
			{
				int posicao=0;
				while(posicao <tamanho && vetor[posicao]==-1)
					++posicao;
				//achou um valor nao marcado
				if(posicao<tamanho)
				{
					(list->last_index)++;
					list->prime_list[list->last_index] = vetor[posicao];
					list->last_prime = vetor[posicao];				
					vetor[posicao]=-1;

					//caso o vetor esteja no limite, ele eh realocado
					if(list->last_index == (list->max_len)-1)
					{
						int novo_tamanho = (list->max_len)*2;
						realoca(&list,novo_tamanho);
						list->max_len = novo_tamanho;
	
					}
				}	
			
			}
		}	
		
	}	
	
	//depois que montou a tabela verifica se o valor esta na tabela
	int inf=0,pos,meio;
	pos  = list->last_index;
	while(inf<=pos)
	{
		int meio=(inf+pos)/2;
		if(list->prime_list[meio]==valor)
		{
			return 1;
		}
		else if (list->prime_list[meio]<valor)
			inf = meio+1;
		else
			pos = meio-1;
	}

	return 0;
}



int main()
{

	primos *list;
	list = malloc(sizeof(primos));
	int i;

	list->last_index=0;
	list->last_prime = 2;
	list->max_len = MAXLENGTH;
	list->prime_list = malloc ((MAXLENGTH)*sizeof(int));
	list->prime_list[0]=2;
	
	//monta a lista de primos ate a 88
	if(crivo(list,8871))
		printf("O numero 8871 é primo");	

	//essa chamada apenas verifica na lista de primos
	if(crivo(list,1357))
		printf("O numero 1357 é primo");

	//monta a lista de primos ate 99
	if(crivo(list,2000))
		printf("O numero 2000 é primo");

	//essa chamada apenas verifica na lista de primos
	if(crivo(list,9987))
		printf("O numero 9987 é primo");

	//essa chamada apenas verifica na lista de primos
	if(crivo(list,13421))
		printf("O numero 13421 é primo");

	//essa chamada apenas verifica na lista de primos
	if(crivo(list,13763))
		printf("O numero 13763 é primo");

	//essa chamada apenas verifica na lista de primos
	if(crivo(list,1321))
		printf("O numero 1321 é primo");

	for(i=0;i<=(list->last_index);++i)
		printf("-%d-",(list->prime_list[i]));

	printf("Tamanhoooo-%d-",(list->last_index));


	return 1;

}
