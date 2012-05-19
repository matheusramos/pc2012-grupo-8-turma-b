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
