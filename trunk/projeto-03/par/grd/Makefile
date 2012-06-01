all: jr_par2000 jr_par3000 jr_par4000 

CC = mpicc
C_FLAGS = -Wall -fopenmp

jr_par2000.o: jr_par2000.c
	$(CC) $(C_FLAGS) -c jr_par2000.c

jr_par2000: jr_par2000.o
	$(CC) $(C_FLAGS) jr_par2000.o -o jr_par2000

jr_par3000.o: jr_par3000.c
	$(CC) $(C_FLAGS) -c jr_par3000.c

jr_par3000: jr_par3000.o
	$(CC) $(C_FLAGS) jr_par3000.o -o jr_par3000

jr_par4000.o: jr_par4000.c
	$(CC) $(C_FLAGS) -c jr_par4000.c

jr_par4000: jr_par4000.o
	$(CC) $(C_FLAGS) jr_par4000.o -o jr_par4000
