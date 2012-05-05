#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]){ 
	int id, p, i;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	for(i=id; i < 16; i += p){
		printf("Processo: %d Num threads: %d\n", id, omp_get_num_procs());
		/*
		#pragma omp parallel
		{ 
		printf("    Teste\n");
		fflush(stdout);
		}
		*/
	}
	
	MPI_Finalize();
	
	return 1;
}