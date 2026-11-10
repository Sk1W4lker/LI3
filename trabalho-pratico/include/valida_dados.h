#ifndef VALIDA_DADOS_H
#define VALIDA_DADOS_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DATA_TAMANHO 10
#define HORA_TAMANHO 8


typedef struct dia Dia;
typedef struct hora Hora;

int data_validation(const char* data_aux);
Dia* quebraData(const char* data);
int calculaIdade(const char* birth_date);
void converteParaFormatoHora(int total_segundos, char* resultado);
int verifica_subscription_type(const char* subscription_type);
char* clean_string(char* str);
void remove_newlines(char* str);
void remove_quotes(char* str);


#endif // VALIDA_DADOS_H