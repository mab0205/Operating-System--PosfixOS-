#include <stdio.h>
#include <stdlib.h>
#include"FilaDinamica.h"

fila* cria_fila() {
    fila* f = (fila*)malloc(sizeof(fila));
    f->inicio = f->fim = NULL;
    return f;
}

int vazia_fila(fila* f) {
    if (f->inicio == NULL)
        return 1;
    return 0;
}

void push_fila(fila* f, int x) {
    nodo_fila* novo = (nodo_fila*)malloc(sizeof(nodo_fila)); //aritmetica modular reinicie el posicionamiento de cada numero en el mismo tamaño del vector 
    novo->info = x;
    novo->prox = NULL;
    if (f->fim != NULL)f->fim->prox = novo;

    f->fim = novo;
    if (f->inicio==NULL) f->inicio = novo;
}

int pop_fila(fila* f) {
    int x = f->inicio->info;
    nodo_fila *aux = f->inicio->prox;
    if (f->fim == f->inicio) f->fim = NULL;

    free(f->inicio);

    f->inicio = aux;
    return x;
}
void libera_f(fila* f) {
    while (vazia_fila(f) != 1) {
        pop_fila(f);
    }
}

