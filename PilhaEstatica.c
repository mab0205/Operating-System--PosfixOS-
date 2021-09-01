#include <stdio.h>
#include <stdlib.h>
#include "PilhaEstatica.h"

Pilha* cria_pilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->topo = -1;
    return p;
}

int vazia(Pilha* p) {
    return (p->topo == -1) ? 1 : 0;
}

void push(Pilha* p, int x) {
    p->topo++;
    p->v[p->topo] = x;
}

int pop(Pilha* p) {
    int t = p->v[p->topo];
    p->topo--;
    return t;
}

void free_pilha(Pilha* p) {
    free(p);
}

void libera_P(Pilha* p){
    while (vazia(p) != 1) {
        pop(p);
    }

}

