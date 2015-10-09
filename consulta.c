#include "func.h"
#include <stdio.h>

int eliminar_consulta(List lista,int bi){
    List ant,atual;

    ant = lista;
    atual = lista->next;

    for(;;){
        if(atual->bi == bi){
            /*printf("Paciente excluido:\nNome: %s\nBI: %d\n\n",atual->nome,atual->bi);*/
            ant->next = atual->next;
            free(atual);
            return 1;
            break;
        }
        else if(atual->next == NULL){
            /*printf("O paciente com o BI %d nao se encontra na lista.\n",bi);*/
            return 0;
            break;
        }
        ant = atual;
        atual = atual->next;
    }
    return 0;
}


void inserir_fim(List prioridade,List node_espera){
    List head = prioridade;

    List no = (List)malloc(sizeof(pnode));
    *no = *node_espera;

    while(head->next != NULL){
        head = head->next;
    }

    head->next = no;
    no->next = NULL;
}

void inserir_inicio(List prioridade,List node_espera){
    List head = prioridade;

    List no = (List)malloc(sizeof(pnode));
    *no = *node_espera;
    no->next = NULL;

    if(head->next != NULL){    /* ou seja a lista estar vazia */
        no->next = head->next;
        head->next = no;
    }
    else{
        head->next = no;
    }
}

int dados_bi_consulta(List lista,int bi){
    List aux = lista->next;

    while(aux){
        if(aux->bi == bi){
            return 1;
        }
        aux = aux->next;
    }
    return 0;
}
