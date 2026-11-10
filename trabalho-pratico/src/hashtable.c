#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/hashtable.h"
#include "../include/arraydin.h"
#include "../include/valida_dados.h"

typedef struct hashtable_item {
    void* dado;
    char* id;
    struct hashtable_item* prox;
} HT_Item;

typedef struct hashtable {
    int N;
    int max;
    HT_Item** lista;
} *HashTable;

int hashFunc(const char* s, int N) {
    unsigned long a=0;
    int b=0;
    int N_=strlen(s);
    for (int i=0;i<N_;i++) {
        b=abs(s[i]);
        a = ((a << 5) + a) + b;
    }

    int res=a%N;
    return res;
}

// ##################################################################
//                      GETTERS
// ##################################################################

//Obtem o número de elementos na HashTable
int getHTN (HashTable t) {
    return t->N;
}

//Obtem a capacidade da HashTable
int getHTMax (HashTable t) {
    return t->max;
}

void* getHTItemDado(HT_Item* item) {
    return item->dado;
}

const char* getHTItemId(HT_Item* item) {
    return item->id;
}

HT_Item** getHTLista(HashTable t) {
    return t->lista;
}

HT_Item* getHTItemProx(HT_Item* item) {
    return item->prox;
}



//Obtem o pior caso da hash table
int piorCasoHashTable(HashTable t) {
    int max=0;

    int N=t->max;

    for (int i=0;i<N;i++) {
        int num=0;
        HT_Item* aux=t->lista[i];
        while (aux) {
            num++;
            aux=aux->prox;
        }
        if (num>max) max=num;
    }

    return max;
}

//Obtem o Item da HashTable
void* getHTItem(const char* s, HashTable lista, int (*hashF)(const char*, int)) {
    HT_Item* a=procura_HashTable(s,lista,hashF);
    if (a) return a->dado;
    else return NULL;
}
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     SET'S     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

//Função que verifica se o número é primo
short NumeroPrimo(int n) {
    if (n < 2) return 0; //Se for menor que 2, não é primo
    
    //Verifica se n é divisivel por todos os numeros de 2 a raiz quadrada de n (Crivo de Eratóstenes)
    for (int i=2; i*i <= n;i++) 
        if (n%i==0) return 0; //é divisivel, logo não é primo
    
    return 1; //Não sendo encontrado um divisor, n é primo
}

//Função que obtendo um número encontra um número primo acima de 2n
int encontraNumeroPrimo(int n) {

    //Procura um numero primo entre n e n+200
    for (int i=0;i<200;i++) {
        if (NumeroPrimo(n+i)==1) return n+i; //encontrou, logo devolve esse número
    }

    return n; //Não encontrou, entao devolve o n
}

//Função que inicia a Hash Table
HashTable inicia_HashTable(int N_) {

    int N=encontraNumeroPrimo(N_);

    HashTable novo=malloc(sizeof(struct hashtable));
    novo->max=N;
    novo->N=0;
    novo->lista=malloc(sizeof(struct hashtable_item*)*N);

    for (int i=0;i<N;i++) {
        novo->lista[i]=NULL; //Inicializa tudo a NULL
    }

    return novo;
}

//Função que insere coisas na Hashtable
void insere_HashTable(const char* s, HashTable lista, void* dado, int (*hashF)(const char*, int)) {
    int i = hashF(s, lista->max); // Calcula o índice pela Função Hash

    HT_Item* ant = NULL;
    HT_Item* aux = lista->lista[i];
    while (aux && strcmp(aux->id, s) != 0) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux) {
        //printf("Elemento '%s' já existe, ignorando...\n", s); // Verificação de duplicata
        return; // Nodo existe, então já está inserido
    } else {
        aux = malloc(sizeof(struct hashtable_item));
        aux->id = strdup(s);
        aux->dado = dado;
        aux->prox = NULL;

        if (ant) ant->prox = aux;
        else lista->lista[i] = aux;

        lista->N++;
    }
}


//Função que procura o indice dado no array dinamico usando a Hash Table e o ID
HT_Item* procura_HashTable(const char*s, HashTable lista,int (*hashF)(const char*, int)) {
    //hashF -> hashFunction

    int i=hashF(s,lista->max)%(lista->max); //calcula o indice pela Função Hash

    HT_Item* aux=lista->lista[i];
    while (aux) {
        if (strcmp(aux->id,s)==0) return aux;
        aux=aux->prox;
    }
    return NULL; //Nao encontrou
}


//Função que imprime a hash table
void printHashTable(HashTable lista, void (*print)(void*)) {
    // print -> função que imprime o dado de cada nodo

    if (lista == NULL) {
        //printf("Hash Table inexistente\n");
    } else {
        

        // Ciclo para ver todos os espaços da Hash Table
        for (int i = 0; i < lista->max; i++) { 
            if (lista->lista[i] != NULL) {  // Somente imprime slots ocupados
                //printf("\n");
                HT_Item* aux = lista->lista[i]; 
                while (aux) {
                    print(aux->dado);               // Imprime os dados usando a função fornecida
                    aux = aux->prox;
                }
            }
        }
        //printf("Hash Table com %d slots e %d itens\n", lista->max, lista->N);
    }
    return;
}


//Função que apaga a Hash Table
void apagaHashTable(HashTable lista,void (*apagaNodo)(void*)) {
    //apagaNodo -> apaga o dado de cada nodo

    if (!lista) return; //HashTable não existe

    int N=lista->max;

    for (int i=0;i<N;i++) {
        HT_Item* aux=lista->lista[i];
        while (aux) {
            free(aux->id);
            apagaNodo(aux->dado);
            HT_Item* aux2=aux;
            aux=aux->prox;
            free(aux2);
        }
    }
    free(lista->lista);
    free(lista);
    return;
}