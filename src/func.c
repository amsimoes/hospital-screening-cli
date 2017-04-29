#include "func.h"
#include <stdio.h>

List cria_lista(void){

    List aux;
    aux = (List) malloc (sizeof (pnode));

    if (aux != NULL){
        aux->next = NULL;
    }
    else
        printf("Erro na alocacao de memoria.");
    return aux;
}

void linha(char* nome){
    if(nome[strlen(nome)-1] == '\n'){
        nome[strlen(nome)-1] = '\0';
    }
}

void imprimir_lista(List triagem){
	List l = triagem->next; /* para saltar o header e nao apresentar o primeiro elemento criado pelo cria_lista() */
	while(l){
		printf("\nPaciente: %s\nBI: %d\nData: %d/%d/%d\tHora: %d:%d:%d",l->nome,l->bi,l->entrada->dia,l->entrada->mes,l->entrada->ano,l->entrada->hora,l->entrada->min,l->entrada->seg);
		printf("\n\n");
		l=l->next;
	}
}

void imprimir_no(List head){
    List l = head;
    if(l != NULL){
        printf("\nNome: %s\nBI: %d\nData: %d/%d/%d\tHora: %d:%d:%d",l->nome,l->bi,l->entrada->dia,l->entrada->mes,l->entrada->ano,l->entrada->hora,l->entrada->min,l->entrada->seg);
		printf("\n\n");
    }
}

/* retorna 1 se a lista estiver vazia */
int lista_vazia(List lista){
	return (lista->next == NULL ? 1 : 0);
}
