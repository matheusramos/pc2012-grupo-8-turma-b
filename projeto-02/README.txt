=================================================

INSTRUÇÕES PARA EXECUTAR OS CÓDIGOS DO TRABALHO

=================================================

Para executar os códigos .c do trabalho basta apenas executar o arquivo .sh correspondentes, segue a relação:

sequencial_pequeno.c 	executa_seq_peq.sh
sequencial_grande.c 	executa_seq_grd.sh
hibrida_pequeno.c 		executa_hib_peq.sh
hibrida_grande.c 			executa_hib_grd.sh
paralelo_pequeno.c 		executa_par_peq.sh
paralelo_grande.c 		executa_par_peq.sh

Para executar o .sh basta inserir no terminal linux "./nome_do_arquivo.sh"
Para executar os arquivos "pequenos" é necessário possuir o arquivo "shakespe.txt" no mesmo diretório.
Para executar os arquivos "grandes" é necessário possuir o arquivo "wikipedia.txt" no mesmo diretório.
Ambos arquivos "shakespe.txt" e "wikipedia.txt" foram disponibilizados no Moodle Lasdpc (http://moodle.lasdpc.icmc.usp.br).

Para compilar os arquivos é necessário possuir o compilador gcc 4.2 e as bibliotecas "OpenMP" e "MPI".

As saídas de todos os programas são apresentadas em tela.
Não serão imprimidas na tela as palavras palíndromas com menos de 2 letras