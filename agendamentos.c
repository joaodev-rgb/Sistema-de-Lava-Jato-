#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define AGENDAR "agendamentos.txt"
#include "agendamentos.h"
#include "login.h"

char ler[256];
int j;

 Agendar agendar;

void cabecalhoa_agendamentos(void){
  FILE *arq = fopen(AGENDAR, "r"); 
 
      if (arq == NULL){
          arq = fopen(AGENDAR, "w"); 
      if (arq == NULL){
        printf("Erro ai tentar criar arquivo.\n");
        return; 
      }    

            fprintf(arq, "Placa;ano-modelo;Servico;Cliente;data-entrega;hora;status;atendente;cpf-atendente\n"); 
      }
      fclose(arq);  
      }  




void agendamentos(void){
         
     cabecalhoa_agendamentos();

     FILE *arc = fopen(AGENDAR, "a");
        
          if (arc == NULL){
            printf("Erro ao abrir o arquivo.\n");
            return; 
          }

           for (j = 0; j < 1; j++){

             printf("Placa do veiculo:\n");
              fgets(agendar[j].placa, sizeof(agendar[j].placa), stdin);
                agendar[j].placa[strcspn(agendar[j].placa, "\r" "\n")] = '\0'; 
            
             printf("Ano do Modelo:\n");
              fgets(agendar[j].ano_modelo, sizeof(agendar[j].ano_modelo), stdin);
                agendar[j].ano_modelo[strcspn(agendar[j].ano_modelo, "\r", "\n")] = '\0'; 
                
             printf("Tipo de servico:\n");
             printf("1-Lavagem Simples:\n"
                    "2-Lavagem Detalhada:\n"
                    "3-");




             }

  

}