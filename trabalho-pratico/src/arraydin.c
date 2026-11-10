#include <stdio.h>
#include <stdlib.h>
#include "../include/arraydin.h"
#include <string.h>

typedef struct array_din {
    int N; //Numero de elementos
    int max; //Capacidade máxima do array
    void** lista; //Lista
} ArrayDin;

// ##################################################################
//                      GETTERS
// ##################################################################

//Obtem o tamanho máximo do array din
int getADMax(const ArrayDin* lista) {
    if (!lista) return 0;
    return lista->max;
}

//Obtem o número de elementos do array din
int getADN(const ArrayDin* lista) {
    if (!lista) return 0;
    return lista->N;
}

//Obter o item de índice i
void* getADItem(const ArrayDin* lista, int i) {
    if (i<0 || i>=lista->N) return NULL;
    else return lista->lista[i];
}
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     SET'S     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

//Inserção no fim do Array Dinamico
void inserir_ArrayDin(void* dado, ArrayDin* lista) {

    if (lista->N>=lista->max) { //Aumento do tamanho do array
    int novo_max=(lista->max)*2; //Aumenta para o dobro
    void** nova_lista=malloc(sizeof(void*)*novo_max);

    int N2=lista->N;
    for (int i=0;i<N2;i++) { //Copiar todos os elementos do array antigo para o novo
        nova_lista[i]=lista->lista[i];
    }
    free(lista->lista); //Dar free ao array antigo
    lista->lista=nova_lista; //Colocar o novo array
    lista->max=novo_max; //definir um novo máximo
    }

    //Inserção do user
    lista->lista[lista->N]=dado;
    lista->N++;
}

//Função que inicia um array dinamico
ArrayDin* inicia_ArrayDin(int N) {
    ArrayDin* novo=malloc(sizeof(ArrayDin));
    novo->max=N;
    novo->N=0;
    novo->lista=malloc(sizeof(void*)*N);
    return novo;
}

//Função que apaga o array dinamico
void apaga_ArrayDin(ArrayDin* lista, void (*apagaF)(void*)) {
    for (int i = 0; i < lista->N; i++) {
        apagaF(lista->lista[i]);
    }
    free(lista->lista);
    free(lista);
}


void apaga_ADString(void* a_) {
    char* a=a_;
    free(a);
}

//Apaga Array dinamicos de strings
void apaga_ADStrings(ArrayDin* lista) {
    apaga_ArrayDin(lista,&apaga_ADString);
}

