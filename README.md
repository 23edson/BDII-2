Universidade Federal da Fronteira Sul
Ciência da Computação - Banco de Dados II
Implementação de Buffer

PRIMEIRA PARTE:
Por Gabrielle Souza e Lais Borin

SEGUNDA PARTE:
Edson Lemes da Silva
Lucas Cezar Parnoff

BDII-2

Estruturas:
	Para utilização, inclua "func.h" no programa.

	struct CAMPOS : Representa um atributo de uma tabela, deve-se declarar um ponteiro do tipo CAMPOS para o funcionamento 
	do programa.

	struct page : Refere-se a estrutura do buffer, deve-se declarar um ponteiro do tipo page. A constante BP representa
	o número de página que terá o buffer, e o SIZE, tamanho de cada página.

	struct OBJ : Esta estrutura armazena uma tabela, para o funcionamento do programa, deve-se declarar um ponteiro para este tipo.

Funções para o funcionamento:

	Ordem de execução das funções:
	1.Primeiramente, faz-se necessário a declaração de um buffer da seguinte maneira:
	inicializaBuffer(&[PONTEIRO page]);

	Onde a função "inicializaBuffer()" aloca memória para o ponteiro passado pelo parâmetro, definido pelas constantes BP (páginas) 
	com tamanho SIZE de dados.
	*BP e SIZE podem ser modificados no define da biblioteca func.h.
	A função retorna um inteiro, sendo ele negativo, que representa um status. As definições dos status possíveis,estão no arquivo
	"error.h".

	2.leTabela(struct OBJ **table,char *fs_tabela, char *Table_name, char *fs_coluna):
	recebe um ponteiro do tipo OBJ ( deve ser declarado antes);
	recebe uma string contendo o nome da tabela a ser lida.
       fs_coluna representa a localização do arquivo fs_coluna.dat, que contém os arquivos metadados(Passada por argumento na linha de comando. A 	 função retorna um inteiro negativo, que
	representa um status(informações em "error.h").

	3.leMetaDados(struct CAMPOS **campos,char *fs_coluna, struct OBJ *table);
	recebe um ponteiro do tipo CAMPOS (deve ser declarado antes). fs_coluna representa a localização de fs_coluna.dat(passada por argumento 
	na linha de comandos).OBJ table é a estrutura criada com a função leTabela ( primeiro parâmetro).
	O retorna é um inteiro negativo, que representa um status(informações em "error.h").

	4.carregaDados(struct page *buffer, char *meta, struct CAMPOS *campos, struct OBJ *tabela):
	A função recebe uma estrutura do tipo page (criada anteriormente com a função "inicializaBuffer()").
	a string meta deve-ser a localização de fs_coluna.dat passada por argumento na linha de comandos.
	Recebe uma estrutura do tipo campos ( criada na função "leMetaDados()");
	e também, uma função tipo OBJ ( criada em "leTabela");
	
	A função retorna um inteiro negativo, que representa um status, consulte : "error.h".

	5.Com os dados posto no buffer, é dada a opção de mostrar todas as páginas que contenham registro usando
	a função "showBuffer(buffer, esquema, meta)" ou escolher mostrar um determinado registro em uma certa página do	
	buffer utilizando a função "showTupleBuffer(buffer, esquema, meta, numPg, numReg)". Aonde buffer é uma estrutura do tipo page,
	esquema é uma estrutura do tipo CAMPO, meta é o caminho do arquivo fs_coluna.dat; numPG : número da página a ser lida, numReg : número
	do registro a ser lido.

	Utilização:

	Primeiramente o programa deve ter 3 Strings que recebem argumentos da linha de comando.
	ex: char *fs_tabela = arq[1] -- Onde o primeiro argumento é o caminho do arquivo fs_tabela.dat;
	    char *Table_name = arq[2] --Onde o segundo argumento é o nome da tabela a ser lido em fs_tabela.dat (ex: tabela "carro")
	    char *fs_coluna = arq[3] -- O terceiro argumento é o caminho do arquivo fs_coluna.dat, onde estão os metadados.
	    **Importante manter essa ordem de declaração.
		Após devem ser declarados as estruturas, e  chamar as funções de 1 a 5 ( na ordem).

	    EXECUÇÃO:
	    *Supondo que o programa compilado chama-se "main". A execução dele deve-se ocorrem da seguinte maneira:
	    No linux: 	./(NOME ARQUIVO) [CAMINHO DE fs_tabela.dat] [NOME TABELA] [CAMINHO de fs_coluna.dat];
	    
	    Exemplo: ./main files/fs_tabela.dat cliente files/fs_coluna.dat


FUNÇÕES INTERNAS:

	int positionOnFile(char *meta, int id): Essa função uma posição x no arquivo fs_coluna.dat
	Usada para saber onde começa os atributos de uma tabela no arquivo fs_coluna.dat;

	int tamTupla(struct CAMPOS *campos, char *meta): A função conta os tamanhos de cada atributo
	em uma tabela, e retorna a quantidade total de bytes.

	int qtCampos(char *meta, int id): Retorna a quantidade de atributos em uma tabela.

	int leTupla(struct CAMPOS *campos, char *fs_coluna, char *linha): Função que imprime 
	uma tupla na tela(Respeitando cada tipo de dado). 

	getTupla(char *linha,struct CAMPOS *campos, char *meta, struct OBJ *tabela, int from):
	Procura uma tupla no arquivo de dados "Sua localização está em tabela.dir" e seu nome
       em"tabela.fnome".

	setTupla(struct page *buffer,char *tupla, int tam, int pos): Função auxiliar que coloca
	numa página do buffer o conteúdo da tupla.

	colocaTuplaBuffer(struct page *buffer, char *tupla, struct CAMPOS *campos, char *meta):
	Procura uma página livre para colocar a tupla.

	char *strcop(char *data, int pos, int tam): Copia uma tupla do buffer, usada nas funções de
	impressão.  
		

=========

Sobre os arquivos de exemplos:

Foi criado @3  exemplos de tabelas :

	No arquivo fs_tabela.dat esta organizado deste modo:

	id | nome Lógico | nome físico | diretório
	-------------------------------------------
	1  |  cliente     |  000001.dat | files/data/
	2  |  personagem  |  000002.dat | files/data/
	3  |  carro       |  000003.dat | files/data/

	no arquivo fs_coluna.dat esta organizado assim :

	id | nome do atributo  |  tipo  | tamanho
	-----------------------------------------
	 1 |       nome       |   S     | 20
	 1 |       ender      |   S     | 30
     1 |       idade      |   I     |  4
     2 |       nome       |   S     |  30
     2 |       origem     |   S     |  15
     2 |       level      |   I     |  4
     2 |       Hplevel    |   I     |  4
     2 |       Classe     |   S     |  20
     3 |       nome       |   S     |  20
     3 |       chassi     |   S     |  50
     3 |       fabricante |   S     |  20
     3 |       anofab.    |   I     |  4
     3 |       potencia   |   D     |  8

	Arquivo 000001.dat :

	nome | ender  | idade
	---------------------
	Iron  | R. Oito| 450
	Steel | R. Nove| 670 
	Silver| R. Dez | 552	
	
	Arquivo 000002.dat

	nome         | origem     | level | hplevel | classe
	-------------------------------------------------
	The killer   |Wilderness  |30     | 500     | Guerreiro
	Monster B.   |South       |100    |1595     | Paladino
	Hellhound    |Underworld  |150    |2010     | Beast
	Abyssal Demon|Underworld  |150    |2009     | Demon
	Mister Mage  |Land of Snow| 51    |753      | Human

	Arquivo 000003.dat

	nome    | chassi       | fabricante  | anofab | potencia
	--------------------------------------------------------
	Golf    | 66ddf555www62| Volkswagen  | 2010   | 1.8
	Sandero | kk8080dfww101| Renault     | 2013   | 1.6
	Hb20    | mon65dd202758| Hyundai     | 2013   | 1.8
	Civic   | 2255gh3qw22rt| Honda       | 2012   | 2.0
	Corolla | oo2021vb26741| Toyota      | 2012   | 1.4
	Ka      | nn65df555512s| Ford        | 2010   | 1.0
	Classic | 23125la55vo11| Chevrolet   | 2013   | 1.0
