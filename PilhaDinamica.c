#include <stdio.h>
#include <stdlib.h>
#include "PilhaDinamica.h"

Pilha* cria_pilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->topo = NULL;
    return p;
}

int vazia(Pilha* p) {
    return p->topo == NULL ? 1 : 0;
}

void push(Pilha* p, int x) {
    nodo* novo = (nodo*)malloc(sizeof(nodo));
    novo->info = x;
    novo->prox = p->topo;
    p->topo = novo;
}

int pop(Pilha* p) {
    int aux = p->topo->info;
    nodo* prox = p->topo->prox;
    free(p->topo);
    p->topo = prox;
    return aux;
}
void libera_P(Pilha* p) {
    while (vazia(p) != 1) {
        pop(p);
    }
}


