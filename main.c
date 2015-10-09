#include <stdio.h>
#include "func.h"

void clear(){
    system("clear"); /* system("cls") em windows */
}

void volta_menu(){
    printf("Prima Enter para voltar ao menu.");
    getchar();
    system("clear");
}

void menu(List lespera,List lglobal,List lvermelha,List lamarela,List lverde){

    verifica_ficheiros();

    List l = lverde;
    List p;
    List q;

    char bi[MAX];
	int opcao = 0,escolha=0,prioridade;
	int b;

    printf("(1) Admitir um paciente.\n");
    printf("(2) Vizualizar lista de espera para a triagem.\n");
    printf("(3) Cancelar doente na lista de espera para triagem.\n");
    printf("(4) Atribuir um doente a uma prioridade.\n");
    printf("(5) Vizualizar listas de prioridades.\n");
    printf("(6) Vizualizar lista de espera para consulta.\n");
    printf("(7) Cancelar doente na lista de espera para consulta.\n");
    printf("(8) Atender paciente.\n");
    printf("(9) Encerrar programa.\n");

    scanf("%d",&opcao);
    getchar();

    clear();
    switch(opcao){
        case 1:
            admissao_triagem(lespera,lglobal);
            lista_para_ficheiro(lespera,"listas.txt");
            volta_menu();
            break;
        case 2:
            if(lista_vazia(lespera) == 0){
                printf("Lista de espera para triagem:\n");
                imprimir_lista(lespera);
                volta_menu();
            }
            else{
                printf("Nao existem doentes na lista de espera para triagem.\n\n");
                volta_menu();
            }
            break;
        case 3:
            if(lista_vazia(lespera) == 0){
                printf("Lista de espera para triagem:\n");
                imprimir_lista(lespera);
                b = verificacao_bi(bi);
                eliminar_triagem(lespera,b);
                eliminar_doente_ficheiro("listas.txt",b);
                volta_menu();
                break;
            }
            else{
                printf("Nao existem doentes na lista de espera para triagem.\n\n");
                volta_menu();
                break;
            }
        case 4:
            if(lista_vazia(lespera) == 0){
                printf("\tAtribuir prioridade:\n(1) Verde\n(2) Amarela\n(3) Vermelha\nPrioridade: ");
                scanf("%d",&prioridade);
                getchar();
                if(prioridade<1 || prioridade>3){
                    do{
                        printf("Indice de lista invalido. Insira novamente: ");
                        scanf("%d",&prioridade);
                        getchar();
                    }while(prioridade<1 || prioridade>3);
                }
                printf("Paciente movido:\n");
                imprimir_no(lespera->next);
                p = lespera->next;
                inserir_inicio(lglobal,p);  /*  insere no inicio */
                if(prioridade==1){
                        p->pul = 1;
                        inserir_fim(lverde,p);    /* inserir no fim */
                        eliminar_doente_ficheiro("listas.txt",p->bi);
                        lista_para_ficheiro(lverde,"listas.txt");
                        if(lespera->next->next != NULL){
                            lespera->next = lespera->next->next;
                        }
                        else{
                            lespera->next = NULL;
                        }
                        volta_menu();
                        break;
                    }
                else if(prioridade == 2){
                        p->pul = 2;
                        inserir_fim(lamarela,p);
                        eliminar_doente_ficheiro("listas.txt",p->bi);
                        lista_para_ficheiro(lamarela,"listas.txt");
                        if(lespera->next != NULL){
                            lespera->next = lespera->next->next;
                        }
                        else{
                            lespera->next = NULL;
                        }
                        volta_menu();
                        break;
                    }
                else{
                        p->pul = 3;
                        inserir_fim(lvermelha,p);
                        eliminar_doente_ficheiro("listas.txt",p->bi);
                        lista_para_ficheiro(lvermelha,"listas.txt");
                        if(lespera->next != NULL){
                            lespera->next = lespera->next->next;
                        }
                        else{
                            lespera->next = NULL;
                        }
                        volta_menu();
                        break;
                }
            }
            else{
                printf("Nao existem doentes na lista de espera para atribuir prioridades.\n\n");
                volta_menu();
            }
            break;
        case 5:
            printf("Listas de espera para consulta:\n(1) Prioridade Verde\n(2) Prioridade Amarela\n(3) Prioridade Vermelha\nLista que deseja ver: ");

            scanf("%d",&prioridade);
            getchar();
            if(prioridade<1 || prioridade>3){
                do{
                    printf("Indice de lista invalido. Insira novamente: ");
                    scanf("%d",&prioridade);
                    getchar();
                }while(prioridade<1 || prioridade>3);
            }

			if(prioridade == 1){
                if(lista_vazia(lverde) == 0){
                    imprimir_lista(lverde);
                    volta_menu();
                }
                else{
                    printf("Não existem doentes na lista verde.\n");
                    volta_menu();
                }
                break;
			}
			else if(prioridade == 2){
                if(lista_vazia(lamarela) == 0){
                    imprimir_lista(lamarela);
                    volta_menu();
                }
                else{
                    printf("Não existem doentes na lista amarela.\n");
                    volta_menu();
                }
                break;
			}
			else if(prioridade == 3){
                if(lista_vazia(lvermelha) == 0){
                    imprimir_lista(lvermelha);
                    volta_menu();
                }
                else{
                    printf("Não existem doentes na lista vermelha.\n");
                    volta_menu();
                }
                break;
			}
        case 6:
            if(lista_vazia(lglobal) == 0){
                printf("Lista de espera para consulta:\n");
                imprimir_lista(lglobal);
                volta_menu();
            }
            else{
                printf("Nao existem doentes na lista de espera para consulta.\n\n");
                volta_menu();
            }
            break;
        case 7:
            if(lista_vazia(lglobal) == 0){
                printf("Lista de espera para consulta:\n");
                imprimir_lista(lglobal);
                b = verificacao_bi(bi);
                if(dados_bi_consulta(lglobal,b) == 0){
                    printf("O paciente com o BI %d nao se encontra na lista de espera para consulta.\n",b);
                    volta_menu();
                    break;
                }
                else{
                    eliminar_consulta(lglobal,b);
                    eliminar_doente_ficheiro("listas.txt",b);
                }
                if(dados_bi_consulta(lverde,b)==1){
                    eliminar_consulta(lverde,b);
                }
                else if(dados_bi_consulta(lamarela,b)==1){
                    eliminar_consulta(lamarela,b);
                }
                else if(dados_bi_consulta(lvermelha,b)==1){
                    eliminar_consulta(lvermelha,b);
                }
                volta_menu();
            }
            else{
                printf("Nao existem doentes na lista de espera para consulta.\n\n");
                volta_menu();
            }
            break;
        case 8:     /* Paciente a atender */
            if(lista_vazia(lglobal) != 1){
                /*printf("Contador Vermelho:%d\nContador Amarelo:%d\nContador Azul:%d\n",cont->vermelha,cont->amarela,cont->verde);*/
                b = AtenderPaciente(lglobal,lverde,lamarela,lvermelha);
                eliminar_doente_ficheiro("listas.txt",b);
                volta_menu();
            }
            else{
                printf("Nao existem pacientes a espera para serem atendidos.\n");
                volta_menu();
            }
            break;
        case 9:
            exit(0);
    }

    menu(lespera,lglobal,lvermelha,lamarela,lverde);
}

int main(){
    List lespera,lvermelha,lamarela,lverde,lglobal;

    lespera = cria_lista();
    lvermelha = cria_lista();
    lamarela = cria_lista();
    lverde = cria_lista();
    lglobal = cria_lista();

    verifica_ficheiros();
    ficheiro_para_lista(lespera,lglobal,lverde,lamarela,lverde,"listas.txt");
    menu(lespera,lglobal,lvermelha,lamarela,lverde);
    return 0;
}
