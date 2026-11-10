#ifndef FICHEIROS
#define FICHEIROS

#include "arraydin.h"

typedef struct ficheiro Ficheiro;

//Getters
int LinhasFicheiro(Ficheiro* fich);
void escreveLinha(Ficheiro* fich,const char* string);
char* lerLinha(Ficheiro* fich);

//Setters
Ficheiro* iniciaFicheiro(const char* nome,const char* modo);
void apagaFicheiro(Ficheiro* fich);
int escreveFicheiro(const char* nome_ficheiro, ArrayDin* lista);

ArrayDin* separa_String(const char* s); 

void compararResultados(const char *output_file, const char *expected_file, int num_teste, int *corretos, int *erros);

char** parse_csv_line(const char* line, int* num_fields);

#endif