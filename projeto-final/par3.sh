#for (( j = 0 ; j < 5 ; j++ ))
#do
	mpirun -np 13 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno macacos_par3 >> par3.txt
#done

