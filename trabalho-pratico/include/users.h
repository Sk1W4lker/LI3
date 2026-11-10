#ifndef USERS_H
#define USERS_H

#include "arraydin.h"
#include "hashtable.h"
#include "musics.h"

// Estrutura para armazenar informações temporárias dos pré-usuários
typedef struct pre_dados_users Pre_Users;

typedef struct genero_contador Genero_Contador;

// Estrutura para armazenar informações de cada usuário individual
typedef struct dados_users Users;

// Estrutura para armazenar todos os usuários e informações adicionais
typedef struct users User_Dados;
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     GET'S     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

int getUserExiste(User_Dados* HTU, const char* user_id);
char* getUserName(User_Dados* HT, const char* s);
char* getUserEmail(User_Dados* HT, const char* s);
char* getUserFirstName(User_Dados* HT, const char* s);
char* getUserLastName(User_Dados* HT, const char* s);
char* getUserDate(User_Dados* HT, const char* s);
int getUserAge(User_Dados* HT, const char* s);
char* getUserCountry(User_Dados* HT, const char* s);
char* getUserSubscription(User_Dados* HT, const char* s);
const char* getUserID(const Users* user);
size_t getGeneroContadorSize();
Genero_Contador* criaGeneroContador(const char* genero, int contador);
void apagaGeneroContador(Genero_Contador* contador);


int getUserDadosResultado(User_Dados* lista);
int getUserDadosLidos(User_Dados* lista);
int getUserDadosSucc(User_Dados* lista);
int getUserDadosFail(User_Dados* lista);
const char* getGenero(const Genero_Contador* genero);
char* getGeneroPos(Genero_Contador* genero_contadores, int indice, int num_generos);
int getContador(const Genero_Contador* genero);
int getContadorPos(Genero_Contador* genero_contadores, int indice, int num_generos);
int getUserNumGeneros(const Users* user);
Genero_Contador* getUserGeneroContador(const Users* user, int index);
HashTable* getUserHashTable(User_Dados* user_dados);



void setGeneroContador(Genero_Contador* genero_contador, const char* genero, int contador);


//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||   Setters    |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

void defineUsername(const char* user_, const char* username, User_Dados* HTU);
void defineEmail(const char* user_, const char* email, User_Dados* HTU);
void defineFirstName(const char* user_, const char* first_name, User_Dados* HTU);
void defineLastName(const char* user_, const char* last_name, User_Dados* HTU);
void defineBirthDate(const char* user_, const char* birth_date, User_Dados* HTU);
void defineCountry(const char* user_, const char* country, User_Dados* HTU);
void defineSubscriptionType(const char* user_, const char* subscription_type, User_Dados* HTU);
void setGeneroContadorGenero(Genero_Contador* contador, const char* genero);
void setGeneroPos(Genero_Contador* genero_contadores, int indice, int num_generos, const char* genero);
void setGeneroContadorValor(Genero_Contador* contador, int valor);
void setContadorPos(Genero_Contador* genero_contadores, int indice, int num_generos, int contador);

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     Funções    |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

int user_validation(Pre_Users users);
Users* PreUser_para_User(Pre_Users dados, Music_Dados* musics);
User_Dados* iniciaUsers(const char* caminho_, Music_Dados* musics);
void apaga_Users(void* user_);
void apagaDadosUsers(User_Dados* lista);
void printUser(void* a_);
void printUsers(User_Dados* User, short modo);

#endif // USERS_H