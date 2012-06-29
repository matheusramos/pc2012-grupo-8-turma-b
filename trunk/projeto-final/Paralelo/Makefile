all: macacos macacos_par macacos_par10p macacos_par20p macacos_par50p

CC = gcc
MPICC = mpicc
C_FLAGS = -g -fopenmp -Wall


miscelanea.o: miscelanea.c miscelanea.h
	$(CC) $(C_FLAGS) -c miscelanea.c

macacos.o: macacos.c miscelanea.h
	$(CC) $(C_FLAGS) -c macacos.c

macacos_par.o: macacos_par.c miscelanea.h
	$(MPICC) $(C_FLAGS) -c macacos_par.c

macacos_par10p.o: macacos_par10p.c miscelanea.h
	$(MPICC) $(C_FLAGS) -c macacos_par10p.c

macacos_par20p.o: macacos_par20p.c miscelanea.h
	$(MPICC) $(C_FLAGS) -c macacos_par20p.c

macacos_par50p.o: macacos_par50p.c miscelanea.h
	$(MPICC) $(C_FLAGS) -c macacos_par50p.c

macacos: macacos.o miscelanea.o
	$(CC) $(C_FLAGS) macacos.o miscelanea.o -o macacos

macacos_par: macacos_par.o miscelanea.o
	$(MPICC) $(C_FLAGS) macacos_par.o miscelanea.o -o macacos_par 

macacos_par10p: macacos_par10p.o miscelanea.o
	$(MPICC) $(C_FLAGS) macacos_par10p.o miscelanea.o -o macacos_par10p 

macacos_par20p: macacos_par20p.o miscelanea.o
	$(MPICC) $(C_FLAGS) macacos_par20p.o miscelanea.o -o macacos_par20p

macacos_par50p: macacos_par50p.o miscelanea.o
	$(MPICC) $(C_FLAGS) macacos_par50p.o miscelanea.o -o macacos_par50p 


clean:
	rm *.o trata_arquivo macacos macacos_par macacos_par10p macacos_par20p macacos_par50p
