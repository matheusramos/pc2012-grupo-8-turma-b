all: trata_arquivo macacos macacos_par macacos_par2 macacos_par3

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

macacos_par2.o: macacos_par2.c miscelanea.h
	$(MPICC) $(C_FLAGS) -c macacos_par2.c

macacos_par3.o: macacos_par3.c miscelanea.h
	$(MPICC) $(C_FLAGS) -c macacos_par3.c

trata_arquivo: trata_arquivo.o miscelanea.o
	$(CC) $(C_FLAGS) trata_arquivo.o miscelanea.o -o trata_arquivo

macacos: macacos.o miscelanea.o
	$(CC) $(C_FLAGS) macacos.o miscelanea.o -o macacos

macacos_par: macacos_par.o miscelanea.o
	$(MPICC) $(C_FLAGS) macacos_par.o miscelanea.o -o macacos_par 

macacos_par2: macacos_par2.o miscelanea.o
	$(MPICC) $(C_FLAGS) macacos_par2.o miscelanea.o -o macacos_par2

macacos_par3: macacos_par3.o miscelanea.o
	$(MPICC) $(C_FLAGS) macacos_par3.o miscelanea.o -o macacos_par3

clean:
	rm *.o trata_arquivo macacos macacos_par macacos_par2 macacos_par3
