#ifndef ARRAYDIN
#define ARRAYDIN

typedef struct array_din ArrayDin;

//Getters

int getADN(const ArrayDin* lista);
void* getADItem(const ArrayDin* lista, int i);
int getADMax(const ArrayDin* lista);


//Setters
void inserir_ArrayDin(void* dado, ArrayDin* lista);
ArrayDin* inicia_ArrayDin(int N);
void apaga_ArrayDin(ArrayDin* lista,void(*apagaF)(void*));
void apaga_ADString(void* a_);
void apaga_ADStrings(ArrayDin* lista);


#endif