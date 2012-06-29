#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"miscelanea.h"
//#include<mpi.h>
//#include<omp.h>

/**
 * Verifica se deve ser realizado um backtracking para que a busca por palavras conhecidas continue.
 *
 * @param *vetor: ponteiro para o vetor de registros.
 * @param t_vetor: tamanho do vetor
 * @param posicao: posicao atual do vetor
 * @param *palavra: strin contendo a palavra gerada.
 *
 * @return: 1 se deve ser realizado o backtracking, 0 caso contrário.
 */
int indicarBacktracking(registro *vetor, int t_vetor, int posicao, char *palavra)
{
	int anterior=0, atual=0, proximo=0;
	if(strlen(palavra) == T_STR_MENOR) //se a palavra já tem o máximo de caracteres realiza o backtracking
		return 1;
	if(strlen(palavra) == 0)
		return 0;

	//Definir a posicao anterior, atual e posterior
	atual = vetor[posicao].flag_achado? -1 : posicao;
		
	if (posicao == 0) //primeira posicao do vetor
	{
		anterior = -1;

		proximo = posicao+1;
		while(vetor[proximo].flag_achado == 1 && proximo++ < t_vetor-1); //varre os proximos para achar a proxima posicao ainda não encontrada
		if(vetor[proximo].flag_achado == 1)
			proximo = -1;
	}
	else if(posicao == t_vetor-1)//ultima posicao do vetor
	{
		proximo = -1;

		anterior = posicao-1;
		while(vetor[anterior].flag_achado == 1 && anterior-- < 0); //varre os anterior para achar posicao da palavra ainda não encontrada
		if(vetor[anterior].flag_achado == 1)
			anterior = -1;
	}
	else
	{
		anterior = posicao-1;
		while(vetor[anterior].flag_achado == 1 && anterior-- < 0); //varre os anterior para achar posicao da palavra ainda não encontrada
		if(vetor[anterior].flag_achado == 1)
			anterior = -1;

		proximo = posicao+1;
		while(vetor[proximo].flag_achado == 1 && proximo++ < t_vetor-1); //varre os proximos para achar a proxima posicao ainda não encontrada
		if(vetor[proximo].flag_achado == 1)
			proximo = -1;
	}
	
	//se houver a estrutura no anterior não faz o backtracking
	if (anterior >=0 && !strncmp(vetor[anterior].palavra,palavra,strlen(palavra)))
		return 0;

	//idem ao atual
	if (atual >=0 && !strncmp(vetor[atual].palavra,palavra,strlen(palavra)))
		return 0;

	//idem ao proximo
	if (proximo >=0 && !strncmp(vetor[proximo].palavra,palavra,strlen(palavra)))
		return 0;

	return 1;
}

/**
 * Faz uma busca sequêncial no vetor maior, para a partir de UMA palavra gerada, identificar UMA OU MAIS palavras maiores. 
 * OBS: Esse algoritmo destrói o conteúdo das palavras maiores, ou seja, pode não ser possível imprimi-las da maneira correta.
 * TODO: Adicionar OpenMP.
 *
 * @param *vetor: ponteiro para o vetor de registros.
 * @param t_vetor: tamanho do vetor de registros.
 * @param *palavra: palavra gerada.
 *
 * @return: a posicão que a palavra foi encontrada, -1 caso contrário.
 */
void buscarVetorMaior(registro *vetor, int t_vetor, char *palavra, long int *contador)
{
	register long int i=0;
	register int j=0;
	int t_palavra = strlen(palavra);
	char *pos=NULL;

	for(i=0; i<t_vetor; i++) //corre o vetor
	{
		//printf("ESTOU PROCURANDO NA POSICAO %ld\n",i);
		//fflush(stdout);
		if (!vetor[i].flag_achado) //se a palavra ainda nao foi reconhecida
		{
			pos = strstr(vetor[i].palavra,palavra);
			while(pos != NULL) //limpa as substrings nas palavras maiores
			{
				*pos = SEPARADOR;
				for(j=1; *(pos+j-1) != '\0'; j++) //<= transpor até o '\0'
				{
					*(pos+j) = *(pos+t_palavra+j-1); //transpoe o cada caractere restante da string para trás - POSSIVEL LUGAR PARA ERROS NAS EXTREMIDADES
				}
				pos = strstr(vetor[i].palavra,palavra);
			}
			
			//consome todos os separadores do começo da string
			while(vetor[i].palavra[0] == SEPARADOR)
				for(j=0; j<strlen(vetor[i].palavra); j++)
					vetor[i].palavra[j] = vetor[i].palavra[j+1];

			if(vetor[i].palavra[0] == '\0') //ACHOU A PALAVRA - STRING VAZIA!!!!
			{
				(*contador)++;
				vetor[i].flag_achado = 1;
				//printf("PALAVRA GRANDE NA POSIÇÃO %ld ENCONTRADA\n",i);
				//fflush(stdout);
				//TODO AVISAR OS OUTRAS THREADS
			}
		}
	}
}

int main(int argc, char **argv)
{	
	registro *menor, *maior;
	long int t_menor=0, t_maior=0, posicao=0, cont_menor=0, cont_maior=0;
	char *palavra;
	short int t_palavra=0, flag_achou=0;
	unsigned long int conta_aleat =1;/* Variavel criada para que o processo nao gere a mesma letra aleatoria dentro do intervalo de tempo de segundo*/ 

	/*MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);*/

	recuperarVetorRegistro(&menor,&t_menor,T_STR_MENOR,"menor.dat");
	recuperarVetorRegistro(&maior,&t_maior,T_STR_MAIOR,"maior.dat");

	palavra = (char *) malloc((T_STR_MENOR+1)*sizeof(char)); //só tem o tamanho da palavra menor, que vão ser o tamanho máximo gerado.
	
	while(cont_menor < t_menor)
	{
		palavra[t_palavra++] = gerarCaractere(0,conta_aleat++); //gera caractere aleatório
		palavra[t_palavra] = '\0'; //marca o fim da string

		//printf("%s",palavra);
		//fflush(stdout);

		posicao = buscarPalavraMenor(menor,palavra,t_menor,&flag_achou); //procura a palavra no vetor de palavras menores
		//printf(" - %ld\n",posicao);
		//fflush(stdout);

		if(flag_achou)
		{
			cont_menor++;
			//printf("MENOR %ld: %s\n",cont_menor,palavra);
			//fflush(stdout);
			menor[posicao].flag_achado = 1;

			if (t_palavra > 1) //só procura no vetor de maiores se o length for maior do que 1
			{
				//PROCURA NO VETOR MAIOR
				buscarVetorMaior(maior,t_maior,palavra,&cont_maior);
			}
			//while(indicarBacktracking(menor,t_menor,posicao,palavra)) //retorna até o ponto que é válido fazer o backtracking
				//palavra[--t_palavra] = '\0';

		}
		//else
		//if(indicarBacktracking(menor,t_menor,posicao,palavra)) //retorna até o ponto que é válido fazer o backtracking
			//palavra[--t_palavra] = '\0';

		while(indicarBacktracking(menor,t_menor,posicao,palavra)) //retorna até o ponto que é válido fazer o backtracking, feito com while pq somente com um if pedira causar a entrada de um nó em loop infinito, caso algum outro nó encontrasse uma palavra que estava para ser encontrada no nó atual. Ele faz o backtracking várias vezes até chegar aoponto que existe ainda alguma palavra que ele possa encontrar.
		{
			palavra[--t_palavra] = '\0';
			posicao = buscarPalavraMenor(menor,palavra,t_menor,&flag_achou);
			printf("BACKTRACKING - NOVA PALAVRA: %s POSICAO: %ld\n",palavra,posicao);
		}
	}

	printf("%ld de %ld palavras pequenas encontradas\n",cont_menor,t_menor);
	printf("%ld de %ld palavras grandes encontradas\n",cont_maior,t_maior);
	free(palavra);
	desalocarVetorRegistro(&menor,t_menor);
	desalocarVetorRegistro(&maior,t_maior);

	//MPI_Finalize();
	
	return EXIT_SUCCESS;
}
