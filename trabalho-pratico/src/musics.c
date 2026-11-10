#include <locale.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "arraydin.h"
#include "hashtable.h"
#include "valida_dados.h"
#include <sys/stat.h>  // Para mkdir

#include "musics.h"
#include "artists.h"
#include "users.h"

#include "ficheiros.h"

typedef struct pre_dados_musics {
    char* music_id;
    char* music_title;
    char* music_artist_id;
    char* music_album_id;
    char* music_duration;
    char* music_genre;
    char* music_year;
    //char* music_lyrics;
} Pre_Musics;

// Estrutura para armazenamento das músicas na Hash Table
typedef struct dados_music {
    char *id;
    char *title;
    char **artist_id;
    int num_artist_id;
    char *album_id;
    int duration_seconds;
    char *duration;
    char *genre;
    char *year;
    //char *lyrics;
} Musics;

// Estrutura para gerenciar todos os dados de músicas
typedef struct musics {
    HashTable HT;
    char resultado;
    int lidos;
    int succ;
    int fail;
} Music_Dados;

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     GET'S     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


int getMusicExiste(Music_Dados* HTU, const char* user_id) {
    // Tenta obter o music da tabela hash
    Musics* music = getHTItem(user_id, HTU->HT, &hashFunc);
    
    // Se o music for encontrado, retorna 1 (existe)
    if (music != NULL) {
        return 1; // Music existe
    }
    
    // Se não encontrado, retorna 0 (não existe)
    return 0; // Music não existe
}

char* getMusicTitle(Music_Dados* HT, const char* id) {
    Musics* music = getHTItem(id, HT->HT, &hashFunc);
    return music ? strdup(music->title) : NULL;
}

// Retorna o número de IDs de artista associados à música
int getNumArtists(Music_Dados* HT, const char* id) {
    Musics* music = getHTItem(id, HT->HT, &hashFunc);
    return music ? music->num_artist_id : 0;
}

// Retorna um array com os IDs de artista
char** getMusicArtistIDs(Music_Dados* HT, const char* id, int* num_artists) {
    Musics* music = getHTItem(id, HT->HT, &hashFunc);
    if (music && music->num_artist_id > 0) {
        *num_artists = music->num_artist_id;
        char** artist_ids = malloc(music->num_artist_id * sizeof(char*));
        for (int i = 0; i < music->num_artist_id; i++) {
            artist_ids[i] = strdup(music->artist_id[i]);
        }
        return artist_ids;
    }
    *num_artists = 0;
    return NULL;
}

char* getMusicAlbumID (Music_Dados* HT, const char* id){
    Musics* music = getHTItem(id, HT->HT, &hashFunc);
    return music ? strdup(music->album_id) : NULL;
}

char* getMusicDuration(Music_Dados* HT, const char* id) {
    Musics* music = getHTItem(id, HT->HT, &hashFunc);
    return music ? strdup(music->duration) : NULL;
}

int getMusicDurationSeconds(Music_Dados* HT, const char* id) {
    Musics* music = getHTItem(id, HT->HT, &hashFunc);
    return music ? music->duration_seconds : 0;
}

char* getMusicGenre(Music_Dados* HT, const char* id) {
    Musics* music = getHTItem(id, HT->HT, &hashFunc);
    return music ? strdup(music->genre) : NULL;
}

char* getMusicYear(Music_Dados* HT, const char* id) {
    Musics* music = getHTItem(id, HT->HT, &hashFunc);
    return music ? strdup(music->year) : NULL;
}
/*
char* getMusicLyrics(Music_Dados* HT, const char* id) {
    Musics* music = getHTItem(id, HT->HT, &hashFunc);
    return music ? strdup(music->lyrics) : NULL;
}
*/
HashTable* getMusicHashTable(Music_Dados* musics) {
    return &musics->HT;
}

//Obter o resultado do User Dados
int getMusicDadosResultado(Music_Dados* lista) {
    return lista->resultado;
}

//Obter os dados lidos do User Dados
int getMusicDadosLidos(Music_Dados* lista) {
    return lista->lidos;
}

//Obter os dados incorporados do User Dados
int getMusicDadosSucc(Music_Dados* lista) {
    return lista->succ;
}

//Obter os dados rejeitados do User Dados
int getMusicDadosFail(Music_Dados* lista) {
    return lista->fail;
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     SET'S     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

void setMusicTitle(Music_Dados* HT, const char* id, const char* title) {
    Musics* music = getHTItem(id, HT->HT, &hashFunc);
    if (music) {
        free(music->title);
        music->title = strdup(title);
    }
}

// Define múltiplos artist_id
void setMusicArtistIDs(Music_Dados* HT, const char* id, char** artist_ids, int num_artists) {
    Musics* music = getHTItem(id, HT->HT, &hashFunc);
    if (music) {
        for (int i = 0; i < music->num_artist_id; i++) {
            free(music->artist_id[i]);
        }
        free(music->artist_id);

        music->artist_id = malloc(num_artists * sizeof(char*));
        for (int i = 0; i < num_artists; i++) {
            music->artist_id[i] = strdup(artist_ids[i]);
        }
        music->num_artist_id = num_artists;
    }
}

void setMusicAlbumID (Music_Dados* HT, const char* id, const char* album_id){
    Musics* music = getHTItem(id, HT->HT, &hashFunc);
    if (music) {
        free(music->album_id);
        music->album_id = strdup(album_id);
    }
}

void setMusicDuration(Music_Dados* HT, const char* id, const char* duration) {
    Musics* music = getHTItem(id, HT->HT, &hashFunc);
    if (music) {
        free(music->duration);
        music->duration = strdup(duration);
        int hours, minutes, seconds;
        sscanf(duration, "%d:%d:%d", &hours, &minutes, &seconds);
        music->duration_seconds = hours * 3600 + minutes * 60 + seconds;
    }
}

void setMusicGenre(Music_Dados* HT, const char* id, const char* genre) {
    Musics* music = getHTItem(id, HT->HT, &hashFunc);
    if (music) {
        free(music->genre);
        music->genre = strdup(genre);
    }
}

void setMusicYear(Music_Dados* HT, const char* id, const char* year) {
    Musics* music = getHTItem(id, HT->HT, &hashFunc);
    if (music) {
        free(music->year);
        music->year = strdup(year);
    }
}
/*
void setMusicLyrics(Music_Dados* HT, const char* id, const char* lyrics) {
    Musics* music = getHTItem(id, HT->HT, &hashFunc);
    if (music) {
        free(music->lyrics);
        music->lyrics = strdup(lyrics);
    }
}
*/
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||   Funções     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


// Função que verifica se um Pre-Music é válido
int music_validation(Pre_Musics musics, Albuns_Dados* albuns) {
    // Verificação de campos obrigatórios
    if (musics.music_id == NULL) {
        //printf("Falha na validação: music_id é NULL\n");
        return 0;
    }
    if (musics.music_title == NULL) {
        //printf("Falha na validação: music_title é NULL\n");
        return 0;
    }
    if (musics.music_artist_id == NULL) {
        //printf("Falha na validação: music_artist_id é NULL\n");
        return 0;
    }
    // Validação do formato de music_artist_id (deve começar com "[" e terminar com "]")
    size_t artist_id_len = strlen(musics.music_artist_id);
    if (artist_id_len < 2 || musics.music_artist_id[0] != '[' || musics.music_artist_id[artist_id_len - 1] != ']') {
        //printf("Falha na validação: formato de music_artist_id inválido para %s\n", musics.music_artist_id);
        return 0;
    }
    if(musics.music_album_id){
        return (getAlbumExiste(albuns,musics.music_album_id));
    }else{
        return 0;
    }
    if (musics.music_genre == NULL) {
        //printf("Falha na validação: music_genre é NULL\n");
        return 0;
    }
    if (musics.music_year == NULL) {
        //printf("Falha na validação: music_year é NULL\n");
        return 0;
    }
    
    // Validação do formato da duração (HH:MM:SS)
    if (musics.music_duration) {
        // Verifica o comprimento da string (HH:MM:SS tem exatamente 8 caracteres)
        if (strlen(musics.music_duration) != 8 || 
            musics.music_duration[2] != ':' || 
            musics.music_duration[5] != ':') {
            //printf("Falha na validação: formato de duração inválido para %s\n", musics.music_duration);
            return 0;
        }
    if (musics.music_album_id != NULL) {
    // Verifica se album_id contém '[' ou ']'
    if (strchr(musics.music_album_id, '[') != NULL || strchr(musics.music_album_id, ']') != NULL) {
        //printf("Falha na validação: formato de music_album_id inválido para %s\n", musics.music_album_id);
        return 0;
    }
} else {
    //printf("Falha na validação: music_album_id é NULL\n");
    return 0;
}
        // Verificação detalhada de cada componente
        int hours, minutes, seconds;
        int count = sscanf(musics.music_duration, "%2d:%2d:%2d", &hours, &minutes, &seconds);
        
        if (count != 3 || hours < 0 || minutes < 0 || minutes >= 60 || seconds < 0 || seconds >= 60) {
            //printf("Falha na validação: formato de duração inválido para %s\n", musics.music_duration);
            return 0;
        }
    } else {
        //printf("Falha na validação: music_duration é NULL\n");
        return 0;
    }

    // Validação do formato do ano (YYYY)
    int year;
    if (sscanf(musics.music_year, "%4d", &year) != 1 || year < 0) {
        //printf("Falha na validação: formato de ano inválido para %s\n", musics.music_year);
        return 0;
    }

    return 1; // Passou em todas as validações
}



Musics* PreMusics_para_Music(Pre_Musics dados, Artist_Dados* artist) {
    Musics* novo = malloc(sizeof(Musics));
    if (!novo) return NULL;

    // Copia os dados de 'Pre_Musics' para a estrutura 'Musics'
    novo->id = strdup(dados.music_id);
    novo->title = strdup(dados.music_title);
    novo->album_id = strdup (dados.music_artist_id);
    novo->duration = strdup(dados.music_duration);
    novo->genre = strdup(dados.music_genre);
    novo->year = strdup(dados.music_year);
    //novo->lyrics = strdup(dados.music_lyrics);

    // Separação de múltiplos artist_id usando a função separa_String
    ArrayDin* artist_list = separa_String(dados.music_artist_id);
    novo->num_artist_id = getADN(artist_list); // Use o getter para obter o número de elementos

    
    // Aloca espaço para armazenar os ponteiros de cada artist_id
    novo->artist_id = malloc(sizeof(char*) * novo->num_artist_id);
    for (int i = 0; i < novo->num_artist_id; i++) {
        novo->artist_id[i] = strdup((char*)getADItem(artist_list, i)); // Use o getter para acessar os elementos
    }
    
    // Libera o array dinâmico temporário usado para dividir os IDs
    apaga_ArrayDin(artist_list,free);

    // Conversão de duração para segundos
    int hours = 0, minutes = 0, seconds = 0;
    sscanf(dados.music_duration, "%d:%d:%d", &hours, &minutes, &seconds);
    novo->duration_seconds = hours * 3600 + minutes * 60 + seconds;

    // Atualiza discografia_total para cada artist_id encontrado na HashTable de artistas
    for (int i = 0; i < novo->num_artist_id; i++) {
    HashTable* artist_HT = getArtistHashTable(artist);
        Artists* artista = (Artists*)getHTItem(novo->artist_id[i], *artist_HT, &hashFunc);

    if (artista) {
        incrementArtistDiscografiaTotal(artista, novo->duration_seconds);
    } else {
            //printf("Artista com ID %s não encontrado. Discografia total não será atualizada.\n", novo->artist_id[i]);
        }
    }

    return novo;
}


// Função para iniciar o processamento das músicas
Music_Dados* iniciaMusics(const char* caminho_, Artist_Dados* artist, Albuns_Dados* albuns) {
    Music_Dados* dados = malloc(sizeof(Music_Dados));
    if (!dados) return NULL;

    dados->lidos = 0;
    dados->fail = 0;
    dados->succ = 0;
    dados->resultado = 1;

    if (!caminho_) {
        dados->resultado = 0;
        dados->HT = inicia_HashTable(1);
        return dados;
    }

    // Verifica se caminho_ já é o próprio arquivo ou precisa de uma extensão
    char caminho[1000];
    if (strstr(caminho_, "musics.csv") != NULL) {
        snprintf(caminho, sizeof(caminho), "%s", caminho_);
    } else {
        snprintf(caminho, sizeof(caminho), "%s/musics.csv", caminho_);
    }
    //printf("Tentando abrir o arquivo: %s\n", caminho);

    // Tenta abrir o arquivo de dados
    Ficheiro* ficheiro = iniciaFicheiro(caminho, "r");
    if (!ficheiro) {
        //printf("Erro: arquivo %s não encontrado\n", caminho);
        dados->resultado = 0;
        dados->HT = inicia_HashTable(1);
        return dados;
    }

    // Cria o diretório "resultados" se ele não existir
    struct stat st = {0};
    if (stat("resultados", &st) == -1) {
        mkdir("resultados", 0700);
    }

    // Tenta abrir o arquivo de erros em "resultados/users_errors.csv"
    Ficheiro* erros = iniciaFicheiro("resultados/musics_errors.csv", "w+");
    if (!erros) {
        //printf("Erro ao abrir ou criar o arquivo de erros.\n");
        apagaFicheiro(ficheiro);
        dados->resultado = 0;
        dados->HT = inicia_HashTable(1);
        return dados;
    }

    // Processamento das linhas do arquivo
    char* string = NULL;
    int N_ficheiro = LinhasFicheiro(ficheiro);
    dados->HT = inicia_HashTable(N_ficheiro - 1);

    for (int i = 0; i < N_ficheiro; i++) {
        int j = 0;
        string = lerLinha(ficheiro);

        if (!string) continue;

        // Verifique se a linha é excessivamente longa
        if (strlen(string) > 2048) {
            //printf("Linha muito longa ou inválida, ignorando...\n");
            free(string);
            continue;
        }

        string[strlen(string) - 1] = '\0'; // Remova a nova linha no final
        char* string_copia = strdup(string);

        if (i == 0) { // Cabeçalho do arquivo
            escreveLinha(erros, string_copia);
            free(string);
            free(string_copia);
            continue;
        }

        Pre_Musics pre_music = {0};
        char* token = NULL;
        char* string_aux = string;
//"user1;john.doe@example.com;John;Doe;1990-01-01;30;USA;premium;1,2,3"

while ((token = strsep(&string, ";")) != NULL) {

    switch (j) {
        case 0: pre_music.music_id = strdup(token); 
        remove_quotes(pre_music.music_id);break;
        case 1: pre_music.music_title = strdup(token);
        remove_quotes(pre_music.music_title); break;
        case 2: pre_music.music_artist_id = strdup(token); 
        remove_quotes(pre_music.music_artist_id);break;
        case 3: pre_music.music_album_id = strdup(token);
        remove_quotes(pre_music.music_album_id);break;
        case 4: pre_music.music_duration = strdup(token); 
        remove_quotes(pre_music.music_duration);break;
        case 5: pre_music.music_genre = strdup(token); 
        remove_quotes(pre_music.music_genre);break;
        case 6: pre_music.music_year = strdup(token); 
        remove_quotes(pre_music.music_year);break;
        case 7: //pre_music.music_lyrics = strdup(token); 
        //remove_quotes(pre_music.music_lyrics);break;
        default: break;
    }
    j++;
}

        dados->lidos++;
        
        if (music_validation(pre_music, albuns) == 1) {
            Musics* music = PreMusics_para_Music(pre_music, artist);
            insere_HashTable(music->id, dados->HT, music, &hashFunc);

            dados->succ++;
        } else {
            escreveLinha(erros, string_copia);
            dados->fail++;
        }

        free(pre_music.music_id);
        free(pre_music.music_title);
        free(pre_music.music_artist_id);
        free(pre_music.music_album_id);
        free(pre_music.music_duration);
        free(pre_music.music_genre);
        free(pre_music.music_year);
        //free(pre_music.music_lyrics);

        free(string_aux);
        free(string_copia);
    }

    apagaFicheiro(ficheiro);
    apagaFicheiro(erros);

    return dados;
}
// Função para liberar a memória de uma música
void apaga_Music(void* music_) {
    Musics* music = music_;
    free(music->id);
    free(music->title);
    for (int i = 0; i < music->num_artist_id; i++) {
        free(music->artist_id[i]);
    }
    free(music->artist_id);
    free(music->duration);
    free(music->genre);
    free(music->year);
    //free(music->lyrics);
    free(music);
}


//Função que imprime um User
void printMusic(void* a_) {
    Musics* a = a_;

    printf("Music ID: %s\n", a->id);
    printf("Titulo: %s\n", a->title);
    printf("Artist IDs: ");
    for (int i = 0; i < a->num_artist_id; i++) {
        printf("%s", a->artist_id[i]);
        if (i < a->num_artist_id - 1) {
            printf(", "); // Adiciona uma vírgula entre IDs, mas não após o último
        }
    }
    printf("\n");
    printf("Album ID: %s\n", a->album_id);
    printf("Duração: %s\n", a->duration);
    printf("Generos: %s\n", a->genre);
    printf("Ano: %s\n", a->year);
    //printf("Lyrics: %s\n", a->lyrics);

    // Exibir uma linha em branco para separar os usuários
    printf("\n");
}

// Função para liberar todos os dados de Músicas
void apagaDadosMusics(Music_Dados* lista) {
    if (!lista) return;
    apagaHashTable(lista->HT, &apaga_Music);
    free(lista);
}

void printMusics(Music_Dados* Music, short modo) {
    //  modo:  0 -> tudo  |  1 -> só músicas

    if (!Music) return;

    // Supondo que printHashTable seja uma função genérica para imprimir a hash table
    if (modo != 2) {
        printHashTable(Music->HT, &printMusic);
    }
}


