all: t1progconcorrente

CC = gcc
C_FLAGS = -Wall -pthread -lgmp

main.o: main.c gmp_gauss_legendre.h gmp_gauss_legendre_par.h gmp_monte_carlo.h gmp_monte_carlo_par.h gmp_borwein.h gmp_borwein_par.h 
	$(CC) $(C_FLAGS) -c main.c
        
gmp_gauss_legendre.o: gmp_gauss_legendre.c gmp_gauss_legendre.h
	$(CC) $(C_FLAGS) -c gmp_gauss_legendre.c

gmp_gauss_legendre_par.o: gmp_gauss_legendre_par.c gmp_gauss_legendre_par.h
	$(CC) $(C_FLAGS) -c gmp_gauss_legendre_par.c

gmp_monte_carlo.o: gmp_monte_carlo.c gmp_monte_carlo.h
	$(CC) $(C_FLAGS) -c gmp_monte_carlo.c

gmp_monte_carlo_par.o: gmp_monte_carlo_par.c gmp_monte_carlo_par.h
	$(CC) $(C_FLAGS) -c gmp_monte_carlo_par.c

gmp_borwein.o: gmp_borwein.c gmp_borwein.h
	$(CC) $(C_FLAGS) -c gmp_borwein.c

gmp_borwein_par.o: gmp_borwein_par.c gmp_borwein_par.h
	$(CC) $(C_FLAGS) -c gmp_borwein_par.c
    
t1progconcorrente: main.o gmp_gauss_legendre.o gmp_gauss_legendre_par.o gmp_monte_carlo.o gmp_monte_carlo_par.o gmp_borwein.o gmp_borwein_par.o
	$(CC) $(C_FLAGS)  main.o gmp_monte_carlo.o gmp_gauss_legendre.o gmp_gauss_legendre_par.o gmp_monte_carlo_par.o gmp_borwein.o gmp_borwein_par.o -o t1progconcorrente
