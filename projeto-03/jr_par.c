#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<mpi.h>

int jacobiRichardson(double **,double *,double *,int,double,double,int *, int, char **);

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

    else return 0;
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
	
	arquivo = fopen("entradas/matriz250.txt","r");
	
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
			if(MA[i][j] == 0)
			{
				fprintf(stderr,"Falha: Determinante é zero");
				return EXIT_FAILURE;
			}
		}

	/*Lê o vetor b*/
	for(i=0; i<j_order; i++)
		fscanf(arquivo,"%lf",&b[i]);

	//imprimirMatrizQuadDoub(MA,j_order);
		

	/*Chama o método numérico*/
	if(!jacobiRichardson(MA,x,b,j_order,j_error,j_ite_max,&n_iteracoes, argc,argv))
	{
		fprintf(stderr,"Falha: Matriz não atende ao critério de convergência");
		return EXIT_FAILURE;
	}
	
	imprimirResultado(MA,x,b,j_order,n_iteracoes,j_row_test);
	printf("ID do processo %d",id);

	/*Desaloca variáveis*/
	free(x);
	free(b);
	desalocarMatrizQuadDoub(&MA,j_order);
	
	MPI_Finalize();

	return EXIT_SUCCESS;
}

/**
 * Método Jacobi-Richarson
 * @return 
 * FALSE se não passar em algum critério de convergência.
 */
int jacobiRichardson(double **MA, double *x, double *b, int tamanho, double ERRO, double MAXiteracoes, int *n_iteracoes, int argc, char **argv){

	double *xAnt;
	double *erros;
	double diagonal, result;
	register int i=0,j=0;

	xAnt = (double *)calloc(tamanho,sizeof(double));
	erros = (double *)malloc(tamanho*sizeof(double));

	//As linhas da matriz A e da matriz B são dividida pelos respectivos elementos da diagonal
	//para dividir no MPI
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
	do
	{
		for(i=0;i<tamanho;i++)
		{
			result =0;
		   	for (j=0;j<tamanho;j++)
			{
		        if(i!=j)
		            result = result + ((-1)*MA[i][j]*xAnt[j]);
		    }
		    x[i]=result + b[i];
			erros[i]=fabs(x[i]-xAnt[i]);
		}
		//salva os valores anteriores
		for(i=0;i<tamanho;i++)
            xAnt[i]=x[i];
		
		++(*n_iteracoes);
	}while(verificarErro(erros,x,tamanho,ERRO)==0 && *n_iteracoes<MAXiteracoes);

	/*printf("Resultado pelo Metodo de Jacobi-Richardson: \n");
    for(i=0;i<tamanho;i++){
        printf("x%d = %8.5f\n", i+1, x[i]);
    }
	*/
	
	return 1;
}

