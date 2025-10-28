#ifndef __LINKED_LIST__
#define __LINKED_LIST__

// Estrutura que representa uma magia
typedef struct {
    char* nome;
    int level;
    float custoMana;
} Magia;

// Estrutura que representa um mago, que contém uma magia principal
typedef struct {
    char *nome;
    int idade;
    Magia* magiaForte; 
} Mago;

// Nó da lista encadeada, guarda um mago e aponta para o próximo nó
typedef struct No {
    Mago* mago; 
    struct No* proximo;
} No;

// Estrutura da lista, com ponteiro para o primeiro nó e tamanho total
typedef struct {
    No* primeiro;
    int tamanho;
} Lista;

// Declaração das funções utilizadasI
Lista* criaLista(void);
No* criaNo(Mago* mago);
Mago* criaMago(void);
int criaMagia(Mago* mago);

void liberaLista(Lista* lista);
void liberaNo(No* no);
void liberaMago(Mago* mago);
void liberaMagia(Magia* magia);

// Mago* search(Lista* lista, char* nome); Função de busca que será implementada no futuro

void add(Lista* lista, Mago* mago);
void append(Lista* lista, Mago* mago);
Mago* pop(Lista* lista, int pos);

void imprimeLista(Lista* lista);

#endif // __LINKED_LIST__
