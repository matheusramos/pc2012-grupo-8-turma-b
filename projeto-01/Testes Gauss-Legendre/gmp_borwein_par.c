#include<stdio.h>
#include<gmp.h>
#include<math.h>
#include<pthread.h>

 /*tipos gmpf_t para a thread*/
typedef struct{
  mpf_t a0,a1,y0,y1;
  mpf_t aux_y1,aux_y2,aux_a1,aux_a2;
  mpf_t y_valoratual; //utilizado para o calculo de a, deixando com que y nao fique dependendo da execucao de a
  long unsigned int k;
}thr_gmpf_t;

void gmp_borwein_par();
void *mpf_init_thread(mpf_t *);
void *calc_y(thr_gmpf_t *);
void *calc_a(thr_gmpf_t *);
void *mpf_seta_thread(thr_gmpf_t *);
void *mpf_sety_thread(thr_gmpf_t *);

/**
  * Algoritmo de Borwein
  *
  * vars.a1 se aproxima do valor de 1/PI.
  * Cada iteração quadruplica o número de dígitos corretos.
  *
  */
void gmp_borwein_par()
{

  /*threads*/
  pthread_t init[9], calc[4];
  /*variáveis para calculos*/
  thr_gmpf_t vars;

  mpf_set_default_prec(33219280);//(33219280); /*define a precisao do float em bits*/
  vars.k = 0; /*Seta o valor inicial do iterador*/
  calc[1] = 0;
  calc[3] = 0;

  /*Inicializa as variáveis em 0*/
  pthread_create(&init[0],NULL,(void *)&mpf_init,(void *)&vars.a0);
  pthread_create(&init[1],NULL,(void *)&mpf_init,(void *)&vars.a1);
  pthread_create(&init[2],NULL,(void *)&mpf_init,(void *)&vars.y0);
  pthread_create(&init[3],NULL,(void *)&mpf_init,(void *)&vars.y1);
  pthread_create(&init[4],NULL,(void *)&mpf_init,(void *)&vars.aux_y1);
  pthread_create(&init[5],NULL,(void *)&mpf_init,(void *)&vars.aux_y2);
  pthread_create(&init[6],NULL,(void *)&mpf_init,(void *)&vars.aux_a1);
  pthread_create(&init[7],NULL,(void *)&mpf_init,(void *)&vars.aux_a2);
  pthread_create(&init[8],NULL,(void *)&mpf_init,(void *)&vars.y_valoratual);
  /*A função espera as variáveis serem atualizadas*/
  pthread_join(init[0],NULL);
  pthread_join(init[1],NULL);
  pthread_join(init[2],NULL);
  pthread_join(init[3],NULL);
  pthread_join(init[4],NULL);
  pthread_join(init[5],NULL);
  pthread_join(init[6],NULL);
  pthread_join(init[7],NULL);
  pthread_join(init[8],NULL);

  /*TODO: verificar se é possível fazer os cálculos abaixo assim que a variável for inicializada acima*/
  /*seta os valores inicias das váriaveis de precisão variável*/
  /*d = sqrt(2)*/
  mpf_set_ui(vars.aux_y1,2);
  mpf_sqrt(vars.aux_y1,vars.aux_y1);

  /*a0 = 6-4*d*/
  mpf_mul_ui(vars.a0,vars.aux_y1,4);
  mpf_ui_sub(vars.a0,6,vars.a0);
  mpf_set(vars.a1,vars.a0); //a1=a0

  /*y0 = d-1*/
  mpf_sub_ui(vars.y0,vars.aux_y1,1); /*vars.y0 = sqrt(2)-1*/

  while(vars.k<12)
  {
    /*Certifica que o valor de y está atualizado antes de calcular o próximo valor de y*/
    if(calc[3] != 0)
      pthread_join(calc[3],NULL);

    pthread_create(&calc[0], NULL, (void *) &calc_y, (void *)&vars); //calcula valor de y-> nao depende de a nem de k, só do y anterior

    /*Certifica que a já foi calculado antes de fazer a0=a1*/
    if(calc[1] != 0)
      pthread_join(calc[1],NULL);
    pthread_create(&calc[2], NULL, (void *) &mpf_seta_thread, (void *)&vars); //troca o valor de a
    
    pthread_join(calc[0],NULL);
    mpf_set(vars.y_valoratual,vars.y1); //seta o valor de y que será usado para calcular a

    /*Troca o valor de y0=y1*/
    pthread_create(&calc[3], NULL, (void *) &mpf_sety_thread, (void *)&vars);

    pthread_join(calc[2],NULL);
    
    /*Calcula o novo valor de a*/
    pthread_create(&calc[1], NULL, (void *) &calc_a, (void *)&vars);
  }

  mpf_ui_div(vars.a1,1,vars.a1); /*PI=1/vars.a1*/

  gmp_printf("%.*Ff\n",10000000,vars.a1);

  /*Limpa as variáveis da memória*/ 
  mpf_clear(vars.a0),mpf_clear(vars.a1),mpf_clear(vars.y0),mpf_clear(vars.y1);
  mpf_clear(vars.aux_y1),mpf_clear(vars.aux_y2),mpf_clear(vars.aux_a1),mpf_clear(vars.aux_a2); 
  mpf_clear(vars.y_valoratual);

}

/**
  * Função genérica utilizada para iniciar o float de alta precisão usando threads
  *
  * @param x: variável a ser inicializada.
  */
void *mpf_init_thread(mpf_t *x)
{
  mpf_init(*x);
  return NULL;
}

/**
  * Função que faz a atribuição y0=y1 usando threads
  *
  * @param vars: ponteiro para a struct com as variáveis para cálculo do algoritmo de borwein
  */
void *mpf_sety_thread(thr_gmpf_t *vars)
{
  mpf_set(vars->y0,vars->y1);
  return NULL;
}

void *mpf_seta_thread(thr_gmpf_t *vars)
{
  mpf_set(vars->a0,vars->a1);
  return NULL;
}

void *calc_y(thr_gmpf_t *vars)
{
  /*vars.y1 = (1-sqrt(sqrt((1-pow(vars.y0,4))))) / (1+sqrt(sqrt(1-pow(vars.y0,4))));*/
  /*b = sqrt(sqrt(1-y0^4))*/
  mpf_pow_ui(vars->y1,vars->y0,4); /*y1 = pow(y0,4)*/
  mpf_ui_sub(vars->y1,1,vars->y1); /*y1 = 1 - y1*/
  mpf_sqrt(vars->y1,vars->y1);
  mpf_sqrt(vars->y1,vars->y1);

  /*y1 = 1-b/1+b*/
  mpf_ui_sub(vars->aux_y1,1,vars->y1);
  mpf_add_ui(vars->aux_y2,vars->y1,1);
  mpf_div(vars->y1,vars->aux_y1,vars->aux_y2);

  pthread_exit(NULL);
  return NULL;
}

/*TODO verificar se a melhor maneira de proceder com o cálculo abaixo*/
void *calc_a(thr_gmpf_t *vars)
{
    /*vars.a1 = vars.a0*pow(1 + vars.y1,4) - pow(2,2*k+3)*vars.y1*(1+vars.y1+pow(vars.y1,2));*/

    /*c = y1+1;*/
    mpf_add_ui(vars->aux_a1,vars->y_valoratual,1);

    mpf_pow_ui(vars->a1,vars->aux_a1,4); /*a1 = c^4*/
    mpf_mul(vars->a1,vars->a0,vars->a1); /*a1 = a0*a1*/ 

    mpf_pow_ui(vars->aux_a2,vars->y_valoratual,2); /*aux2 = pow(y_valoratual,2)*/
    mpf_add(vars->aux_a2,vars->aux_a2,vars->aux_a1); /*aux2 += c*/
    mpf_mul(vars->aux_a2,vars->aux_a2,vars->y_valoratual); /*vars->aux2 *= vars->y_valoratual*/


    /*continua os cálculos de a que não dependem de y*/
    /*o cálculo abaixo pode ser feito paralelamente*/
    mpf_set_ui(vars->aux_a1,2); /* aux1=2 */
    mpf_pow_ui(vars->aux_a1,vars->aux_a1,2*vars->k+3); /* aux_a1 = pow(aux_a1,2*k+3)*/

    mpf_mul(vars->aux_a1,vars->aux_a1,vars->aux_a2); /*vars->aux1 = vars->aux1*vars->aux2*/

    mpf_sub(vars->a1,vars->a1,vars->aux_a1);

    vars->k = vars->k+1;

    pthread_exit(NULL);
    return NULL;
}
