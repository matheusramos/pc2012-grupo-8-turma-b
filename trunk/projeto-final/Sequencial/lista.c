typedef struct pal
{
	char *word;
	struct pal *ant;
	struct pal *prox;
	
}palavra;


void insere_lista (palavra **alfabeto, char *valor)
{
	int letra;
	letra = valor[0]-97;
	
	palavra *p;
	p=malloc(sizeof(palavra));
	p->word = valor;
	p->ant = NULL;
	p->prox=NULL;
	
	
	/*inserir logo apos o $*/
	if(alfabeto[letra]->prox ==NULL || strcmp(alfabeto[letra]->prox->word,valor)>0 )
	{
		p->prox = alfabeto[letra]->prox;
		if(alfabeto[letra]->prox !=NULL)
			alfabeto[letra]->prox-> ant =p;
		alfabeto[letra]->prox = p;
		p->ant = alfabeto[letra];
		
	}
		else
		{
			/*para que nao repita a primeira palavra já inserida na lista*/
			if(strcmp(alfabeto[letra]->prox->word,valor)!=0)
			{
				palavra *aux;
				aux = alfabeto[letra]->prox;
				
				while(aux->prox!=NULL && strcmp(aux->prox->word,valor)<0)
				{		
					aux=aux->prox;
				}
							
										/*deve inserir a palavra apenas se ela nao foi inserida*/	
										if(aux->prox==NULL || strcmp(aux->prox->word,valor)!=0)
										{	
											p->prox = aux->prox;
											if(aux->prox !=NULL)
												aux->prox-> ant =p;
											aux->prox = p;
											p->ant = aux;	
										}
												
			}
		}
			
				
					
}


int main(int argc, char **argv)
{	
	int j=time(NULL); //rand_r(&j);
		int i;
		
			palavra **alfabeto;
			alfabeto = malloc(26*sizeof(palavra *));
			
			for(i=0;i<26;++i)
			{
					alfabeto[i]=malloc(sizeof(palavra));
				alfabeto[i]->ant = NULL;
				alfabeto[i]->prox=NULL;
				alfabeto[i]->word="$"; /*marcando o inicio da lista*/
			}
			
			
			insere_lista (alfabeto,"abacaxi");
			insere_lista (alfabeto,"aa");
			insere_lista (alfabeto,"a");
			insere_lista (alfabeto,"azzzzzzzz");
			insere_lista (alfabeto,"afff");
			insere_lista (alfabeto,"bb");
			insere_lista (alfabeto,"boneca");
			insere_lista (alfabeto,"beijo");
			insere_lista (alfabeto,"a");
			
			
			palavra *aux;
			aux=alfabeto[0];
			while(aux!=NULL)
			{
						printf("\n%s",aux->word);
					aux=aux->prox;
			}
			
			aux=alfabeto[1];
			while(aux!=NULL)
			{
					printf("\n%s",aux->word);
				aux=aux->prox;
			}
			
}