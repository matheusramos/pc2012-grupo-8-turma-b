for (( j = 0 ; j < 5 ; j++ ))
do
	(time mpirun -np 13 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno jr_par3000) 2>>resultado_par3000.txt
done
