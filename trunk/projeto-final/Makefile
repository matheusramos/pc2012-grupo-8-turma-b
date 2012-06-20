all: trata_arquivo

CC = gcc
C_FLAGS = -g -Wall

trata_arquivo.o: trata_arquivo.c
	$(CC) $(C_FLAGS) -c trata_arquivo.c

trata_arquivo: trata_arquivo.o
	$(CC) $(C_FLAGS) trata_arquivo.o -o trata_arquivo

clean:
	rm *.o trata_arquivo
