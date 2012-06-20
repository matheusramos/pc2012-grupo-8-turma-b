#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<mpi.h>

/*
 *
 *
 */

char geraCaracter (int id, int contAleat)
{

	unsigned int i=time(NULL);
	unsigned int iProc;	

	iProc = i*(id+1)*contAleat;
	
	return rand_r(&iProc)%26+97;
	

}

int main(int argc, char **argv)
{
	int i,id, p; 
	unsigned long int contAleat =1;/* Variavel criada para que o processo nao gere a mesma letra aleatoria dentro do intervalo de tempo de segundo*/ 
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	
	for(i=0;i<4;++i)
	{
		printf("%c\n",geraCaracter(id,contAleat));
		++contAleat;
	}	

	MPI_Finalize();
	
	return EXIT_SUCCESS;
}










