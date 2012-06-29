#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"miscelanea.h"
#include<mpi.h>
#include<omp.h>

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
 * Envia a posicao achada para todos os nós que estão executando.
 *
 * @param id: id do processo atual.
 * @param numproc: número total de processos.
 * @param numvetor: flag indicando se a palavra achada foi no VETOR MENOR ou no MAIOR.
 * @param posicao: posição da palavra encontrada.
 *
 */
void enviarAchadoGalera(int id, int numproc, int numvetor, long int posicao)
{
	register long int i=0;
	long int mensagem[2]; //SUPER IMPORTANTE!!!! A PRIMEIRA POSICAO DEFINE SE O DADO É DO VETOR MENOR OU DO MAIOR(0->MENOR 1->MAIOR), A SEGUNDA POSICAO É A POSICAO DA PALAVRA NO VETOR

	mensagem[0]=numvetor, mensagem[1]=posicao;
	for(i=0; i<numproc; i++) //envia o comunicado para todos os processos
		if(i != id) //só não envia pra si mesmo
			MPI_Send(&mensagem,2,MPI_LONG,i,0,MPI_COMM_WORLD);
}

/**
 * Faz uma busca sequêncial no vetor maior, para a partir de UMA palavra gerada, identificar UMA OU MAIS palavras maiores. 
 * OBS: Esse algoritmo destrói o conteúdo das palavras maiores, ou seja, pode não ser possível imprimi-las da maneira correta.
 * TODO: Adicionar OpenMP.
 *
 * @param *vetor: ponteiro para o vetor de registros.
 * @param t_vetor: tamanho do vetor de registros.
 * @param *palavra: palavra gerada.
 * @param id: id do processo atual.
 * @param numproc: número de palavras.
 *
 * @return: a posicão que a palavra foi encontrada, -1 caso contrário.
 */
void buscarVetorMaior(registro *vetor, int t_vetor, char *palavra, long int *contador, int id, int numproc)
{
	register long int i=0;
	register int j=0;	
	int t_palavra = strlen(palavra);
	char *pos=NULL;

	#pragma omp for private(j,pos)
	for(i=0; i<t_vetor; i++) //corre o vetor
	{
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

				//Envia a mensagem para os outros nós
				enviarAchadoGalera(id,numproc,VETOR_MAIOR,i);
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
	int id=0, p=0, i_porcentagem=1, flag_recebimento=0, cont_recebimento=0;
	time_t time_inicial=0, time_final=0;
	long int mensagem[2];
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	recuperarVetorRegistro(&menor,&t_menor,T_STR_MENOR,"menor.dat");
	recuperarVetorRegistro(&maior,&t_maior,T_STR_MAIOR,"maior.dat");
	palavra = (char *) malloc((T_STR_MENOR+1)*sizeof(char)); //só tem o tamanho da palavra menor, que vão ser o tamanho máximo gerado.
	
	time_inicial = time(NULL);
	
	while(cont_menor < (t_menor/5))
	{
		if(id == 0) //PROCESSO QUE VAI APENAS CONTABILIZAR A QUANTIDADE DE PALAVRAS GERADAS E IMPRIMIR OS RESULTADOS NA TELA
		{
			MPI_Recv(&mensagem,2,MPI_LONG,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&status);
			//MPI_Bcast(&posicao,1,MPI_LONG,1,MPI_COMM_WORLD);
			
			//printf("Recebida a posição %ld\n",mensagem[1]);
			//fflush(stdout);
			if(mensagem[0] == VETOR_MENOR) //é o vetor menor
				cont_menor++;
			else
				cont_maior++;
			
			if(((t_menor+t_maior)/100)*i_porcentagem == (cont_menor+cont_maior)) //imprime a porcentagem de 1 em 1
			{
				time_final = time(NULL);
				printf("%d%% em %ld segundos\n",i_porcentagem,time_final-time_inicial);
				//fflush(stdout);
				i_porcentagem++;
			}
		}
		else
		{

			palavra[t_palavra++] = gerarCaractere(id,conta_aleat++); //gera caractere aleatório
			palavra[t_palavra] = '\0'; //marca o fim da string

			posicao = buscarPalavraMenor(menor,palavra,t_menor,&flag_achou); //procura a palavra no vetor de palavras menores

			if(flag_achou)
			{
				cont_menor++;
				menor[posicao].flag_achado = 1;

				//MPI_Bcast(&posicao,1,MPI_LONG,id,MPI_COMM_WORLD);
				enviarAchadoGalera(id,p,VETOR_MENOR,posicao);//Envia a mensagem para os outros nós 

				if (t_palavra > 1) //só procura no vetor de maiores se o length for maior do que 1
				{
					//PROCURA NO VETOR MAIOR -- SE ACHAR VAI COMUNICAR OS OUTROS PROCESSOS LÁ DENTRO
					buscarVetorMaior(maior,t_maior,palavra,&cont_maior,id,p);
				}
			}
			
			MPI_Iprobe(MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&flag_recebimento,&status); //verifica se foram recebidos alguma mensagem, flag_recebido será true se houver mensagens recebidas
			//printf("MPI_SOURCE: %d\n",status.MPI_SOURCE);
			if(flag_recebimento)
			{
				flag_recebimento = 0;
				MPI_Recv(&mensagem,2,MPI_LONG,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
				MPI_Get_count(&status,MPI_LONG,&cont_recebimento);
				//printf("EU SOU O PROCESSO %d e recebi uma %d do processo %d mensagem\n",id,cont_recebimento,status.MPI_SOURCE);
			//if(request != NULL)
			//{
				if (mensagem[0] == VETOR_MENOR) //se é o vetor menor
				{
					menor[mensagem[1]].flag_achado = 1;
					cont_menor++;
					//buscarVetorMaior(maior,t_maior,palavra,&cont_maior,id,p);
				}
				else //se é o maior
				{
					maior[mensagem[1]].flag_achado = 1;
					cont_maior++;
				}
			/*	MPI_Request_free(request);
				request = NULL;
			}
			else
			{
				printf("Não tinha nada para receber quando eu tinha %ld palavras, daí eu continuei",cont_menor+cont_maior);
			}
			MPI_Request_get_status(request,&flag_recebimento,&status);
			printf("O status devolvido foi %d\n",flag_recebimento);*/
			}


			while(indicarBacktracking(menor,t_menor,posicao,palavra)) //retorna até o ponto que é válido fazer o backtracking, feito com while pq somente com um if pedira causar a entrada de um nó em loop infinito, caso algum outro nó encontrasse uma palavra que estava para ser encontrada no nó atual. Ele faz o backtracking várias vezes até chegar aoponto que existe ainda alguma palavra que ele possa encontrar.
			{
				palavra[--t_palavra] = '\0';
				posicao = buscarPalavraMenor(menor,palavra,t_menor,&flag_achou);
			}
		}
	}
	
	printf("Eu sou o processo de id %d\n",id);
	printf("%ld de %ld (%f%%) palavras pequenas encontradas\n",cont_menor,t_menor,((float) cont_menor/t_menor)*100);
	printf("%ld de %ld (%f%%) palavras grandes encontradas\n",cont_maior,t_maior,((float) cont_maior/t_maior)*100);
	printf("%ld de %ld (%f%%) palavras totais encontradas\n",cont_menor+cont_maior,t_menor+t_maior,(((float) (cont_menor+cont_maior)/(t_menor+t_maior))*100));

	free(palavra);
	desalocarVetorRegistro(&menor,t_menor);
	desalocarVetorRegistro(&maior,t_maior);

	MPI_Finalize();
	
	return EXIT_SUCCESS;
}
