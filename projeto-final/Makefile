all: trata_arquivo macacos 

CC = gcc
MPICC = mpicc
C_FLAGS = -g -Wall

trata_arquivo.o: trata_arquivo.c miscelanea.h
	$(CC) $(C_FLAGS) -c trata_arquivo.c

miscelanea.o: miscelanea.c miscelanea.h
	$(CC) $(C_FLAGS) -c miscelanea.c

macacos.o: macacos.c miscelanea.h
	$(CC) $(C_FLAGS) -c macacos.c

trata_arquivo: trata_arquivo.o miscelanea.o
	$(CC) $(C_FLAGS) trata_arquivo.o miscelanea.o -o trata_arquivo

macacos: macacos.o miscelanea.o
	$(CC) $(C_FLAGS) macacos.o miscelanea.o -o macacos

clean:
	rm *.o trata_arquivo macacos
