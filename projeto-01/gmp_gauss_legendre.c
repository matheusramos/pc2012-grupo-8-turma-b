#include"gmp_gauss_legendre.h"
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>

void gmp_gauss_legendre(void)
{

    mpf_t aAnt,bAnt,tAnt,pAnt;
    mpf_t aPos,bPos,tPos,pPos;
    mpf_t pi;
    mpf_t temp1, temp2;
	int iteracao = 0;


    /*A precisao padrao sera no minimo 10.000.000*log10 na base 2.=  33.219.280 */
    mpf_set_default_prec (34000000);

    /*O objeto mpf_t deve ser inicializado antes de receber algum valor.*/
    mpf_init(aAnt), mpf_init(bAnt),mpf_init(tAnt), mpf_init(pAnt),mpf_init(aPos) ,mpf_init(bPos), mpf_init(tPos),mpf_init(pPos), mpf_init(pi), mpf_init(temp1),mpf_init(temp2);

    /*Inicializando as variaveis*/
    mpf_set_d (aAnt,1);

    /*bAnt = 1/sqrt(2)*/
    mpf_set_d (temp1,2);        /* temp1 = 2*/
    mpf_sqrt (temp2,temp1);     /* temp2 = sqrt(temp1) */
    mpf_ui_div (bAnt,1, temp2); /* bAnt = 1/temp2 */

    mpf_set_d (tAnt,0.25);
    mpf_set_d (pAnt,1);

	/* O algoritmo de Gauss-Legendre tem convergencia de secunda ordem, ou seja
	a cada iteracao o numero de digitos corretos dobra, ou seja 
	2^(qtdade_iteracoes) = numero de digitos corretos, com isso para gerar
	10 mi de digitos corretos sao necessarias 24 iteracoes. */
    while (iteracao < 24)
    {

        /*calculo do valor An+1
        aPos = (aAnt + bAnt)/2 */
        mpf_add(temp1,aAnt,bAnt);   /*temp1 = aAnt + bAnt   */
        mpf_div_ui (aPos,temp1,2); /*aPos = (temp1)/2     */


        /*calculo do valor Bn+1
        bPos = sqrt(aAnt * bAnt) */
        mpf_mul (temp1,aAnt,bAnt);  /*temp1 = aAnt * bAnt   */
        mpf_sqrt (bPos,temp1);      /*bPos = sqrt(temp1)    */


        /*calculo do valor Tn+1
        tPos = tAnt - pAnt*pow((aAnt-aPos),2) */
        mpf_sub (temp1, aAnt, aPos);    /*temp 1 = aAnt-aPos*/
        mpf_pow_ui (temp2,temp1,2);     /*temp2 = temp1^2*/
        mpf_mul (temp1,pAnt,temp2);     /*temp1= pAnt*temp2 */
        mpf_sub (tPos, tAnt, temp1);    /*tPos = tAnt - temp1 */

        /*calculo do valor Pn+1
        pPos = 2*pAnt */
        mpf_mul_ui(pPos,pAnt,2);    /*pPos = 2*pAnt */

		/* Se fosse necessario saber o valor de pi de cada iteracao, utilizaria-se
		o codigo de calculo do pi que esta apos o loop neste lugar*/


        mpf_set (aAnt,aPos);        /* aAnt = aPos */
        mpf_set (bAnt,bPos);        /* bAnt = bPos */
        mpf_set (tAnt,tPos);        /* tAnt = tPos */
        mpf_set (pAnt,pPos);        /* pAnt = pPos */
		
		++iteracao;

    }

	/*calculo do valor de piPos
    piPos = (pow((aPos+bPos),2))/(4*tPos) */

    mpf_add(temp1,aPos,bPos);       /*temp1 = aPos + bPos   */
    mpf_pow_ui (temp1,temp1,2);     /*temp1 = temp1^2*/
    mpf_mul_ui(temp2,tPos,4);       /*temp2 = 4*tPos */
    mpf_div (pi,temp1,temp2);    /*piPos = (temp1)/(temp2) */

    mpf_out_str (stdout,10,10000000,pi);
	
	mpf_clear(aAnt),mpf_clear(bAnt),mpf_clear(tAnt),mpf_clear(pAnt),mpf_clear(aPos),mpf_clear(bPos), mpf_clear(tPos),mpf_clear(pPos),mpf_clear(pi), mpf_clear(temp1),mpf_clear(temp2);


}

