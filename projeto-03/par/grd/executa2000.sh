for (( j = 0 ; j < 5 ; j++ ))
do
	(time mpirun -np 13 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno jr_par2000) 2>>resultado_par2000.txt
done
