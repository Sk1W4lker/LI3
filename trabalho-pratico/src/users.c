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
#include "users.h"

#include "ficheiros.h"

// Estrutura para armazenar informações temporárias dos pré-usuários
typedef struct pre_dados_users {
    char* user_user_id;
    char* user_email;
    char* user_first_name;
    char* user_last_name;
    char* user_birth_date;
    char* user_idade;
    char* user_country;
    char* user_subscription_type;
    char* user_liked_musics_id;
} Pre_Users;

typedef struct genero_contador {
    char* genero;
    int contador; 
} Genero_Contador;

// Estrutura para armazenar informações de cada usuário individual
typedef struct dados_users {
    char* user_id;
    char* username;
    char* email;
    char* first_name;
    char* last_name;
    char* birth_date;
    char idade;
    char* country;
    char* subscription_type;
    ArrayDin* liked_musics_id;
    int num_liked_musics;
    Genero_Contador* genero_contadores; 
    int num_generos;
} Users;

// Estrutura para armazenar todos os usuários e informações adicionais
typedef struct users {
    HashTable HT;
    char resultado;
    int lidos;
    int succ;
    int fail;
} User_Dados;

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     GET'S     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

int getUserExiste(User_Dados* HTU, const char* user_id) {
    // Tenta obter o usuário da tabela hash
    Users* user = getHTItem(user_id, HTU->HT, &hashFunc);
    
    // Se o usuário for encontrado, retorna 1 (existe)
    if (user != NULL) {
        return 1; // Usuário existe
    }
    
    // Se não encontrado, retorna 0 (não existe)
    return 0; // Usuário não existe
}

const char* getUserID(const Users* user) {
    if (user == NULL) {
        return NULL;
    }
    return user->user_id;
}


//Obtem Nome do User
char* getUserName(User_Dados* HT, const char* s) {
    Users* user= getHTItem(s,HT->HT,&hashFunc);
    return strdup(user->user_id);
}

//Obtem Nome do User
char* getUserEmail(User_Dados* HT, const char* s) {
    Users* user= getHTItem(s,HT->HT,&hashFunc);
    return strdup(user->email);
}

//Obtem o primeiro nome
char* getUserFirstName(User_Dados* HT, const char* s) {
    Users* user= getHTItem(s,HT->HT,&hashFunc);
    return strdup(user->first_name);
}

//Obtem o ultimo nome
char* getUserLastName(User_Dados* HT, const char* s) {
    Users* user= getHTItem(s,HT->HT,&hashFunc);
    return strdup(user->last_name);
}

//Obtem a data de nascimento
char* getUserDate(User_Dados* HT, const char* s) {
    Users* user= getHTItem(s,HT->HT,&hashFunc);
    return strdup(user->birth_date);
}

//Obtem a idade 
int getUserAge(User_Dados* HT, const char* s) {
    Users* user= getHTItem(s,HT->HT,&hashFunc);
    return (int) user->idade;
}

//Obtem o pais
char* getUserCountry(User_Dados* HT, const char* s) {
    Users* user= getHTItem(s,HT->HT,&hashFunc);
    return strdup(user->country);
}

//Obtem a subscrição
char* getUserSubscription(User_Dados* HT, const char* s) {
    Users* user= getHTItem(s,HT->HT,&hashFunc);
    return strdup(user->subscription_type);
}

//Obter o resultado do User Dados
int getUserDadosResultado(User_Dados* lista) {
    return lista->resultado;
}

//Obter os dados lidos do User Dados
int getUserDadosLidos(User_Dados* lista) {
    return lista->lidos;
}

//Obter os dados incorporados do User Dados
int getUserDadosSucc(User_Dados* lista) {
    return lista->succ;
}

//Obter os dados rejeitados do User Dados
int getUserDadosFail(User_Dados* lista) {
    return lista->fail;
}

int getUserNumGeneros(const Users* user) {
    if (user == NULL) {
        return 0;
    }
    return user->num_generos;
}

const char* getGenero(const Genero_Contador* genero_contador) {
    if (genero_contador == NULL) {
        return NULL;
    }
    return genero_contador->genero;
}

// Getter para o gênero em uma posição específica
char* getGeneroPos(Genero_Contador* genero_contadores, int indice, int num_generos) {
    if (genero_contadores == NULL || indice < 0 || indice >= num_generos) {
        return NULL; // Verificação de limites e validação
    }
    return genero_contadores[indice].genero;
}

int getContador(const Genero_Contador* genero_contador) {
    if (genero_contador == NULL) {
        return 0;
    }
    return genero_contador->contador;
}

// Getter para o contador em uma posição específica
int getContadorPos(Genero_Contador* genero_contadores, int indice, int num_generos) {
    if (genero_contadores == NULL || indice < 0 || indice >= num_generos) {
        return -1; // Valor de erro
    }
    return genero_contadores[indice].contador;
}

void setGeneroContador(Genero_Contador* genero_contador, const char* genero, int contador) {
    if (genero_contador == NULL) {
        return;
    }
    free(genero_contador->genero);  // Libera a memória anterior
    genero_contador->genero = strdup(genero);  // Define o novo gênero
    genero_contador->contador = contador;  // Define o novo contador
}

HashTable* getUserHashTable(User_Dados* user_dados) {
    return &user_dados->HT;
}

Genero_Contador* getUserGeneroContador(const Users* user, int index) {
    if (user == NULL || index < 0 || index >= user->num_generos) {
        return NULL;
    }
    return &user->genero_contadores[index];
}

size_t getGeneroContadorSize() {
    return sizeof(Genero_Contador);
}

void setGeneroContadorGenero(Genero_Contador* contador, const char* genero){
    contador->genero = strdup(genero);
}

// Setter para o gênero em uma posição específica
void setGeneroPos(Genero_Contador* genero_contadores, int indice, int num_generos, const char* genero) {
    if (genero_contadores == NULL || indice < 0 || indice >= num_generos) {
        return; // Validação: Não faz nada em caso de erro
    }
    // Libera a string antiga (se necessário) e atualiza o gênero
    genero_contadores[indice].genero = strdup(genero); // Duplica a string para evitar problemas com ponteiros
}

void setGeneroContadorValor(Genero_Contador* contador, int valor){
    contador->contador = valor;
}

// Setter para o contador em uma posição específica
void setContadorPos(Genero_Contador* genero_contadores, int indice, int num_generos, int contador) {
    if (genero_contadores == NULL || indice < 0 || indice >= num_generos) {
        return; // Validação: Não faz nada em caso de erro
    }
    genero_contadores[indice].contador = contador;
}

Genero_Contador* criaGeneroContador(const char* genero, int contador) {
    Genero_Contador* novo = malloc(sizeof(Genero_Contador));
    if (!novo) return NULL;
    novo->genero = strdup(genero);
    novo->contador = contador;
    return novo;
}

void apagaGeneroContador(Genero_Contador* contador) {
    if (!contador) return;
    free(contador->genero);
    free(contador);
}


//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     SET'S     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

// Função que define o nome de usuário
void defineUsername(const char* user_, const char* username, User_Dados* HTU) {
    if (getUserExiste(HTU, user_) == 0) return; // Usuário não existe

    Users* user = getHTItem(user_, HTU->HT, &hashFunc);
    free(user->user_id);
    user->user_id = strdup(username);
}

// Função que define o email
void defineEmail(const char* user_, const char* email, User_Dados* HTU) {
    if (getUserExiste(HTU, user_) == 0) return; // Usuário não existe

    Users* user = getHTItem(user_, HTU->HT, &hashFunc);
    free(user->email);
    user->email = strdup(email);
}

// Função que define o primeiro nome
void defineFirstName(const char* user_, const char* first_name, User_Dados* HTU) {
    if (getUserExiste(HTU, user_) == 0) return; // Usuário não existe

    Users* user = getHTItem(user_, HTU->HT, &hashFunc);
    free(user->first_name);
    user->first_name = strdup(first_name);
}

// Função que define o último nome
void defineLastName(const char* user_, const char* last_name, User_Dados* HTU) {
    if (getUserExiste(HTU, user_) == 0) return; // Usuário não existe

    Users* user = getHTItem(user_, HTU->HT, &hashFunc);
    free(user->last_name);
    user->last_name = strdup(last_name);
}

// Função que define a data de nascimento
void defineBirthDate(const char* user_, const char* birth_date, User_Dados* HTU) {
    if (getUserExiste(HTU, user_) == 0) return; // Usuário não existe
    Users* novo = malloc(sizeof(Users));

    Users* user = getHTItem(user_, HTU->HT, &hashFunc);
    free(user->birth_date);
    user->birth_date = strdup(birth_date);
    user->idade = calculaIdade(novo->birth_date); // Recalcula a idade ao definir nova data de nascimento
}

// Função que define o país
void defineCountry(const char* user_, const char* country, User_Dados* HTU) {
    if (getUserExiste(HTU, user_) == 0) return; // Usuário não existe

    Users* user = getHTItem(user_, HTU->HT, &hashFunc);
    free(user->country);
    user->country = strdup(country);
}

// Função que define o tipo de subscrição
void defineSubscriptionType(const char* user_, const char* subscription_type, User_Dados* HTU) {
    if (getUserExiste(HTU, user_) == 0) return; // Usuário não existe

    Users* user = getHTItem(user_, HTU->HT, &hashFunc);
    free(user->subscription_type);
    user->subscription_type = strdup(subscription_type);
}

void setGenero(Genero_Contador* genero, const char* novo_genero) {
    free(genero->genero);
    genero->genero = strdup(novo_genero);
}

void setContador(Genero_Contador* genero, int novo_contador) {
    genero->contador = novo_contador;
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     Funções    |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

int user_validation(Pre_Users users) {
    // Verificação de campos obrigatórios
    if (users.user_user_id == NULL) {
        return 0;
    }
    if (users.user_email == NULL) {
        return 0;
    }
    if (users.user_birth_date == NULL) {
        return 0;
    }

    // Remover aspas da data de nascimento, se presentes
    remove_quotes(users.user_birth_date);

    // Verificação das datas
    // Validação do formato da data de nascimento
    if (data_validation(users.user_birth_date) == 0) return 0;

    // Verificação do formato do e-mail
    char* user_email = strdup(users.user_email);
    if (user_email == NULL) return 0;  // Verifica se a alocação ocorreu corretamente
    char* user_email2 = user_email;

    // Divide o email em partes: username, domain e subdomínio
    char* username = strsep(&user_email, "@");
    char* domain = strsep(&user_email, ".");
    char* subdomain = user_email;

    int valid = 1;

    // Validar se o username contém apenas caracteres [a-z0-9]
    if (!username || strlen(username) == 0) {
        valid = 0;
    } else {
        for (int i = 0; username[i] != '\0'; i++) {
            if (!(isalnum(username[i]) && (isalpha(username[i]) ? islower(username[i]) : 1))) {
                valid = 0;
                break;
            }
        }
    }

    // Verificar domínio e subdomínio
    if (valid && (!domain || strlen(domain) == 0 || !subdomain || strlen(subdomain) < 2 || strlen(subdomain) > 3)) {
        valid = 0;
    } else if (valid) {
        // Validar caracteres de domínio (lstring e rstring)
        for (int i = 0; domain[i] != '\0'; i++) {
            if (!isalpha(domain[i]) || !islower(domain[i])) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            for (int i = 0; subdomain[i] != '\0'; i++) {
                if (!isalpha(subdomain[i]) || !islower(subdomain[i])) {
                    valid = 0;
                    break;
                }
            }
        }
    }

    free(user_email2);

    // Verificação do tipo de assinatura
    if (valid && !verifica_subscription_type(users.user_subscription_type)) {
        valid = 0;
    }
    if (users.user_liked_musics_id == NULL) {
        return 0;
    }
    size_t liked_musics_len = strlen(users.user_liked_musics_id);
    if (liked_musics_len < 2 || users.user_liked_musics_id[0] != '[' || users.user_liked_musics_id[liked_musics_len - 1] != ']') {
        //printf("Falha na validação: formato de liked_musics_id inválido para %s\n", users.user_liked_musics_id);
        return 0;
    }

    return valid;
}


// Cria um 'Users' com base nos dados trazidos pelo parser dos users
Users* PreUser_para_User(Pre_Users dados, Music_Dados* musics) {
    Users* novo = malloc(sizeof(Users));
    if (!novo) return NULL;

    // Copia os dados de 'Pre_Users' para a estrutura 'Users'
    novo->user_id = strdup(dados.user_user_id);
    novo->email = strdup(dados.user_email);
    novo->first_name = strdup(dados.user_first_name);
    novo->last_name = strdup(dados.user_last_name);
    novo->birth_date = dados.user_birth_date ? strdup(dados.user_birth_date) : NULL;
    novo->idade = (novo->birth_date) ? calculaIdade(novo->birth_date) : -1;
    novo->country = strdup(dados.user_country);
    novo->subscription_type = strdup(dados.user_subscription_type);

    // Inicializa lista liked_musics_id
    ArrayDin* liked_music_ids = separa_String(dados.user_liked_musics_id);
    novo->liked_musics_id = inicia_ArrayDin(getADN(liked_music_ids));


    // Inicializa contador de gêneros
    novo->genero_contadores = NULL;
    novo->num_generos = 0;

    // Copia cada music_id para liked_musics_id e processa gêneros
    for (int i = 0; i < getADN(liked_music_ids); i++) {
        char* music_id = (char*)getADItem(liked_music_ids, i);
        inserir_ArrayDin(strdup(music_id), novo->liked_musics_id);

        // Verifica se a música existe no sistema e obtém o gênero
        HashTable* music_HT = getMusicHashTable(musics);
        Musics* musica = getHTItem(music_id, *music_HT, &hashFunc);

        if (!musica) {
            // Música não existe, limpa memória alocada e retorna NULL
            apaga_Users(novo); // Chama apaga_Users para liberar toda a memória alocada
            apaga_ArrayDin(liked_music_ids, free); // Libera array temporário
            return NULL;
        }
        const char* musica_genre = getMusicGenre(musics, music_id); 
        // Atualiza contadores de gêneros
        int found = 0;
        for (int j = 0; j < novo->num_generos; j++) {
            if (strcmp(novo->genero_contadores[j].genero, musica_genre) == 0) {
                novo->genero_contadores[j].contador++;
                found = 1;
                break;
            }
        }
        if (!found) {
            novo->genero_contadores = realloc(novo->genero_contadores, sizeof(Genero_Contador) * (novo->num_generos + 1)); // Linha da perda da memoria
            novo->genero_contadores[novo->num_generos].genero = strdup(musica_genre);
            novo->genero_contadores[novo->num_generos].contador = 1;
            novo->num_generos++;
        }
    }

    // Libera array temporário
    apaga_ArrayDin(liked_music_ids, free);

    return novo;
}


// Função que coleta todos os dados dos users, processa-os e preenche a hash table de users
User_Dados* iniciaUsers(const char* caminho_, Music_Dados* musics) {
    User_Dados* dados = malloc(sizeof(User_Dados));
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
    if (strstr(caminho_, "users.csv") != NULL) {
        snprintf(caminho, sizeof(caminho), "%s", caminho_);
    } else {
        snprintf(caminho, sizeof(caminho), "%s/users.csv", caminho_);
    }

    // Tenta abrir o arquivo de dados
    Ficheiro* ficheiro = iniciaFicheiro(caminho, "r");
    if (!ficheiro) {
        //printf("Erro: arquivo %s não encontrado\n", caminho);
        dados->resultado = 0;
        dados->HT = inicia_HashTable(1);
        return dados;
    }

    // Cria o diretório "Resultados" se ele não existir
    struct stat st = {0};
    if (stat("resultados", &st) == -1) {
        mkdir("resultados", 0700);
    }

    // Tenta abrir o arquivo de erros em "resultados/users_errors.csv"
    Ficheiro* erros = iniciaFicheiro("resultados/users_errors.csv", "w+");
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

        Pre_Users pre_user = {0};
        char* token = NULL;
        char* string_aux = string;

        while ((token = strsep(&string, ";")) != NULL) {
            switch (j) {
        case 0: 
            pre_user.user_user_id = strdup(token); 
            remove_quotes(pre_user.user_user_id);  // Remove aspas do user_id
            break;
        case 1: 
            pre_user.user_email = strdup(token); 
            remove_quotes(pre_user.user_email);   // Remove aspas do email
            break;
        case 2: 
            pre_user.user_first_name = strdup(token); 
            remove_quotes(pre_user.user_first_name);  // Remove aspas do primeiro nome
            break;
        case 3: 
            pre_user.user_last_name = strdup(token); 
            remove_quotes(pre_user.user_last_name);   // Remove aspas do último nome
            break;
        case 4: 
            pre_user.user_birth_date = strdup(token); 
            remove_quotes(pre_user.user_birth_date);  // Remove aspas da data de nascimento
            break;
        case 5: 
            pre_user.user_country = strdup(token); 
            remove_quotes(pre_user.user_country);  // Remove aspas do país
            break;
        case 6: 
            pre_user.user_subscription_type = strdup(token); 
            remove_quotes(pre_user.user_subscription_type);  // Remove aspas do tipo de subscrição
            break;
        case 7: 
            pre_user.user_liked_musics_id = strdup(token); 
            remove_quotes(pre_user.user_liked_musics_id);  // Remove aspas dos IDs das músicas
            break;
        default: 
            break;

            }
            j++;
        }

        dados->lidos++;

        // Validação e inserção
        if (user_validation(pre_user) == 1) {
            Users* user = PreUser_para_User(pre_user, musics);
            if (user) {
                insere_HashTable(user->user_id, dados->HT, user, &hashFunc);
                dados->succ++;
            } else {
                //printf("Falha ao criar usuário para ID: %s\n", pre_user.user_user_id);
                escreveLinha(erros, string_copia);
                dados->fail++;
            }
        } else {
            escreveLinha(erros, string_copia);
            dados->fail++;
        }

        // Liberação de memória
        free(pre_user.user_user_id);
        free(pre_user.user_email);
        free(pre_user.user_first_name);
        free(pre_user.user_last_name);
        free(pre_user.user_birth_date);
        free(pre_user.user_country);
        free(pre_user.user_subscription_type);
        free(pre_user.user_liked_musics_id);

        free(string_aux);
        free(string_copia);
    }

    apagaFicheiro(ficheiro);
    apagaFicheiro(erros);

    return dados;
}


//Funçaõ que apaga o array dinamico dos Users
void apaga_Users(void* user_) {
    Users* user = (Users*)user_;
    if (!user) return;

    // Liberar strings somente se os ponteiros não forem nulos
    if (user->user_id) free(user->user_id);
    if (user->email) free(user->email);
    if (user->first_name) free(user->first_name);
    if (user->last_name) free(user->last_name);
    if (user->birth_date) free(user->birth_date);
    if (user->country) free(user->country);
    if (user->subscription_type) free(user->subscription_type);

    // Liberar array dinâmico liked_musics_id, se não for nulo
    if (user->liked_musics_id) {
        apaga_ArrayDin(user->liked_musics_id, free); // Libera o conteúdo de liked_musics_id
    }

    free(user);  // Libera a estrutura `user`
}


//Função que apaga a Hash Table de Users
void apagaDadosUsers(User_Dados* lista) {
    if (!lista) return;
    apagaHashTable(lista->HT,&apaga_Users);
    free(lista);
}

// Função que imprime um User (só para testes)
void printUser(void* a_) {
    Users* a = (Users*)a_;

    // Imprime as informações do usuário
    printf("User ID: %s\n", a->user_id);
    printf("Email: %s\n", a->email);
    printf("First Name: %s\n", a->first_name);
    printf("Last Name: %s\n", a->last_name);
    printf("Birth Date: %s\n", a->birth_date ? a->birth_date : "N/A");
    printf("Idade: %d\n", a->idade);
    printf("Country: %s\n", a->country);
    printf("Subscription Type: %s\n", a->subscription_type);

    // Imprime as músicas curtidas pelo usuário
    printf("Liked Musics:\n");
    for (int i = 0; i < getADN(a->liked_musics_id); i++) {
    printf("  - Music %d: %s\n", i + 1, (char*)getADItem(a->liked_musics_id, i));
    }

    // Imprime os gêneros e contadores
    printf("Generos Favoritos:\n");
    for (int i = 0; i < a->num_generos; i++) {
        printf("  - Genero: %s, Contadores: %d\n", a->genero_contadores[i].genero, a->genero_contadores[i].contador);
    }

    printf("\n");
}


//Função que imprime os dados dos Users
void printUsers(User_Dados* User, short modo) {
//  modo:  0 -> tudo  |  1 -> só users   |  2 -> user_q9  

    if (!User) return;

    if (modo!=2) printHashTable(User->HT,&printUser);
}