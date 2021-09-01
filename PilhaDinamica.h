#ifndef PILHADINAMICA
#define PILHADINAMICA

typedef struct nodo {
    int info;
    struct nodo* prox;
} nodo;

typedef struct Pilha {
    struct nodo* topo;
}Pilha;

Pilha* cria_pilha();

int vazia(Pilha* p);

void push(Pilha* p, int x);

int pop(Pilha* p);
void libera_P(Pilha* p);


#endif

