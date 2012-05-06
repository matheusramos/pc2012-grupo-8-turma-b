#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<omp.h>

#define NUM_PROCESSORS 8 /*somente para a versão sequencial, simula o nro de processadores*/

/*
 *
 * TODO Testar as bordas das partições.
 *
 */

/**
 * Verifica o caractere c é um separador ou EOF.
 */
int isSeparador(char c, char separador[])
{
	if (strchr(separador,c) != NULL || c == EOF)
		return 1;
	else
		return 0;
}

/**
 * Funcao que recebe o byte em que começa a partição e o que termina e copia
 * os dados para a string particão.
 */
void montarParticao(FILE *arq, char **particao, int byte_inicio, int byte_fim)
{
	*particao = (char *) malloc( (byte_fim-byte_inicio+1)*sizeof(char)); /*Aloca exatamente o tamanho necessário para a particao +1 para o \0*/

	/*Leitura dos dados*/
	fseek(arq,byte_inicio,SEEK_SET);
	fread(*particao,sizeof(char),byte_fim-byte_inicio,arq);

	(*particao)[byte_fim-byte_inicio] = '\0';
}

/**
 * Função que irá buscar um separador no stream apartir do offset
 * o retorno é o offset do ultimo caractere antes do separador
 * ou o EOF.
 *
 * Se o caracter atual for um Separador, correrá para a esquerda, caso contrário, irá para a direita.
 */
int buscarUltimoNaoSeparador(FILE *arq, int offset, char separador[])
{
	char c = 0;

	fseek(arq,offset,SEEK_SET);

	do
	{
		c = fgetc(arq);
	}
	while(!isSeparador(c,separador));
	
	if (c == EOF)
		return ftell(arq);
	else
		return ftell(arq)-1;
}

/**
 * Função semelhante a de cima, porém busca o não separador em uma string
 */
int buscarUltimoNaoSeparadorString(char *str, int indice, char separador[])
{
	long int i=0;

		for(i=indice; !isSeparador(str[i],separador) || !str[i]!='\0'; i++);

	if(str[i] == '\0')
		return i;
	else
		return i-1;
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



/**
 * Regras para separadores:
 * argc = 0 -> separadores: espaço, \n\r (ARQUIVO PEQUENO)
 * argc = 1 -> separadores: \n\r (ARQUIVO GRANDE)
 */
int main(int argc, char **argv)
{
	FILE *arq=NULL;
	long int tamanho_bytes=0;
	char *particao_texto[NUM_PROCESSORS], separador[4];
	register int i=0,j=0, k=0;
	int byte_inicio=0, byte_fim=0;

	/*Variáveis partição*/
	long int particao_tamanho=0, part_offset_inic=0, part_offset_fim=0;
	short int fator_thread=1; /*Quantos threads serão criadas para verificar as partições (será multiplicado pelo número máximo de threads)*/
	char *palin_candidate, *str_subpart, *str_aux;

	/*Definição dos separadores*/
	separador[0]='\n';
	separador[1]='\r';
	if (argc == 0)
	{
		separador[2]=' ';
	}
	separador[3]='\0';
	
	/*
	printf("Arquivo: %s\n",argv[2]);
	printf("Tipo arquivo = %d\n",atoi(argv[1]));
	*/

	arq = fopen(argv[2],"r+"); /*Abre o arquivo*/
	if (arq == NULL) /*Verifica se o arquivo existe*/
		return EXIT_FAILURE;

	/* 
	 * Calcula tamanho do arquivo - o ftell() para streams texto pode não voltar o tamanho do arquivo
	 * caso não funcione procurar pela função stat.
	 */
	fseek(arq,0,SEEK_END);
	tamanho_bytes = ftell(arq);
	fseek(arq,0,SEEK_SET);
	tamanho_bytes -= ftell(arq);
	
	/* 
	 * Aqui o arquivo vai ser divido em partes, o critério de divisão é o tamanho do arquivo e a ocorrência
	 * de um separador para que um palíndromo não seja cortado em dois pedaços.
	 */
	for(i=0; i<NUM_PROCESSORS; i++)
	{
		/*Calcula o byte de início da partição, corre o stream até achar um separador*/
		byte_inicio = (int)(tamanho_bytes*((float)i/(float)NUM_PROCESSORS)); 
		byte_inicio = buscarUltimoNaoSeparador(arq,byte_inicio, separador);
		/*Calcula o byte final da partição, corre o stram até achado um separador ou EOF*/
		byte_fim = (int)(tamanho_bytes*((float)(i+1)/(float)NUM_PROCESSORS));
		byte_fim = buscarUltimoNaoSeparador(arq,byte_fim, separador);

		/*Impressão para checagem*/
		/*
		printf("%d\n",(int)(tamanho_bytes*((float)i/(float)NUM_PROCESSORS)));
		printf("Byte inicial=%d, byte final=%d\n",byte_inicio,byte_fim);
		*/

		/*Transfere a partição para uma string*/
		montarParticao(arq,&particao_texto[i],byte_inicio,byte_fim);
		
		particao_tamanho = byte_fim-byte_inicio; /*Calcula o tamanho da partição para economizar em chamadas ao strlen()*/
		
		//omp_set_num_threads(fator_thread*omp_get_num_procs()); /*Caso queira aumentar nro de threads*/
		fator_thread = omp_get_num_procs();

		//#pragma omp parallel for private(part_offset_inic) private(part_offset_fim)
		for(j=0; j<fator_thread; j++)
		{
			part_offset_inic = (int)(particao_tamanho*( (float)j/ (float)omp_get_num_procs()));
			//part_offset_inic =	buscarUltimoNaoSeparadorString(particao_texto[i],part_offset_inic,separador);

			part_offset_fim = (int)(particao_tamanho*( (float)(j+1)/ (float)omp_get_num_procs()));
			//part_offset_fim =	buscarUltimoNaoSeparadorString(particao_texto[i],part_offset_fim,separador);
			
			printf("Byte inicial=%ld, byte final=%ld, tamanho=%ld, endereco=%ld\n",part_offset_inic,part_offset_fim,part_offset_fim-part_offset_inic,&(particao_texto[i][part_offset_inic]));
			/*fflush(stdout);*/
			
			/*if(j != fator_thread-1)
				particao_texto[i][part_offset_fim-1] = '\0'; Seta como \0 o ultimo caractere da subparticao para que o strtok() pare (sobrescreve um separador)*/
			//str_subpart = (char *) malloc((part_offset_fim-part_offset_inic)*sizeof(char));
			//fread(str_subpart,sizeof(char),part_offset_fim-part_offset_inic,particao_texto[i]);
			
			/*str_aux = particao_texto[i];*/

			str_subpart = (char *) malloc((part_offset_fim-part_offset_inic+1)*sizeof(char));
			memcpy(str_subpart,&(particao_texto[i][part_offset_inic]), part_offset_fim-part_offset_inic);
			str_subpart[part_offset_fim-part_offset_inic] = '\0';
			

			/*for(k=0; k<particao_tamanho; k++)
				printf("%c",(char)(particao_texto[i][k]));*/
				if(j<=1)
			printf("PONTO\n%s\n",str_subpart);

			/* VERIFICAÇÃO DE PALÍNDROMOS - TODO: conferir*/
			palin_candidate = strtok((char *) particao_texto[i],separador);

			while(palin_candidate != NULL)
			{
				//printf("%d %s\n",verificaPalindromo(palin_candidate),palin_candidate);
				//fflush(stdout);
				palin_candidate = strtok(NULL,separador);
			}
		}

	}
	
	if (!fclose(arq)) /*Tenta fechar o ponteiro do arquivo*/ 
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}


