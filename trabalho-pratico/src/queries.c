#include "queries.h"
#include "arraydin.h"
#include "users.h"
#include "hashtable.h"




//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||   QUERY 1     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
void query1(ArrayDin* output, short tipo_output, char* id, User_Dados* Users, Artist_Dados* Artistas) {
    //printf("Processando ID: %s\n", id);

    if (id[0] == 'U') {
        // Caso seja um usuário
        if (getUserExiste(Users, id) == 1) {
            //printf("ID %s encontrado como Usuário.\n", id);

            char* user_email = getUserEmail(Users, id);
            char* user_firstname = getUserFirstName(Users, id);
            char* user_lastname = getUserLastName(Users, id);
            int user_age = getUserAge(Users, id);
            char* user_country = getUserCountry(Users, id);

            char linha[LinhaMax];
            if (tipo_output == 0) 
                sprintf(linha, "%s;%s;%s;%d;%s", user_email, user_firstname, user_lastname, user_age, user_country);
            else if (tipo_output == 1) 
                sprintf(linha, "%s=%s=%s=%d=%s", user_email, user_firstname, user_lastname, user_age, user_country);

            //printf("Dados formatados para inserção: %s\n", linha);

            free(user_email);
            free(user_firstname);
            free(user_lastname);
            free(user_country);

            inserir_ArrayDin(strdup(linha), output);
        } else {
            // Usuário não encontrado
            inserir_ArrayDin(strdup("\0"), output);
        }
    } else if (id[0] == 'A') {
        // Caso seja um artista
        Artists* artist = getArtistByID(Artistas, id); // Busca o artista pelo ID
        if (artist != NULL) {
            //printf("ID %s encontrado como Artista.\n", id);

            const char* artist_name = getArtistName(artist);
            const char* artist_type = getArtistType(artist);
            const char* artist_country = getArtistCountry(artist);
            int num_albums_individual = getArtistNumAlbumInd(artist);
            double total_recipe = getArtistRecipeTotal(artist);

            char linha[LinhaMax];
            if (tipo_output == 0) 
                sprintf(linha, "%s;%s;%s;%d;%.2f", artist_name, artist_type, artist_country, num_albums_individual, total_recipe);
            else if (tipo_output == 1) 
                sprintf(linha, "%s=%s=%s=%d=%.2f", artist_name, artist_type, artist_country, num_albums_individual, total_recipe);

            //printf("Dados formatados para inserção: %s\n", linha);

            inserir_ArrayDin(strdup(linha), output);
        } else {
            // Artista não encontrado
            inserir_ArrayDin(strdup("\0"), output);
        }
    } else {
        // Caso o ID não corresponda nem a usuário nem a artista
        inserir_ArrayDin(strdup("\0"), output);
    }
}


//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||   QUERY 2     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

// Função de comparação para ordenação dos artistas por duração da discografia (decrescente) e id (crescente)
int compara_artistas_por_discografia(const void* a, const void* b) {
    Artists* artist_a = *((Artists**)a);
    Artists* artist_b = *((Artists**)b);

    // Comparação pela duração total da discografia (decrescente)
    if (getArtistDiscografiaTotal(artist_a) != getArtistDiscografiaTotal(artist_b)) {
        return getArtistDiscografiaTotal(artist_b) - getArtistDiscografiaTotal(artist_a);  // Ordem decrescente
    }

    return strcmp(getArtistID(artist_a), getArtistID(artist_b));

    
    // Se houver empate, compara pelo id (crescente)
    return strcmp(getArtistID(artist_a), getArtistID(artist_b));
}

ArrayDin* query2(int N, const char* country, short tipo_output,Artist_Dados* dados_artistas, Music_Dados* dados_musicas) {
    ArrayDin* resultado = inicia_ArrayDin(N);  // Array Dinâmico para armazenar os resultados
    int contagem = 0;

    // Array de ponteiros para armazenar os artistas
    HashTable* artist_HT = getArtistHashTable(dados_artistas);
    Artists* artistas_array[getHTMax(*artist_HT)];
    int num_artistas = 0;

    // Itera sobre cada posição da tabela hash de artistas
   for (int i = 0; i < getHTMax(*artist_HT); i++) {
        HT_Item** lista = getHTLista(*artist_HT);
        HT_Item* item = lista[i];
        
        // Percorre a lista encadeada em cada posição da tabela
        while (item != NULL) {
        Artists* artist = (Artists*) getHTItemDado(item);  // Acessa os dados do artista

            // Se for um filtro de país, verifica se o país do artista corresponde
             if (country && strcmp(getArtistCountry(artist), country) != 0) {
                item = getHTItemProx(item);
                continue;
            }

            // Armazenar o artista no array de artistas
            artistas_array[num_artistas++] = artist;

            item = getHTItemProx(item);
        }
    }

    // Ordena os artistas pelo total da discografia e, em caso de empate, pelo ID
    qsort(artistas_array, num_artistas, sizeof(Artists*), compara_artistas_por_discografia);

    // Agora que os artistas estão ordenados, adicione-os ao resultado
    for (int i = 0; i < num_artistas && contagem < N; i++) {
        Artists* artist = artistas_array[i];

        // Calcular a duração total da discografia do artista
        int total_segundos = getArtistDiscografiaTotal(artist);

        // Cria a string que vai armazenar o formato hh:mm:ss
        char tempo_formatado[9]; // hh:mm:ss tem 8 caracteres + 1 para '\0'

        converteParaFormatoHora(total_segundos, tempo_formatado);  // Converte o tempo para o formato desejado

        // Insere o artista no resultado
        if (contagem < N) {
            // Insere nome, tipo, duração da discografia (no formato hh:mm:ss) e país no resultado
            char* artista_info = malloc(1000 * sizeof(char));  // Aloca memória para a string de resultado

            if (tipo_output == 0) sprintf(artista_info, "%s;%s;%s;%s", getArtistName(artist), getArtistType(artist), tempo_formatado, getArtistCountry(artist));
            else if (tipo_output == 1) sprintf(artista_info, "%s=%s=%s=%s", getArtistName(artist), getArtistType(artist), tempo_formatado, getArtistCountry(artist));

            inserir_ArrayDin(artista_info, resultado);  // Insere no ArrayDin
            contagem++;
        }
    }

    if (contagem == 0 && getADN(resultado) == 0) {
        inserir_ArrayDin(strdup("\0"), resultado);
    }

    return resultado;
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||   QUERY 3     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


// Função para liberar memória de inteiros (usada para apagaHashTable)
void libera_int(void* dado) {
    free((int*)dado);
}

// Função de comparação para qsort
int compara_generos(const void* a, const void* b) {
    Genero_Contador* gen_a = (Genero_Contador*)a;
    Genero_Contador* gen_b = (Genero_Contador*)b;

    if (getContador(gen_a) != getContador(gen_b)) {
        return getContador(gen_b) - getContador(gen_a);
    }
    return strcmp(getGenero(gen_a), getGenero(gen_b));
}


ArrayDin* query3(int min_age, int max_age, short tipo_output,User_Dados* dados_users, Music_Dados* dados_musicas) {
    ArrayDin* resultado = inicia_ArrayDin(10); // Inicia ArrayDin para o output
    int total_generos = 0;  // Para contar o número total de gêneros populares

    // HashTable para armazenar cada gênero e seu contador
    HashTable contador_generos = inicia_HashTable(10);

    // Percorre cada usuário na tabela hash de `dados_users`
HashTable* user_ht = getUserHashTable(dados_users);

for (int i = 0; i < getHTMax(*user_ht); i++) {
    HT_Item** lista = getHTLista(*user_ht);
    HT_Item* item = lista[i];

    while (item != NULL) {
        Users* user = (Users*)getHTItemDado(item);
        
       if (getUserAge(dados_users, getUserName(dados_users, getUserID(user))) >= min_age &&
            getUserAge(dados_users, getUserName(dados_users, getUserID(user))) <= max_age) {


           for (int j = 0; j < getUserNumGeneros(user); j++) {
                Genero_Contador* genero_contador = getUserGeneroContador(user, j);

                const char* genero = getGenero(genero_contador);
                int likes = getContador(genero_contador);

                int* contador_atual = (int*)getHTItem(genero, contador_generos, &hashFunc);
                if (contador_atual) {
                    *contador_atual += likes;
                } else {
                    int* novo_contador = malloc(sizeof(int));
                    *novo_contador = likes;
                    insere_HashTable(genero, contador_generos, novo_contador, &hashFunc);
                    total_generos++;
                }
            }
        }
        item = getHTItemProx(item);
    }
}


    // Converte a HashTable para um array para ordenação
Genero_Contador* array_generos = malloc(total_generos * getGeneroContadorSize());
    int index=0;
    for (int i = 0; i < getHTMax(contador_generos); i++) {
        HT_Item** lista = getHTLista(contador_generos);
        HT_Item* item = lista[i];
        while (item) {
            const char* genero = getHTItemId(item);
            int likes = *(int*)getHTItemDado(item);


        setGeneroPos(array_generos, index, total_generos, genero);
        setContadorPos(array_generos, index, total_generos, likes);
        index++;

            item = getHTItemProx(item);
        }
    }

    // Ordena o array de gêneros por popularidade e nome
    qsort(array_generos, total_generos, getGeneroContadorSize(), compara_generos);

    // Formata o resultado e insere no ArrayDin
    for (int i = 0; i < total_generos; i++) {
        char linha[LinhaMax];
        if (tipo_output == 0) sprintf(linha, "%s;%d", getGeneroPos (array_generos, i, total_generos), getContadorPos(array_generos, i, total_generos));
        else if (tipo_output == 1) sprintf(linha, "%s=%d", getGeneroPos (array_generos, i, total_generos), getContadorPos(array_generos, i, total_generos));
        inserir_ArrayDin(strdup(linha), resultado);
    }

    // Se nenhum dado foi adicionado, insere um valor nulo
if (getADN(resultado) == 0) {

    inserir_ArrayDin(strdup("\0"), resultado);
}

    // Limpeza de memória
    apagaHashTable(contador_generos, libera_int);
    free(array_generos);

    return resultado;
}

// Função que remove o primeiro char da string
void tiraChar(char* str) {   
    int i;
    int t = strlen(str);
    char* s = strdup(str);

    for (i = 0; i < t - 1; i++) {
        str[i] = s[i + 1];
    }
    str[t - 1] = '\0';
    free(s);
}

// Função que calcula o tamanho da string até o caractere especificado
int tamanho(char* s, char* c) {
    int i = 0;
    char c1 = *c;

    while (s[i] != '\0' && s[i] != c1) {
        i++;
    }
    return i;
}

// Função que devolve o argumento sem aspas
char* arg_semAspas(char* s, char* s2, char** nova_string) {
    int i = 0, h = 0, t = 0;
    char c = '\"';   
    tiraChar(s); // Remove o primeiro char da string (aspa)
    int t1 = tamanho(s, &c); // Tamanho da string até a segunda aspa
    char* str = malloc(t1 + 1); 
    
    while (s[i] != '\0' && s[i] != '"') {
        str[i] = s[i];
        i++;
    }
    str[i] = '\0';
    int g = strlen(s2) - strlen(s); // Posição onde começa o argumento
    for (h = g + i + 2; s2[h] != '\0'; h++) { 
        t++;
    }

    return str;
}

// Função que quebra a query e processa cada argumento
void quebraQuery(char* query, char args[MAX_LINHAS][MAX_COLUNAS], int* N) {
    char* arg = NULL;
    char* query2 = strdup(query);
    char* qAux = query2;
    char* copiaQuery = strdup(query);
    char* p;
    char* str;
   
    int l = 0;
    while ((arg = strsep(&query2, " ")) != NULL) {   
        if (arg[0] == '\"') {  
            p = strstr(copiaQuery, arg); // Obtém a string desde `arg`
            str = arg_semAspas(p, copiaQuery, &query2); // Retorna o argumento sem aspas
            strcpy(args[l], str); // Guarda na matriz
            free(str);      
        } else {
            strcpy(args[l], arg);
        }
        l++;
    } 
    *N = l;
    free(copiaQuery);
    free(qAux);
}

int processaIdQuery(char* query, short int* tipo_output) {
    // Verifica se a string é nula ou vazia
    if (query == NULL || strlen(query) == 0) {
        //printf("Erro: Query vazia ou nula em processaIdQuery.\n");
        return -1; // Retorna um ID inválido
    }

    // Verifica se o primeiro caractere é um número entre '1' e '5'
    if (query[0] >= '1' && query[0] <= '5') {
        int id_query = query[0] - '0'; // Converte o caractere para inteiro

        // Garante que há pelo menos dois caracteres antes de acessar query[1]
        if (strlen(query) > 1) {
            // Verifica se o segundo caractere é 'S'
            if (query[1] == 'S') { // Certifica-se de que não há mais caracteres após 'S'
                *tipo_output = 1; // Ativa o tipo de saída especial
            } else {
                //printf("Erro: Query contém caracteres inválidos após o número inicial.\n");
                return -1; // Query inválida
            }
        }

        return id_query; // Retorna o ID da query
    }

    // Se o primeiro caractere não for um número válido
    //printf("Erro: Query deve começar com um número entre 1 e 5.\n");
    return -1;
}


// Função de interpretação das queries
ArrayDin* interpretarQueries(char* query, User_Dados* Users, Music_Dados* Musics, Artist_Dados* Artists, History_Dados* History, Albuns_Dados* Albuns, bool batch) {
    char args[MAX_LINHAS][MAX_COLUNAS]; // Matriz para guardar argumentos

    // Inicia o array colocando todos os chars como '\0'
    for (int i = 0; i < MAX_LINHAS; i++) args[i][0] = '\0';

    int N_query = 0; // Indica quantos argumentos existem
    char* copiaQuery = strdup(query); // Realiza uma cópia da query
    quebraQuery(copiaQuery, args, &N_query); // Quebra a string e coloca cada argumento no array de strings "args"
    ArrayDin* output = inicia_ArrayDin(1); // Inicia o array dinâmico onde vamos inserir o output

    short tipo_output = 0; // Número que indica se a query tem a flag 'F'
    char id_query = processaIdQuery(args[0], &tipo_output); // Indica qual o número da query a ser realizada
    
    switch (id_query) {
        case 1: // Query 1
            query1(output, tipo_output, args[1], Users, Artists);
            if (batch == true) //printf("(Query 01) ");
            break;
        
        case 2: // Query 2
            // Para a Query 2, precisa passar os parâmetros: N, country, dados_artistas e dados_musicas
            int N = atoi(args[1]); // Converte o argumento N para inteiro
            const char* country = (args[2][0] != '\0') ? args[2] : NULL; // Se country não for vazio, usa como parâmetro
            
            output = query2(N, country,tipo_output, Artists, Musics); // Chama query2 passando os parâmetros necessários

            if (batch == true) //printf("(Query 02) ");
            break;

        case 3:
            // Parâmetros: min_age e max_age
            int min_age = atoi(args[1]);
            int max_age = atoi(args[2]);
            output =query3(min_age, max_age,tipo_output, Users, Musics);
            if (batch == true) //printf("(Query 03) ");
            break;


        default: // Query inválida ou não feita
            apaga_ADStrings(output);  
            output = NULL; // Define-o como NULL
            if (batch == true) //printf("(\?\?\?) ");
            break;
    }
    free(copiaQuery);

        return output;
    
}
