BDII-2
======

Eu criei @2  exemplo de tabela :

	no arquivo fs_tabela.dat esta organizado deste modo:

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

	 O programa lê o fs_tabela.dat e o fs_coluna.dat e arquivo de dados
	coloca no buffer e imprime.

	Acredito que as funcionalidades básicas já estão ok.

	

	para executar usa 

	./(NOME ARQUIVO) [CAMINHO DE fs_tabela.dat] [NOME TABELA] [CAMINHO
	de fs_coluna.dat];

	NOME TABELA : tabela a ser aberta, neste caso tem a tabela cliente
	e a tabela personagem nos arquivos
