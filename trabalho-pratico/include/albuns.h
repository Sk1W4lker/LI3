#ifndef ALBUNS_H
#define ALBUNS_H

#include "arraydin.h"
#include "hashtable.h"
#include "musics.h"
#include "ficheiros.h"
#include "valida_dados.h"

typedef struct pre_dados_albuns Pre_Albuns;

// Estrutura para armazenar informações de cada usuário individual
typedef struct dados_albuns Albuns;

// Estrutura para armazenar todos os usuários e informações adicionais
typedef struct albuns Albuns_Dados;

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     GET'S     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

int getAlbunsDadosResultado(Albuns_Dados* lista);
int getAlbumExiste(Albuns_Dados* HTU, const char* album_id);
char* getAlbumName(Albuns_Dados* HT, const char* album_id);
char* getAlbumArtistId(Albuns_Dados* HTA, const char* album_id);
int getNumAlbumArtistsId(Albuns_Dados* HTA, const char* album_id);
char* getAlbumGenre(Albuns_Dados* HT, const char* album_id);
char* getAlbumReleaseDate(Albuns_Dados* HT, const char* album_id);
int getAlbumTotalTracks(Albuns_Dados* HT, const char* album_id);

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||    SETTERS    ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

void setAlbumName(Albuns_Dados* HT, const char* album_id, const char* name);
void setAlbumArtistId(const char* album_id, char** artists_id, int num_artists, Albuns_Dados* HTA);
void setNumArtistsId(const char* album_id, int num_artists, Albuns_Dados* HTA);
void setAlbumGenre(Albuns_Dados* HT, const char* album_id, const char* genre);
void setAlbumReleaseDate(Albuns_Dados* HT, const char* album_id, const char* release_date);
void setAlbumTotalTracks(Albuns_Dados* HT, const char* album_id, int total_tracks);

////////////////////         FUNÇOES ///////////////////////////

Albuns_Dados* iniciaAlbuns(const char* caminho_, Artist_Dados* artists);
Albuns* PreAlbuns_para_Albuns(Pre_Albuns pre_album, Artist_Dados* artists);
void apagaAlbuns(void* album);
void apagaDadosAlbuns(Albuns_Dados* lista);
void printAlbuns(Albuns_Dados* albuns_dados);
void printAlbum(void* album);

#endif // ALBUNS_H
