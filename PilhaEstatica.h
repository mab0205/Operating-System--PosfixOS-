//se define as funcoes
#ifndef PILHAESTATICA
#define PILHAESTATICA
#define MAX 100

typedef struct {
    int v[MAX];
    int topo;
    unsigned capacity;
} Pilha;

Pilha* cria_pilha();

int cheia(Pilha* p);

int vazia(Pilha* p);

void push(Pilha* p, int x);

int pop(Pilha* p);

void free_pilha(Pilha* p);

void libera_P(Pilha* p);

#endif
