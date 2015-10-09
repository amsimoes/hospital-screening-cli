#include "func.h"
#include <stdio.h>

int AtenderPaciente(List lglobal,List lverde,List lamarela,List lvermelha){
    static int cont_vermelha;
    static int cont_amarela;
    static int cont_verde;

    /*printf("Verde:%d\nAmarelo:%d\nVermelho:%d\n",cont_verde,cont_amarela,cont_vermelha);*/

    ficheiro_para_contador("contador.txt",&cont_verde,&cont_amarela,&cont_vermelha);

    int bif;

    for(;;){
        if(lista_vazia(lvermelha) != 1){
            if(cont_vermelha % 3 == 0 && cont_vermelha != 0){
                if(lista_vazia(lamarela) != 1){
                    printf("[Lista Amarela]\n");
                    bif = atender(lglobal,lamarela);
                    cont_amarela += 1;
                    cont_vermelha = 0;
                    break;
                    }
                else{  /* se a lista amarela estiver vazia */
                    if(cont_vermelha % 5 == 0 && cont_vermelha != 0){
                        if(lista_vazia(lverde) != 1){
                            printf("[Lista Verde]\n");
                            bif = atender(lglobal,lverde);
                            cont_verde += 1;
                            cont_vermelha = 0;
                            break;
                        }
                        else{
                            printf("[Lista Vermelha]\n");
                            bif = atender(lglobal,lvermelha);
                            cont_vermelha += 1;
                            break;
                        }
                    }
                    else{
                        printf("[Lista Vermelha]\n");
                        bif = atender(lglobal,lvermelha);
                        cont_vermelha += 1;
                        break;
                    }
                }
            }
            else{
                printf("[Lista Vermelha]\n");
                bif = atender(lglobal,lvermelha);
                cont_vermelha += 1;
                break;
            }
        }
        else{
            if(lista_vazia(lamarela) == 1){ /* lista amarela vazia, ou seja, verde preenchida */
                printf("[Lista Verde]\n");
                bif = atender(lglobal,lverde);
                cont_verde += 1;
                break;
            }
            else if(lista_vazia(lverde) == 1){   /* lista verde vazia, ou seja, amarela preenchida */
                printf("[Lista Amarela]\n");
                bif = atender(lglobal,lamarela);
                cont_amarela += 1;
                break;
            }
            else if(lista_vazia(lamarela) != 1 && lista_vazia(lverde) != 1){    /* lista verde e amarela não vazias */
                if(cont_amarela % 5 == 0 && cont_amarela != 0){
                    printf("[Lista Verde]\n");
                    bif = atender(lglobal,lverde);
                    cont_verde += 1;
                    cont_amarela = 0;
                    break;
                }
                else{
                    printf("[Lista Amarela]\n");
                    bif = atender(lglobal,lamarela);
                    cont_amarela += 1;
                    break;
                }
            }
        }
    }
    contador_para_ficheiro("contador.txt",&cont_verde,&cont_amarela,&cont_vermelha);
    return(bif);
}

int atender(List lglobal,List prioridade){
    int bi;

    bi = eliminar_no(prioridade);
    eliminar_consulta(lglobal,bi);
    return(bi);
}

int eliminar_no(List prioridade){
    List head = prioridade;
    List ptr = head->next;

    int bi;

    if(ptr->next != NULL){
        printf("Paciente atendido:\nNome:%s\nBI:%d\n",ptr->nome,ptr->bi);
        bi = ptr->bi;
        ptr = ptr->next;
        head->next = ptr;
        return(bi);
    }
    else{
        printf("Paciente atendido:\nNome:%s\nBI:%d\n",ptr->nome,ptr->bi);
        bi = ptr->bi;
        ptr = NULL;
        head->next = ptr;
        return(bi);
    }
    return 1;
}
