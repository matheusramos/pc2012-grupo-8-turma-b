#include"gmp_monte_carlo_par.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <gmp.h>
#include <math.h>
#include <time.h>

#define NUMTH 1000
/*Estrutura que sera o tipo recebido pela funçao executada em paralelo, reune o total de pontos, o numero de pontos */
typedef struct {
  mpf_t intern_points, total_points;
  int numpoints;
} thr_montecarlo;
/*Vetor que reune os parametros para cada thread, o programa executa no maximo a chamada para 1000 threads */
thr_montecarlo param[999];
/*Função chamada pela thread, que gera os pontos aleatórios*/
void *montecarlo_thr(thr_montecarlo *p)
{
    double x, y;
    int i=0;
    srand (time(NULL));
	    /* Para uma quantidade de pontos determinada na chamada da função*/
    while(i<p->numpoints)
    {
	/*Dividindo o valor por RAND_MAX obtemos um valor entre 0 e 1*/
        x = (double) rand()/RAND_MAX;
        y = (double) rand()/RAND_MAX;

        if((pow(x,2)+pow(y,2))<=1)/* Pertence a circunferencia*/
	    mpf_add_ui (p->intern_points,p->intern_points,1);
	    mpf_add_ui (p->total_points,p->total_points,1);
	++i;

    }
    pthread_exit(NULL);
}

void gmp_monte_carlo_par (int numthr, int numpts)
{
    int i =0;
    mpf_t pi;
    /*Variavel que armazena quantos pontos vao ficar dentro da circunferencia, o total de pontos e a divisao de um pelo outro*/
    mpf_t intern_points, total_points, ratio;
    /*Vetor que reune as threads que serão executadas, o programa executa no maximo a chamada para 1000 threads  */
    pthread_t tabela_thr[1000];
 
    /*A precisao padrao sera no minimo 10.000.000*log10.*/
    mpf_set_default_prec (34000000);
	

    /*O objeto mpf_t deve ser inicializado antes de receber algum valor.*/
    mpf_init(pi),mpf_init(intern_points),mpf_init(total_points),mpf_init(ratio);
	
	
    /* Inicializa a semente para calcular o valor aleatorio*/
    srand (time(NULL));
	/* Para uma quantidade de threads passadas no parametro da função*/
	i=0;
	if(numthr>1000) numthr=1000;
	while(i<numthr)
	{
	  /* Inicializo os dados da estrutura */
	  mpf_init(param[i].intern_points);
	  mpf_init(param[i].total_points);
	  param[i].numpoints=numpts;
	  /*Executo a thread*/
	  pthread_create(&tabela_thr[i], NULL, (void*)&montecarlo_thr, (void*) & param[i]);
	  i++;
	}
	i=0;
	while(i<numthr){
	  /*Aguardo que todas as threads terminem e vou somando os pontos internos e totais para o calculo considerando todas as threads*/
	  pthread_join(tabela_thr[i], NULL);
	  mpf_add(intern_points,intern_points,param[i].intern_points);
	  mpf_add(total_points,total_points,param[i].total_points);
	  i++;
	}
	
	/*calculando o valor de pi
        pi = 4* (double) intern_points /total_points */

	mpf_div (ratio,intern_points,total_points);  /*ratio = intern_points / total_points*/
	mpf_mul_ui (pi,ratio,4);                 /* pi = 4*ratio*/
	/*imprime o valor de pi*/
	mpf_out_str (stdout,10,10000000,pi);
     
}

