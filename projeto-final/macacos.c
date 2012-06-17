#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//#include<mpi.h>
//#include<omp.h>

int main(int argc, char **argv)
{
	int i=time(NULL);
	int j;
	for(j=0; j<20; j++)
		printf("%d => %f\n", i, (double) rand_r(&i)/RAND_MAX);
	
	return 1;
}