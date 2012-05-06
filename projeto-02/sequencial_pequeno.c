#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<omp.h>

#define NUM_PROCESSORS 8 /*somente para a versão sequencial, simula o nro de processadores*/
#define MAXLENGTH 200
#define ARQUIVO_PEQUENO 0
#define ARQUIVO_GRANDE 1

/*
 *
 *
 */

typedef struct
{
        int last_index;
        int last_prime;
        int max_len;
        int *prime_list;
}primos;

void realoca (primos **p, int novo_tamanho)
{
        int *realocado;
        realocado = realloc ((*p)->prime_list, novo_tamanho * sizeof(int));
        (*p)->prime_list = realocado;
        
}

int crivo(primos *list, int valor)
{ 

        int i,j;
        int *vetor,prime;

        //temos que calcular mais primos
        if(valor > (list->last_prime))
        {
                int tamanho = valor - (list->last_prime);

                vetor = malloc(tamanho*sizeof(int));
        
                //preenche o vetor
                //#pragma omp parallel for
                for(i=0;i<tamanho;i++)
                                vetor[i]=(list->last_prime)+i+1;
        
                                
                for(i=0;i<=(list->last_index);++i)
                {
                        prime = list->prime_list[i];
                        
                        //#pragma omp parallel for
                        for(j=0;j<tamanho;++j)
                        {
                                //se eh multiplo
                                if(vetor[j]%prime==0)
                                        vetor[j]=-1;
                                        
                        }
                        //jah percorreu toda a lista inicial de primos, eh hora de add mais algum primo
                        if(i==(list->last_index))
                        {
                                int posicao=0;
                                while(posicao <tamanho && vetor[posicao]==-1)
                                        ++posicao;
                                //achou um valor nao marcado
                                if(posicao<tamanho)
                                {
                                        (list->last_index)++;
                                        list->prime_list[list->last_index] = vetor[posicao];
                                        list->last_prime = vetor[posicao];                              
                                        vetor[posicao]=-1;

                                        //caso o vetor esteja no limite, ele eh realocado
                                        if(list->last_index == (list->max_len)-1)
                                        {
                                                int novo_tamanho = (list->max_len)*2;
                                                realoca(&list,novo_tamanho);
                                                list->max_len = novo_tamanho;
        
                                        }
                                }       
                        
                        }
                }       
                
        }       
        
        //depois que montou a tabela verifica se o valor esta na tabela
        int inf=0,pos=0;
        pos  = list->last_index;
        while(inf<=pos)
        {
                int meio=(inf+pos)/2;
                if(list->prime_list[meio]==valor)
                {
                        return 1;
                }
                else if (list->prime_list[meio]<valor)
                        inf = meio+1;
                else
                        pos = meio-1;
        }

        return 0;
}



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

        if(offset ==0)
                return 0;

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
        
        if (indice == 0)
                return 0;

        for(i=indice; !isSeparador(str[i],separador) || str[i]!='\0'; i++);

        return i;
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
                        if((abs(palavra[i]-palavra[tam-1-i])!=32) || palavra[i]<65 || palavra[tam-1-i]<65) return -1;
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

void imprimePalindromosFrase(char *str, char separador[], primos *list)
{
        char *palin_candidate, *sem_espaco;
        int ascii_palindromo=0;
        /* VERIFICAÇÃO DE PALÍNDROMOS NAS PALAVRAS*/
        palin_candidate = strtok((char *) str,separador);
        
        while(palin_candidate != NULL)
        {
                sem_espaco = (char *) malloc(strlen(palin_candidate)*sizeof(char));
                removeCaracter(palin_candidate,' ',sem_espaco);

                if(strlen(sem_espaco) >1)
                {
                        ascii_palindromo = verificaPalindromo(sem_espaco);

                        /*
                        printf("SEM ESPACO: %s\n",sem_espaco);
                        fflush(stdout);
                        */
                         
                        if(ascii_palindromo > 0)
                        {
                                if(crivo(list,ascii_palindromo))
                                        printf("Palindromo:%s\t\tSoma ASCII: %d\tÉ primo\n",sem_espaco,ascii_palindromo);
                                else
                                        printf("Palindromo:%s\t\tSoma ASCII: %d\tNao primo\n",sem_espaco,ascii_palindromo);
                                fflush(stdout);
                        }
                }
                free(sem_espaco);

                palin_candidate = strtok(NULL,separador);
        }

}

void imprimePalindromosPalavra(char *str, char separador[], primos *list)
{
        char *palin_candidate, *str_palavra;    
        int ascii_palindromo=0;
        separador[8]=' ';
        
        //usada para cópia para que a string original não seja destruída pelo strtok()
        str_palavra = (char *) malloc((strlen(str)+1)*sizeof(char));
        strcpy(str_palavra,str);
        /* VERIFICAÇÃO DE PALÍNDROMOS NAS PALAVRAS*/
        palin_candidate = strtok((char *) str_palavra,separador);
        
        while(palin_candidate != NULL)
        {
                if(strlen(palin_candidate)>1)
                {
                        ascii_palindromo = verificaPalindromo(palin_candidate);

                        /*printf("%dPalindromo candidato: %s\n",flag_arquivo,palin_candidate);
                        fflush(stdout);
                        */
                         
                        if(ascii_palindromo > 0)
                        {
                                if(crivo(list,ascii_palindromo))
                                        printf("Palindromo:%s\t\tSoma ASCII: %d\tÉ primo\n",palin_candidate,ascii_palindromo);
                                else
                                        printf("Palindromo:%s\t\tSoma ASCII: %d\tNao primo\n",palin_candidate,ascii_palindromo);
                                fflush(stdout);
                        }
                }
        
                palin_candidate = strtok(NULL,separador);
        }

        free(str_palavra);
        separador[8] = '\0';
}

/**
 * Regras para separadores:
 * argc = 0 -> separadores: separadores (ARQUIVO PEQUENO)
 * argc = 1 -> separadores: separadores + "espaço" (ARQUIVO GRANDE)
 */
int main(int argc, char **argv)
{
        FILE *arq=NULL;
        long int tamanho_bytes=0;
        char *particao_texto[NUM_PROCESSORS], separador[12];
        register int i=0,j=0;
        int byte_inicio=0, byte_fim=0, flag_arquivo=0;

        /*Variáveis partição*/
        long int particao_tamanho=0, part_offset_inic=0, part_offset_fim=0;
        short int fator_thread=1; /*Quantos threads serão criadas para verificar as partições (será multiplicado pelo número máximo de threads)*/
        char *str_subpart;

        primos *list;
        list = (primos *) malloc(sizeof(primos));

				flag_arquivo=ARQUIVO_PEQUENO;
				char nome[20] = "shakespe.txt";

				//flag_arquivo=ARQUIVO_GRANDE;
				//char nome[20] = "wikipedia.txt";


        list->last_index=0;
        list->last_prime = 2;
        list->max_len = MAXLENGTH;
        list->prime_list = (int *) malloc ((MAXLENGTH)*sizeof(int));
        list->prime_list[0]=2;

        /*Definição dos separadores*/
        separador[0]='\n';
        separador[1]='\r';
        separador[2]='\t';
        separador[3]='.';
        separador[4]='!';
        separador[5]='?';
        separador[6]='-';
        separador[7]='\'';
        separador[8]='\0';
        if (flag_arquivo == ARQUIVO_GRANDE)
        {
                separador[8]=' ';
        }
        separador[9]='\0';
        
        /*
        printf("Arquivo: %s\n",argv[2]);
        printf("Tipo arquivo = %d\n",atoi(argv[1]));
        */

        arq = fopen(nome,"r+"); /*Abre o arquivo*/
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
                        part_offset_inic =      buscarUltimoNaoSeparadorString(particao_texto[i],part_offset_inic,separador);

                        part_offset_fim = (int)(particao_tamanho*( (float)(j+1)/ (float)omp_get_num_procs()));
                        part_offset_fim =       buscarUltimoNaoSeparadorString(particao_texto[i],part_offset_fim,separador);
                        
                        /*printf("Byte inicial=%ld, byte final=%ld\n",part_offset_inic,part_offset_fim);*/

                        /*Aloca a substring em uma nova string*/        
                        str_subpart = (char *) malloc((part_offset_fim-part_offset_inic+1)*sizeof(char));
                        strncpy(str_subpart,&(particao_texto[i][part_offset_inic]), part_offset_fim-part_offset_inic);
                        str_subpart[part_offset_fim-part_offset_inic] = '\0';

                        /*Calcula palindromos e primos*/
                        if(flag_arquivo == ARQUIVO_PEQUENO)
                        {
                                imprimePalindromosPalavra(str_subpart, separador, list);
                                imprimePalindromosFrase(str_subpart,separador,list);
                        }
                        else
                                imprimePalindromosPalavra(str_subpart, separador, list);
                        
                        free(str_subpart); //libera a memória da subparticao
                }
                free(particao_texto[i]); //libera a memória da partição
        }

        free(list->prime_list);
        free(list);
        
        /*Faz arquivos para teste*/
        /*for(i=0; i<NUM_PROCESSORS; i++)
        {
                sprintf(name,"teste_%d",i);
                particao_teste[i] = fopen(name,"w+");
                fseek(particao_teste[i],0,SEEK_SET);
                fputs(particao_texto[i],particao_teste[i]);
                fclose(particao_teste[i]);
        }*/
        
        if (!fclose(arq)) /*Tenta fechar o ponteiro do arquivo*/ 
                return EXIT_FAILURE;

        return EXIT_SUCCESS;
}
