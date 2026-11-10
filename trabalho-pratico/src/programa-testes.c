#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/resource.h>
#include "../include/users.h"
#include "../include/artists.h"
#include "../include/valida_dados.h"
#include "../include/musics.h"
#include "../include/ficheiros.h"
#include "../include/queries.h"
#include "../include/arraydin.h"
#include "../include/process.h"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Uso: %s <diretório-dataset> <arquivo-queries> <diretório-outputs>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *dataset_dir = argv[1];
    const char *caminho_queries = argv[2];
    const char *output_dir = argv[3];

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


    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    bool testes = true;
    
    // Variáveis para acumular o tempo dos três blocos de queries
    double total_tempo_query1 = 0.0;
    double total_tempo_query2 = 0.0;
    double total_tempo_query3 = 0.0;

    // Executa as queries e calcula o tempo de cada bloco de 25 queries
    lerQueries(caminho_queries, user_data, music_data, artist_data, history_data, albuns_data, testes, &total_tempo_query1, &total_tempo_query2, &total_tempo_query3);

    clock_gettime(CLOCK_REALTIME, &end);
    double tempo_execucao_total = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    int linhas_corretas = 0;
    int linhas_erradas = 0;

    // Realiza a comparação dos resultados
    for (int i = 1; i <= 75; i++) {
        char query_output[1024];
        char query_expected[1024];
        snprintf(query_output, sizeof(query_output), "resultados/command%d_output.txt", i);
        snprintf(query_expected, sizeof(query_expected), "%scommand%d_output.txt", output_dir, i);

        compararResultados(query_output, query_expected, i, &linhas_corretas, &linhas_erradas);
    }

    // Calcula a média de tempo para cada grupo de 25 queries
    double media_tempo_query1 = total_tempo_query1 / 25;
    double media_tempo_query2 = total_tempo_query2 / 25;
    double media_tempo_query3 = total_tempo_query3 / 25;

    printf("\nMédia de tempo para a querie 1: %.6f segundos\n", media_tempo_query1);
    printf("Média de tempo para a querie 2: %.6f segundos\n", media_tempo_query2);
    printf("Média de tempo para a querie 3: %.6f segundos\n", media_tempo_query3);
    printf("Tempo total de execução: %.6f segundos\n", tempo_execucao_total);

    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Uso de memória: %ld KB\n", r_usage.ru_maxrss);

    printf("Linhas corretas: %d\n", linhas_corretas);
    printf("Linhas incorretas: %d\n", linhas_erradas);

    apagaDadosUsers(user_data);
    apagaDadosArtists(artist_data);
    apagaDadosMusics(music_data);

    printf("Programa-testes executado com sucesso.\n");

    return EXIT_SUCCESS;
}