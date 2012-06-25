all: trata_arquivo macacos teste_recuperacao

CC = gcc
MPICC = mpicc
C_FLAGS = -g -Wall

trata_arquivo.o: trata_arquivo.c miscelanea.h
	$(CC) $(C_FLAGS) -c trata_arquivo.c

miscelanea.o: miscelanea.c miscelanea.h
	$(CC) $(C_FLAGS) -c miscelanea.c

macacos.o: macacos.c miscelanea.h
	$(CC) $(C_FLAGS) -c macacos.c

teste_recuperacao.o: teste_recuperacao.c miscelanea.h
	$(CC) $(C_FLAGS) -c teste_recuperacao.c

trata_arquivo: trata_arquivo.o miscelanea.o
	$(CC) $(C_FLAGS) trata_arquivo.o miscelanea.o -o trata_arquivo

macacos: macacos.o miscelanea.o
	$(CC) $(C_FLAGS) macacos.o miscelanea.o -o macacos

teste_recuperacao: teste_recuperacao.o
	$(CC) $(C_FLAGS) teste_recuperacao.o miscelanea.o -o teste_recuperacao

clean:
	rm *.o trata_arquivo macacos
