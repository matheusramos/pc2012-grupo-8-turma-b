all: jr_par250 jr_par500 jr_par1000 jr_par1500

CC = mpicc
C_FLAGS = -Wall -fopenmp

jr_par250.o: jr_par250.c
	$(CC) $(C_FLAGS) -c jr_par250.c

jr_par250: jr_par250.o
	$(CC) $(C_FLAGS) jr_par250.o -o jr_par250

jr_par500.o: jr_par500.c
	$(CC) $(C_FLAGS) -c jr_par500.c

jr_par500: jr_par500.o
	$(CC) $(C_FLAGS) jr_par500.o -o jr_par500

jr_par1000.o: jr_par1000.c
	$(CC) $(C_FLAGS) -c jr_par1000.c

jr_par1000: jr_par1000.o
	$(CC) $(C_FLAGS) jr_par1000.o -o jr_par1000

jr_par1500.o: jr_par1500.c
	$(CC) $(C_FLAGS) -c jr_par1500.c

jr_par1500: jr_par1500.o
	$(CC) $(C_FLAGS) jr_par1500.o -o jr_par1500
