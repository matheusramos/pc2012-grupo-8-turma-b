#define false 0
#define true 1

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int verificaPalindromoPar(char* palavra){
	int tam, i, limite, ascii, somaascii=0, ret=1;
	
	tam=strlen(palavra);
	limite=floor((double) (tam)/ (double) 2);
	
	omp_set_num_threads(4);
	#pragma omp parallel for reduction (+:somaascii) reduction(&&:ret)
	for(i=0; i<limite;i++){
		somaascii+=palavra[i]+palavra[tam-1-i];
		if(palavra[i]!=palavra[tam-1-i]){ 
			if(abs(palavra[i]-palavra[tam-1-i])!=32) ret=0;
		}
	}
	if(ret==0){
		return -1;
	}
	if(tam%2==1) {
		ascii=palavra[limite];
		somaascii+=ascii;
	}
	return somaascii;
}

void removeCaracter(char* palavra, char caracter, char* palavranova){
	char p;
	int i=0, j=0;
	do{
		p=palavra[i];
		if(p!=caracter){
			palavranova[j]=p;
			j++;
		}
		i++;
	}while(p!='\0');
}

int verificaPalindromo(char* palavra){
	int tam, i, limite, ascii, somaascii=0;
	
	tam=strlen(palavra);
	limite=floor((double) (tam)/ (double) 2);
	
	//printf("%d => %s\n", tam, palavra);
	
	for(i=0; i<limite;i++){
		ascii=palavra[i];
		somaascii+=ascii;
		ascii=palavra[tam-1-i];
		somaascii+=ascii;
		//printf("%c %c %d - %d %d\n",palavra[i],palavra[tam-1-i], ascii, i, (tam-1-i));
		if(palavra[i]!=palavra[tam-1-i]){ 
			if(abs(palavra[i]-palavra[tam-1-i])!=32) return -1;
		}
	}
	if(tam%2==1) {
		ascii=palavra[limite];
		somaascii+=ascii;
	}
	return somaascii;
}
/*
 * Função para checagem, não será usada no programa final
 */
int somaAscii(char* palavra){
	int tam, i, ascii, somaascii=0;
	
	tam=strlen(palavra);
	for(i=0; i<tam;i++){
		ascii=palavra[i];
		somaascii+=ascii;
	}
	return somaascii;
}
int main(int argc, char *argv[]){ 
	int len;
	char *palavra, *palavrasemspacos;
	if(argc >= 2){
		len=strlen(argv[1]);
		palavra = malloc(len * sizeof(char));
		strcpy(palavra, argv[1]);
		palavrasemspacos = malloc(len * sizeof(char));
	}
	else{
		printf("ERRO: PALAVRA NÃO INFORMADA NOS ARGUMENTOS");
		exit(1);
	}
	palavra="A droga da gorda";
	removeCaracter(palavra,' ',palavrasemspacos);
	printf("%s\n", palavrasemspacos);
	int j,ret;
	for(j=0;j<100000;j++){
		ret=verificaPalindromoPar(palavrasemspacos);
	}
	if(ret > 0){
		printf("%s => Palindromo com soma ASCII: %d %d", palavra, ret, somaAscii(palavrasemspacos));
	}else{
		printf("%s => Nao Palindromo", palavrasemspacos);
	}
	printf("\n");
	return 1;
}