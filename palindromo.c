#define false 0
#define true 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verificaPalindromo(char* palavra){
	int tam, i;
	tam=strlen(palavra);
	//printf("%d => %s\n", tam, palavra);
	for(i=0; i<tam;i++){
		printf("%c %c - %d %d\n",palavra[i],palavra[tam-1-i], i, (tam-1-i));
		if(palavra[i]!=palavra[tam-1-i]) return false;
	}
	return true;
}
int main(){
	char palavra[] = "martram";
	if(verificaPalindromo(palavra)){
		printf("Palindromo");
	}else{
		printf("Nao Palindromo");
	}
	printf("\n");
	return 1;
}