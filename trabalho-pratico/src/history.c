#include "history.h"


typedef struct pre_dados_history {
    char* history_history_id;
    char* history_user_id;
    char* history_music_id;
    char* history_timestamp;
    char* history_duration;
    char* history_platform;
} Pre_Historys;

// Estrutura para armazenar informações de cada usuário individual
typedef struct dados_historys {
    char* history_id;
    char* user_id;
    char* music_id;
    char* timestamp;
    char* duration;
    char* platform;
} historys;

// Estrutura para armazenar todos os usuários e informações adicionais
typedef struct historys {
    HashTable HT;
    char resultado;
    int lidos;
    int succ;
    int fail;
} History_Dados;

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     GET'S     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

//Obter o resultado do User Dados
int getHistoryDadosResultado(History_Dados* lista) {
    return lista->resultado;
}

// Verifica se um histórico existe na HashTable
int getHistoryExiste(History_Dados* HTH, const char* history_id) {
    historys* history = getHTItem(history_id, HTH->HT, &hashFunc);
    return history != NULL; // Retorna 1 se existe, 0 caso contrário
}

// Obtém o ID do usuário do histórico
char* getHistoryUserId(History_Dados* HTH, const char* history_id) {
    historys* history = getHTItem(history_id, HTH->HT, &hashFunc);
    return history ? strdup(history->user_id) : NULL;
}

// Obtém o ID da música do histórico
char* getHistoryMusicId(History_Dados* HTH, const char* history_id) {
    historys* history = getHTItem(history_id, HTH->HT, &hashFunc);
    return history ? strdup(history->music_id) : NULL;
}

// Obtém o timestamp do histórico
char* getHistoryTimestamp(History_Dados* HTH, const char* history_id) {
    historys* history = getHTItem(history_id, HTH->HT, &hashFunc);
    return history ? strdup(history->timestamp) : NULL;
}

// Obtém a duração do histórico
char* getHistoryDuration(History_Dados* HTH, const char* history_id) {
    historys* history = getHTItem(history_id, HTH->HT, &hashFunc);
    return history ? strdup(history->duration) : NULL;
}

// Obtém a plataforma do histórico
char* getHistoryPlatform(History_Dados* HTH, const char* history_id) {
    historys* history = getHTItem(history_id, HTH->HT, &hashFunc);
    return history ? strdup(history->platform) : NULL;
}


//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     SET'S     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

// Define o ID do usuário no histórico
void defineHistoryUserId(const char* history_id, const char* user_id, History_Dados* HTH) {
    if (!getHistoryExiste(HTH, history_id)) return; // Histórico não existe

    historys* history = getHTItem(history_id, HTH->HT, &hashFunc);
    free(history->user_id);
    history->user_id = strdup(user_id);
}

// Define o ID da música no histórico
void defineHistoryMusicId(const char* history_id, const char* music_id, History_Dados* HTH) {
    if (!getHistoryExiste(HTH, history_id)) return; // Histórico não existe

    historys* history = getHTItem(history_id, HTH->HT, &hashFunc);
    free(history->music_id);
    history->music_id = strdup(music_id);
}

// Define o timestamp do histórico
void defineHistoryTimestamp(const char* history_id, const char* timestamp, History_Dados* HTH) {
    if (!getHistoryExiste(HTH, history_id)) return; // Histórico não existe

    historys* history = getHTItem(history_id, HTH->HT, &hashFunc);
    free(history->timestamp);
    history->timestamp = strdup(timestamp);
}

// Define a duração do histórico
void defineHistoryDuration(const char* history_id, const char* duration, History_Dados* HTH) {
    if (!getHistoryExiste(HTH, history_id)) return; // Histórico não existe

    historys* history = getHTItem(history_id, HTH->HT, &hashFunc);
    free(history->duration);
    history->duration = strdup(duration);
}

// Define a plataforma no histórico
void defineHistoryPlatform(const char* history_id, const char* platform, History_Dados* HTH) {
    if (!getHistoryExiste(HTH, history_id)) return; // Histórico não existe

    historys* history = getHTItem(history_id, HTH->HT, &hashFunc);
    free(history->platform);
    history->platform = strdup(platform);
}

//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||    
//||||||||||||||||||||||||||||||||||  FUNÇOES     |||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

// Função que verifica se um Pre-Historys é válido
int history_validation(Pre_Historys history) {
    // Verificação de campos obrigatórios
    if (history.history_history_id == NULL) {
        //printf("Falha na validação: history_id é NULL\n");
        return 0;
    }
    if (history.history_user_id == NULL) {
        //printf("Falha na validação: user_id é NULL\n");
        return 0;
    }
    if (history.history_music_id == NULL) {
        //printf("Falha na validação: music_id é NULL\n");
        return 0;
    }
    if (history.history_timestamp == NULL) {
        //printf("Falha na validação: timestamp é NULL\n");
        return 0;
    }

    // Validação do formato da duração (HH:MM:SS)
    if (history.history_duration) {
        // Verifica o comprimento da string (HH:MM:SS tem exatamente 8 caracteres)
        if (strlen(history.history_duration) != 8 || 
            history.history_duration[2] != ':' || 
            history.history_duration[5] != ':') {
            return 0;
        }

        // Verificação detalhada de cada componente
        int hours, minutes, seconds;
        int count = sscanf(history.history_duration, "%2d:%2d:%2d", &hours, &minutes, &seconds);
        
        if (count != 3 || hours < 0 || minutes < 0 || minutes >= 60 || seconds < 0 || seconds >= 60) {
            return 0;
        }
    } else {
        //printf("Falha na validação: music_duration é NULL\n");
        return 0;
    }

    if (history.history_platform == NULL || (!((strcasecmp(history.history_platform, "mobile") == 0)|| (strcasecmp(history.history_platform, "desktop") == 0)))) {
        //printf("Falha na validação: platform é NULL\n");
        return 0;
    }

    return 1; // Válido
}

// Função para inicializar os históricos
History_Dados* iniciaHistory(const char* caminho_, Artist_Dados* artists, Music_Dados* musics) {
    History_Dados* dados = malloc(sizeof(History_Dados));
    if (!dados) return NULL;

    dados->lidos = 0;
    dados->succ = 0;
    dados->fail = 0;
    dados->resultado = 1;

    if (!caminho_) {
        dados->HT = inicia_HashTable(1);
        dados->resultado = 0;
        return dados;
    }

    // Verifica se caminho_ já é o próprio arquivo ou precisa de uma extensão
    char caminho[1000];
    if (strstr(caminho_, "history.csv") != NULL) {
        snprintf(caminho, sizeof(caminho), "%s", caminho_);
    } else {
        snprintf(caminho, sizeof(caminho), "%s/history.csv", caminho_);
    }

    Ficheiro* ficheiro = iniciaFicheiro(caminho, "r");
    if (!ficheiro) {
        dados->HT = inicia_HashTable(1);
        dados->resultado = 0;
        return dados;
    }


    // Tenta abrir o arquivo de erros em "resultados/history_errors.csv"
    Ficheiro* erros = iniciaFicheiro("resultados/history_errors.csv", "w+");
    if (!erros) {
        //printf("Erro ao abrir ou criar o arquivo de erros.\n");
        apagaFicheiro(ficheiro);
        dados->resultado = 0;
        dados->HT = inicia_HashTable(1);
        return dados;
    }

    int numLinhas = LinhasFicheiro(ficheiro);
    dados->HT = inicia_HashTable(numLinhas - 1);

    for (int i = 0; i < numLinhas; i++) {
        char* linha = lerLinha(ficheiro);
        if (!linha) continue;

        char* linhaOriginal = strdup(linha); 
        remove_newlines(linhaOriginal);         
        Pre_Historys preHistory = {0};
        char* token;
        int j = 0;
        char* linhaAux = linha;

        while ((token = strsep(&linha, ";")) != NULL) {
            remove_newlines(token);
            switch (j) {
                case 0: preHistory.history_history_id = strdup(token); remove_quotes(preHistory.history_history_id);break;
                case 1: preHistory.history_user_id = strdup(token); remove_quotes(preHistory.history_user_id);break;
                case 2: preHistory.history_music_id = strdup(token); remove_quotes(preHistory.history_music_id) ;break;
                case 3: preHistory.history_timestamp = strdup(token); remove_quotes(preHistory.history_timestamp) ;break;
                case 4: preHistory.history_duration = strdup(token); remove_quotes(preHistory.history_duration) ;break;
                case 5: preHistory.history_platform = strdup(token); remove_quotes(preHistory.history_platform) ;break;
            }
            j++;
        }

        dados->lidos++;

        if (history_validation(preHistory) == 1) { // Validação do histórico
            historys* novoHistory = preHistoryParaHistory(preHistory, artists, musics); // Converte Pre_Historys para historys
            insere_HashTable(novoHistory->history_id, dados->HT, novoHistory, &hashFunc); // Insere na tabela hash
            dados->succ++;
        } else {
            escreveLinha(erros, linhaOriginal); // Escreve no arquivo de erros
            dados->fail++;
        }

        free(linhaAux);
    }

    apagaFicheiro(ficheiro);
    apagaFicheiro(erros);
    return dados;
}

// Converte Pre_Historys para historys
historys* preHistoryParaHistory(Pre_Historys pre, Artist_Dados* artists, Music_Dados* musics) {
    historys* novo = malloc(sizeof(historys));
    if (!novo) return NULL;
    novo->history_id = strdup(pre.history_history_id);
    novo->user_id = strdup(pre.history_user_id);
    novo->music_id = strdup(pre.history_music_id);
    novo->timestamp = strdup(pre.history_timestamp);
    novo->duration = strdup(pre.history_duration);
    novo->platform = strdup(pre.history_platform);
    
    int num_artist = getNumArtists(musics, novo->music_id);
    char** artists_ids= getMusicArtistIDs (musics, novo->music_id, &num_artist);
    for (int i = 0; i < num_artist; i++) {
        Artists* artist = getArtistByID(artists, artists_ids[i]); // Obtenha o ponteiro para o artista
    if (artist) {
        double artist_recipe = getArtistRecipePerStream(artists, artists_ids[i]);
        if (strcasecmp("group", getArtistType(artist)) == 0) { //strcasecmp compara strings ingorando as maiusculas e minusculas
            int num_constituent = getArtistNumConstituent(artist);
            char* constituents = getArtistConstituent(artists, artists_ids[i]); 
            double recipe_per_artist = ((double)artist_recipe / (double)num_constituent);
            if (constituents) {
                // Dividir a string de constituintes em IDs individuais
                char* constituent_id = strtok(constituents, ",");
                while (constituent_id != NULL) {
                    // Processar cada constituinte
                    Artists* constituent_artist = getArtistByID(artists, constituent_id);
                    if (constituent_artist) {
                        double total_recipe_before = getArtistRecipeTotal(constituent_artist);
                        double total_recipe_after = total_recipe_before + recipe_per_artist;
                        setArtistRecipeTotal(artists, constituent_id, total_recipe_after);
                    }
                    // Ir para o próximo constituinte
                    constituent_id = strtok(NULL, ",");
                }
                free(constituents); // Liberar a memória alocada para os constituintes
        }
    }
        // Lógica para o artista principal
        double total_recipe_before = getArtistRecipeTotal(artist);
        double total_recipe_after = total_recipe_before + artist_recipe;
        setArtistRecipeTotal(artists, artists_ids[i], total_recipe_after);
    }
    }
    for (int i = 0; i < num_artist; i++) {
    free(artists_ids[i]);
    }
    free(artists_ids);

    free(pre.history_history_id);
    free(pre.history_user_id);
    free(pre.history_music_id);
    free(pre.history_timestamp);
    free(pre.history_duration);
    free(pre.history_platform);

    return novo;
}

// Apaga um único histórico
void apagaHistory(void* history_) {
    historys* history = (historys*)history_;
    if (!history) return;

    free(history->history_id);
    free(history->user_id);
    free(history->music_id);
    free(history->timestamp);
    free(history->duration);
    free(history->platform);
    free(history);
}

// Apaga todos os históricos e a HashTable
void apagaDadosHistories(History_Dados* history_data) {
    if (!history_data) return;

    apagaHashTable(history_data->HT, &apagaHistory);
    free(history_data);
}

// Imprime um único histórico
void printHistory(void* history_) {
    historys* history = (historys*)history_;
    if (!history) return;

    printf("History ID: %s\n", history->history_id);
    printf("User ID: %s\n", history->user_id);
    printf("Music ID: %s\n", history->music_id);
    printf("Timestamp: %s\n", history->timestamp);
    printf("Duration: %s\n", history->duration);
    printf("Platform: %s\n", history->platform);
    printf("\n");
}

// Imprime todos os históricos
void printHistories(History_Dados* history_data) {
    if (!history_data) return;

    printHashTable(history_data->HT, &printHistory);
}