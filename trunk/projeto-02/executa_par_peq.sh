export OMPI_CC=gcc-4.2;
mpicc -o ppeq paralelo_pequeno.c -fopenmp
time mpirun --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno ppeq
