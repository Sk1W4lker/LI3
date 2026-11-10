#ifndef QUERIES
#define QUERIES

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "arraydin.h"
#include "hashtable.h"
#include "valida_dados.h"

#include "users.h"
#include "musics.h"
#include "artists.h"
#include "history.h"
#include "albuns.h"

#define LinhaMax 100000
#define MAX_LINHAS 100
#define MAX_COLUNAS 1000

void query1(ArrayDin* output, short tipo_output, char* id, User_Dados* Users, Artist_Dados* Artistas);

int compara_artistas_por_discografia(const void* a, const void* b) ;
ArrayDin* query2(int N, const char* country, short tipo_output,Artist_Dados* dados_artistas, Music_Dados* dados_musicas);

void libera_int(void* dado);
int compara_generos(const void* a, const void* b);
ArrayDin* query3(int min_age, int max_age, short tipo_output,User_Dados* dados_users, Music_Dados* dados_musicas);

void tiraChar(char* str);
int tamanho(char* s, char* c);
char* arg_semAspas(char* s, char* s2, char** nova_string);
void quebraQuery(char* query, char args[MAX_LINHAS][MAX_COLUNAS], int* N);
int processaIdQuery(char* query, short int* tipo_output);
ArrayDin* interpretarQueries(char* query, User_Dados* Users, Music_Dados* Musics, Artist_Dados* Artists, History_Dados* history_data, Albuns_Dados* albuns_data, bool batch);


#endif