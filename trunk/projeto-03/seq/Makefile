all: jr_seq

CC = gcc
C_FLAGS = -Wall

jr_seq.o: jr_seq.c
	$(CC) $(C_FLAGS) -c jr_seq.c

jr_seq: jr_seq.o
	$(CC) $(C_FLAGS) jr_seq.o -o jr_seq
