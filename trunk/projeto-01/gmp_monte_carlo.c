#include"gmp_monte_carlo.h"
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>
#include <time.h>
/* Função monte carlo sequencial:
  Recebe como parametro o numero de pontos que devem ser escolhidos aleatoriamente*/
void gmp_monte_carlo (int numpts)
{
/*Para realizar o metodo Monte Carlo foi utilizado uma circunferencia
de raio igual a 1 (para facilitar a comparacao que verifica se o ponto
esta dentro da circunferencia) inscrita em uma quadrado de lado igual a 2.
Foi considerado apenas o primeiro quadrante, pois assim as coordenadas dos
pontos variam de 0 a 1. */
    int i =0;
    double x, y;
    mpf_t pi;
    mpf_t intern_points, total_points, ratio;


    /*A precisao padrao sera no minimo 10.000.000*log10.*/
    mpf_set_default_prec (34000000);
	

    /*O objeto mpf_t deve ser inicializado antes de receber algum valor.*/
    mpf_init(pi),mpf_init(intern_points),mpf_init(total_points),mpf_init(ratio);
	
	
    /* Inicializa a semente para calcular o valor aleatorio*/
    srand (time(NULL));
	/* Para uma quantidade de pontos definidas na chamada da função*/
	while(i<numpts)
    {
		/*Dividindo o valor por RAND_MAX obtemos um valor entre 0 e 1*/
        x = (double) rand()/RAND_MAX;
        y = (double) rand()/RAND_MAX;

        if((pow(x,2)+pow(y,2))<=1)/* Pertence a circunferencia*/
           	mpf_add_ui (intern_points,intern_points,1);
        	
		mpf_add_ui (total_points,total_points,1);
		++i;

    }

	/*calculando o valor de pi
        pi = 4* (double) intern_points /total_points */

    mpf_div (ratio,intern_points,total_points);  /*ratio = intern_points / total_points*/
    mpf_mul_ui (pi,ratio,4);                 /* pi = 4*ratio*/
				
    /*Imprime pi */
    mpf_out_str (stdout,10,10000000,pi);
     
}

