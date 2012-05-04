#define false 0
#define true 1

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

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
	char *palavra;
	if(argc >= 2){
		len=strlen(argv[1]);
		palavra = malloc(len * sizeof(char));
		strcpy(palavra, argv[1]);
	}
	else{
		printf("ERRO: PALAVRA NÃO INFORMADA NOS ARGUMENTOS");
		exit(1);
	}
	
	
	int ret=verificaPalindromo(palavra);
	if(ret > 0){
		printf("%s => Palindromo com soma ASCII: %d %d", palavra, ret, somaAscii(palavra));
	}else{
		printf("%s => Nao Palindromo", palavra);
	}
	printf("\n");
	return 1;
}