#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/valida_dados.h"

typedef struct dia {
    short year;
    short month;
    short day;
} Dia;
typedef struct hora {
    short hour;
    short minute;
    short second;
} Hora;

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| VALIDA DIA DE NASCIMENTO  ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// Função de validação de data no formato "YYYY/MM/DD"
// Função de validação de data no formato "YYYY/MM/DD"
int data_validation(const char* data_aux) {
    // Verifica se a entrada é nula ou se o tamanho está incorreto
    if (!data_aux || strlen(data_aux) != DATA_TAMANHO) return 0;

    Dia* dia = quebraData(data_aux);  // Tenta criar a estrutura Dia
    if (!dia) return 0;

    // Valida o intervalo de ano, mês e dia
    if (dia->year < 1900 || dia->year > 2023 ||
        dia->month < 1 || dia->month > 12 ||
        dia->day < 1 || dia->day > 31) {
        //printf("Data fora do intervalo válido: \"%s\" (ano: %d, mês: %d, dia: %d)\n", data_aux, dia->year, dia->month, dia->day);
        free(dia);  // Libera a memória caso a data seja inválida
        return 0;
    }

    // Verificação adicional para garantir que a data seja menor que 31/10/2024
    if (dia->year > 2024 || (dia->year == 2024 && dia->month > 10) ||
        (dia->year == 2024 && dia->month == 10 && dia->day > 31)) {
        free(dia);
        return 0;
    }
    free(dia);
    return 1;  // Data é válida
}

// Função que cria uma estrutura Dia a partir de uma string no formato "YYYY/MM/DD"
Dia* quebraData(const char* data) {
    if (!data || strlen(data) != DATA_TAMANHO) return NULL;
    Dia* dia = malloc(sizeof(Dia));
    if (!dia) return NULL;
    char strings[3][5] = {{0}};
    int i = 0;
    char* copia = strdup(data);
    char* token = strtok(copia, "/");
    while (token && i < 3) {
        strncpy(strings[i++], token, 4);
        token = strtok(NULL, "/");
    }
    dia->year = (short)atoi(strings[0]);
    dia->month = (short)atoi(strings[1]);
    dia->day = (short)atoi(strings[2]);
    free(copia);
    return dia;
}
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| CONVERTE PARA HORAS  |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

// Função para converter a duração total da discografia para o formato hh:mm:ss
void converteParaFormatoHora(int total_segundos, char* resultado) {
    int horas = total_segundos / 3600;        // 1 hora = 3600 segundos
    int minutos = (total_segundos % 3600) / 60; // 1 minuto = 60 segundos
    int segundos = total_segundos % 60;      // Resto é os segundos

    // Formata a string no formato hh:mm:ss
    sprintf(resultado, "%02d:%02d:%02d", horas, minutos, segundos);
}
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| CALCULA IDADE  |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// Função para verificar o tipo de assinatura
int calculaIdade(const char* birth_date) {
    int ano_nascimento, mes_nascimento, dia_nascimento;
    int ano_atual = 2024, mes_atual = 9, dia_atual = 9;

    // Assume-se que a data está no formato YYYY-MM-DD
    sscanf(birth_date, "%d/%d/%d", &ano_nascimento, &mes_nascimento, &dia_nascimento);

    int idade = ano_atual - ano_nascimento;
    if (mes_atual < mes_nascimento || (mes_atual == mes_nascimento && dia_atual < dia_nascimento)) {
        idade--;
    }
    return idade;
}


int verifica_subscription_type(const char* subscription_type) {
    // Verifica se a entrada é nula
    if (!subscription_type) {
        //printf("O tipo de assinatura não pode ser nulo.\n");
        return 0; // Retorna 0 para inválido
    }
    // Compara a string fornecida com os tipos válidos
    if (strcmp(subscription_type, "normal") == 0 || strcmp(subscription_type, "premium") == 0) {
        return 1; // Retorna 1 para válido
    } else {
        //printf("Tipo de assinatura inválido: \"%s\". Deve ser 'normal' ou 'premium'.\n", subscription_type);
        return 0; // Retorna 0 para inválido
    }
}


void remove_newlines(char* str) {
    if (!str || strlen(str) == 0) return;

    size_t len = strlen(str);

    // Remove '\n' ou '\r' do final da string
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0';
        len--;
    }
}

void remove_quotes(char* str) {
    if (!str || strlen(str) == 0) return;

    size_t len = strlen(str);

    if (str[0] == '"') {
        memmove(str, str + 1, len);
        len--;
    }

    if (len > 0 && str[len - 1] == '"') {
        str[len - 1] = '\0';
    }

}