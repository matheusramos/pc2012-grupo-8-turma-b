#ifndef MISC_H
#define MISC_H

#define TAMANHO_ADICIONAL 100000
#define T_STR_MENOR 5
#define T_STR_MAIOR 100
#define SEPARADOR '%'

struct
{
	char palavra[T_STR_MAIOR];
	int flag_achado;
}typedef registro;

void alocarVetorRegistro(registro **,long int *,int);
void desalocarVetorRegistro(registro **,int);
void realocarVetorRegistro(registro **,long int *,int);
void strToLower(char *);
void gravarVetorRegistro(registro *,long int,char *);
void recuperarVetorRegistro(registro **,long int *,int,char *);
void imprimirVetorRegistro(registro *, long int);
void gerarPalavra(int,long unsigned int *,registro *,int);
char gerarCaractere(int,unsigned long int);
int buscarPalavraMenor(registro *,char *,long int,short int *);

#endif
