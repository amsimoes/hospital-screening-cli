#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "func.h"

void verifica_ficheiros(){
	if (access("listas.txt",F_OK)==-1){
    	FILE *f1;
    	f1=fopen("listas.txt","w");
    	fclose(f1);
	}
	if(access("contador.txt",F_OK)==-1){
        FILE *f;
        f = fopen("contador.txt","w");
        fclose(f);
	}
}

int procura_ficheiro(char *fname,char *str){    /* ELIMINAR POR BI */
    FILE *f;

    int numero_linha = 1;

    f = fopen(fname,"r");
    char max[150];
    while(fgets(max,sizeof(max),f) != NULL){
        if((strstr(max,str) != NULL)){
            /*printf("Paciente encontrado com o BI: %s\n",str);*/
            return numero_linha;
        }
        numero_linha++;
    }
}

void eliminar_doente_ficheiro(char *fname,int bi){  /* elimina por BI */
    FILE *fptr1,*fptr2;
    char ch;
    char str_bi[8];

    sprintf(str_bi,"%d",bi);

    fptr1 = fopen(fname,"r");
    ch = getc(fptr1);

    int num_linha = 1;
    int linha_apagar = procura_ficheiro(fname,str_bi);

    fptr2 = fopen("replica.c","w");

    /*ch = getc(fptr1);
    while(ch != EOF){
        ch = getc(fptr1);
        if(ch == '\n'){
            num_linha++;
        }
        if(num_linha != linha_apagar){
            putc(ch,fptr2);
        }
    }*/

    for(;;){
        if(ch == EOF){
            break;
        }
        if(num_linha != linha_apagar){
            putc(ch,fptr2);
        }
        if(ch == '\n'){
            num_linha++;
        }
        ch = getc(fptr1);
    }
    fclose(fptr1);
    fclose(fptr2);
    remove(fname);
    rename("replica.c",fname);
}

void lista_para_ficheiro(List lista,char *fname){   /* escreve sempre no fim do ficheiro o ultimo elemento da lista */
    FILE *f;
    f = fopen(fname,"a");

    List aux = lista;
    List primeiro = lista->next;
    /*if(primeiro->pul == 4){ // NAO É NECESSARIA A LISTA GLOBAL SER IMPRIMIDA PARA O FICHEIRO TEXTO POIS A PARTIR DAS PRIORIDADES ADICIONAMOS NA GLOBAL
        fprintf(f,"%d-%d-%d/%d/%d-%d:%d:%d-%s\n",primeiro->pul,primeiro->bi,primeiro->entrada->dia,primeiro->entrada->mes,primeiro->entrada->ano,primeiro->entrada->hora,primeiro->entrada->min,primeiro->entrada->seg,primeiro->nome);
    }*/
    if(primeiro->pul!=4){
        while(aux->next!=NULL){
            aux = aux->next;
        }
        fprintf(f,"%d-%d-%d/%d/%d-%d:%d:%d-%s\n",aux->pul,aux->bi,aux->entrada->dia,aux->entrada->mes,aux->entrada->ano,aux->entrada->hora,aux->entrada->min,aux->entrada->seg,aux->nome);
    }

    fclose(f);
}

void ficheiro_para_lista(List triagem, List lglobal, List lverde, List lamarela, List lvermelha, char *fname){
	FILE *f;
	f=fopen(fname,"r");
	int pos=0;
	int pulseira = 0;
	char nome_prov[SIZENOME];
	while(fgetc(f) != EOF){
		fseek(f,pos,SEEK_SET);
		List aux = (List*) malloc(sizeof(pnode));
		aux->entrada = (Data*)malloc(sizeof(Data));
		fscanf(f,"%d-%d-%d/%d/%d-%d:%d:%d-",&aux->pul,&aux->bi,&aux->entrada->dia,&aux->entrada->mes,&aux->entrada->ano,&aux->entrada->hora,&aux->entrada->min,&aux->entrada->seg);
		/*strcpy(aux->nome,nome_prov);*/
		fgets(aux->nome,SIZENOME,f);
		linha(aux->nome);
		if(aux->pul == 0){
            inserir_fim(triagem,aux);
        }
        else if(aux->pul == 1){
            inserir_inicio(lglobal,aux);
            inserir_fim(lverde,aux);
        }
        else if(aux->pul == 2){
            inserir_inicio(lglobal,aux);
            inserir_fim(lamarela,aux);
        }
        else if(aux->pul == 3){
            inserir_inicio(lglobal,aux);
            inserir_fim(lvermelha,aux);
        }
		pos = ftell(f);
	}
	fclose(f);
}

void contador_para_ficheiro(char *fname,int *c_verde,int *c_vermelho,int *c_amarelo){
    FILE *f;

    f = fopen(fname,"w");
    fprintf(f,"%d-%d-%d",*c_verde,*c_vermelho,*c_amarelo);
    fclose(f);
}

void ficheiro_para_contador(char *fname,int *c_verde,int *c_vermelho,int *c_amarelo){
    FILE *f;

    f = fopen(fname,"r");
    fscanf(f,"%d-%d-%d",c_verde,c_vermelho,c_amarelo);

    fclose(f);
}
