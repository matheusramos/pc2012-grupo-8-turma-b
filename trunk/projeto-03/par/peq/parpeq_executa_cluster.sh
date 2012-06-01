for i in `ls jr_par*`
do
	for (( j = 0 ; j < 5 ; j++ ))
	do
		(time mpirun -np 13 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno $i) 2>>par_$i.txt
	done
done

