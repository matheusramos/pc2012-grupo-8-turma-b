all: trata_arquivo

CC = gcc
C_FLAGS = -g -Wall

trata_arquivo.o: trata_arquivo.c miscelanea.h
	$(CC) $(C_FLAGS) -c trata_arquivo.c

miscelanea.o: miscelanea.c miscelanea.h
	$(CC) $(C_FLAGS) -c miscelanea.c

trata_arquivo: trata_arquivo.o miscelanea.o
	$(CC) $(C_FLAGS) trata_arquivo.o miscelanea.o -o trata_arquivo

clean:
	rm *.o trata_arquivo
