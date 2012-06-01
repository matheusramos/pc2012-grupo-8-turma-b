for i in `ls peq/jr_par*.c`
do
	for (( j = 0 ; j < 5 ; j++ ))
	do
		(time mpirun -np 13 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno $i) 2>>par_$i.txt
	done
done

for i in `ls grd/jr_par*.c`
do
	for (( j = 0 ; j < 3 ; j++ ))
	do
		(time mpirun -np 13 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno $i) 2>>par_$i.txt
	done
done

