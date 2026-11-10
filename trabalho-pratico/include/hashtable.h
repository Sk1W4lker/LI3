#ifndef HASHTABLE
#define HASHTABLE

#include "arraydin.h"

typedef struct hashtable_item HT_Item;

typedef struct hashtable* HashTable;

int hashFunc(const char* s, int N);
// Getters
void* getHTItem(const char* s, HashTable lista, int (*hashF)(const char*, int));
int getHTN (HashTable t);
int getHTMax (HashTable t);
void* getHTItemDado(HT_Item* item);
HT_Item* getHTItemProx(HT_Item* item);
const char* getHTItemId(HT_Item* item);
int piorCasoHashTable(HashTable t);
short NumeroPrimo(int n);


// Função que encontra um número primo acima de 2n
int encontraNumeroPrimo(int n);

// Setters
HashTable inicia_HashTable(int N_);
void insere_HashTable(const char* s, HashTable lista, void* dado, int (*hashF)(const char*, int));
HT_Item* procura_HashTable(const char* s, HashTable lista, int (*hashF)(const char*, int));
HT_Item** getHTLista(HashTable t);
int getHTN (HashTable t);
int getHTMax (HashTable t);
int piorCasoHashTable(HashTable t);
void* getHTItem(const char* s, HashTable lista, int (*hashF)(const char*, int));
void printHashTable(HashTable lista, void (*print)(void*));
void apagaHashTable(HashTable lista, void (*apagaNodo)(void*));

#endif
