for i in `ls ../entradas/peq/`
do
	for (( j = 0 ; j < 5 ; j++ ))
	do
		(time ./jr_seq < ../entradas/peq/$i) 2>>seq_$i.txt
	done
done

for i in `ls ../entradas/grd/`
do
	for (( j = 0 ; j < 3 ; j++ ))
	do
		(time ./jr_seq < ../entradas/grd/$i) 2>>seq_$i.txt
	done
done
