echo "------------------------------------------------" >> teste_par10.txt
echo "Teste par10p.c" >> teste_par10.txt
echo "------------------------------------------------" >> teste_par10.txt
echo "Teste para 4 hosts, 4 processos" >> teste_par10.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 4 --host wolverine,magneto,hulk,colossus macacos_par10p) 2>>  teste_par10.txt
done
echo "------------------------------------------------" >> teste_par10.txt
echo "Teste para 4 hosts, 8 processos" >> teste_par10.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 8 --host wolverine,magneto,hulk,colossus macacos_par10p) 2>>  teste_par10.txt
done
echo "------------------------------------------------" >> teste_par10.txt
echo "Teste para 4 hosts, 16 processos" >> teste_par10.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 16 --host wolverine,magneto,hulk,colossus macacos_par10p) 2>>  teste_par10.txt
done
echo "------------------------------------------------" >> teste_par10.txt
echo "Teste para 8 hosts, 8 processos" >> teste_par10.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 8 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira macacos_par10p) 2>>  teste_par10.txt
done
echo "------------------------------------------------" >> teste_par10.txt
echo "Teste para 8 hosts, 16 processos" >> teste_par10.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 16 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira macacos_par10p) 2>>  teste_par10.txt
done
echo "------------------------------------------------" >> teste_par10.txt
echo "Teste para 8 hosts, 32 processos" >> teste_par10.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 32 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira macacos_par10p) 2>>  teste_par10.txt
done
echo "------------------------------------------------" >> teste_par10.txt
echo "Teste para 13 hosts, 13 processos" >> teste_par10.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 13 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno macacos_par10p) 2>>  teste_par10.txt
done
echo "------------------------------------------------" >> teste_par10.txt
echo "Teste para 13 hosts, 26 processos" >> teste_par10.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 26 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno macacos_par10p) 2>>  teste_par10.txt
done
echo "------------------------------------------------" >> teste_par10.txt
echo "Teste para 13 hosts, 52 processos" >> teste_par10.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 52 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno macacos_par10p) 2>>  teste_par10.txt
done


echo "------------------------------------------------" >> teste_par20p.txt
echo "Teste par20p.c" >> teste_par20p.txt
echo "------------------------------------------------" >> teste_par20p.txt
echo "Teste para 4 hosts, 4 processos" >> teste_par20p.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 4 --host wolverine,magneto,hulk,colossus macacos_par20p) 2>>  teste_par20p.txt
done
echo "------------------------------------------------" >> teste_par20p.txt
echo "Teste para 4 hosts, 8 processos" >> teste_par20p.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 8 --host wolverine,magneto,hulk,colossus macacos_par20p) 2>>  teste_par20p.txt
done
echo "------------------------------------------------" >> teste_par20p.txt
echo "Teste para 4 hosts, 16 processos" >> teste_par20p.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 16 --host wolverine,magneto,hulk,colossus macacos_par20p) 2>>  teste_par20p.txt
done
echo "------------------------------------------------" >> teste_par20p.txt
echo "Teste para 8 hosts, 8 processos" >> teste_par20p.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 8 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira macacos_par20p) 2>>  teste_par20p.txt
done
echo "------------------------------------------------" >> teste_par20p.txt
echo "Teste para 8 hosts, 16 processos" >> teste_par20p.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 16 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira macacos_par20p) 2>>  teste_par20p.txt
done
echo "------------------------------------------------" >> teste_par20p.txt
echo "Teste para 8 hosts, 32 processos" >> teste_par20p.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 32 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira macacos_par20p) 2>>  teste_par20p.txt
done
echo "------------------------------------------------" >> teste_par20p.txt
echo "Teste para 13 hosts, 13 processos" >> teste_par20p.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 13 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno macacos_par20p) 2>>  teste_par20p.txt
done
echo "------------------------------------------------" >> teste_par20p.txt
echo "Teste para 13 hosts, 26 processos" >> teste_par20p.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 26 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno macacos_par20p) 2>>  teste_par20p.txt
done
echo "------------------------------------------------" >> teste_par20p.txt
echo "Teste para 13 hosts, 52 processos" >> teste_par20p.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 52 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno macacos_par20p) 2>>  teste_par20p.txt
done



echo "------------------------------------------------" >> teste_par50p.txt
echo "Teste par50p.c" >> teste_par50p.txt
echo "------------------------------------------------" >> teste_par50p.txt
echo "Teste para 4 hosts, 4 processos" >> teste_par50p.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 4 --host wolverine,magneto,hulk,colossus macacos_par50p) 2>>  teste_par50p.txt
done
echo "------------------------------------------------" >> teste_par50p.txt
echo "Teste para 4 hosts, 8 processos" >> teste_par50p.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 8 --host wolverine,magneto,hulk,colossus macacos_par50p) 2>>  teste_par50p.txt
done
echo "------------------------------------------------" >> teste_par50p.txt
echo "Teste para 4 hosts, 16 processos" >> teste_par50p.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 16 --host wolverine,magneto,hulk,colossus macacos_par50p) 2>>  teste_par50p.txt
done
echo "------------------------------------------------" >> teste_par50p.txt
echo "Teste para 8 hosts, 8 processos" >> teste_par50p.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 8 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira macacos_par50p) 2>>  teste_par50p.txt
done
echo "------------------------------------------------" >> teste_par50p.txt
echo "Teste para 8 hosts, 16 processos" >> teste_par50p.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 16 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira macacos_par50p) 2>>  teste_par50p.txt
done
echo "------------------------------------------------" >> teste_par50p.txt
echo "Teste para 8 hosts, 32 processos" >> teste_par50p.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 32 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira macacos_par50p) 2>>  teste_par50p.txt
done
echo "------------------------------------------------" >> teste_par50p.txt
echo "Teste para 13 hosts, 13 processos" >> teste_par50p.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 13 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno macacos_par50p) 2>>  teste_par50p.txt
done
echo "------------------------------------------------" >> teste_par50p.txt
echo "Teste para 13 hosts, 26 processos" >> teste_par50p.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 26 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno macacos_par50p) 2>>  teste_par50p.txt
done
echo "------------------------------------------------" >> teste_par50p.txt
echo "Teste para 13 hosts, 52 processos" >> teste_par50p.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 52 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno macacos_par50p) 2>>  teste_par50p.txt
done



echo "------------------------------------------------" >> teste_par.txt
echo "Teste par.c" >> teste_par.txt
echo "------------------------------------------------" >> teste_par.txt
echo "Teste para 4 hosts, 4 processos" >> teste_par.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 4 --host wolverine,magneto,hulk,colossus macacos_par) 2>>  teste_par.txt
done
echo "------------------------------------------------" >> teste_par.txt
echo "Teste para 4 hosts, 8 processos" >> teste_par.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 8 --host wolverine,magneto,hulk,colossus macacos_par) 2>>  teste_par.txt
done
echo "------------------------------------------------" >> teste_par.txt
echo "Teste para 4 hosts, 16 processos" >> teste_par.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 16 --host wolverine,magneto,hulk,colossus macacos_par) 2>>  teste_par.txt
done
echo "------------------------------------------------" >> teste_par.txt
echo "Teste para 8 hosts, 8 processos" >> teste_par.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 8 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira macacos_par) 2>>  teste_par.txt
done
echo "------------------------------------------------" >> teste_par.txt
echo "Teste para 8 hosts, 16 processos" >> teste_par.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 16 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira macacos_par) 2>>  teste_par.txt
done
echo "------------------------------------------------" >> teste_par.txt
echo "Teste para 8 hosts, 32 processos" >> teste_par.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 32 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira macacos_par) 2>>  teste_par.txt
done
echo "------------------------------------------------" >> teste_par.txt
echo "Teste para 13 hosts, 13 processos" >> teste_par.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 13 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno macacos_par) 2>>  teste_par.txt
done
echo "------------------------------------------------" >> teste_par.txt
echo "Teste para 13 hosts, 26 processos" >> teste_par.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 26 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno macacos_par) 2>>  teste_par.txt
done
echo "------------------------------------------------" >> teste_par.txt
echo "Teste para 13 hosts, 52 processos" >> teste_par.txt
for (( j = 0 ; j < 6; j++ ))
do
	(time mpirun -np 52 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno macacos_par) 2>>  teste_par.txt
done
