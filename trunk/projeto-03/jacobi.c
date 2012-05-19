#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*Para cada linha, a soma do módulo do valor dos elementos, retirando a diagonal, deve ser menor do que 1
*Para cada coluna, a soma do módulo do valor dos elementos, retirando a diagonal, deve ser menor do que 1*/
int verifica_linhas_colunas(double **MatrizA, int tamanho)
{
	int i,j;
	double somaLinhas, somaColunas, diagonal;
	for(i=0;i<tamanho;++i)
	{
		diagonal = fabs(MatrizA[i][i]);
		somaLinhas=0;
		somaColunas=0;
		for(j=0;j<tamanho;++j)
			if(i!=j)
			{			
				somaLinhas+=fabs(MatrizA[i][j]);
				somaColunas+=fabs(MatrizA[j][i]);
			}
		if(somaLinhas>=1 || somaColunas>=1)
			return 0;
	}
	return 1;
}

int VerificaErro(double *erros, double *x, int tamanho, double ERRO){
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


int Jacobi(double **MatrizA, double *MatrizB, int tamanho, double ERRO, double MAXiteracoes){

	double *xAnt;
	double *x, *erros;
	double diagonal, result;
	int i,j,iteracoes=0;

	xAnt = (double *)malloc(tamanho*sizeof(double));
	x = (double *)malloc(tamanho*sizeof(double));
	erros = (double *)malloc(tamanho*sizeof(double));

	for(i=0;i<tamanho;++i)
		xAnt[i]=0;

	//As linhas da matriz A e da matriz B são dividida pelos respectivos elementos da diagonal
	//para dividir no MPI
	for(i=0;i<tamanho;++i)
	{
		diagonal = MatrizA[i][i];
		MatrizB[i] = MatrizB[i]/diagonal; 	
		for(j=0;j<tamanho;++j)
			MatrizA[i][j]=MatrizA[i][j]/diagonal;
		
	}

	for(i = 0; i < tamanho; i++) {
        for(j = 0; j < tamanho; j++)
            printf("%5.2f ", MatrizA[i][j]);
        printf(" = %5.2f", MatrizB[i]);
        printf("\n");
    }

	if(verifica_linhas_colunas(MatrizA,tamanho)==0)
	{
		printf("A matriz A falhou na verificação do critério das linhas e/ou das colunas\n");
		return 0;
	}

	
	//calculo dos resultados
	do
	{
		for(i=0;i<tamanho;i++)
		{
			result =0;
		   	for (j=0;j<tamanho;j++)
			{
		        if(i!=j)
		            result = result + ((-1)*MatrizA[i][j]*xAnt[j]);
		    }
		    x[i]=result + MatrizB[i];
			erros[i]=fabs(x[i]-xAnt[i]);
		}
		//salva os valores anteriores
		for(i=0;i<tamanho;i++)
            xAnt[i]=x[i];
		
		++iteracoes;
	}while(VerificaErro(erros,x,tamanho,ERRO)==0 && iteracoes<MAXiteracoes);

	printf("Resultado pelo Metodo de Jacobi-Richardson: \n");
    for(i=0;i<tamanho;i++){
        printf("x%d = %8.5f\n", i+1, x[i]);
    }

	return 1;
}
int main(int argc, char *argv[])
{
    int i;
	
	double **MA;
	double *MB;
	int tamanho = atoi(argv[1]);
	int ERRO = atoi(argv[2]);
	int iteracoes = atoi(argv[3]);
	
	MA = (double **)malloc(tamanho*sizeof(double *));
	MB = (double *)malloc(tamanho*sizeof(double));

	for(i=0;i<tamanho;++i)
		MA[i] = (double *)malloc(tamanho*sizeof(double));

	MA[0][0]=10;
	MA[0][1]=2;
	MA[0][2]=1;
	MA[1][0]=1;
	MA[1][1]=5;
	MA[1][2]=1;
	MA[2][0]=2;
	MA[2][1]=3;
	MA[2][2]=10;

	MB[0]=7;
	MB[1]=-8;
	MB[2]=6;
    Jacobi(MA, MB,tamanho,ERRO, iteracoes);
    printf("\n");
    

    return 0;
}
