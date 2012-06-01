#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<mpi.h>
#include<omp.h>

typedef struct
{
	double valor;
	int indice;
} valorIndex;

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
	
	arquivo = fopen("../../entradas/peq/matriz500.txt","r");

	if(arquivo == NULL)
	{
		fprintf(stderr,"Falha ao abrir arquivo\n");
		return EXIT_FAILURE;
	}
	
	fscanf(arquivo,"%d",&j_order);

	alocarMatrizQuadDoub(&MA,j_order); //TODO:Paralelizar alocacao enquanto ocorre o resto da leitura
	b = (double *) calloc(j_order,sizeof(double)); //TODO: pode ser paralelizado
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
	for(i=0; i<j_order; i++)
		fscanf(arquivo,"%lf",&b[i]);

	//imprimirMatrizQuadDoub(MA,j_order);
		

	/*Chama o método numérico*/
	if(!jacobiRichardson(MA,x,b,j_order,j_error,j_ite_max,&n_iteracoes, id, p))
	{
		fprintf(stderr,"Falha: Matriz não atende ao critério de convergência");
		MPI_Abort(MPI_COMM_WORLD,-1);
		return EXIT_FAILURE;
	}
	
	if(id == 0)
		imprimirResultado(MA,x,b,j_order,n_iteracoes,j_row_test);
	//printf("ID do processo %d",id);

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

	double *xAnt;
	double *erros;
	double diagonal=0, result=0;
	int flag_terminou=0;
	register int i=0,j=0;
	MPI_Datatype mpi_dt_x;
	MPI_Status status;
	valorIndex calculado;
	/*Argumentos para o MPI_DataType da struct valorIndex*/
	int blen[3] = {1,1,1}; //Quantidade de cada elemento
	MPI_Aint indices[3] = {0,sizeof(double),sizeof(valorIndex)}; //indice de inicio de cada elemento na struct
	MPI_Datatype old_types[3] = {MPI_DOUBLE,MPI_INT,MPI_UB}; //tipos dos elementos da struct, MPI_UP -> upperbound, mostra o final da struct

	/*Define o tipo da estrutura valorIndex*/
	MPI_Type_struct(3,blen,indices,old_types,&mpi_dt_x);
	MPI_Type_commit(&mpi_dt_x);

	xAnt = (double *)calloc(tamanho,sizeof(double));
	erros = (double *)malloc(tamanho*sizeof(double));

	//As linhas da matriz A e da matriz B são dividida pelos respectivos elementos da diagonal
	#pragma omp for private(j)
	for(i=0;i<tamanho;++i)
	{
		diagonal = MA[i][i];
		b[i] = b[i]/diagonal; 	
		for(j=0;j<tamanho;++j)
			MA[i][j]=MA[i][j]/diagonal;
	}
	
	if(criterioLinhasColunas(MA,tamanho)==0)
		return 0;
	
	//calculo dos resultados
	if(id == 0)
	{
		do
		{
			/*printf("[INFO] ID %d, INICIANDO a iteração %d\n",id,*n_iteracoes);
			fflush(stdout);
			*/
			
			/*Envia flag para não terminar os processos*/
			MPI_Bcast(&flag_terminou,1,MPI_INT,0,MPI_COMM_WORLD);

			/*Envia o vetor de x para todos os processos*/
			MPI_Bcast(&(x[0]),tamanho,MPI_DOUBLE,0,MPI_COMM_WORLD);
			/*printf("[ENVIADO] ID %d - Vetor x pro broadcast [ITERACAO %d]\n",id,*n_iteracoes);
			fflush(stdout);
			*/

			/*Atualiza os valores anteriores para cálculo de erro*/
			#pragma omp for
			for(i=0; i<tamanho; i++)
				xAnt[i] = x[i];

			/*Recebe os novos valores de x*/
			#pragma omp for private(calculado)
			for(i=0; i<tamanho; i++)
			{
				/*printf("[RECEBENDO] ID %d - Posicao x [ITERACAO %d]\n",id,*n_iteracoes);
				fflush(stdout);*/
				MPI_Recv(&calculado,1,mpi_dt_x,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&status);
				/*printf("[RECEBIDO] ID %d - x[%d]=%lf [ITERACAO %d]\n",id,calculado.indice,calculado.valor,*n_iteracoes);
				fflush(stdout);*/
				x[calculado.indice] = calculado.valor;
				erros[calculado.indice] = fabs(x[calculado.indice]-xAnt[calculado.indice]); //calcula o erro
			}

			/*printf("[INFO] ID %d, TERMINANDO a iteração %d\n",id,*n_iteracoes);
			fflush(stdout);*/

			++(*n_iteracoes);
		}while(verificarErro(erros,x,tamanho,ERRO)==0 && *n_iteracoes<max_iteracoes);
		
		flag_terminou = 1;
		/*Envia flag para terminar execução*/
		MPI_Bcast(&flag_terminou,1,MPI_INT,0,MPI_COMM_WORLD);

		/*flag_terminou = 1;
		for(i=1;i<num_proc;i++)
			MPI_Isend(&flag_terminou,1,MPI_INT,i,0,MPI_COMM_WORLD,&request);
			*/
		/*TODO Fazer o processo 0 matar os outros aqui*/
		//MPI_Abort(MPI_COMM_WORLD,0);

	}
	else

	{
		do
		{
			/*printf("[INFO] ID %d, INICIANDO a iteração %d\n",id,*n_iteracoes);
			fflush(stdout);*/

			/*Recebe a mensagem to nó 0*/
			MPI_Bcast(&flag_terminou,1,MPI_INT,0,MPI_COMM_WORLD);
			if(flag_terminou == 1)
				break;

			/*printf("[RECEBENDO] ID %d, Vetor x por broadcast [ITERACAO %d]\n",id, *n_iteracoes);
			fflush(stdout);*/
			MPI_Bcast(&(x[0]),tamanho,MPI_DOUBLE,0,MPI_COMM_WORLD);
			/*printf("[RECEBIDO] ID %d, Vetor x por broadcast [ITERACAO %d]\n",id, *n_iteracoes);
			fflush(stdout);
			*/


			for(i=id-1;i<tamanho;i+=(num_proc-1)) //id-1 porque o processo 0 não calcula o valor de x, dessa maneira outro processo deve calculá-lo
			{
				result = 0;

				#pragma omp parallel for reduction (+:result)
				for (j=0;j<tamanho;j++)
				{
					if(i != j) //não utiliza os valores da diagonal principal no cálculo
						result += ((-1)*MA[i][j]*x[j]);
				}
				/*Guarda os valores na struct*/
				calculado.valor = result + b[i];
				calculado.indice = i;

				/*Envia o novo valor de x calculado*/
				/*printf("[ENVIADO] ID %d - x[%d]=%lf para o Processo 0 [ITERACAO %d]\n",id,i,calculado.valor,*n_iteracoes);
				fflush(stdout);*/
				MPI_Send(&calculado,1,mpi_dt_x,0,0,MPI_COMM_WORLD);
			}

			/*printf("[INFO] ID %d, TERMINANDO a iteração %d\n",id,*n_iteracoes);
			fflush(stdout);
			*/

			++(*n_iteracoes);

			/*MPI_Irecv(&flag_terminou,1,MPI_INT,0,0,MPI_COMM_WORLD,&request);
			printf("[RECEBIDO] ID %d - Flag Terminou = %d [ITERACAO %d]\n",id,flag_terminou,*n_iteracoes);*/
		//}while(1==1);
		}while(*n_iteracoes<max_iteracoes);
		
	}

	/*printf("Resultado pelo Metodo de Jacobi-Richardson: \n");
    for(i=0;i<tamanho;i++){
        printf("x%d = %8.5f\n", i+1, x[i]);
    }
	*/
	MPI_Finalize();
	
	return 1;
}

