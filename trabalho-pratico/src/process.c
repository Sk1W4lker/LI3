#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "process.h"
#include "hashtable.h"
#include "arraydin.h"
#include "queries.h"
#include "ficheiros.h"

#include "users.h"
#include "musics.h"
#include "artists.h"
#include <time.h>


//Função de parser para o ficheiro das queries
void lerQueries(const char* caminho, User_Dados* user_data, Music_Dados* music_data, Artist_Dados* artist_data, History_Dados* history_data, Albuns_Dados* albuns_data, bool testes, double *tempo_query1, double *tempo_query2, double *tempo_query3){
  // queries -> nome do ficheiro com as queries
  int lidos=0,succ=0,fail=0,unknown=0,result=0;

  Ficheiro* ficheiro=iniciaFicheiro(caminho,"r"); //Abre o ficheiro das queries

  if (!ficheiro) { //Se nao existe, as queries não acontecem

    result=0;

  }
  else { //Ficheiro existe

  result=1;

  int N_queries=LinhasFicheiro(ficheiro); //Numero de linhas para ler
  // Inicializa variáveis de tempo para cada querie
      *tempo_query1 = 0.0;
      *tempo_query2 = 0.0;
      *tempo_query3 = 0.0;

  for (int i=0;i<N_queries;i++) {

  char* string=lerLinha(ficheiro);

    if (strlen(string)==0) { //Se a linha está vazia, ignora-a e passa para a proxima linha
      free(string);
      continue;
    }

    lidos++;
    string[strlen(string)-1]='\0'; //Tirar o char especial

    char output_frase[1000];
    sprintf(output_frase,"resultados/command%d_output.txt",i+1); //criar o nome do ficheiro

    //printf("    Interpretando %03dº comando... ",(i+1));

     struct timespec start,end;
     double elapsed;
     clock_gettime(CLOCK_REALTIME,&start);

      ArrayDin* linha = interpretarQueries(string, user_data, music_data, artist_data, history_data, albuns_data, true); //Execução da query
    
      if (linha) { //Se o array dinamico existe, é porque alguma query foi executada

      int N_linha=getADN(linha);

      if (N_linha==0) { //Se nao tem elementos, aconteceu um erro na query
        fail++;
        //printf("(Erro)");
      }
      else { //Se há elementos, a query foi bem executada
        succ++;
        //printf("(Feito)");
      }

      }
      else unknown++; //Se o array dinamico nao existe, então nenhuma query foi executada
      
      clock_gettime(CLOCK_REALTIME, &end);
      elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
      if (i < 25) {
        *tempo_query1 += elapsed;
      } else if (i < 50) {
        *tempo_query2 += elapsed;
      } else {
        *tempo_query3 += elapsed;
      }
      if(testes==1)
      {
      //printf(" Tempo: %.6f seconds\n.",elapsed);
      }

      //printf("\n");

      escreveFicheiro(output_frase,linha); //Escreve o ficheiro
      if (linha) apaga_ADStrings(linha); //Se o array dinamico existe, apaga-o

      free(string);
  }
  }

  // |||||||||||||||||||||||||||||||||||||||||||||||||||||| RESULTADOS ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

      if (result==1) { //Se result é 1, é porque um ficheiro foi lido

      //printf("\n        Ficheiro %s encontrado\n",caminho);
      //printf("            Total de queries lidas: %d\n            Total de queries feitas: %d\n            Total de queries falhadas: %d\n            Total de queries desconhecidas: %d\n\n",lidos,succ,fail,unknown);

      }
      else { //Ficheiro nao foi encontrado
        //printf("        Ficheiro \"%s\" não existe\n\n",caminho);
      }

    apagaFicheiro(ficheiro); //Fecha o ficheiro das queries

    return;
}
