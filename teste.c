#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
FILE *arq = NULL;
	int id =  1;
	arq = fopen("files/fs_tabela.dat", "a+");
	
	char lnome[30] = "cliente\0";
	char fnome[30] = "000001.dat\0";
	char dir[30] = "files/data/\0";
	fwrite(&id,sizeof(int), 1, arq);
	fwrite(lnome,sizeof(char),30, arq);
	fwrite(fnome,sizeof(char),30, arq);
	fwrite(dir,sizeof(char),30, arq);
	
	
	
	fseek(arq,0,SEEK_SET);
	
	int id1;
	char lnome1[30];
	char fnome1[30];
	char dir1[30];
	

		/*fread(&id1, sizeof(int),1, arq);
		fread(lnome1, sizeof(char),30,arq);
		fread(fnome1,sizeof(char),30, arq);
		fread(dir1,sizeof(char),30,arq);
	
	
	printf("id :%d\n", id1);
	puts(lnome1);
	puts(fnome1);
	puts(dir1);
	
	fclose(arq);*/
	return 0;
}
