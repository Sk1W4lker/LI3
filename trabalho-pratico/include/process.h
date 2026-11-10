#ifndef BATCH
#define BATCH

#include "arraydin.h"
#include "hashtable.h"
#include <stdbool.h>
#include "users.h"
#include "musics.h"
#include "artists.h"
#include "history.h"
#include "albuns.h"

void lerQueries(const char* caminho, User_Dados* user_data, Music_Dados* music_data, Artist_Dados* artist_data, History_Dados* history_data, Albuns_Dados* albuns_data, bool testes, double *tempo_query1, double *tempo_query2, double *tempo_query3);
#endif