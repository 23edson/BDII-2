/*
Executado no Ubuntu 12.04
Compilado com gcc version 4.6.3

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BP 512
#define SIZE 1024


struct CAMPOS
 {
   unsigned int id;  //identificador
   char nome[40];
   char tipo;
   int tamanho;
};

struct page {
   unsigned int nrec;            // numero de registros
   char data[SIZE];              //armazenamento das tuplas da página
   unsigned int pc;              // pin_count -> contador de uso da página
   unsigned int db;              // dirty_bit -> se dados foram modificados
   unsigned int position;        // posição livre da página
};

struct OBJ {
	unsigned int id; //identificador
	char lnome[30]; //nome lógico
	char fnome[30]; //nome físico
	char dir[30];  //diretório
};

//FUNÇÕES DISPONIVEL PARA USO
int leTabela(struct OBJ **table,char *fs_tabela, char *Table_name, char *fs_coluna); //Identifica a estrutura da tabela
int leMetaDados(struct CAMPOS **campos,char *fs_coluna, struct OBJ *table); //Identifica a estrutura do metadados
int inicializaBuffer(struct page **buffer); //Valores default para cada pagina
//Funções de IMPRESSÃO
int showBuffer(struct page *buffer, struct CAMPOS *campos, char *meta); //Mostra as paginas do buffer 
int showTupleBuffer(struct page *buffer, struct CAMPOS *campos, char *meta, int pg, int rg); //mostra um registro especifico em um página específica


