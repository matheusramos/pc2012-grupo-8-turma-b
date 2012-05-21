all: jr_par

CC = mpicc
C_FLAGS = -Wall 

jr_par.o: jr_par.c
	$(CC) $(C_FLAGS) -c jr_par.c

jr_par: jr_par.o
	$(CC) $(C_FLAGS) jr_par.o -o jr_par
