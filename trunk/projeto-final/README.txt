Trabalho Final - Programação Concorrente

Fábio Henrique Gomes Sikansi	6792461
Matheus Edson Ramos				6793177
Vanessa Queiroz Marinho			6793201

Observação: Desconsidere as pastas Sequencial e Paralelo, só foram criadas para realizar testes adicionais
----------------------------------------
Descrição dos executáveis:

macacos			Implementação sequencial do programa
macacos_par		Implementação paralela do programa
trata_arquivo	Implementação do tratamento do arquivo de teste

----------------------------------------
Procedimento Pré-compilação

No cluster é necessário executar a seguinte linha de comando:
	export OMPI_CC=gcc-4.2;
----------------------------------------
Procedimento de compilação

Execute a linha de comando: 
	make

Observações: O makefile está programado para executar o gcc-4.2, isso foi necessário para compilação no cluster
----------------------------------------
Procedimento de preparo dos arquivos

Execute a linha de comando:
	./trata_arquivo palavras.txt 

----------------------------------------
Procedimento de execução

Sequencial:

Execute a linha de comando:
	./macacos

Paralelo: 

Execute a linha de comando:
	./timetest_par.sh
Será executado testes utilizando 4, 8 e 13 hosts, variando entre 1, 2 e 4 processos por host