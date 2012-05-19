#include<stdio.h>
#include<stdlib.h>

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

int main(int argc, char **argv)
{
	double **MA;
	int j_order=0; //Ordem da matriz
	int j_row_test=0; //Linha(Fila) para ser avaliada
	double j_error=0; //Erro permitido
	int j_ite_max=0; //Numero máximo de iterações

	register int i=0,j=0; //int para iteração

	scanf("%d",&j_order);

	alocarMatrizQuadDoub(&MA,j_order); //TODO:Paralelizar alocacao enquanto ocorre o resto da leitura
	
	scanf("%d",&j_row_test);
	scanf("%lf",&j_error);
	scanf("%d",&j_ite_max);
	
	/*Lê a matriz A*/
	for(i=0; i<j_order; i++)
		for(j=0; j<j_order; j++)
			scanf("%lf",&MA[i][j]);

	imprimirMatrizQuadDoub(MA,j_order);	

	desalocarMatrizQuadDoub(&MA,j_order);
	

	return EXIT_SUCCESS;
}
