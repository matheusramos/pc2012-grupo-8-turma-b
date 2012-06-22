#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
//#include<mpi.h>
//#include<omp.h>

#define SIZE 600000
#define NHASH 29989 //Use a prime number!
#define MULT 31

unsigned int hash(char *p)
{
	unsigned int h = 0;
	for(; *p; p++){
		h = MULT * h + *p;
		printf("%c", *p);
	}
	printf("\n");
	return h % NHASH;
}


void montarParticao(FILE *arq, char **particao, int byte_inicio, int byte_fim)
{
	*particao = (char *) malloc( (byte_fim-byte_inicio+1)*sizeof(char)); /*Aloca exatamente o tamanho necessário para a particao +1 para o \0*/
	
	/*Leitura dos dados*/
	fseek(arq,byte_inicio,SEEK_SET);
	fread(*particao,sizeof(char),byte_fim-byte_inicio,arq);
	
	(*particao)[byte_fim-byte_inicio] = '\0';
}


int main(int argc, char **argv)
{	
	int j=time(NULL); //rand_r(&j);
	int i;
	FILE *arquivo;
	
	arquivo = fopen("palavras.txt","r+"); 
	
	printf("%d\n%d\n%d\n", hash("teste"), hash("fabio"), hash("dpsaidfs"));
			
	
	return 1;
}