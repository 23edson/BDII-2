/*
Executado no Ubuntu 12.04
Compilado com gcc version 4.6.3

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BP 512
#define SIZE 1024
#define FS_TABELA_NOT_FOUND -1
#define FS_COLUNA_NOT_FOUND -2
#define DATA_FILE_NOT_FOUND -3
#define OUT_OF_MEMORY -4
#define ERRO_LEITURA -5
#define TUPLE_NOT_FOUND -6
#define BUFFER_CHEIO -7
#define TABLE_NOT_FOUND -8
#define PAGE_INVALIDA -9
#define EMPTY_PAGE -10
#define GENERIC_ERROR -11
#define OKAY -12

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


int leTabela(struct OBJ **table,char *fs_tabela, char *Table_name, char *fs_coluna); //Identifica a estrutura da tabela
int positionOnFile(char *meta, int id);
int leMetaDados(struct CAMPOS **campos,char *fs_coluna, struct OBJ *table); //Identifica a estrutura do metadados
int tamTupla(struct CAMPOS *campos, char *meta); //tamanho de uma tupla (tamanho dos atributos somados)
int leTupla(struct CAMPOS *campos, char *fs_coluna, char *linha);//impressão na tela
int qtCampos(char *meta, int id); //Quantidade campos de uma tablea
int getTupla(char *linha,struct CAMPOS *campos, char *meta, struct OBJ *tabela, int from); //Carrega uma tupla  do arquivo de dados em forma de string
int carregaDados(struct page *buffer, char *meta, struct CAMPOS *campos, struct OBJ *tabela); //Função principal entre CARREGAR TUPLA E COLOCAR NO BUFFER
int inicializaBuffer(struct page **buffer); //Valores default para cada pagina
void setTupla(struct page *buffer,char *tupla, int tam, int pos); //Função complementar de colocaTuplaBuffer
int colocaTuplaBuffer(struct page *buffer, char *tupla, struct CAMPOS *campos, char *meta); //Controle do buffer e páginas
char *strcop(char *data, int pos, int tam); //Copia uma tupla do buffer para a impressao na tela
int showBuffer(struct page *buffer, struct CAMPOS *campos, char *meta); //Funções de IMPRESSÃO
int showTupleBuffer(struct page *buffer, struct CAMPOS *campos, char *meta, int pg, int rg);


