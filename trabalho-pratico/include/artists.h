#ifndef ARTISTS_H
#define ARTISTS_H

#include "arraydin.h"
#include "hashtable.h"

// Estrutura para armazenar informações temporárias dos pré-artistas
typedef struct pre_dados_artists Pre_Artists;

// Estrutura para armazenar informações de cada artista individual
typedef struct artist Artists;

// Estrutura para armazenar todos os artistas e informações adicionais
typedef struct artists Artist_Dados;

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     GET'S     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

int getArtistExiste(Artist_Dados* HTU, const char* user_id);
Artists* getArtistByID(Artist_Dados* artists_data, const char* artist_id);
const char* getArtistName(Artists* artist);
//char* getArtistDescription(Artist_Dados* HT, const char* s);
double getArtistRecipePerStream(Artist_Dados* HT, const char* s);
const char* getArtistCountry(Artists* artist);
const char* getArtistType(Artists* artist);
int getArtistDiscografiaTotal(Artists* artist);
const char* getArtistID(Artists* artist);
char* getArtistConstituent(Artist_Dados* HT, const char* s);
int getArtistNumConstituent(Artists* artist);
HashTable* getArtistHashTable(Artist_Dados* artists);
int getArtistDadosResultado(Artist_Dados* lista);
int getArtistDadosLidos(Artist_Dados* lista);
int getArtistDadosSucc(Artist_Dados* lista);
int getArtistDadosFail(Artist_Dados* lista);
void incrementArtistDiscografiaTotal(Artists* artist, int duration_seconds);
double getArtistRecipeTotal(Artists* artist);
int getArtistNumAlbumInd (Artists* artist);

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||   Setters    |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

void setArtistName(Artist_Dados* HT, const char* id, const char* name);
//void setArtistDescription(Artist_Dados* HT, const char* id, const char* description);
void setArtistRecipePerStream(Artist_Dados* HT, const char* id, double recipe_per_stream);
void setArtistRecipeTotal(Artist_Dados* HT, const char* id, double recipe_total);
void setArtistCountry(Artist_Dados* HT, const char* id, const char* country);
void setArtistType(Artist_Dados* HT, const char* id, const char* type);
void setArtistDiscografiaTotal(Artist_Dados* HT, const char* id, int discografia_total);
void setArtistConstituent(Artist_Dados* HT, const char* id, const char* constituents);
void setArtistNumAlbumInd (Artist_Dados* HT, const char* id, int num_album_ind);


int artist_validation(Pre_Artists artists); // Função de validação de artistas
Artists* PreArtists_para_Artist(Pre_Artists dados); // Função para converter um Pre_Artists para Artists
Artist_Dados* iniciaArtists(const char* caminho_);
void apaga_Artist(void* artist_) ;
void apagaDadosArtists(Artist_Dados* lista);
void printArtist(void* a_);
void printArtists(Artist_Dados* Artist, short modo);

#endif // ARTISTS_H
