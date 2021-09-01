#include <stdio.h>
#include <stdlib.h>
#define MAX 100

/* Sistema Operativo PosfixOS ( multithread )*/

#include"PilhaEstatica.h"//Pilha Estatica
//#include"PilhaDinamica.h"//Pilha Dinamica
//#include"FilaEstatica.h"//fila Estatica
#include"FilaDinamica.h"//fila Dinamica

void Ensere_Vetor(int numprogramas, int programas[MAX][MAX], int elementos[MAX]) {
    int i = 0, j = 0; //variaveis auxiliares
    int aux1; //recebe o int de atoi 
    char aux[MAX]; //recebe os numeros ou carateres do usuario
    for (i = 0; i < numprogramas; i++) {
        scanf("%d", &elementos[i]);//recebe os numeros ou carateres do usuario
        for (j = 0; j < elementos[i]; j++) {
            scanf("%s", aux);
            switch (aux[0]) {
            case '+':
                programas[i][j] = -1;// recebe um entero(-1 --> +) e armazena na matriz 
                break;

            case '-':
                programas[i][j] = -2;// recebe um entero(-2 --> -) e armazena na matriz 
                break;

            case '*':
                programas[i][j] = -3;// recebe um entero(-3 --> *) e armazena na matriz
                break;

            case '/':
                programas[i][j] = -4;// recebe um entero(-4 --> /) e armazena na matriz
                break;

            default:
                aux1 = atoi(aux); // aux1 recebe o valor int de atoi (aux->char)
                programas[i][j] = aux1; // recebe um entero e armazena na matriz 
                break;
            };
        }
    }
}

void vetor_fila(fila* f[MAX], int programas[MAX][MAX], int elementos[MAX], int numprogramas) {
    int i = 0, j = 0;//variaveis auxiliares
    for (i = 0; i < numprogramas; i++) {
        for (j = 0; j < elementos[i]; j++) {
            push_fila(f[i], programas[i][j]); //ensere conteudo vetor->fila 
        }
    }
}

int num_mayor(int elementos[MAX], int num) {
    int mayor, i = 0;//variaveis auxiliares
    for (i = 0; i < num; i++) {
        if (elementos[i] > mayor) mayor = elementos[i]; //armazena  o maior numero de operacoes entre os programas 
    }
    return mayor;
}

//funcao para tratamento de erros e libera memoria
void TratamentoErros(fila* f[MAX], Pilha* p[MAX], int i, int count[MAX], int elementos[MAX]) {
    libera_f(f[i]); //funcao para liberar fila na posicao i 
    libera_P(p[i]);//funcao para liberar pilha na posicao i 

    count[i] = elementos[i];
    printf("erro, fim\n");
}

int main(int argc, char const* argv[]) {
    int programas[MAX][MAX]; // vetor para armazenar as operacoes
    int elementos[MAX]; // vetor para armazenar o total de numeros de cada operacao
    int numprogramas; // vetor com total de programas a ser executado
    int i = 0, j = 0, k = 0;
    int aux = 0;
    unsigned int aux1 = 0, aux2 = 0, aux3 = 0, div = 0; //variaveis para fazer os calculos das operacoes

    int count[MAX], mayor; //count sirve para contar las posiciones de la fila y mayor para la operacion mas extensa
                        //count conta o total de elementos da fila e mayor a operacao mais grande 
    Pilha* p[MAX];
    fila* f[MAX];

    scanf("%d", &numprogramas); //entra numero de programs 

    for (i = 0; i < numprogramas; i++) f[i] = cria_fila(); //crea el numero filas --> programas
    for (i = 0; i < numprogramas; i++) p[i] = cria_pilha(); //crea el numero pilas --> programas
    for (i = 0; i < numprogramas; i++) count[i] = 0; // se crea o total de programas 

    //ensere as operacoes no vetor vetor char(2 5 + 2 / 1 +) --->programas[][](2 5 -1 2 -3 1 -1)
    Ensere_Vetor(numprogramas, programas, elementos);

    //ensere conteudo vetor->fila   programas[][](2 5 -1 2 -3 1 -1)--->fila(-1 1 -3 2 -1 5 2)
    vetor_fila(f, programas, elementos, numprogramas);

    //mayor armazena a operacao maior a dos elementos 
    mayor = num_mayor(elementos, numprogramas);

    /*Calculadora Notacao Polonesa Inversa... fila-->pilha*/
    //se faz um pop de cada posicao da fila (primero as filas e pois as colunas)
    //      1  2  3 4 5 6  7
    //      ↆ  ↆ ↆ ↆ ↆ ↆ ↆ 
    //fila1(-1 1 -3 2 -1 5 2)
    //fila2( 42 50 - 8 +)
    //mayor = 7
    for (j = 0; j < mayor; j++) { //colunas da matriz 
        for (i = 0; i < numprogramas; i++) { //filas da matriz
            if (count[i] < elementos[i]) {
                aux = pop_fila(f[i]); //faz pop da fila e armazena o inteiro na variavel aux
                printf("programa %d: ", i + 1);
                if (aux == -1) {// recebe um entero(-1 --> +) e raliza a operacao 
                    if (vazia(p[i]) == 1) {// tratamento a) uma operacao (+, -, * ou /) e realizada com menos de dois elementos na pilha do respectivo programa.
                        TratamentoErros(f, p, i, count, elementos);
                        break;
                    }
                    aux1 = pop(p[i]);
                    if (vazia(p[i]) == 1) {// tratamento a) uma operacao (+, -, * ou /) e realizada com menos de dois elementos na pilha do respectivo programa.
                        TratamentoErros(f, p, i, count, elementos);
                        break;
                    }
                    aux2 = pop(p[i]);
                    push(p[i], aux1 + aux2);
                    printf("desempilha %d, desempilha %d, empilha %d", aux1, aux2, aux1 + aux2);
                    if (count[i] == elementos[i] - 1) printf(", fim");
                    printf("\n");
                }
                else if (aux == -2) {// recebe um entero(-2 --> -) e raliza a operacao 
                    if (vazia(p[i]) == 1) {// tratamento a) uma operacao (+, -, * ou /) e realizada com menos de dois elementos na pilha do respectivo programa.
                        TratamentoErros(f, p, i, count, elementos);
                        break;
                    }
                    aux1 = pop(p[i]);
                    if (vazia(p[i]) == 1) {// tratamento a) uma operacao (+, -, * ou /) e realizada com menos de dois elementos na pilha do respectivo programa.
                        TratamentoErros(f, p, i, count, elementos);
                        break;
                    }
                    aux2 = pop(p[i]);
                    push(p[i], aux2 - aux1);
                    printf("desempilha %d, desempilha %d, empilha %d", aux1, aux2, aux2 - aux1);
                    if (count[i] == elementos[i] - 1) printf(", fim");
                    printf("\n");
                }
                else if (aux == -3) {// recebe um entero(-3 --> *) e raliza a operacao 
                    if (vazia(p[i]) == 1) {// tratamento a) uma operacao (+, -, * ou /) e realizada com menos de dois elementos na pilha do respectivo programa.
                        TratamentoErros(f, p, i, count, elementos);
                        break;
                    }
                    aux1 = pop(p[i]);
                    if (vazia(p[i]) == 1) {// tratamento a) uma operacao (+, -, * ou /) e realizada com menos de dois elementos na pilha do respectivo programa.
                        TratamentoErros(f, p, i, count, elementos);
                        break;
                    }
                    aux2 = pop(p[i]);
                    push(p[i], aux1 * aux2);
                    printf("desempilha %d, desempilha %d, empilha %d", aux1, aux2, aux2 * aux1);
                    if (count[i] == elementos[i] - 1) printf(", fim");
                    printf("\n");
                }
                else if (aux == -4) {// recebe um entero(-4 --> /) e raliza a operacao 
                    if (vazia(p[i]) == 1) {// tratamento a) uma operacao (+, -, * ou /) e realizada com menos de dois elementos na pilha do respectivo programa.
                        TratamentoErros(f, p, i, count, elementos);
                        break;
                    }
                    aux1 = pop(p[i]);
                    if (vazia(p[i]) == 1) {// tratamento a) uma operacao (+, -, * ou /) e realizada com menos de dois elementos na pilha do respectivo programa.
                        TratamentoErros(f, p, i, count, elementos);
                        break;
                    }
                    aux2 = pop(p[i]);
                    if (aux1 == 0) {// tratamento b) se ocorre uma divisao por zero.
                        TratamentoErros(f, p, i, count, elementos);
                        break;
                    }
                    push(p[i], aux2 / aux1);
                    printf("desempilha %d, desempilha %d, empilha %d", aux1, aux2, aux2 / aux1);
                    if (count[i] == elementos[i] - 1) printf(", fim");
                    printf("\n");
                }
                else { //else para qualquer numero 
                    push(p[i], aux);
                    printf("empilha %d", aux);
                    printf("\n");
                }
                count[i]++;
            }
        }
    }
    //libera memoria da a fila y a pilha
    for (j = 0; j < mayor; j++) {
        for (i = 0; i < numprogramas; i++) {
            libera_f(f[i]);
            libera_P(p[i]);
        }
    }
    return 0;
}

/*      ⓂⒶⓇⓉⒾⓃ口ⒶⓋⒾⓁⒶ
        ⒺⓈⓉⓇⓊⓉⓊⓇⒶ口ⒹⒺ口ⒹⒶⒹⓄⓈ
        ⓇⒶ⫸➁➁➆➃➀➇➂
 */
