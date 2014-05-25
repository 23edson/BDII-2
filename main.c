#include "func.h"

int main(int rg, char *arq[]){
    //main demonstrativa, para mais detalhes consulte arquivo LEIAME.txt e func.c

   char *fs_tabela = arq[1], *Table_name = arq[2], *fs_coluna = arq[3]; //Faça a atribuição conforme a ordem de entrada na execução pela linha de comando

    struct page *buffer = inicializaBuffer();//ok

	struct OBJ *table =leTabela(fs_tabela,Table_name, fs_coluna);
	
	/*int foo;	
	printf("MAINid: %d \n", table->id);
	puts(table->lnome);
	puts(table->fnome);
	puts(table->dir);*/
	//puts(fs_coluna);
	
	struct CAMPOS *campos = leMetaDados(fs_coluna, table->id); // Traz pra memória o esquema dos dados //ok
	/*printf("\nid: %d \n", campos[0].id);
		puts(campos[0].nome);
		printf("TIPO  %c\n", campos[0].tipo);
		printf("TAAMM: %d\n", campos[0].tamanho);
		
		
	   printf("\nid: %d \n", campos[1].id);
		puts(campos[1].nome);
		printf("TIPO  %c\n", campos[1].tipo);
		printf("TAAMM: %d\n", campos[1].tamanho);
		
		printf("\nid: %d \n", campos[2].id);
		puts(campos[2].nome);
		printf("TIPO  %c\n", campos[2].tipo);
		printf("TAAMM: %d\n", campos[2].tamanho);*/
		//int tf = *CAMPOS_TAM ;
	carregaDados(buffer,fs_coluna, campos,table);

    //showBuffer(buffer, campos, fs_coluna);

   showTupleBuffer(buffer, campos, fs_coluna, 0, 1);

    return 0;
}
