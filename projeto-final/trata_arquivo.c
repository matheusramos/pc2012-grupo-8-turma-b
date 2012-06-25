#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"miscelanea.h"

int insereOrdenado(registro *vetor, char *palavra, long int tamanho)
{
	long int i=0,j=0;
	
	/*Primeira posicao do vetor*/
	if(tamanho==0)
		strcpy(vetor[0].palavra,palavra);
		
	else
	{	
		int inf=0,pos=tamanho-1;
		int meio=0;

		/*Faz a busca binaria para ver qual posicao inserir a palavra*/
		while(inf<pos)
		{
			meio=(inf+pos)/2;
			int comp=strcmp(vetor[meio].palavra,palavra);

			/*Achou a palavra deve sair*/
			if(comp==0)
				break;
			else if (comp<0)
				inf = meio+1;
			else
			{
				/*para evitar que pos fique -1*/
				if(meio==0)
					pos =0;
				else
					pos = meio-1;
			}			
		}
	
		meio=(inf+pos)/2;
		/*verifica se saiu porque achou a palavra, deve calcular o meio de novo, pq antes de sair do while
		pode ter mudado o valor dos limites inf e pos */
		if(strcmp(vetor[meio].palavra,palavra)==0)
			return 0;
		else
		{
			/*se a palavra que achou no vetor eh lexicograficamente menor, deve-se inserir na frente*/
			if(strcmp(vetor[pos].palavra,palavra)<0)
				i = pos+1;
			else
				i = pos;
			/*desloca os elementos*/
			for(j=tamanho;j>i;j--)
				strcpy(vetor[j].palavra,vetor[j-1].palavra);

			/*insere o elemento*/
			strcpy(vetor[i].palavra,palavra);

		}
	}

	return 1;
}

int main(int argc, char **argv)
{
	FILE *p_texto;
	long int p_texto_tam=0, t_vet_menor=0, t_vet_maior=0, i_menor=0, i_maior=0;
	registro *vetor_menor, *vetor_maior;
	char *s_texto, *palavra_atual;

	registro *registro_teste;
	long int tamanho_teste=0;

	/*Verifica se o argumento foi passado*/
	if(argc < 2)
	{
		fprintf(stderr,"Erro: Arquivo texto deve ser passado no primeiro argumento do programa.\n");
		return EXIT_FAILURE;
	}

	/*Abrir o arquivo*/
	p_texto = fopen(argv[1],"r");
	if(p_texto == NULL)
	{
		fprintf(stderr,"Erro: Erro ao abrir o arquivo especificado.\n");
		return EXIT_FAILURE;
	}

	/*Copiar o arquivo todo para uma string*/
	fseek(p_texto,0,SEEK_END);
	p_texto_tam = ftell(p_texto); //recupera o nro do byte final do arquivo
	fseek(p_texto,0,SEEK_SET);
	s_texto = (char *) malloc(p_texto_tam*sizeof(char) + 1*sizeof(char));

	fgets(s_texto,p_texto_tam,p_texto); //copia o texto do arquivo para a string -> [TESTADO] copia o texto na íntegra

	fclose(p_texto); /*Fecha o arquivo que não será mais utilizado*/
	
	t_vet_menor = TAMANHO_ADICIONAL;
	t_vet_maior = TAMANHO_ADICIONAL;
	alocarVetorRegistro(&vetor_menor,&t_vet_menor,T_STR_MENOR); //aloca vetor menor
	alocarVetorRegistro(&vetor_maior,&t_vet_maior,T_STR_MAIOR); // aloca vetor maior

	/*Separa as palavras no vetor maior ou menor*/
	palavra_atual = strtok(s_texto," ,-\n\r");

	while(palavra_atual != NULL)
	{
		strToLower(palavra_atual);

		if(strlen(palavra_atual) <= T_STR_MENOR) //inserir no vetor menor
		{
			if(i_menor+2 == t_vet_menor) //verificar se é já foram utilizadas todas as posiçoes do vetor
			{
				realocarVetorRegistro(&vetor_menor,&t_vet_menor,T_STR_MENOR);
				printf("Tamanho menor %ld\n",t_vet_menor);
				fflush(stdout);
			}

			if(insereOrdenado(vetor_menor,palavra_atual,i_menor))
				i_menor++;
			
		}
		else //inserir no vetor maior
		{
			if(i_maior+2 == t_vet_maior) //verificar se é já foram utilizadas todas as posiçoes do vetor
			{
				realocarVetorRegistro(&vetor_maior,&t_vet_maior,T_STR_MAIOR);
				printf("Tamanho maior %ld\n",t_vet_maior);
				fflush(stdout);
			}


			if(insereOrdenado(vetor_maior,palavra_atual,i_maior))
				i_maior++;
		}

		palavra_atual = strtok(NULL," ,-\n\r");
	}

	/*gravarVetorRegistro(vetor_menor,i_menor,"menor.dat");
	gravarVetorRegistro(vetor_maior,i_maior,"maior.dat");*/
	
	desalocarVetorRegistro(&vetor_menor,t_vet_menor);
	desalocarVetorRegistro(&vetor_maior,t_vet_maior);

	/*recuperarVetorRegistro(&registro_teste,&tamanho_teste,T_STR_MENOR,"menor.dat");
	imprimirVetorRegistro(registro_teste,tamanho_teste);
	desalocarVetorRegistro(&registro_teste,tamanho_teste);
*/
	/*recuperarVetorRegistro(&registro_teste,&tamanho_teste,T_STR_MAIOR,"maior.dat");
	imprimirVetorRegistro(registro_teste,tamanho_teste);
	*/
	//desalocarVetorRegistro(&registro_teste,tamanho_teste);
	
	//printf("Palavras menor: %ld - Palavras maior: %ld\n",i_menor,i_maior);
	free(s_texto);
	return EXIT_SUCCESS;
}
