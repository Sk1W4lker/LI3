#ifndef HISTORY_H
#define HISTORY_H

#include "arraydin.h"
#include "hashtable.h"
#include "valida_dados.h"
#include "musics.h"
#include "users.h"
#include "ficheiros.h"

typedef struct pre_dados_history Pre_Historys;

// Estrutura para armazenar informações de cada usuário individual
typedef struct dados_historys historys;

// Estrutura para armazenar todos os usuários e informações adicionais
typedef struct historys History_Dados;

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     GET'S     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

int getHistoryDadosResultado(History_Dados* lista);
int getHistoryExiste(History_Dados* HTH, const char* history_id);
char* getHistoryUserId(History_Dados* HTH, const char* history_id);
char* getHistoryMusicId(History_Dados* HTH, const char* history_id);
char* getHistoryTimestamp(History_Dados* HTH, const char* history_id);
char* getHistoryDuration(History_Dados* HTH, const char* history_id);
char* getHistoryPlatform(History_Dados* HTH, const char* history_id);

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     SET'S     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

void defineHistoryUserId(const char* history_id, const char* user_id, History_Dados* HTH);
void defineHistoryMusicId(const char* history_id, const char* music_id, History_Dados* HTH);
void defineHistoryTimestamp(const char* history_id, const char* timestamp, History_Dados* HTH);
void defineHistoryDuration(const char* history_id, const char* duration, History_Dados* HTH);
void defineHistoryPlatform(const char* history_id, const char* platform, History_Dados* HTH);

///////////////////     FUNCOES      ////////////////////////////

int history_validation(Pre_Historys history) ;
History_Dados* iniciaHistory(const char* caminho_, Artist_Dados* artists, Music_Dados* musics);
historys* preHistoryParaHistory(Pre_Historys pre, Artist_Dados* artists, Music_Dados* musics);
void apagaHistory(void* history_);
void apagaDadosHistories(History_Dados* history_data);
void printHistory(void* history_);
void printHistories(History_Dados* history_data);


#endif // HISTORY_H
