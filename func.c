/*t
Executado no Ubuntu 12.04
Compilado com gcc version 4.6.3

*/
#include "func.h"
#define CONST 60
#define CONST1 30
#define OBJ_TAM 94
#define CAMPOS_TAM 49
#define TAM_NOME 40


int leTabela(struct OBJ **table,char *fs_tabela, char *Table_name, char *fs_coluna){ // Retorna os metadados em uma estrutura.
		//printf("oooi");
		
	if(!fs_coluna){
		return FS_COLUNA_NOT_FOUND;
	}else if(!Table_name){
		return TABLE_NOT_FOUND;
	}
	FILE *tabela;
	*table = NULL;
	tabela = fopen( fs_tabela, "r");
	int error;

	//error = letabela_2 ( tabela, Table_name, fs_coluna);
	if(!(tabela )){
		return FS_TABELA_NOT_FOUND;
	}

	*table = (struct OBJ *) malloc(sizeof(struct OBJ));
	if(!(table)){
		return OUT_OF_MEMORY;
	}
	//printf("memo %p    ", &(*table));
	char endloop;

	do {
		fread(&(*table)->id, sizeof(int), 1, tabela); 
		fread((*table)->lnome,sizeof(char), CONST1, tabela);;
		fread((*table)->fnome,sizeof(char), CONST1, tabela); 
		fread((*table)->dir,sizeof(char), CONST1, tabela);
		fseek(tabela,-1,SEEK_CUR);
	}while(strcmp((*table)->lnome,Table_name)!=0 && (endloop = fgetc(tabela) != EOF));
	if(strcmp((*table)->lnome, Table_name)){
		return TABLE_NOT_FOUND;
	}

	fclose(tabela);
	return OKAY;
}
int positionOnFile(char *meta, int id){
	FILE *fs_coluna = NULL;

	int pula = 0;
	int counter1 = 0;
	if(!(fs_coluna = fopen(meta, "r"))){
		return OUT_OF_MEMORY;
	}

   fseek(fs_coluna,0,SEEK_END);
	long pos = ftell(fs_coluna); //pega o tamanho do arquivo
	rewind(fs_coluna);

	while(pula < pos){
			fread(&counter1, sizeof(int),1,fs_coluna);
			//pula = pula + sizeof(int);
			if(counter1 == id){
				return ftell(fs_coluna) - sizeof(int);

			}
			else{
			//pula++;
				fseek(fs_coluna,CAMPOS_TAM - sizeof(int),SEEK_CUR);
				pula += CAMPOS_TAM;
			}
	}

	return GENERIC_ERROR ;
}
int leMetaDados(struct CAMPOS **campos,char *fs_coluna, struct OBJ *table){

	FILE *metadados;
	*campos = NULL;
	int qtdCampos, i, j = 0, tam;
	char c;
	int error;
	if(!table->id){
		return TABLE_NOT_FOUND;
	}
	//printf("idddd  %d", id);
	
	qtdCampos = qtCampos(fs_coluna, table->id);
	if(!(qtdCampos)){
		error = qtdCampos;
		return error;
	}
		//printf("qt : %d",qtdCampos);
	
	metadados = fopen(fs_coluna, "r");
	if(!(metadados)){
		
		return FS_COLUNA_NOT_FOUND;
	}
		 // Abre os metadados armazenados em meta

	int posi = positionOnFile(fs_coluna, table->id);
	if(!(posi)){
		return GENERIC_ERROR;
	}
   fseek(metadados, posi, SEEK_CUR);
	//printf("pos : %d", ftell(metadados));
    if(qtdCampos) // Lê o primeiro inteiro que representa a quantidade de campos da tabela.
    {
	   int t;
	  
	   *campos =(struct CAMPOS *)malloc(sizeof(struct CAMPOS)*qtdCampos);
	   
	   if(!(*campos)){
		    // Cria uma estrutura para armazenar os dados dos campos.
		    return OUT_OF_MEMORY;
		}
	   for( i = 0; i < qtdCampos ; i ++) // Laço para ler o nome, tipo e tamanho de cada campo.
	   {
		   
		   (*campos)->id = table->id;
		   fread(&t, sizeof(int),1,metadados);
		   fread(&c, sizeof(char),1,metadados);
			while (c != '\0') // Laço para ler o nome do campo.
			{
				(*campos)->nome[j] = c;
				fread(&c, sizeof(char),1,metadados);
				j++;
			}
			fseek(metadados, TAM_NOME - j -1, SEEK_CUR);
			fread(&c, 1, 1, metadados); // Lê o tipo do campo.
			(*campos)->tipo = c;
			fread(&tam , sizeof(int), 1, metadados); // Lê o tamanho do campo.
			(*campos)->tamanho = tam;
			j = 0;
			(*campos)++;
			
			//fseek(metadados,0,SEEK_END);
			//long pos = ftell(metadados); //pega o tamanho do arquivo

			//printf("t : %d e %d", pos,qtdCampos);

	   }
	   fclose(metadados);// Fecha o arquivo meta
	   (*campos) -= i;

	   return OKAY;
    }

	return GENERIC_ERROR;
}
int tamTupla(struct CAMPOS *campos, char *meta){// Retorna o tamanho total da tupla da tabela.

    int qtdCampos, i, tamanhoGeral = 0;
    qtdCampos = qtCampos(meta, campos[0].id);
    if(!(qtdCampos)){
		return GENERIC_ERROR;
	}

    // Lê o primeiro inteiro que representa a quantidade de campos da tabela.
	for(i = 0; i < qtdCampos; i++)
		tamanhoGeral += campos[i].tamanho ; // Soma os tamanhos de cada campo da tabela.

	return tamanhoGeral;
}
int qtCampos(char *meta, int id){ // Retorna a quantidade de campos do esquema
    FILE *fs_coluna = NULL;
    int qtdCampos = 0;
    int pula = 0;
    int counter1 = 0;
    char endloop;
   // struct CAMPOS g;
   // puts(meta);
    //printf("sizeof %d", sizeof(int));
    if(!(fs_coluna = fopen(meta, "r"))){
		return FS_COLUNA_NOT_FOUND;
	}


    fseek(fs_coluna,0,SEEK_END);
	long pos = ftell(fs_coluna); //pega o tamanho do arquivo
	rewind(fs_coluna);
	long h;
	

     //counter1 = id;
     int condicao = 1;
     while(condicao && pula < pos){
			fread(&counter1, sizeof(int),1,fs_coluna);
			//pula = pula + sizeof(int);
			if(counter1 == id){
				qtdCampos++;
				fseek(fs_coluna,CAMPOS_TAM - sizeof(int),SEEK_CUR);
				pula += CAMPOS_TAM;h = pula; 

			}
			else{
			//pula++;
				fseek(fs_coluna,CAMPOS_TAM - sizeof(int),SEEK_CUR);
				pula += CAMPOS_TAM;
			}
	 }


   // fread(&qtdCampos, sizeof(int), 1, metadados); //Lê o primeiro inteiro que representa a quantidade de campos da tabela.
    fclose(fs_coluna);
	
    return qtdCampos;
}
int leTupla(struct CAMPOS *campos, char *fs_coluna, char *linha){ //Lê uma tupla da memória

    char *auxStr; //Variável auxiliar para leitura de stringd

    if(linha == NULL)
        return ERRO_LEITURA;

    int qtdCampos, j, k=0 ; // k é a posição do byte dentro da tupla
    qtdCampos = qtCampos(fs_coluna, campos[0].id);

    for(j=0 ; j<qtdCampos; j++){
        if(j!=0)
            printf(" | ");
        if(campos[j].tipo == 'S'){
            auxStr = linha + k;    //acesso a posição de inínio de uma string
            printf("%-15s", auxStr);
            k += campos[j].tamanho;     //Atualição de leitura do número de bytes para char
        }else if(campos[j].tipo == 'D'){
            double *n = (double *)&linha[k];
            printf("%-16f", *n);
            k += sizeof(double);   //Atualição de leitura do número de bytes para double
        }else if(campos[j].tipo == 'I'){
            int *n = (int *)&linha[k];
            printf("%-16d", *n);
            k += sizeof(int);   //Atualição de leitura do número de bytes para int
        }
    }
    printf("\n");
    return OKAY;

}
int getTupla(char *linha,struct CAMPOS *campos, char *meta, struct OBJ *tabela, int from){ //Pega uma tupla do disco a partir do valor de from
	//int id;

    int tamTpl = tamTupla(campos, meta);

    FILE *dados;
    char *arquivo;
    if(!(arquivo = (char*)malloc(sizeof(char)* CONST))){
		 return OUT_OF_MEMORY;
	 }
		 //const 60 porque concatenando dir e nome fisica terá no max 60 bytes

    arquivo[0] = '\0';
    strcat(arquivo, tabela->dir);
    strcat(arquivo, tabela->fnome);
    

    if(!(dados = fopen(arquivo, "r"))){
		return DATA_FILE_NOT_FOUND;
	}


    fseek(dados, from, 1);
    if(fgetc (dados) != EOF){
        fseek(dados, -1, 1);
        fread(linha, sizeof(char), tamTpl, dados); //Traz a tupla inteira do arquivo
    }
    else{       //Caso em que o from possui uma valor inválido para o arquivo de dados
        fclose(dados);
        return GENERIC_ERROR;
    }
    fclose(dados);
    return OKAY;
    //return linha;
}


//============================ BUFFER ===========================//

int inicializaBuffer(struct page **buffer){

	*buffer = NULL;
    *buffer = (struct page *)malloc(sizeof(struct page)*BP);
    
    if(!(*buffer)){
		return OUT_OF_MEMORY;
	} //Aloca as páginas do buffer

    int i;
	for (i=0;i<BP;i++)  //Inicializa o buffer
	{
		(*buffer)->db=0;
		(*buffer)->pc=0;
		(*buffer)->nrec=0;
		(*buffer)->position=0;
		(*buffer)++;
	}
	
	(*buffer) -=i;

	return OKAY;
}
void setTupla(struct page *buffer,char *tupla, int tam, int pos){ //Coloca uma tupla de tamanho "tam" no buffer e na página "pos"
	int i=buffer[pos].position;
	for (;i<buffer[pos].position + tam;i++){
		buffer[pos].data[i] = *(tupla++);
	}
}
int colocaTuplaBuffer(struct page *buffer, char *tupla, struct CAMPOS *campos, char *meta){//Define a página que será incluida uma nova tupla
	
    int i=0, found=0;
    int error;
	while (!found && i < BP)//Procura pagina com espaço para a tupla.
	{
    	if(SIZE - buffer[i].position > tamTupla(campos, meta)){// Se na pagina i do buffer tiver espaço para a tupla, coloca tupla.
            setTupla(buffer, tupla, tamTupla(campos, meta), i);
            found = 1;
            buffer[i].position += tamTupla(campos,meta); // Atualiza proxima posição vaga dentro da pagina.
            buffer[i].nrec += 1;
            return OKAY;
    	}
    	i++;// Se não, passa pra proxima página do buffer.
    }
    return BUFFER_CHEIO;
    /*
    if (!found)
    {
        printf("Buffer Cheio! Implementar a política de troca.\n");
		return;
    }
    */
}
int showTupleBuffer(struct page *buffer, struct CAMPOS *campos, char *meta, int pg, int rg){
//mostra o registro de número "rg" da página "pg" do bufffer
    int k, i, tam = tamTupla(campos,meta), qt=qtCampos(meta,campos[0].id);
    char *linha = NULL;
	int error;
	if(pg < 0 || pg > BP)
		return PAGE_INVALIDA;
	else if(buffer[pg].nrec == 0)
			return EMPTY_PAGE;
    if(buffer[pg].position != 0){
        for(i = 0; i< qt; i++)
            printf("%-20s", campos[i].nome);
        printf("\n--------------------------------------------------------------------------------------------\n");
        for(k = 0; k < buffer[pg].nrec; k ++){
            if(k == rg){
                linha = strcop(buffer[pg].data, k, tam); //Função que devolve uma string para a impressão da tupla
                if(!linha){
					return OUT_OF_MEMORY;
				}
                error = leTupla(campos, meta, linha); //Mostra a string
                if(error != OKAY)
					return error;
				printf("\n\n");
                return OKAY;
            }
        }
        return TUPLE_NOT_FOUND;
    }
    return GENERIC_ERROR;

}
int showBuffer(struct page *buffer, struct CAMPOS *campos, char *meta){
//Mostra todas as páginas do buffer que contenham registros
    int i, k, tam = tamTupla(campos,meta);
    char *linha = NULL;
    int error;

    for(i = 0; i < BP; i++){
        if(buffer[i].position != 0){
            printf("Página %d:\n", i);
            for(k = 0; k < buffer[i].nrec; k ++){
                linha = strcop(buffer[i].data, k, tam);
                if(!linha)
					return OUT_OF_MEMORY;

                error = leTupla(campos, meta, linha);
                if(error != OKAY)
					return error;
            }
        }
    }
    return OKAY;
}
char *strcop(char *data, int pos, int tam){//Copia registro do buffer
    //pos é a posição inicial do registro a ser copiado e tam é seu tamanho total
    int i;
   
    char *linha = (char *)malloc(sizeof(char)*tam);
    if(!(linha))
		return NULL;

    for(i = 0; i < tam ; i++){
        linha[i] = data[(tam*pos) + i];// Copia a tupla para uma variável auxiliar.
		
    }
    
    return linha;
}
int carregaDados(struct page *buffer, char *meta, struct CAMPOS *campos, struct OBJ *tabela){
//Traz todos os registros para o buffer
	//int id = 1;
    int i=1,tamTpl = (tamTupla(campos, meta)); //tamTpl representa o tamanho total dos atributos
    char *linha;
     if(!(tamTpl)){
		 return GENERIC_ERROR;
	 }

     if(!(linha =(char *)malloc(sizeof(char)*tamTpl))){
		 return OUT_OF_MEMORY;
	 }
    int error;
	
    error = getTupla(linha,campos, meta, tabela, 0);
    if(error == OKAY){

		while(linha != NULL){ //Pega as tuplas e insere no buffer até que acabe o arquivo
			error = colocaTuplaBuffer(buffer, linha, campos, meta);
			free(linha);
			linha =(char *)malloc(sizeof(char)*tamTpl);
			if(error == OKAY){
				error = getTupla(linha,campos, meta, tabela, i*tamTpl);
				
				if( error != OKAY){
					return OKAY;
				}
				i++;
			}else return error;
		}
		
	}
	else
		return error;
}
