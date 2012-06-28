echo "------------------------------------------------" >>par.txt
echo "Teste par.c" >>par.txt
echo "------------------------------------------------" >>par.txt
echo "Teste para 4 hosts, 4 processos" >>par.txt
#for (( j = 0 ; j < 3 ; j++ ))
#do
	mpirun -np 4 --host wolverine,magneto,hulk,colossus macacos_par >> par.txt
#done
echo "------------------------------------------------" >>par.txt
echo "Teste para 4 hosts, 8 processos" >>par.txt
#for (( j = 0 ; j < 3 ; j++ ))
#do
	mpirun -np 8 --host wolverine,magneto,hulk,colossus macacos_par >> par.txt
#done
echo "------------------------------------------------" >>par.txt
echo "Teste para 4 hosts, 16 processos" >>par.txt
#for (( j = 0 ; j < 3 ; j++ ))
#do
	mpirun -np 16 --host wolverine,magneto,hulk,colossus macacos_par >> par.txt
#done
echo "------------------------------------------------" >>par.txt
echo "Teste para 8 hosts, 8 processos" >>par.txt
#for (( j = 0 ; j < 3 ; j++ ))
#do
	mpirun -np 8 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira macacos_par >> par.txt
#done
echo "------------------------------------------------" >>par.txt
echo "Teste para 8 hosts, 16 processos" >>par.txt
#for (( j = 0 ; j < 3 ; j++ ))
#do
	mpirun -np 16 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira macacos_par >> par.txt
#done
echo "------------------------------------------------" >>par.txt
echo "Teste para 8 hosts, 32 processos" >>par.txt
#for (( j = 0 ; j < 3 ; j++ ))
#do
	mpirun -np 32 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira macacos_par >> par.txt
#done
echo "------------------------------------------------" >>par.txt
echo "Teste para 13 hosts, 13 processos" >>par.txt
#for (( j = 0 ; j < 3 ; j++ ))
#do
	mpirun -np 13 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno macacos_par >> par.txt
#done
echo "------------------------------------------------" >>par.txt
echo "Teste para 13 hosts, 26 processos" >>par.txt
#for (( j = 0 ; j < 3 ; j++ ))
#do
	mpirun -np 26 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno macacos_par >> par.txt
#done
echo "------------------------------------------------" >>par.txt
echo "Teste para 13 hosts, 52 processos" >>par.txt
#for (( j = 0 ; j < 3 ; j++ ))
#do
	mpirun -np 52 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno macacos_par >> par.txt
#done
