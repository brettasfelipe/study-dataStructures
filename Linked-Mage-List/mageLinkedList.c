/*
Programa para treino de Listas Encadeadas.

Esse programa é feito para criar uma lista encadeada de Magos, no qual cada mago possui uma magia característica dele, trabalhando o uso de structs dentro de structs.

Felipe Brettas, 13/10/25
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedList.h"

int main(){
    Lista* lista = criaLista(); // Cria lista vazia
    Mago* mago = NULL;
    int verifMagia;
    int pos, option;

    while (1) { // Menu principal
        printf("\nEscolha uma opção:\n1- Adicionar um mago no início da lista\n2- Adicionar um mago ao final da lista\n3- Remover um mago da lista\n4- Visualizar a lista de magos\n5- Sair do programa\n");
        scanf("%d", &option);
        getchar();

        if (option == 5) {
            break; // Sai do programa
        }

        switch(option) {
            case 1: // Adiciona mago no início
                mago = criaMago();

                if (!mago) {
                    fprintf(stderr, "Não foi possível adicionar o mago\n");
                    liberaLista(lista);
                    exit(EXIT_FAILURE);
                }

                verifMagia = criaMagia(mago);

                if (!verifMagia) {
                    fprintf(stderr, "Não foi possível criar a magia do mago %s\n", mago->nome);
                    liberaLista(lista);
                    exit(EXIT_FAILURE);
                }
                
                add(lista, mago);
                break;
            case 2: // Adiciona mago no final
                mago = criaMago();

                if (!mago) {
                    fprintf(stderr, "Não foi possível adicionar o mago\n");
                    liberaLista(lista);
                    exit(EXIT_FAILURE);
                }

                verifMagia = criaMagia(mago);

                if (!verifMagia) {
                    fprintf(stderr, "Não foi possível criar a magia do mago %s\n", mago->nome);
                    liberaLista(lista);
                    exit(EXIT_FAILURE);
                }

                append(lista, mago);
                break;
            case 3: // Remove mago por posição
                if (!lista->primeiro) {
                    printf("\nNão é possível remover pois a lista está vazia.\n");
                    break;
                }

                printf("\nQual a posição do mago que você quer remover?\n");
                scanf("%d", &pos);
                getchar();
                
                if (pos >= lista->tamanho || pos < 0) {
                    printf("\nA posição %d é inválida\n", pos);
                    break;
                }

                mago = pop(lista, pos); // Remove e retorna o mago removido
                
                if (!mago) {
                    fprintf(stderr, "Não foi possível remover o mago\n");
                    liberaLista(lista);
                    exit(EXIT_FAILURE);
                }
                
                printf("\nO mago %s foi removido da lista.\n", mago->nome);
                liberaMago(mago); // Libera memória do mago removido

                break;
            case 4: // Imprime lista completa
                imprimeLista(lista);
                break;
            default:
                printf("\nOpção inválida, tente novamente\n");
                break;
        }

    }    

    liberaLista(lista); // Libera toda a memória usada pela lista
} // end main() 
