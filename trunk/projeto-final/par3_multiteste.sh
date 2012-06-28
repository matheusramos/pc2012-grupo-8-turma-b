echo "------------------------------------------------" >>par3.txt
echo "Teste par3.c" >>par3.txt
echo "------------------------------------------------" >>par3.txt
echo "Teste para 4 hosts, 4 processos" >>par3.txt
#for (( j = 0 ; j < 3 ; j++ ))
#do
	mpirun -np 4 --host wolverine,magneto,hulk,colossus macacos_par3 >> par3.txt
#done
echo "------------------------------------------------" >>par3.txt
echo "Teste para 4 hosts, 8 processos" >>par3.txt
#for (( j = 0 ; j < 3 ; j++ ))
#do
	mpirun -np 8 --host wolverine,magneto,hulk,colossus macacos_par3 >> par3.txt
#done
echo "------------------------------------------------" >>par3.txt
echo "Teste para 4 hosts, 16 processos" >>par3.txt
#for (( j = 0 ; j < 3 ; j++ ))
#do
	mpirun -np 16 --host wolverine,magneto,hulk,colossus macacos_par3 >> par3.txt
#done
echo "------------------------------------------------" >>par3.txt
echo "Teste para 8 hosts, 8 processos" >>par3.txt
#for (( j = 0 ; j < 3 ; j++ ))
#do
	mpirun -np 8 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira macacos_par3 >> par3.txt
#done
echo "------------------------------------------------" >>par3.txt
echo "Teste para 8 hosts, 16 processos" >>par3.txt
#for (( j = 0 ; j < 3 ; j++ ))
#do
	mpirun -np 16 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira macacos_par3 >> par3.txt
#done
echo "------------------------------------------------" >>par3.txt
echo "Teste para 8 hosts, 32 processos" >>par3.txt
#for (( j = 0 ; j < 3 ; j++ ))
#do
	mpirun -np 32 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira macacos_par3 >> par3.txt
#done
echo "------------------------------------------------" >>par3.txt
echo "Teste para 13 hosts, 13 processos" >>par3.txt
#for (( j = 0 ; j < 3 ; j++ ))
#do
	mpirun -np 13 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno macacos_par3 >> par3.txt
#done
echo "------------------------------------------------" >>par3.txt
echo "Teste para 13 hosts, 26 processos" >>par3.txt
#for (( j = 0 ; j < 3 ; j++ ))
#do
	mpirun -np 26 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno macacos_par3 >> par3.txt
#done
echo "------------------------------------------------" >>par3.txt
echo "Teste para 13 hosts, 52 processos" >>par3.txt
#for (( j = 0 ; j < 3 ; j++ ))
#do
	mpirun -np 52 --host wolverine,magneto,hulk,colossus,tempestade,demolidor,venon,vampira,gambit,elektra,anjo,justiceiro,noturno macacos_par3 >> par3.txt
#done
