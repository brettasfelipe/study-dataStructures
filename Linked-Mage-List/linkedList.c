#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedList.h"

// Exibe todos os magos da lista
void imprimeLista(Lista* lista) {
    No* atual = lista->primeiro;
    int index = 0;

    if (!lista->primeiro) {
        printf("A lista está vazia\n");
        return;
    }

    printf("\n[#########################]\n");
    printf("\nLista dos Magos:\n");
    while (atual) {
        // Exibe informações do mago e sua magia
        printf("[%d] %s, %d anos\n\t- Magia principal: %s, Nível=%d, Custo de Mana=%.2f\n",
               index, atual->mago->nome, atual->mago->idade,
               atual->mago->magiaForte->nome, atual->mago->magiaForte->level,
               atual->mago->magiaForte->custoMana); 
        atual = atual->proximo;
        index++;
    }
    printf("\nO tamanho da lista é: %d\n", lista->tamanho);
    printf("\n[#########################]\n");
}

// Insere mago no início da lista
void add(Lista* lista, Mago* mago) {
    No* no = criaNo(mago);
    no->proximo = lista->primeiro;
    lista->primeiro = no;
    lista->tamanho++;
}

// Insere mago no final da lista
void append(Lista* lista, Mago* mago) {
    No* no = criaNo(mago);
    No* atual = lista->primeiro;

    if (!lista->primeiro) {
        lista->primeiro = no; // Lista vazia
    }
    else {
        while (atual->proximo) { // Avança até o último nó
            atual = atual->proximo;
        }
        atual->proximo = no;
    }
    lista->tamanho++;
}

// Remove mago pela posição e retorna ele
Mago* pop(Lista* lista, int pos) {
    No* atual = lista->primeiro;
    No* removido;
    Mago* magoRemovido;

    // Verifica se posição é válida
    if (!lista->primeiro || pos>=lista->tamanho || pos < 0) return NULL;

    if (pos == 0) { // Remove o primeiro
        removido = lista->primeiro;
        lista->primeiro = removido->proximo;
        magoRemovido = removido->mago;
    }
    else { // Remove do meio ou fim
        for (int i = 0; i<pos-1; i++) {
            atual = atual->proximo;
        }

        removido = atual->proximo;
        atual->proximo = removido->proximo;
        magoRemovido = removido->mago;
    }

    free(removido); // Libera o nó, mas não o mago
    lista->tamanho--;

    if(lista->tamanho == 0) lista->primeiro = NULL;

    return magoRemovido;
}

// Cria lista vazia
Lista* criaLista(void) {
    Lista* lista = (Lista *) malloc(sizeof(Lista));

    if (!lista) {
        fprintf(stderr, "Não foi possível alocar memória para a Lista");
        exit(EXIT_FAILURE);
    }

    lista->primeiro = NULL;
    lista->tamanho = 0;

    return lista;
}

// Cria um nó que armazena um mago
No* criaNo(Mago* mago){
    No* no = (No *) malloc(sizeof(No));

    if (!no) {
        fprintf(stderr, "Não foi possível alocar memória para o Nó\n");
        return NULL;
    }

    no->mago = mago;
    no->proximo = NULL;

    return no;
}

// Cria um novo mago e solicita seus dados ao usuário
Mago* criaMago(void) {
    Mago* mago = (Mago *) malloc(sizeof(Mago));
    char buffNome[100];
    int idade;

    if (!mago) {
        fprintf(stderr, "Não foi possível alocar memória para o Mago\n");
        return NULL;
    }

    // Leitura dos dados do mago
    printf("\nQual o nome do Mago? ");
    scanf(" %99[^\n]", buffNome);
    getchar();

    printf("Qual a idade do Mago? ");
    scanf("%d", &idade);
    getchar();

    // Aloca memória pro nome do mago
    mago->nome = (char *) malloc((strlen(buffNome) + 1) * sizeof(char));

    if (!mago->nome) {
        fprintf(stderr, "Não foi possível alocar memória para o nome do Mago\n");
        free(mago);
        return NULL;
    }

    strcpy(mago->nome, buffNome);
    mago->idade = idade;
    mago->magiaForte = NULL;

    return mago;
}

// Cria uma magia e associa ao mago
int criaMagia(Mago* mago) {
    Magia* magia = (Magia *) malloc(sizeof(Magia));

    if (!magia) {
        fprintf(stderr, "Não foi possível alocar memória para a Magia\n");
        return 0;
    }
    
    char buffMagia[100];
    int level;
    float custoMana;

    // Coleta dados da magia
    printf("\nDigite o nome da magia do %s: ", mago->nome);
    scanf(" %99[^\n]", buffMagia);
    getchar();

    printf("Digite o nível da magia: ");
    scanf("%d", &level);
    getchar();

    printf("Digite o custo de mana da magia: ");
    scanf("%f", &custoMana);
    getchar();

    // Aloca nome da magia
    magia->nome = (char *) malloc((strlen(buffMagia) + 1) * sizeof(char));

    if (!magia->nome) {
        fprintf(stderr, "Não foi possível alocar memória para o nome da magia.\n");
        free(magia);
        return 0;
    }

    strcpy(magia->nome, buffMagia);
    magia->level = level;
    magia->custoMana = custoMana;
    
    mago->magiaForte = magia;

    return 1;
}

// Libera toda a lista e seus nós
void liberaLista(Lista* lista) {
    No* atual = lista->primeiro;

    while (atual) {
        lista->primeiro = lista->primeiro->proximo;
        liberaNo(atual);
        atual = lista->primeiro;
    }

    free(lista);
}

// Libera memória de um nó e do mago dentro dele
void liberaNo(No* no) {
    liberaMago(no->mago);
    free(no);
}

// Libera memória de um mago e sua magia
void liberaMago(Mago* mago) {
    free(mago->nome);
    liberaMagia(mago->magiaForte);
    free(mago);
}

// Libera memória da magia
void liberaMagia(Magia* magia) {
    free(magia->nome);
    free(magia);
}
