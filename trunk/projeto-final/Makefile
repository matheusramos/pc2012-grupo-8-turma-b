all: trata_arquivo macacos macacos_par
CC = gcc-4.2
MPICC = mpicc
C_FLAGS = -g -fopenmp -Wall

trata_arquivo.o: trata_arquivo.c miscelanea.h
	$(CC) $(C_FLAGS) -c trata_arquivo.c

miscelanea.o: miscelanea.c miscelanea.h
	$(CC) $(C_FLAGS) -c miscelanea.c

macacos.o: macacos.c miscelanea.h
	$(CC) $(C_FLAGS) -c macacos.c

macacos_par.o: macacos_par.c miscelanea.h
	$(MPICC) $(C_FLAGS) -c macacos_par.c


trata_arquivo: trata_arquivo.o miscelanea.o
	$(CC) $(C_FLAGS) trata_arquivo.o miscelanea.o -o trata_arquivo

macacos: macacos.o miscelanea.o
	$(CC) $(C_FLAGS) macacos.o miscelanea.o -o macacos

macacos_par: macacos_par.o miscelanea.o
	$(MPICC) $(C_FLAGS) macacos_par.o miscelanea.o -o macacos_par 

clean:
	rm *.o trata_arquivo macacos macacos_par