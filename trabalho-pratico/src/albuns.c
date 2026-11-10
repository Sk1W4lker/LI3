#include "albuns.h"

typedef struct pre_dados_albuns {
    char* albuns_albuns_id;
    char* albuns_title;
    char* albuns_artists_id;
    char* albuns_year;
    char* albuns_producers;
} Pre_Albuns;

// Estrutura para armazenar informações de cada usuário individual
typedef struct dados_albuns {
    char* albuns_id;
    char* title;
    char** artists_id;
    int num_artists_id;
    char* year;
    char* producers;
} Albuns;

// Estrutura para armazenar todos os usuários e informações adicionais
typedef struct albuns {
    HashTable HT;
    char resultado;
    int lidos;
    int succ;
    int fail;
} Albuns_Dados;

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     GET'S     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

//Obter o resultado do User Dados
int getAlbunsDadosResultado(Albuns_Dados* lista) {
    return lista->resultado;
}

// Verifica se um álbum existe na HashTable
int getAlbumExiste(Albuns_Dados* HTA, const char* album_id) {
    Albuns* album = getHTItem(album_id, HTA->HT, &hashFunc);
    return album != NULL; // Retorna 1 se existe, 0 caso contrário
}

// Obtém o título do álbum
char* getAlbumTitle(Albuns_Dados* HTA, const char* album_id) {
    Albuns* album = getHTItem(album_id, HTA->HT, &hashFunc);
    return album ? strdup(album->title) : NULL;
}

// Obtém os IDs dos artistas do álbum
char* getAlbumArtistId(Albuns_Dados* HTA, const char* album_id) {
    Albuns* album = getHTItem(album_id, HTA->HT, &hashFunc);
    if (album && album->artists_id && album->num_artists_id > 0) {
        // Cria uma string que contém todos os IDs dos artistas separados por vírgula
        size_t len = 0;
        for (int i = 0; i < album->num_artists_id; i++) {
            len += strlen(album->artists_id[i]) + 1; // 1 para o separador
        }
        
        char* artists_ids = malloc(len + 1); // +1 para o terminador de string
        artists_ids[0] = '\0';
        
        for (int i = 0; i < album->num_artists_id; i++) {
            strcat(artists_ids, album->artists_id[i]);
            if (i < album->num_artists_id - 1) {
                strcat(artists_ids, ",");
            }
        }
        return artists_ids;
    }
    return NULL;
}

// Obtém o número de artistas associados ao álbum
int getNumAlbumArtistsId(Albuns_Dados* HTA, const char* album_id) {
    Albuns* album = getHTItem(album_id, HTA->HT, &hashFunc);
    if (album) {
        return album->num_artists_id;
    }
    return 0; // Retorna 0 se o álbum não for encontrado
}

// Obtém o ano do álbum
char* getAlbumYear(Albuns_Dados* HTA, const char* album_id) {
    Albuns* album = getHTItem(album_id, HTA->HT, &hashFunc);
    return album ? strdup(album->year) : NULL;
}

// Obtém o(s) produtor(es) do álbum
char* getAlbumProducers(Albuns_Dados* HTA, const char* album_id) {
    Albuns* album = getHTItem(album_id, HTA->HT, &hashFunc);
    return album ? strdup(album->producers) : NULL;
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     SET'S     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

// Define o título do álbum
void setAlbumTitle(const char* album_id, const char* title, Albuns_Dados* HTA) {
    if (!getAlbumExiste(HTA, album_id)) return; // Álbuns não existe

    Albuns* album = getHTItem(album_id, HTA->HT, &hashFunc);
    free(album->title);
    album->title = strdup(title);
}

// Define os IDs dos artistas para o álbum
void setAlbumArtistId(const char* album_id, char** artists_id, int num_artists, Albuns_Dados* HTA) {
    if (!getAlbumExiste(HTA, album_id)) return; // Álbuns não existe

    Albuns* album = getHTItem(album_id, HTA->HT, &hashFunc);

    // Apaga os antigos IDs dos artistas
    if (album->artists_id) {
        for (int i = 0; i < album->num_artists_id; i++) {
            free(album->artists_id[i]);
        }
        free(album->artists_id);
    }

    // Atualiza com os novos IDs
    album->artists_id = malloc(num_artists * sizeof(char*));
    for (int i = 0; i < num_artists; i++) {
        album->artists_id[i] = strdup(artists_id[i]);
    }
    album->num_artists_id = num_artists;
}

// Define o número de artistas associados ao álbum
void setNumArtistsId(const char* album_id, int num_artists, Albuns_Dados* HTA) {
    if (!getAlbumExiste(HTA, album_id)) return; // Álbuns não existe

    Albuns* album = getHTItem(album_id, HTA->HT, &hashFunc);

    // Atualiza o número de artistas, sem alterar os IDs dos artistas
    album->num_artists_id = num_artists;
}

// Define o ano do álbum
void setAlbumYear(const char* album_id, const char* year, Albuns_Dados* HTA) {
    if (!getAlbumExiste(HTA, album_id)) return; // Álbuns não existe

    Albuns* album = getHTItem(album_id, HTA->HT, &hashFunc);
    free(album->year);
    album->year = strdup(year);
}

// Define os produtores do álbum
void setAlbumProducers(const char* album_id, const char* producers, Albuns_Dados* HTA) {
    if (!getAlbumExiste(HTA, album_id)) return; // Álbuns não existe

    Albuns* album = getHTItem(album_id, HTA->HT, &hashFunc);
    free(album->producers);
    album->producers = strdup(producers);
}

////////////////////////////////////////////////////////
//////  FUNÇOES ///////////////////////////////////////////
///////////////////////////////////////////////

// Função que inicializa os dados dos álbuns
Albuns_Dados* iniciaAlbuns(const char* caminho_, Artist_Dados* artists) {
    Albuns_Dados* dados = malloc(sizeof(Albuns_Dados));
    if (!dados) return NULL;

    dados->lidos = 0;
    dados->succ = 0;
    dados->fail = 0;
    dados->resultado = 1;

    if (!caminho_) {
        dados->resultado = 0;
        dados->HT = inicia_HashTable(1);
        return dados;
    }

    // Verifica se caminho_ já é o próprio arquivo ou precisa de uma extensão
    char caminho[1000];
    if (strstr(caminho_, "albums.csv") != NULL) {
        snprintf(caminho, sizeof(caminho), "%s", caminho_);
    } else {
        snprintf(caminho, sizeof(caminho), "%s/albums.csv", caminho_);
    }

    Ficheiro* ficheiro = iniciaFicheiro(caminho, "r");
    if (!ficheiro) {
        //printf("Erro: arquivo %s não encontrado\n", caminho);
        dados->resultado = 0;
        dados->HT = inicia_HashTable(1);
        return dados;
    }


    // Tenta abrir o arquivo de erros em "resultados/albums_errors.csv"
    Ficheiro* erros = iniciaFicheiro("resultados/albums_errors.csv", "w+");
    if (!erros) {
        //printf("Erro ao abrir ou criar o arquivo de erros.\n");
        apagaFicheiro(ficheiro);
        dados->resultado = 0;
        dados->HT = inicia_HashTable(1);
        return dados;
    }

    int N_ficheiro = LinhasFicheiro(ficheiro);
    dados->HT = inicia_HashTable(N_ficheiro - 1);

    for (int i = 0; i < N_ficheiro; i++) {
        int j = 0;
        char* string = lerLinha(ficheiro);

        if (!string) continue;

        string[strlen(string) - 1] = '\0';
        char* string_copia = strdup(string);

        if (i == 0) {
            escreveLinha(erros, string_copia);
            free(string);
            free(string_copia); 
            continue;
        }

        Pre_Albuns pre_album = {0};
        char* token = NULL;
        char* string_aux = string;

        while ((token = strsep(&string, ";")) != NULL) {
            switch (j) {
                case 0: pre_album.albuns_albuns_id = strdup(token); remove_quotes(pre_album.albuns_albuns_id); break;
                case 1: pre_album.albuns_title = strdup(token);remove_quotes(pre_album.albuns_title); break;
                case 2: pre_album.albuns_artists_id = strdup(token);remove_quotes(pre_album.albuns_artists_id); break;
                case 3: pre_album.albuns_year = strdup(token); remove_quotes(pre_album.albuns_year);break;
                case 4: pre_album.albuns_producers = strdup(token); remove_quotes(pre_album.albuns_producers);break;
            }
            j++;
        }

        dados->lidos++;

        Albuns* album = PreAlbuns_para_Albuns(pre_album, artists);
        if (album) {
            insere_HashTable(album->albuns_id, dados->HT, album, &hashFunc);
            dados->succ++;
        } else {
            dados->fail++;
        }

        free(string_aux);
        free(pre_album.albuns_albuns_id);
        free(pre_album.albuns_title);
        free(pre_album.albuns_artists_id);
        free(pre_album.albuns_year);
        free(pre_album.albuns_producers);
    }

    apagaFicheiro(ficheiro);
    apagaFicheiro(erros);

    return dados;
}

// Função que converte pré-álbuns para álbuns
Albuns* PreAlbuns_para_Albuns(Pre_Albuns pre_album, Artist_Dados* artists) {
    Albuns* novo = malloc(sizeof(Albuns));
    if (!novo) return NULL;

    novo->albuns_id = strdup(pre_album.albuns_albuns_id);
    novo->title = strdup(pre_album.albuns_title);
    novo->year = strdup(pre_album.albuns_year);
    novo->producers = strdup(pre_album.albuns_producers);

    if (pre_album.albuns_artists_id) {
        ArrayDin* artists_list = separa_String(pre_album.albuns_artists_id);
        novo->num_artists_id = getADN(artists_list);
        novo->artists_id = malloc(novo->num_artists_id * sizeof(char*));
        for (int i = 0; i < novo->num_artists_id; i++) {
            novo->artists_id[i] = strdup(getADItem(artists_list, i));
        }

        // Atualiza o número de álbuns individuais para cada artista
        for (int i = 0; i < novo->num_artists_id; i++) {
            char* artist_id = novo->artists_id[i];

            // Obtém o artista pelo ID
            Artists* artist = getArtistByID(artists, artist_id);
            if (artist) {
                // Incrementa o número de álbuns individuais do artista
                setArtistNumAlbumInd(artists, artist_id, getArtistNumAlbumInd(artist) + 1);
            }
        }
    }

    return novo;
}

// Função que apaga um álbum
void apagaAlbuns(void* album_) {
    Albuns* album = (Albuns*)album_;
    if (!album) return;

    if (album->albuns_id) free(album->albuns_id);
    if (album->title) free(album->title);
    if (album->artists_id) {
        for (int i = 0; i < album->num_artists_id; i++) {
            free(album->artists_id[i]);
        }
        free(album->artists_id);
    }
    if (album->year) free(album->year);
    if (album->producers) free(album->producers);

    free(album);
}

void apagaDadosAlbuns(Albuns_Dados* lista){
    if (!lista) return;
    apagaHashTable(lista->HT,&apagaAlbuns);
    free(lista);
}

// Função que imprime um álbum
void printAlbum(void* album_) {
    Albuns* album = (Albuns*)album_;
    printf("Album ID: %s\n", album->albuns_id);
    printf("Title: %s\n", album->title);
    printf("Artists Id: ");
    if (album->artists_id && album->num_artists_id > 0) {
        for (int i = 0; i < album->num_artists_id; i++) {
            printf("%s", album->artists_id[i]);
            if (i < album->num_artists_id - 1) {
            }
        }
    } else {
        printf("None");
    }
    printf("\n");
    printf("Year: %s\n", album->year);
    printf("Producers: %s\n", album->producers);
}

// Função que imprime todos os álbuns
void printAlbuns(Albuns_Dados* albuns_dados) {
    if (!albuns_dados) return;
    printHashTable(albuns_dados->HT, &printAlbum);
}