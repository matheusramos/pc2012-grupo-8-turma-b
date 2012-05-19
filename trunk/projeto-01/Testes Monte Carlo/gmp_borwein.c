#include "gmp_borwein.h"
#include<stdio.h>
#include<gmp.h>
#include<math.h>
#include<time.h>



/**
  * Algoritmo de Borwein
  *
  * a1 se aproxima do valor de 1/PI.
  * Cada iteração quadruplica o número de dígitos corretos.
  *
  */
void gmp_borwein()
{
  /*variáveis para calculo com respectivos valores iniciais*/
  mpf_t a0, a1, y0, y1, aux1, aux2;
  /*contador de iterações*/
  long unsigned int k=0;


  //mpf_set_default_prec(33220); /*define a precisao do float em bits*/
  mpf_set_default_prec(33219280);//(33219280); /*define a precisao do float em bits*/
  mpf_init(a0),mpf_init(a1),mpf_init(y0),mpf_init(y1),mpf_init(aux1),mpf_init(aux2); /*Inicializa as variáveis em 0*/

  /*seta os valores inicias das váriaveis de precisão variável*/
  /*a0 = 6-4*sqrt(2)*/
  mpf_set_ui(aux1,2);
  mpf_sqrt(aux1,aux1); /*sqrt(2)*/
  mpf_mul_ui(a0,aux1,4);
  mpf_ui_sub(a0,6,a0);

  //mpf_set_d(a0, 6-4*sqrt(2));
  mpf_sub_ui(y0,aux1,1); /*y0 = sqrt(2)-1*/

  while(k<12)
  {
    /*y1 = (1-sqrt(sqrt((1-pow(y0,4))))) / (1+sqrt(sqrt(1-pow(y0,4))));*/
    mpf_pow_ui(y1,y0,4); /*y1 = pow(y0,4)*/
    mpf_ui_sub(y1,1,y1); /*y1 = 1 - y1*/
    mpf_sqrt(y1,y1);
    mpf_sqrt(y1,y1);
    mpf_ui_sub(aux1,1,y1);
    mpf_add_ui(aux2,y1,1);
    mpf_div(y1,aux1,aux2);

    /*a1 = a0*pow(1 + y1,4) - pow(2,2*k+3)*y1*(1+y1+pow(y1,2));*/
    mpf_add_ui(a1,y1,1); /*a1 = y1+1*/
    mpf_pow_ui(a1,a1,4); /*a1 = a1^4*/
    mpf_mul(a1,a0,a1); /*a1 = a0*a1*/ 

    mpf_pow_ui(aux2,y1,2); /*aux2 = pow(y1,2)*/
    mpf_add(aux2,aux2,y1); /*aux2 += y1*/
    mpf_add_ui(aux2,aux2,1); /*aux2++*/
    mpf_mul(aux2,aux2,y1); /*aux2 *= y1*/

    mpf_set_ui(aux1,2); /* aux1=2 */
    mpf_pow_ui(aux1,aux1,2*k+3); /* aux1 = pow(aux1,2*k+3)*/

    mpf_mul(aux1,aux1,aux2); /*aux1 = aux1*aux2*/

    mpf_sub(a1,a1,aux1);

    
    /*troca os valores das variáveis de maneira eficiente*/
    mpf_swap(a0,a1);
    mpf_swap(y0,y1);
    
    k++;
  
    /*gmp_printf("k=%ld, y1=%.*Ff, 1/PI=%.*Ff\n", k, 20, y1, 20, a1);
    gmp_printf("a0=%.*Ff, y0=%.*Ff\n", 20, a0, 20, y0);*/
  }

  mpf_ui_div(a1,1,a1); /*PI=1/a1*/

  gmp_printf("%.*Ff\n",10000000,a1);

  mpf_clear(a0),mpf_clear(a1),mpf_clear(y0),mpf_clear(y1),mpf_clear(aux1),mpf_clear(aux2); /*Limpa as variáveis da memória*/

  
}
