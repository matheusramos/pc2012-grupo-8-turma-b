#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<mpi.h>
#include<omp.h>

int jacobiRichardson(double **,double *,double *,int,double,double,int *, int, int);

/**
 * Verifica os critérios de linhas e colunas:
 * Para cada linha, a soma do módulo do valor dos elementos, retirando a diagonal, deve ser menor do que 1
 * Para cada coluna, a soma do módulo do valor dos elementos, retirando a diagonal, deve ser menor do que 1
 */
int criterioLinhasColunas(double **MA, int tamanho)
{
	register int i=0, j=0;
	double soma_linhas=0, soma_colunas=0;

	for(i=0;i<tamanho;++i)
	{
		soma_linhas=0;
		soma_colunas=0;
		for(j=0;j<tamanho;++j)
			if(i!=j)
			{			
				soma_linhas+=fabs(MA[i][j]);
				soma_colunas+=fabs(MA[j][i]);
			}
		if(soma_linhas>=1 || soma_colunas>=1)
			return 0;
	}
	return 1;
}

int verificarErro(double *erros, double *x, int tamanho, double ERRO){
	int i;
	double maxErro=0,maxSol=0;

	//pega o valor máximo do erro e da solução
	for(i=0;i<tamanho;i++)
	{
		if(maxErro<erros[i]) 
			maxErro=erros[i];
		if(maxSol<x[i]) 
			maxSol=x[i];
	}
    
	if(maxErro/maxSol < ERRO)
		return 1;
	else 
		return 0;
}

/**
 * Aloca uma matriz M quadrada de doubles de ordem tamanho.
 */
void alocarMatrizQuadDoub(double ***M, int tamanho)
{
	register int i=0;
	*M = (double **) malloc(tamanho*sizeof(double *));

	for(i=0; i<tamanho; i++)
		(*M)[i] = (double *) calloc(tamanho,sizeof(double));
}

/**
 * Desaloca matriz quadrada M de doubles de ordem tamanho.
 */
void desalocarMatrizQuadDoub(double ***M, int tamanho)
{
	register int i=0;

	for(i=0; i<tamanho; i++)
		free((*M)[i]);
	free(*M);
}

/**
 * Imprime uma matriz M quadrada de doubles de ordem tamanho.
 */
void imprimirMatrizQuadDoub(double **M, int tamanho)
{
	register int i=0,j=0;
	
	for(i=0; i<tamanho; i++)
	{
		for(j=0; j<tamanho; j++)
			printf("%lf ",M[i][j]);
		printf("\n");
	}
}

/**
 * Calcula o valor de b na linha <linha> segundo a equacao Ax=b.
 */
double calcularResultadoLinha(double **A, double *x, int tamanho, int linha)
{
	register int j=0;
	double resultado=0;
	

	//#pragma omp parallel for reduction(+:resultado)
	for(j=0; j<tamanho; j++)
		resultado += A[linha][j]*x[j];
	
	return resultado;
}

/**
 * Imprimir resultado segundo padrão do Júlio.
 * Ax = b
 */
void imprimirResultado(double **A, double *x, double *b, int tamanho, int n_iteracoes, int linha_teste)
{
	printf("---------------------------------------------------------\n");
	printf("Iteration: %d\n",n_iteracoes);
	printf("RowTest: %d => [%lf] ?= %lf\n",linha_teste,calcularResultadoLinha(A,x,tamanho,linha_teste),b[linha_teste]);
	printf("-------------------------------------------------------\n");
}

int main(int argc, char **argv)
{
	double **MA, *b, *x; //x irá guardar os resultados do método numérico
	int j_order=0; //Ordem da matriz
	int j_row_test=0; //Linha(Fila) para ser avaliada
	double j_error=0; //Erro permitido
	int j_ite_max=0; //Numero máximo de iterações

	register int i=0,j=0; //int para iteração
	int n_iteracoes=0;
	int id=0,p=0;
	FILE *arquivo;
	
	/*Inicia os processos MPI*/
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	arquivo = fopen("../entradas/grd/matriz4000.txt","r");

	if(arquivo == NULL)
	{
		fprintf(stderr,"Falha ao abrir arquivo\n");
		return EXIT_FAILURE;
	}
	
	fscanf(arquivo,"%d",&j_order);

	alocarMatrizQuadDoub(&MA,j_order); 
	b = (double *) calloc(j_order,sizeof(double)); 
	x = (double *) calloc(j_order,sizeof(double));
	
	fscanf(arquivo,"%d",&j_row_test);
	fscanf(arquivo,"%lf",&j_error);
	fscanf(arquivo,"%d",&j_ite_max);
	
	/*Lê a matriz A*/
	for(i=0; i<j_order; i++)
		for(j=0; j<j_order; j++)
		{
			fscanf(arquivo,"%lf",&MA[i][j]);
			if(id==0 && MA[i][j] == 0)
			{
				fprintf(stderr,"Falha: Determinante é zero");
				MPI_Abort(MPI_COMM_WORLD,-1);
				return EXIT_FAILURE;
			}
		}

	/*Lê o vetor b*/
	//#pragma omp for
	for(i=0; i<j_order; i++)
		fscanf(arquivo,"%lf",&b[i]);
	

	/*Chama o método numérico*/
	if(!jacobiRichardson(MA,x,b,j_order,j_error,j_ite_max,&n_iteracoes, id, p))
	{
		fprintf(stderr,"Falha: Matriz não atende ao critério de convergência");
		MPI_Abort(MPI_COMM_WORLD,-1);
		return EXIT_FAILURE;
	}
	
	if(id == 0)
		imprimirResultado(MA,x,b,j_order,n_iteracoes,j_row_test);

	
	/*Desaloca variáveis*/
	free(x);
	free(b);
	desalocarMatrizQuadDoub(&MA,j_order);
	

	return EXIT_SUCCESS;
}

/**
 * Método Jacobi-Richarson
 * @return 
 * FALSE se não passar em algum critério de convergência.
 */
int jacobiRichardson(double **MA, double *x, double *b, int tamanho, double ERRO, double max_iteracoes, int *n_iteracoes, int id,int num_proc){

	double *xAnt, *calculado;
	double *erros;
	double diagonal=0, result=0;
	int flag_terminou=0;
	int posIni, posFim;
	register int i=0,j=0;
	MPI_Status status;

	xAnt = (double *)calloc(tamanho,sizeof(double));
	erros = (double *)malloc(tamanho*sizeof(double));

	//As linhas da matriz A e da matriz B são dividida pelos respectivos elementos da diagonal
	
	//#pragma omp for private(j,diagonal)
	for(i=0;i<tamanho;++i)
	{
		diagonal = MA[i][i];
		b[i] = b[i]/diagonal; 	
		for(j=0;j<tamanho;++j)
			MA[i][j]=MA[i][j]/diagonal;
	}
	
	if(criterioLinhasColunas(MA,tamanho)==0)
		return 0;
	
	//calculo dos resultaddos
	if(id == 0)
	{
		do
		{			
			
			/*Envia flag para não terminar os processos*/
			MPI_Bcast(&flag_terminou,1,MPI_INT,0,MPI_COMM_WORLD);

			/*Envia o vetor de x para todos os processos*/
			MPI_Bcast(&(x[0]),tamanho,MPI_DOUBLE,0,MPI_COMM_WORLD);
	
			/*Atualiza os valores anteriores para cálculo de erro*/
			//#pragma omp for
			for(i=0; i<tamanho; i++)
				xAnt[i] = x[i];

			/*Recebe os novos valores de x, o i esta sendo utilizado para representar o rank do processo*/
			#pragma omp for private(j, posIni, posFim, calculado)
			for(i=1; i<num_proc; i++)
			{
				/*Define a posicao de inicio e de fim que o processo sera responsavel por calcular, sendo que no processo 0 nada calcula*/
				posIni = (i-1)*(tamanho/(num_proc-1));
				
				/*posFim é a ultima posicao que o processo calcula*/
				if(i == num_proc -1)
					posFim = tamanho-1;
				else
					posFim = i*(tamanho/(num_proc-1))-1;
				
				/*aloca a estrutura para receber os valores calculados pelo processo*/
				calculado = malloc((posFim-posIni+1)*sizeof(double));
				
				
				MPI_Recv(calculado,(posFim-posIni+1),MPI_DOUBLE,i,0,MPI_COMM_WORLD,&status);
				
				//salvando os valores recebidos na estrutura x
				for(j=0;j <= (posFim - posIni); ++j)
				{
					x[posIni+j] = calculado[j];
					erros[posIni+j] = fabs(x[posIni+j]-xAnt[posIni+j]); //calcula o erro
				}
			}

			++(*n_iteracoes);
			
		}while(verificarErro(erros,x,tamanho,ERRO)==0 && *n_iteracoes<max_iteracoes);
		
		flag_terminou = 1;
		/*Envia flag para terminar execução*/
		MPI_Bcast(&flag_terminou,1,MPI_INT,0,MPI_COMM_WORLD);


	}
	else

	{
		do
		{
			

			/*Recebe a mensagem to nó 0*/
			MPI_Bcast(&flag_terminou,1,MPI_INT,0,MPI_COMM_WORLD);
			if(flag_terminou == 1)
				break;

			MPI_Bcast(&(x[0]),tamanho,MPI_DOUBLE,0,MPI_COMM_WORLD);
			
			/*Define a posicao de inicio e de fim que o processo sera responsavel por calcular*/
			posIni = (id-1)*(tamanho/(num_proc-1));
			
			/*posFim é a ultima posicao, incluse, que o processo calcula*/
			if(id == num_proc -1)
				posFim = tamanho-1;
			else
				posFim = id*(tamanho/(num_proc-1)) -1;
			
			calculado = malloc((posFim-posIni+1)*sizeof(double));


			/*calculo das respectivas variáveis que o  processo deve calcular*/
			#pragma omp for private(j, result)
			for(i=posIni;i <= posFim; ++i)
			{
				result = 0;
				for (j=0;j<tamanho;j++)
				{
					if(i != j) //não utiliza os valores da diagonal principal no cálculo
					result += ((-1)*MA[i][j]*x[j]);
				}
				/*Guarda os valores*/
				calculado[i-posIni] = result + b[i];
			}

			/*Envia o novo valor de x calculado*/
			MPI_Send(calculado,(posFim-posIni+1),MPI_DOUBLE,0,0,MPI_COMM_WORLD);
			

			++(*n_iteracoes);

		}while(*n_iteracoes<max_iteracoes);
		
	}

	MPI_Finalize();
	
	return 1;
}

