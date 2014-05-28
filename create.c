#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define T 30


void leTupla(char *linha, int b){ //Lê uma tupla da memória

    char *auxStr; //Variável auxiliar para leitura de stringd

    if(linha == NULL)
        return;

    int qtdCampos, j, k=0 ; // k é a posição do byte dentro da tupla
    qtdCampos = 3;

    for(j=0 ; j<qtdCampos; j++){
        if(j!=0)
            printf(" | ");
        if(b == 0){
            auxStr = linha + k;    //acesso a posição de inínio de uma string
            printf("%-20s", auxStr);
            k += 20;     //Atualição de leitura do número de bytes para char
            b++;
        }else if(b == 525){
            double *n = (double *)&linha[k];
            printf("%-20.2f", *n);
            k += sizeof(double);   //Atualição de leitura do número de bytes para double
		}
        else if(b == 1){
			auxStr = linha + k;    //acesso a posição de inínio de uma string
            printf("%-20s", auxStr);
            k += 30;     //Atualição de leitura do número de bytes para cha
            b++;
        }
        else if(b == 2){
            int *n = (int *)&linha[k];
            printf("%-20d", *n);
            k += sizeof(int);   //Atualição de leitura do número de bytes para int
        }
    }
    printf("\n");

}

//CRIAÇÃO DE fs_tabela.dat
int main(){

	FILE *arq = NULL;
	int id =  1;
	
	arq = fopen("files/fs_tabela.dat", "w+");
	
	char lnome[T] = "cliente\0";
	char fnome[T] = "000001.dat\0";
	char dir[T] = "files/data/\0";
	
	char lnome3[T] = "personagem\0";
	char fnome3[T] = "000002.dat\0";
	char dir3[T] = "files/data/\0";

	char lnome6[T] = "carro\0";
	char fnome6[T] = "000003.dat\0";
	char dir6[T] = "files/data/\0";
	
	int menor = 0;
	while(menor < 3){
		if(menor == 1){
			id++;
			fwrite(&id,sizeof(int), 1, arq);
			fwrite(lnome3,sizeof(char),T, arq);
			fwrite(fnome3,sizeof(char),T, arq);
			fwrite(dir3,sizeof(char),T, arq);
		}
		else if(menor == 2){
			id++;
			fwrite(&id,sizeof(int), 1, arq);
			fwrite(lnome6,sizeof(char),T, arq);
			fwrite(fnome6,sizeof(char),T, arq);
			fwrite(dir6,sizeof(char),T, arq);
		}		
		fwrite(&id,sizeof(int), 1, arq);
		fwrite(lnome,sizeof(char),T, arq);
		fwrite(fnome,sizeof(char),T, arq);
		fwrite(dir,sizeof(char),T, arq);
		menor++;
	}
	
	
	
	fseek(arq,0,SEEK_SET);
	
	int id1;
	char lnome1[T];
	char fnome1[T];
	char dir1[T];
	
	
	menor = 0;

	while(menor < 3){
		fread(&id1, sizeof(int),1, arq);
		fread(lnome1, sizeof(char),30,arq);
		fread(fnome1,sizeof(char),30, arq);
		fread(dir1,sizeof(char),30,arq);
		menor++;
	
		printf("id :%d\n", id1);
		puts(lnome1);
		puts(fnome1);
		puts(dir1);
	
	
	}
	
	
	
	fclose(arq);
	
	
	//A partir daqui criação do fs_coluna
	/*struct v{
		int id;
		char atnome[40];
		char tipo;
		int tam;
	};
	
	struct v vet[3];
	struct v vet1[5];
	int i =0;
	
	arq = fopen("files/fs_coluna.dat", "a+");
	//fseek(arq,0,SEEK_SET);
	int reg = 0;
	
	//vet[0].atnome[40] = t;
	while(i < 3){
		if( i == 0){
			strcpy(vet[i].atnome,"nome\0");
			vet[i].tipo = 'S';
			vet[i].tam = 20;
		}
		else if( i == 1){
			strcpy(vet[i].atnome,"ender\0");
			vet[i].tipo = 'S';
			vet[i].tam = 30;
		}
		else{
			strcpy(vet[i].atnome,"idade\0");
			vet[i].tipo = 'I';
			vet[i].tam = 4;
		}
		fwrite(&id,sizeof(int),1,arq);
		fwrite(vet[i].atnome,sizeof(char),T+10,arq);
		fwrite(&vet[i].tipo,sizeof(char),1,arq);
		fwrite(&vet[i].tam,sizeof(int),1,arq);
		i++;
	}
	i = 0;
	id++;
	while( i < 5){
		if(i == 0){
			
			strcpy(vet1[i].atnome,"nome\0");
			vet1[i].tipo = 'S';
			vet1[i].tam = 30;
		}
		else if(i == 1){
			strcpy(vet1[i].atnome,"origem\0");
			vet1[i].tipo = 'S';
			vet1[i].tam = 15;
		}
		else if( i == 2){
			strcpy(vet1[i].atnome,"level\0");
			vet1[i].tipo = 'I';
			vet1[i].tam = 4;
		}
		else if( i == 3){
			strcpy(vet1[i].atnome,"Hp level\0");
			vet1[i].tipo = 'I';
			vet1[i].tam = 4;
		}
		else{
			strcpy(vet1[i].atnome,"Classe\0");
			vet1[i].tipo = 'S';
			vet1[i].tam = 20;
		}
		fwrite(&id,sizeof(int), 1, arq);
		fwrite(vet1[i].atnome,sizeof(char),40, arq);
		fwrite(&vet1[i].tipo,sizeof(char),1, arq);
		fwrite(&vet1[i].tam,sizeof(int),1, arq);
		
		i++;
	}
	i = 0;
	fseek(arq,0,SEEK_SET);
	
	
	struct v v2[3];
	struct v v3[5];
	
	while( i < 3){
		fread(&v2[i].id,sizeof(int),1,arq);
		fread(v2[i].atnome,sizeof(char),T+10,arq);
		fread(&v2[i].tipo,sizeof(char),1,arq);
		fread(&v2[i].tam, sizeof(int),1,arq);
		
		printf("\n id :%d\n", v2[i].id);
		puts(v2[i].atnome);
		printf("\n tipo : %c\n", v2[i].tipo);
		printf("\n TAM : %d\n", v2[i].tam);
		i++;
	}
	i = 0;
	while( i < 5){
		fread(&v3[i].id,sizeof(int),1,arq);
		fread(v3[i].atnome,sizeof(char),T+10,arq);
		fread(&v3[i].tipo,sizeof(char),1,arq);
		fread(&v3[i].tam, sizeof(int),1,arq);
		
		printf("\n id :%d\n", v3[i].id);
		puts(v3[i].atnome);
		printf("\n tipo : %c\n", v3[i].tipo);
		printf("\n TAM : %d\n", v3[i].tam);
		i++;
	}
	i = 0;
	fclose(arq);*/	
	
	//criação de uma base de dados
		
	arq = fopen("files/data/000001.dat", "a+");
	
	struct dados {
		char nome[20];
		char ender[30];
		int idade;
	};
	struct dados1 {
		char nome[30];
		char origem[15];
		int level;
		int hplevel;
		char classe[20];
	};
	struct dados d[3];
	struct dados d1[3];
	
	
	struct dados1 d2[5];
	struct dados1 d3[5];
	int n = 0;
	
	while(n < 3){
		if ( n ==0){
			strcpy(d[n].nome, "Iron\0"); 
			strcpy(d[n].ender, "R. Oito\0");
			d[n].idade = 450;
	    }
	    else if(n == 1){
			strcpy(d[n].nome, "Steel\0");
			strcpy(d[n].ender, "R. Nove\0");
			d[n].idade = 670;
		}
		else{
			strcpy(d[n].nome, "Silver\0");
			strcpy(d[n].ender, "R. Dez\0");
			d[n].idade = 552;
		}
		int j;
		
		
			
	 fwrite(d[n].nome,sizeof(char),20,arq);
	 fwrite(d[n].ender,sizeof(char),30,arq);
	 fwrite(&d[n].idade,sizeof(int),1, arq);	
	 n++;
	}
	n = 0;
	fclose(arq);
	
	arq = fopen("files/data/000002.dat","a+");
	while(n < 5){
		if ( n ==0){
			strcpy(d2[n].nome, "The Killer\0"); 
			strcpy(d2[n].origem, "Wilderness\0");
			d2[n].level = 30;
			d2[n].hplevel = 500;
			strcpy(d2[n].classe, "Guerreiro\0");
	    }
	    else if(n == 1){
			strcpy(d2[n].nome, "Monster B.\0"); 
			strcpy(d2[n].origem, "South\0");
			d2[n].level = 100;
			d2[n].hplevel = 1595;
			strcpy(d2[n].classe, "Paladino\0");
		}
		else if(n == 2){
			strcpy(d2[n].nome, "Hellhound\0"); 
			strcpy(d2[n].origem, "Underworld\0");
			d2[n].level = 150;
			d2[n].hplevel = 2010;
			strcpy(d2[n].classe, "Beast\0");
		}
		else if(n == 3){
			strcpy(d2[n].nome, "Abyssal Demon\0"); 
			strcpy(d2[n].origem, "Underworld\0");
			d2[n].level = 150;
			d2[n].hplevel = 2009;
			strcpy(d2[n].classe, "Demon\0");
		}
		else{
			strcpy(d2[n].nome, "Mister Mage\0"); 
			strcpy(d2[n].origem, "Land of Snow\0");
			d2[n].level = 51;
			d2[n].hplevel = 753;
			strcpy(d2[n].classe, "Human\0");
		}
		int j;
		
		fwrite(d2[n].nome,sizeof(char),30,arq);
		fwrite(d2[n].origem,sizeof(char),15,arq);
		fwrite(&d2[n].level,sizeof(int),1, arq);
		fwrite(&d2[n].hplevel,sizeof(int),1, arq);
		fwrite(d2[n].classe,sizeof(char),20, arq);
		n++;
	}
	fclose(arq);
	fseek(arq,0,SEEK_SET);
	
	arq = fopen("files/data/000001.dat","a+");
	n = 0;
	while( n < 3){
	fread(d1[n].nome,sizeof(char),20,arq);
	fread(d1[n].ender,sizeof(char),30,arq);
	fread(&d1[n].idade,sizeof(int),1,arq);
	
	puts(d1[n].nome);
	puts(d1[n].ender);
	printf("Idade : %d\n\n", d1[n].idade);
	
	n++;
	}
	fclose(arq);
	arq = fopen("files/data/000002.dat","a+");
	n = 0;
	while( n < 5){
		fread(d3[n].nome,sizeof(char),30,arq);
		fread(d3[n].origem,sizeof(char),15,arq);
		fread(&d3[n].level,sizeof(int),1, arq);
		fread(&d3[n].hplevel,sizeof(int),1, arq);
		fread(d3[n].classe,sizeof(char),20, arq);
	
		puts(d3[n].nome);
		puts(d3[n].origem);
		printf("Level : %d\n", d3[n].level);
		printf("Level HP : %d\n", d3[n].hplevel);
		puts(d3[n].classe);
	
		n++;
	}
	fclose(arq);
	
	
	return 0;
}
