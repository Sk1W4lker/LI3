#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "arraydin.h"
#include "hashtable.h"
#include "valida_dados.h"
#include "ficheiros.h"
#include "artists.h"
#include "users.h"
#include <sys/stat.h>  // Para mkdir

// Estrutura para armazenar informações temporárias dos pré-artistas
typedef struct pre_dados_artists {
    char* artist_id;
    char* artist_name;
    //char* artist_description;
    char* artist_recipe_per_stream;
    char* artist_id_constituent;
    char* artist_country;
    char* artist_type;
} Pre_Artists;

// Estrutura para armazenar informações de cada artista individual
typedef struct artist {
    char* id;                    // Identificador único do artista
    char* name;                  // Nome do artista
    //char* description;           // Descrição do artista
    double recipe_per_stream;     // Receita por stream
    double recipe_total;
    char** id_constituent;        // ID do constituinte
    int num_id_constituent;
    char* country;               // Nacionalidade do artista
    char* type;                  // Tipo de artista (individual ou grupo)
    int discografia_total;       // Total da discografia
    int num_albums_individual;
} Artists;

// Estrutura para armazenar todos os artistas e informações adicionais
typedef struct artists {
    HashTable HT;
    char resultado;                // Hash Table para armazenar os artistas
    int lidos;                   // Contador de artistas lidos
    int succ;                    // Contador de artistas bem-sucedidos
    int fail;                    // Contador de artistas rejeitados
} Artist_Dados;

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     GET'S     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

int getArtistExiste(Artist_Dados* HTU, const char* user_id) {
    // Tenta obter o artista da tabela hash
    Artists* artist = getHTItem(user_id, HTU->HT, &hashFunc);
    
    // Se o artista for encontrado, retorna 1 (existe)
    if (artist != NULL) {
        return 1; // Artista existe
    }
    
    // Se não encontrado, retorna 0 (não existe)
    return 0; // Artista não existe
}

Artists* getArtistByID(Artist_Dados* artists_data, const char* artist_id) {
    if (!artists_data || !artist_id) return NULL; // Verifica parâmetros nulos

    // Procura o artista na hash table
    Artists* artist = (Artists*)getHTItem(artist_id, artists_data->HT, &hashFunc);
    return artist; // Retorna o artista encontrado ou NULL
}

// Obtem o Nome do Artista
const char* getArtistName(Artists* artist) {
    return artist->name;
}
/*
// Obtem a Descrição do Artista
char* getArtistDescription(Artist_Dados* HT, const char* s) {
    Artists* artist = getHTItem(s, HT->HT, &hashFunc);
    return artist ? strdup(artist->description) : NULL;
}
*/
// Obtem a Receita por Stream do Artista
double getArtistRecipePerStream(Artist_Dados* HT, const char* s) {
    Artists* artist = getHTItem(s, HT->HT, &hashFunc);
    return artist->recipe_per_stream;
}

//Obtem a receita total
double getArtistRecipeTotal(Artists* artist) {
    return artist->recipe_total;
}

// Obtem o País do Artista
const char* getArtistCountry(Artists* artist) {
    return artist->country;
}

// Obtem o Tipo de Artista (Individual ou Grupo)
const char* getArtistType(Artists* artist) {
    return artist->type;
}

// Obtem o Total da Discografia
int getArtistDiscografiaTotal(Artists* artist) {
    return artist->discografia_total;
}

const char* getArtistID(Artists* artist) {
    return artist->id;
}


char* getArtistConstituent(Artist_Dados* HT, const char* s) {
    Artists* artist = getHTItem(s, HT->HT, &hashFunc);
    int num_constituent= getArtistNumConstituent(artist);
    if (!artist || (num_constituent == 0)) return NULL;

    // Calcular o tamanho necessário para armazenar todos os IDs com vírgulas
    int length = 0;
    for (int i = 0; i < num_constituent; i++) {
        length += strlen(artist->id_constituent[i]) + 1; // +1 para vírgula/terminador nulo
    }

    char* concatenated_ids = malloc(length);
    if (!concatenated_ids) return NULL;

    concatenated_ids[0] = '\0';
    for (int i = 0; i < num_constituent; i++) {
        strcat(concatenated_ids, artist->id_constituent[i]);
        if (i < num_constituent - 1) strcat(concatenated_ids, ",");
    }

    return concatenated_ids;
}

// Obtem o Número de Constituintes do Artista (para grupos)
int getArtistNumConstituent(Artists* artist) {
    return artist->num_id_constituent;
}

void incrementArtistDiscografiaTotal(Artists* artist, int duration_seconds) {
    artist->discografia_total += duration_seconds;
}

int getArtistNumAlbumInd (Artists* artist){
    return artist->num_albums_individual;
}


HashTable* getArtistHashTable(Artist_Dados* artists) {
    return &artists->HT;
}

//Obter o resultado do User Dados
int getArtistDadosResultado(Artist_Dados* lista) {
    return lista->resultado;
}

//Obter os dados lidos do User Dados
int getArtistDadosLidos(Artist_Dados* lista) {
    return lista->lidos;
}

//Obter os dados incorporados do User Dados
int getArtistDadosSucc(Artist_Dados* lista) {
    return lista->succ;
}

//Obter os dados rejeitados do User Dados
int getArtistDadosFail(Artist_Dados* lista) {
    return lista->fail;
}


//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     SET'S     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

// Define o Nome do Artista
void setArtistName(Artist_Dados* HT, const char* id, const char* name) {
    Artists* artist = getHTItem(id, HT->HT, &hashFunc);
    if (artist) {
        free(artist->name);
        artist->name = strdup(name);
    }
}
/*
// Define a Descrição do Artista
void setArtistDescription(Artist_Dados* HT, const char* id, const char* description) {
    Artists* artist = getHTItem(id, HT->HT, &hashFunc);
    if (artist) {
        free(artist->description);
        artist->description = strdup(description);
    }
}
*/
// Define a Receita por Stream
void setArtistRecipePerStream(Artist_Dados* HT, const char* id, double recipe_per_stream) {
    Artists* artist = getHTItem(id, HT->HT, &hashFunc);
    if (artist) {
        artist->recipe_per_stream = recipe_per_stream;
    }
}

void setArtistRecipeTotal(Artist_Dados* HT, const char* id, double recipe_total){
    Artists* artist = getHTItem(id, HT->HT, &hashFunc);
    if (artist) {
        artist->recipe_total = recipe_total;
    }
}

// Define o País do Artista
void setArtistCountry(Artist_Dados* HT, const char* id, const char* country) {
    Artists* artist = getHTItem(id, HT->HT, &hashFunc);
    if (artist) {
        free(artist->country);
        artist->country = strdup(country);
    }
}

// Define o Tipo de Artista
void setArtistType(Artist_Dados* HT, const char* id, const char* type) {
    Artists* artist = getHTItem(id, HT->HT, &hashFunc);
    if (artist) {
        free(artist->type);
        artist->type = strdup(type);
    }
}

// Define o Total da Discografia
void setArtistDiscografiaTotal(Artist_Dados* HT, const char* id, int discografia_total) {
    Artists* artist = getHTItem(id, HT->HT, &hashFunc);
    if (artist) {
        artist->discografia_total = discografia_total;
    }
}

void setArtistConstituent(Artist_Dados* HT, const char* id, const char* constituents) {
    Artists* artist = getHTItem(id, HT->HT, &hashFunc);
    if (artist) {
        // Libera IDs antigos
        for (int i = 0; i < artist->num_id_constituent; i++) {
            free(artist->id_constituent[i]);
        }
        free(artist->id_constituent);

        // Conta o número de novos IDs
        artist->num_id_constituent = 1;
        for (const char* p = constituents; *p; p++) {
            if (*p == ',') artist->num_id_constituent++;
        }

        // Aloca o array para os novos IDs
        artist->id_constituent = malloc(artist->num_id_constituent * sizeof(char*));

        // Tokeniza e armazena cada novo ID
        int idx = 0;
        char* constituents_copy = strdup(constituents);
        char* token = strtok(constituents_copy, ",");
        while (token != NULL && idx < artist->num_id_constituent) {
            artist->id_constituent[idx++] = strdup(token);
            token = strtok(NULL, ",");
        }
        free(constituents_copy);
    }
}

void setArtistNumAlbumInd (Artist_Dados* HT, const char* id, int num_album_ind){
    Artists* artist = getHTItem(id, HT->HT, &hashFunc);
    if (artist) {
        artist->num_albums_individual = num_album_ind;
    }
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||   FUNÇÕES     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

// Função que verifica se um Pre-Artists é válido
int artist_validation(Pre_Artists artists) {
    // Verificação de campos obrigatórios
    if (artists.artist_id == NULL) {
        //printf("Falha na validação: artist_id é NULL\n");
        return 0;
    }
    if (artists.artist_name == NULL) {
        //printf("Falha na validação: artist_name é NULL\n");
        return 0;
    }
    /*if (artists.artist_description == NULL) {
        //printf("Falha na validação: artist_description é NULL\n");
        return 0;
    }*/
    if (artists.artist_recipe_per_stream == NULL) {
        //printf("Falha na validação: artist_recipe_per_stream é NULL\n");
        return 0;
    }

    if (artists.artist_type == NULL || (!((strcasecmp(artists.artist_type, "individual") == 0)|| (strcasecmp(artists.artist_type, "group") == 0)))){
        //printf("Falha na validação: artist_type inválido\n");
        return 0;
    }

    // Verificação de id_constituent para tipo individual
    if (artists.artist_type != NULL && (strcasecmp(artists.artist_type, "individual") == 0)) {
        if (artists.artist_id_constituent == NULL || strcmp(artists.artist_id_constituent, "[]") != 0) {
            //printf("Falha na validação: id_constituent deve ser '[]' para artista do tipo 'individual'\n");
            return 0;
        }
    }

    return 1;
}


Artists* PreArtists_para_Artist(Pre_Artists dados) {
    Artists* novo = malloc(sizeof(Artists));
    if (!novo) return NULL;

    novo->id = dados.artist_id ? strdup(dados.artist_id) : NULL;
    novo->name = dados.artist_name ? strdup(dados.artist_name) : NULL;
    //novo->description = dados.artist_description ? strdup(dados.artist_description) : NULL;
    novo->recipe_per_stream = atof(dados.artist_recipe_per_stream);
    novo->country = dados.artist_country ? strdup(dados.artist_country) : NULL;
    novo->type = dados.artist_type ? strdup(dados.artist_type) : NULL;
    novo->discografia_total = 0;
    novo->recipe_total = 0.0;
    novo->num_albums_individual=0;

    // Inicialização do campo id_constituent usando a função `separa_String`
    if (dados.artist_id_constituent) {
        ArrayDin* constituent_list = separa_String(dados.artist_id_constituent);

        // Define o número de IDs constituintes e aloca o array
        novo->num_id_constituent = getADN(constituent_list);
        novo->id_constituent = malloc(novo->num_id_constituent * sizeof(char*));

        // Copia cada item do ArrayDin para o array de IDs
        for (int i = 0; i < novo->num_id_constituent; i++) {
            novo->id_constituent[i] = strdup(getADItem(constituent_list, i));
        }

        // Libera a memória do ArrayDin após a cópia
        apaga_ArrayDin(constituent_list, free);
    } else {
        novo->id_constituent = NULL;
        novo->num_id_constituent = 0;
    }

    return novo;
}

// Função para inicializar dados de artistas a partir de um arquivo CSV
Artist_Dados* iniciaArtists(const char* caminho_) {
    Artist_Dados* dados = malloc(sizeof(Artist_Dados));
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
    if (strstr(caminho_, "artists.csv") != NULL) {
        snprintf(caminho, sizeof(caminho), "%s", caminho_);
    } else {
        snprintf(caminho, sizeof(caminho), "%s/artists.csv", caminho_);
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

    struct stat st = {0};
    if (stat("resultados", &st) == -1) {
        mkdir("resultados", 0700);
    }

    // Tenta abrir o arquivo de erros em "resultados/artists_errors.csv"
    Ficheiro* erros = iniciaFicheiro("resultados/artists_errors.csv", "w+");
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
        char* string = lerLinha(ficheiro);

        if (!string) continue;

        string[strlen(string) - 1] = '\0';

        // Se a primeira linha for cabeçalho, salve-a no arquivo de erros
        if (i == 0) {
            escreveLinha(erros, string);
            free(string); 
            continue;
        }

        // Parse da linha CSV usando a função parse_csv_line
        int num_fields;
        char** fields = parse_csv_line(string, &num_fields);

        // Inicializa um Pre_Artists e usa o switch para atribuir os valores
        Pre_Artists pre_artist = {0};
        for (int j = 0; j < num_fields; j++) {
            switch (j) {
                case 0: pre_artist.artist_id = strdup(fields[j]); 
                remove_quotes(pre_artist.artist_id); break;
                case 1: pre_artist.artist_name = strdup(fields[j]); 
                remove_quotes(pre_artist.artist_name); break;
                case 2: //pre_artist.artist_description = strdup(fields[j]); 
                //remove_quotes(pre_artist.artist_description); break;
                case 3: pre_artist.artist_recipe_per_stream = strdup(fields[j]); 
                remove_quotes(pre_artist.artist_recipe_per_stream); break;
                case 4: pre_artist.artist_id_constituent = strdup(fields[j]); 
                remove_quotes(pre_artist.artist_id_constituent); break;
                case 5: pre_artist.artist_country = strdup(fields[j]); 
                remove_quotes(pre_artist.artist_country); break;
                case 6: pre_artist.artist_type = strdup(fields[j]); 
                remove_quotes(pre_artist.artist_type); break;
                default: break;
            }
        }

        dados->lidos++;

        if (artist_validation(pre_artist) == 1) {
            Artists* artist = PreArtists_para_Artist(pre_artist);
            insere_HashTable(artist->id, dados->HT, artist, &hashFunc);
            dados->succ++;
        } else {
            escreveLinha(erros, string);
            dados->fail++;
        }

        // Libera memória dos campos de Pre_Artists
        free(pre_artist.artist_id);
        free(pre_artist.artist_name);
        //free(pre_artist.artist_description);
        free(pre_artist.artist_recipe_per_stream);
        free(pre_artist.artist_id_constituent);
        free(pre_artist.artist_country);
        free(pre_artist.artist_type);

        // Libera a linha e os campos
        for (int j = 0; j < num_fields; j++) {
            free(fields[j]);
        }
        free(fields);
        free(string);
    }

    apagaFicheiro(ficheiro);
    apagaFicheiro(erros);

    return dados;
}
void apaga_Artist(void* artist_) {
    Artists* artist = artist_;
    free(artist->id);
    free(artist->name);
    //free(artist->description);
    free(artist->country);
    free(artist->type);

    // Libera cada ID em id_constituent
    if (artist->id_constituent) {
        for (int i = 0; i < artist->num_id_constituent; i++) {
            free(artist->id_constituent[i]);
        }
        free(artist->id_constituent);
    }

    free(artist);
}


// Função para liberar todos os dados de Artistas
void apagaDadosArtists(Artist_Dados* lista) {
    if (!lista) return;
    apagaHashTable(lista->HT, &apaga_Artist);
    free(lista);
}

void printArtist(void* a_) {
    Artists* a = a_;
    printf("Artist ID: %s\n", a->id);
    printf("Name: %s\n", a->name);
    //printf("Description: %s\n", a->description);
    printf("Recipe per stream: %f\n", a->recipe_per_stream);
    printf("Recipe Total: %f\n", a->recipe_total);

    // Impressão dos IDs constituintes
    printf("Constituent: ");
    if (a->id_constituent && a->num_id_constituent > 0) {
        for (int i = 0; i < a->num_id_constituent; i++) {
            printf("%s", a->id_constituent[i]);
            if (i < a->num_id_constituent - 1) {

            }
        }
    } else {
        printf("None");
    }
    printf("\n");

    printf("Country: %s\n", a->country);
    printf("Type: %s\n", a->type);
    printf("Discografia total: %d\n", a->discografia_total);
    printf("Num de albuns individual: %d\n", a->num_albums_individual);
    printf("\n");
}


// Função que imprime os dados dos Artistas
void printArtists(Artist_Dados* Artist, short modo) {
    if (!Artist) return;
    if (modo != 2) printHashTable(Artist->HT, &printArtist);
}
