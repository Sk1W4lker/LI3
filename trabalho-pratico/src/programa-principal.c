#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../include/users.h"
#include "../include/artists.h"
#include "../include/valida_dados.h"
#include "../include/musics.h"
#include "../include/ficheiros.h"
#include "../include/queries.h"   // Agora usa a declaração de `lerQueries` a partir deste cabeçalho
#include "../include/arraydin.h"
#include "../include/process.h"
#include "../include/history.h"
#include "../include/albuns.h"

int main(int argc, char *argv[]) {
    // Verifica se o número correto de argumentos foi passado
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <diretório-dataset> <arquivo-queries>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Obtém os caminhos a partir dos argumentos
    const char *dataset_dir = argv[1];
    const char *caminho_queries = argv[2];

    // Inicializa os dados dos artistas
    Artist_Dados* artist_data = iniciaArtists(dataset_dir);
        if (getArtistDadosResultado(artist_data) == 0) {
        perror("Erro ao carregar os dados dos artistas");
        return EXIT_FAILURE;
    }
    Albuns_Dados* albuns_data = iniciaAlbuns(dataset_dir, artist_data);
    if (getAlbunsDadosResultado(albuns_data) == 0) {
        perror("Erro ao carregar os dados de usuários");
        return EXIT_FAILURE;
    }
    // Inicializa os dados das músicas
     
    Music_Dados* music_data = iniciaMusics(dataset_dir, artist_data, albuns_data);
    if (getMusicDadosResultado(music_data) == 0) {
        perror("Erro ao carregar os dados das músicas");
        return EXIT_FAILURE;
    }

    User_Dados* user_data = iniciaUsers(dataset_dir, music_data);
    if (getUserDadosResultado(user_data) == 0) {
        perror("Erro ao carregar os dados de usuários");
        return EXIT_FAILURE;
    }

    History_Dados* history_data = iniciaHistory(dataset_dir, artist_data, music_data);
    if (getHistoryDadosResultado(history_data) == 0) {
        perror("Erro ao carregar os dados de usuários");
        return EXIT_FAILURE;
    }




    if (getArtistDadosFail(artist_data) > 0) {
    //printf("Erros encontrados nos dados dos artistas. Consulte 'resultados/artists_errors.csv'\n");
    }
    if (getMusicDadosFail(music_data) > 0) {
    //printf("Erros encontrados nos dados das músicas. Consulte 'resultados/musics_errors.csv'\n");
    }
    if (getUserDadosFail(user_data) > 0) {
    //printf("Erros encontrados nos dados dos usuários. Consulte 'resultados/users_errors.csv'\n");
    }
    bool testes = true;
    double num_testes = 0.0; // necessário para o programa de testes
    // Chama a função lerQueries para processar o arquivo de queries
    lerQueries(caminho_queries, user_data, music_data, artist_data,history_data, albuns_data, testes,&num_testes,&num_testes,&num_testes);

    //printf("Dados dos artistas:\n");
    //printArtists(artist_data,0);
    //printf("Dados das músicas:\n");
    //printMusics(music_data,0);
    //printf("Dados dos Users:\n");
    //printUsers(user_data,0);
    //printf("Dados do history:\n");
    //printHistories(history_data);
    //printf("Dados dos Albuns:\n");
    //printAlbuns (albuns_data);
    

    // Libera a memória alocada
//printf("Liberando dados dos usuários...\n");
apagaDadosUsers(user_data);

//printf("Liberando dados dos artistas...\n");
apagaDadosArtists(artist_data);

//printf("Liberando dados das músicas...\n");
apagaDadosMusics(music_data);

//printf("Liberando dados das histórias...\n");
apagaDadosHistories(history_data);

//printf("Liberando dados dos álbuns...\n");
apagaDadosAlbuns(albuns_data);

    //printf("\nPrograma executado com sucesso\n");

    return EXIT_SUCCESS;
}
