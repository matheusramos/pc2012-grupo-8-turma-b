#include "gmp_gauss_legendre.h"
#include "gmp_gauss_legendre_par.h"
#include "gmp_monte_carlo.h"
#include "gmp_monte_carlo_par.h"
#include "gmp_borwein.h"
#include "gmp_borwein_par.h"
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 
#include <time.h>

int main()
{
    time_t start, end;
    
    
    
    printf("Valor de pi pelo metodo Monte Carlo Sequêncial\n");
    start=time(NULL);
    gmp_monte_carlo(20000000);
    end=time(NULL);
    printf("\nTempo de Execução [Monte Carlo Sequêncial] 20.000.000 de pontos: %.10f\n",(double) (end-start));
    
    printf("\nValor de pi pelo metodo Monte Carlo Paralelo\n");
    start=time(NULL);
    gmp_monte_carlo_par(2,10000000);
    end=time(NULL);
    printf("\nTempo de Execução [Monte Carlo Paralelo] 2 threads com 10.000.000 de pontos por thread: %.10f\n",(double) (end-start));
    start=time(NULL);
    gmp_monte_carlo_par(8,2500000);
    end=time(NULL);
    printf("\nTempo de Execução [Monte Carlo Paralelo] 8 threads com 2.500.000 de pontos por thread: %.10f\n",(double) (end-start));
    start=time(NULL);
    gmp_monte_carlo_par(40,500000);
    end=time(NULL);
    printf("\nTempo de Execução [Monte Carlo Paralelo] 40 threads com 500.000 de pontos por thread: %.10f\n",(double) (end-start));
    start=time(NULL);
    gmp_monte_carlo_par(80,250000);
    end=time(NULL);
    printf("\nTempo de Execução [Monte Carlo Paralelo] 80 threads com 250.000 de pontos por thread: %.10f\n",(double) (end-start));
    start=time(NULL);
    gmp_monte_carlo_par(160,125000);
    end=time(NULL);
    printf("\nTempo de Execução [Monte Carlo Paralelo] 160 threads com 125.000 de pontos por thread: %.10f\n",(double) (end-start));
   
    printf("\nValor de pi pelo metodo Gauss-Legendre Sequencial\n");
    start=time(NULL);
    gmp_gauss_legendre();
    end=time(NULL);
    printf("\nTempo de Execução [Gauss-Legendre Sequencial]: %.10f\n",(double) (end-start));
    
    printf("\nValor de pi pelo metodo Gauss-Legendre Paralelo\n");
    start=time(NULL);
    gmp_gauss_legendre_par();
    end=time(NULL);
    printf("\nTempo de Execução [Gauss-Legendre Paralelo]: %.10f\n",(double) (end-start));
    
    printf("\nValor de pi pelo metodo Borwein Sequencial\n");
    start=time(NULL);
    gmp_borwein();
    end=time(NULL);
    printf("\nTempo de Execução [Borwein Sequencial]: %.10f\n",(double) (end-start));
    
    printf("\nValor de pi pelo metodo Borwein Paralelo\n");
    start=time(NULL);
    gmp_borwein_par();
    end=time(NULL);
    printf("\nTempo de Execução [Borwein Paralelo]: %.10f\n",(double) (end-start));

    return 0;
}
