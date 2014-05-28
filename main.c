#include "func.h"
#include "error.h"
int main(int rg, char *arq[]){
    //main demonstrativa, para mais detalhes consulte arquivo LEIAME.txt e func.c

   char *fs_tabela = arq[1], *Table_name = arq[2], *fs_coluna = arq[3]; //Faça a atribuição conforme a ordem de entrada na execução pela linha de comando

    struct page *buffer;//ok
	struct CAMPOS *campos;
	struct OBJ *table;
	int error;
	
	
	if(!inicializaBuffer(&buffer)== OKAY){
		printf("erro > %d  .SEM MEMORIA\n", error);
		return -1;
	}
	
	error = leTabela(&table,fs_tabela,Table_name, fs_coluna);	
	if(error != OKAY){
		printf("erro > %d  .LEITURA fs_tabela\n", error);
		return -1;
	}
	
	error = leMetaDados(&campos,fs_coluna, table);
	if(error != OKAY){
		printf("erro > %d   .LEITURA fs_coluna\n", error);
		return -1;
	}
	
	error = carregaDados(buffer,fs_coluna, campos,table);
	if(error != OKAY){
		printf("erro > %d   .LOAD DATA\n",error);
		return -1;
	}
    error = showTupleBuffer(buffer, campos, fs_coluna, 0, 2);
	if(error != OKAY){
		printf("erro > %d   .PRINT TUPLA\n",error);
	}
    return 0;
}
