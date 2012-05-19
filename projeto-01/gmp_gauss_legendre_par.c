#include"gmp_gauss_legendre_par.h"
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>
#include <pthread.h>

typedef struct
{
    mpf_t aAnt,bAnt,tAnt, pAnt;
    mpf_t aPos,bPos,tPos, pPos;
}dataGL;

void calculaA ( void * param );
void calculaB ( void * param );
void calculaT ( void * param );
void calculaP ( void * param );

void gmp_gauss_legendre_par(void)
{
    mpf_t pi;
    mpf_t temp1, temp2;
	pthread_t tA, tB, tT, tP;
	int iteracoes = 0;
	dataGL dadosGaussL;

    /*A precisao padrao sera no minimo 10.000.000*log10 na base 2.=  33.219.280 */
    mpf_set_default_prec (34000000);

    /*O objeto mpf_t deve ser inicializado antes de receber algum valor.*/
    mpf_init(dadosGaussL.aAnt), mpf_init(dadosGaussL.bAnt),mpf_init(dadosGaussL.tAnt), mpf_init(dadosGaussL.pAnt), mpf_init(temp1),mpf_init(temp2),mpf_init(dadosGaussL.aPos) ,mpf_init(dadosGaussL.bPos), mpf_init(dadosGaussL.tPos),mpf_init(dadosGaussL.pPos), mpf_init(pi);

    /*Inicializando as variaveis*/
    mpf_set_d (dadosGaussL.aAnt,1);

    /*bAnt = 1/sqrt(2)*/
    mpf_set_d (temp1,2);        /* temp1 = 2*/
    mpf_sqrt (temp2,temp1);     /* temp2 = sqrt(temp1) */
    mpf_ui_div (dadosGaussL.bAnt,1, temp2); /* bAnt = 1/temp2 */

    mpf_set_d (dadosGaussL.tAnt,0.25);
    mpf_set_d (dadosGaussL.pAnt,1);

	/* O algoritmo de Gauss-Legendre tem convergencia de secunda ordem, ou seja
	a cada iteracao o numero de digitos corretos dobra, ou seja 
	2^(qtdade_iteracoes) = numero de digitos corretos, com isso para gerar
	10 mi de digitos corretos sao necessarias 24 iteracoes. */
   	while(iteracoes < 24)
    {

		pthread_create (&tA, NULL, (void *) &calculaA, (void *) &dadosGaussL);
    	pthread_create (&tB, NULL, (void *) &calculaB, (void *) &dadosGaussL);
		pthread_create (&tT, NULL, (void *) &calculaT, (void *) &dadosGaussL);
		pthread_create (&tP, NULL, (void *) &calculaP, (void *) &dadosGaussL);

		/* Espera as threads terminarem para prosseguir com os calculos */
		pthread_join(tA, NULL);
    	pthread_join(tB, NULL);
		pthread_join(tT, NULL);
		pthread_join(tP, NULL);
    
		/* Se fosse necessario saber o valor de pi de cada iteracao, utilizaria-se
		o codigo de calculo do pi que esta apos o loop neste lugar*/

        mpf_set (dadosGaussL.aAnt,dadosGaussL.aPos);        /* aAnt = aPos */
        mpf_set (dadosGaussL.bAnt,dadosGaussL.bPos);        /* bAnt = bPos */
        mpf_set (dadosGaussL.tAnt,dadosGaussL.tPos);        /* tAnt = tPos */
        mpf_set (dadosGaussL.pAnt,dadosGaussL.pPos);        /* pAnt = pPos */
        
		++iteracoes;


    }

	/*calculo do valor de pi
    pi = (pow((aPos+bPos),2))/(4*tPos) */

	mpf_add(temp1,dadosGaussL.aPos,dadosGaussL.bPos);       /*temp1 = aPos + bPos   */
	mpf_pow_ui (temp1,temp1,2);     /*temp1 = temp1^2*/
	mpf_mul_ui(temp2,dadosGaussL.tPos,4);       /*temp2 = 4*tPos */
	mpf_div (pi,temp1,temp2);    /*pi = (temp1)/(temp2) */

	printf("\n");
	mpf_out_str (stdout,10,10000000,pi);

	mpf_clear(dadosGaussL.aAnt),mpf_clear(dadosGaussL.bAnt),mpf_clear(dadosGaussL.tAnt),mpf_clear(dadosGaussL.pAnt),mpf_clear(dadosGaussL.aPos),mpf_clear(dadosGaussL.bPos), mpf_clear(dadosGaussL.tPos),mpf_clear(dadosGaussL.pPos),mpf_clear(pi), mpf_clear(temp1),mpf_clear(temp2);


}


void calculaA ( void * param )
{

	dataGL *dado; 
	mpf_t temp1;
	mpf_init(temp1);
         
    dado = (dataGL *) param;
    /*calculo do valor An+1
    aPos = (aAnt + bAnt)/2 */
    mpf_add(temp1,dado->aAnt,dado->bAnt);   /*temp1 = aAnt + bAnt   */
    mpf_div_ui (dado->aPos,temp1,2); /*aPos = (temp1)/2     */
	mpf_clear(temp1);
    
    pthread_exit(0); /* exit */
}

void calculaB ( void * param )
{

	dataGL *dado; 
	mpf_t temp1;
	mpf_init(temp1);
         
    dado = (dataGL *) param;
 
	/*calculo do valor Bn+1
    bPos = sqrt(aAnt * bAnt) */
	mpf_mul (temp1,dado->aAnt,dado->bAnt);  /*temp1 = aAnt * bAnt   */
    mpf_sqrt (dado->bPos,temp1);      		/*bPos = sqrt(temp1)    */
	mpf_clear(temp1);

    pthread_exit(0); /* exit */
}

void calculaT ( void * param )
{

	dataGL *dado; 
	mpf_t temp1;
	mpf_init(temp1);
        
    dado = (dataGL *) param;
 
	/*calculo do valor Tn+1
    tPos = tAnt - pAnt*pow((aAnt-aPos),2) 

	Obs.: Para depender apenas dos valores anteriores, que ja estao calculados,
	substituimos aPos = (aAnt + bAnt)/2. Portanto,

	tPos = tAnt - pAnt*pow(((aAnt-bAnt)/2),2) 
	*/   
	mpf_sub (temp1, dado->aAnt, dado->bAnt);    /*temp 1 = aAnt-bAnt*/
	mpf_div_ui (temp1,temp1,2); 	/*temp1 = (temp1)/2     */
    mpf_pow_ui (temp1,temp1,2);     /*temp1 = temp1^2*/
    mpf_mul (temp1,dado->pAnt,temp1);     /*temp1= pAnt*temp1 */
    mpf_sub (dado->tPos, dado-> tAnt, temp1);    /*tPos = tAnt - temp1 */	
	
	mpf_clear(temp1);

    pthread_exit(0); /* exit */
}

void calculaP ( void * param )
{
	dataGL *dado;       
    dado = (dataGL *) param;

	/*calculo do valor Pn+1
    pPos = 2*pAnt */
    mpf_mul_ui(dado->pPos,dado->pAnt,2);    /*pPos = 2*pAnt */	

    pthread_exit(0); /* exit */

}





