#ifndef FUNCOES_H
#define FUNCOES_H

#define SIZENOME 200
#define MAX 200


typedef struct data{
    int dia,mes,ano,seg,min,hora;
}Data;

typedef struct paciente *List;
typedef struct paciente{
    char nome[SIZENOME];
    int bi;
    int pul;    /* 0 -> triagem || 1-> lverde || 2-> lamarela || 3 -> lvermelha */
    Data *entrada;
    List next;
}pnode;

List cria_lista(void);
void inscrever_triagem(List *triagem,int bi,char *nome);
int verificacao_bi(char *bi);
void imprimir_lista(List triagem);
int verificacao_nome(char* nome);
void admissao_triagem(List triagem, List global);
void insere_doente(List lista,List novo);
int lista_vazia(List lista);
void eliminar_triagem(List lista,int bi);
int atender(List lglobal,List prioridade);
int eliminar_no(List prioridade);

typedef struct paciente *lespera;
typedef struct paciente *lvermelha;
typedef struct paciente *lamarela;
typedef struct paciente *lverde;
typedef struct paciente *lglobal;



#endif
