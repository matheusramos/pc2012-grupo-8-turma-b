export OMPI_CC=gcc-4.2;
mpicc -o hpeq hibrida_pequeno.c -fopenmp
time mpirun --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno hpeq
