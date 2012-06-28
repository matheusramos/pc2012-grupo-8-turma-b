all: macacos macacos10p macacos20p macacos50p

CC = gcc
MPICC = mpicc
C_FLAGS = -g -Wall


miscelanea.o: miscelanea.c miscelanea.h
	$(CC) $(C_FLAGS) -c miscelanea.c

macacos.o: macacos.c miscelanea.h
	$(CC) $(C_FLAGS) -c macacos.c

macacos10p.o: macacos10p.c miscelanea.h
	$(CC) $(C_FLAGS) -c macacos10p.c

macacos20p.o: macacos20p.c miscelanea.h
	$(CC) $(C_FLAGS) -c macacos20p.c

macacos50p.o: macacos50p.c miscelanea.h
	$(CC) $(C_FLAGS) -c macacos50p.c

macacos: macacos.o miscelanea.o
	$(CC) $(C_FLAGS) macacos.o miscelanea.o -o macacos

macacos10p: macacos10p.o miscelanea.o
	$(CC) $(C_FLAGS) macacos10p.o miscelanea.o -o macacos10p

macacos20p: macacos20p.o miscelanea.o
	$(CC) $(C_FLAGS) macacos20p.o miscelanea.o -o macacos20p

macacos50p: macacos50p.o miscelanea.o
	$(CC) $(C_FLAGS) macacos50p.o miscelanea.o -o macacos50p

clean:
	rm *.o macacos
