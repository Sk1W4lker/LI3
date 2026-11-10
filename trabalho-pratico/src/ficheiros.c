#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ficheiros.h"
#include "arraydin.h"
#include <stdbool.h>

typedef struct ficheiro {
    FILE* ficheiro;
} Ficheiro;

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     GET'S     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

//Função que indica quantas linhas um ficheiro tem
int LinhasFicheiro(Ficheiro* fich) {

    if (!fich) return 0;

    int linhas=0;

    char* line= NULL;
    size_t read,len;
 
 while((read = getline(&line, &len,fich->ficheiro)) != -1) linhas++;
   free(line);

    rewind(fich->ficheiro); //retorna para o inicio do ficheiro

   return linhas;
}

//Função que escreve linhas num ficheiro
void escreveLinha(Ficheiro* fich,const char* string) {

    if (!fich) return;

    fprintf(fich->ficheiro,"%s\n",string);

} 

//Função que lê linha por linha
char* lerLinha(Ficheiro* fich) {

    if (!fich) return NULL;

    char string[2048];

    if (fgets(string, 2048, fich->ficheiro) != NULL) { //lè linha

        char* linha=string;
        return strdup(linha); //se ha linha, devolve essa linha
    } 
    else return NULL; //se nao ha linhas, devolve NULL
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     SET'S     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


//Função que cria um ficheiro
Ficheiro* iniciaFicheiro(const char* nome,const char* modo) {
    FILE* ficheiro=fopen(nome,modo);
    if (!ficheiro) return NULL;

    Ficheiro* novo=malloc(sizeof(Ficheiro));
    novo->ficheiro=ficheiro;
    return novo;
}

//Função que apaga e fecha um ficheiro
void apagaFicheiro(Ficheiro* fich) {

    if (!fich) return;

    if (fich->ficheiro) fclose(fich->ficheiro);
    free(fich);
}


//Função que escreve um ficheiro a partir de um array
int escreveFicheiro(const char* nome_ficheiro, ArrayDin* lista) {

    FILE* ficheiro= fopen(nome_ficheiro, "w+");

    if (!ficheiro) return 0;
    else if (lista) {

        int N=getADN(lista);
        for (int i=0;i<N;i++) {
            char* linha=getADItem(lista,i);
            fprintf(ficheiro,"%s\n",linha);
        }
    }

    fclose(ficheiro);
    return 1;
}

ArrayDin* separa_String (const char* s) {
    if (s==NULL)
        return NULL;
    ArrayDin* lista = inicia_ArrayDin(1);
    int flag = -1;
    //   -1 -> ignorar  |  1 -> copiar
    int i = 0;
    char string[1024];
    string[0]='\0'; //Fazer com que a string seja vazia
    //Enquanto houver chars
    while (*s != '\0') {
        //Se o char for '
        if (*s == '\'') {
            flag*=-1; //Trocar a flag
            if (i > 0) { //Já houve coisas copiadas para a string
                string[i]='\0'; //Para termos uma string correta
                inserir_ArrayDin(strdup(string),lista); //Adicionamos ao array dinámico
                string[0]='\0'; //Resetamos a string
                i=0;
            }
        }
        //O char é diferente de '
        else {
            //Devemos copiar chars
            if (flag == 1) {
                string[i] = *s;
                i++;
            }
        }
        s++; //Avança na string-argumento
    }
    return lista;
}

void compararResultados(const char *output_file, const char *expected_file, int num_teste, int *corretos, int *erros) {
    Ficheiro *output = iniciaFicheiro(output_file, "r");
    Ficheiro *expected = iniciaFicheiro(expected_file, "r");

    if (!output || !expected) {
        fprintf(stderr, "Erro ao abrir arquivos %s ou %s para comparação.\n", output_file, expected_file);
        if (output) apagaFicheiro(output);
        if (expected) apagaFicheiro(expected);
        return;
    }

    int linha_num = 1;
    bool match = true;
    char *linha_output = NULL;
    char *linha_expected = NULL;

    while ((linha_output = lerLinha(output)) && (linha_expected = lerLinha(expected))) {
        if (strcmp(linha_output, linha_expected) != 0) {
            fprintf(stderr, "Incongruência no teste %d na linha %d.\n", num_teste, linha_num);
            match = false;
            (*erros)++;
            break;
        }
        linha_num++;
        (*corretos)++;
        free(linha_output);
        free(linha_expected);
        linha_output = NULL;
        linha_expected = NULL;
    }

    if (output) apagaFicheiro(output);
    if (expected) apagaFicheiro(expected);

    if (match) {
        //printf("Teste %d: Todos os resultados corretos.\n", num_teste);
    }
}

char** parse_csv_line(const char* line, int* num_fields) {
    int field_count = 0;
    int capacity = 10;
    char** fields = malloc(capacity * sizeof(char*));
    const char* start = line;
    bool in_quotes = false;

    // Aloca memória inicial para cada campo e percorre a linha
    for (const char* ptr = line; *ptr; ptr++) {
        if (*ptr == '\"') {
            in_quotes = !in_quotes; // Toggle de aspas
        } else if (*ptr == ';' && !in_quotes) { // Detecta delimitador fora das aspas
            size_t len = ptr - start;
            fields[field_count] = malloc(len + 1);
            strncpy(fields[field_count], start, len);
            fields[field_count][len] = '\0';
            field_count++;

            if (field_count >= capacity) { // Expande a capacidade conforme necessário
                capacity += 10;
                fields = realloc(fields, capacity * sizeof(char*));
            }
            start = ptr + 1;
        }
    }

    // Último campo (se existir)
    if (*start) {
        size_t len = strlen(start);
        fields[field_count] = malloc(len + 1);
        strncpy(fields[field_count], start, len);
        fields[field_count][len] = '\0';
        field_count++;
    }

    *num_fields = field_count;
    return fields;
}