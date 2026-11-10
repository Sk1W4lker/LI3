#ifndef _MUSIC_H_
#define _MUSIC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "artists.h"
#include "albuns.h"

//Deopis temos de arranjar forma de tirar isto daqui
typedef struct albuns Albuns_Dados;


// Estrutura de Dados para os pré-músicas
typedef struct pre_dados_musics Pre_Musics;

// Estrutura para armazenamento das músicas na Hash Table
typedef struct dados_music Musics;

// Estrutura para gerenciar todos os dados de músicas
typedef struct musics Music_Dados;

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     GET'S     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

int getMusicExiste(Music_Dados* HTU, const char* user_id);
char* getMusicTitle(Music_Dados* HT, const char* id);
int getNumArtists(Music_Dados* HT, const char* id);
char** getMusicArtistIDs(Music_Dados* HT, const char* id, int* num_artists);
char* getMusicAlbumID (Music_Dados* HT, const char* id);
char* getMusicDuration(Music_Dados* HT, const char* id);
int getMusicDurationSeconds(Music_Dados* HT, const char* id);
char* getMusicGenre(Music_Dados* HT, const char* id);
char* getMusicYear(Music_Dados* HT, const char* id);
//char* getMusicLyrics(Music_Dados* HT, const char* id);
HashTable* getMusicHashTable(Music_Dados* musics);
int getMusicDadosResultado(Music_Dados* lista);
int getMusicDadosLidos(Music_Dados* lista);
int getMusicDadosFail(Music_Dados* lista);
int getMusicDadosSucc(Music_Dados* lista);

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||   Setters    |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

void setMusicTitle(Music_Dados* HT, const char* id, const char* title);
void setMusicArtistIDs(Music_Dados* HT, const char* id, char** artist_ids, int num_artists);
void setMusicAlbumID (Music_Dados* HT, const char* id, const char* album_id);
void setMusicDuration(Music_Dados* HT, const char* id, const char* duration);
void setMusicGenre(Music_Dados* HT, const char* id, const char* genre);
void setMusicYear(Music_Dados* HT, const char* id, const char* year);
//void setMusicLyrics(Music_Dados* HT, const char* id, const char* lyrics);

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||   Funções    |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

int music_validation(Pre_Musics musics, Albuns_Dados* albuns);
Musics* PreMusics_para_Music(Pre_Musics dados, Artist_Dados* artist);
Music_Dados* iniciaMusics(const char* caminho_, Artist_Dados* artist, Albuns_Dados* albuns);
void apaga_Music(void* music_);
void printMusic(void* a_);
void apagaDadosMusics(Music_Dados* lista);
void printMusics(Music_Dados* Music, short modo);

#endif // _MUSIC_H_
