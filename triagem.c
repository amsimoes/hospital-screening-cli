#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "func.h"

void admissao_triagem(List triagem,List global){
    char nome[MAX];
    char bi[MAX];

    int nbi;
    do{
        printf("Nome do paciente: ");
        fgets(nome,MAX,stdin);
        linha(nome);
    }while(verificacao_nome(nome)!=1);

    linha(nome);
    verificacao_nome(nome);     /* deteta carateres nao alfabeticos, mas ainda nao aceita espaços */
    do{
        nbi = verificacao_bi(bi);   /* retorna BI e está a funcionar tudo bem */
    }while(dados_bi_triagem(nbi,triagem) == 1 || dados_bi_triagem(nbi,global) == 1);
    inscrever_triagem(triagem,nbi,nome);

    printf("Paciente registrado com sucesso.\n");
}

void inscrever_triagem(List *triagem,int bi,char *nome){

    List aux = (List*)malloc(sizeof(pnode));

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    aux->entrada = (Data*)malloc(sizeof(Data));

    aux->entrada->dia = t->tm_mday;
    aux->entrada->mes = t->tm_mon+1;
    aux->entrada->ano = t->tm_year+1900;
    aux->entrada->hora = t->tm_hour;
    aux->entrada->min = t->tm_min;
    aux->entrada->seg = t->tm_sec;

    aux->bi = bi;
    strcpy(aux->nome,nome);

    insere_doente(triagem,aux);
}

void insere_doente(List lista,List novo){
    List tmp = lista;

    while(tmp->next!=NULL){
        tmp = tmp->next;
    }

    tmp->next = novo;
    novo->next = NULL;

}

int verificacao_nome(char *nome){
    int i=0,contagem=0;

    do{
        if((nome[i]>='A' && nome[i]<='Z') || (nome[i]>='a' && nome[i]<='z') || nome[i] == ' '){
            contagem++;
        }
        i++;
    }while(nome[i] != '\0');

    if(nome[0] == ' ' || nome[0] == '\n'){
        printf("Nome inválido. Insira de novo.\n");
        return 0;
    }
    if(contagem==i){
        return 1;   /* se o nome for valido */
    }
    else{
        printf("Nome invalido. Insira de novo.\n");
        return 0;
    }
}

/* pede e verifica o BI e retorna o BI*/
int verificacao_bi(char *bi)
{
    int nbi = 0,i;

    printf("Insira o BI ( 8 Digitos ) do paciente: ");
    fgets(bi,MAX,stdin);

    linha(bi);

    int soma = 8;
    int soma2 = 0;

    char bi2[MAX];
    strcpy(bi2,bi);

    for(i=0;bi2[i] != '\0';i++){
        if(!isdigit(bi2[i])){
            soma2++;
            break;
        }
    }

    if((soma2 > 0) || (strlen(bi2) != 8)){
        while(strlen(bi2) != 8 || soma != 8 || soma2 > 0){
            soma = 0;
            printf("BI Invalido. Insira de novo: ");
            fgets(bi2,sizeof(bi2),stdin);
            linha(bi2);
            soma2 = 0;
            for(i=0; bi2[i] != '\0'; i++){
                if(!isdigit(bi2[i])){
                    break;
                }
                else
                    soma += 1;
            }
        }
    }
    /*printf("BI Validado\n");*/
    for(i=0; i<8; i++)
    {
        nbi=nbi*10+bi2[i]-'0';
    }
    return nbi;
}

int dados_bi_triagem(int bi,List lista){
    List aux = lista->next;

    while(aux){
        if(aux->bi == bi){
            printf("BI ja registado! Insira de novo.\n");
            return 1;
            break;
        }
        aux = aux->next;
    }
    /*printf("BI nunca registado!\n");*/
    return 0;
}

void eliminar_triagem(List lista,int bi){

    List ant, atual;
    ant = lista;
    atual = lista->next;


    for(;;){
        if(atual->bi == bi){
            printf("Paciente excluido:\nNome: %s\nBI: %d\n\n",atual->nome,atual->bi);
            ant->next = atual->next;
            free(atual);
            break;
        }
        else if(atual->next == NULL){
            printf("O paciente com o BI %d nao se encontra na lista de espera para triagem.\n",bi);
            break;
        }
        ant = atual;
        atual = atual->next;
    }
}
