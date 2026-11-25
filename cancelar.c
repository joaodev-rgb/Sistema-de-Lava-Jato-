#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "agendamentos.h"
#include "login.h"
#include "funcoes.h"
#define AGENDAR "agendamentos.txt"
#define CANCELADO "cancelados.txt"
#define TEMP "temporario.txt"


static char lendo[256];
static char placa_cancelado[9];
static short int excluido = 0; 



void cabecalho_cancelados(void){

    FILE *arq = fopen(CANCELADO, "r"); 
 
       if (arq == NULL){
          arq = fopen(CANCELADO, "w"); 
       if (arq == NULL){
          printf("Erro ai tentar criar arquivo.\n");
          return; 
          }    
            fprintf(arq, "Placa;Ano-modelo;Servico;Cliente;Data;Hora;Desconto;Valor;Status;Atendente;Cpf-atendente\n"); 
          }  
         fclose(arq);  
}  
void servico_cancelados(void){

    cabecalho_cancelados();
    
    FILE *arq = fopen(AGENDAR, "r");
    FILE *temp = fopen(TEMP, "w"); 
    FILE *arc = fopen(CANCELADO, "a"); 
       if(arq == NULL || arc == NULL || temp == NULL ){
            printf("Erro ao abrir o arquivo.\n"); 
         if (arq != NULL){fclose(arq);}
         if (temp != NULL){fclose(temp);}
         if (arc != NULL){fclose(arc);}
         return;
        } 
            printf("Placa:\n"); 
              fgets(placa_cancelado, sizeof(placa_cancelado), stdin);
               placa_cancelado[strcspn(placa_cancelado, "\n")] = '\0'; 

              fgets(leitura, sizeof(leitura), arq); 
              fputs(leitura, temp); 

           while(fscanf(arq, " %9[^;\r\n];%9[^;\r\n];%49[^;\r\n];%49[^;\r\n];%19[^;\r\n];%7[^;\r\n];%f;%f;%49[^;\r\n];%99[^;\r\n];%14[^;\r\n]",
                          &placa_temp,
                          &anomodelo_temp,
                          &servico_temp,
                          &cliente_temp,
                          &data_temp,
                          &hora_temp, 
                          &desconto_temp, 
                          &valor_temp, 
                          &status_temp, 
                          &nomeatendente, 
                          &CPF) == 11){
           
             if(strcmp(placa_cancelado, placa_temp) == 0){
                    
                   printf("Altere o status para cancelado.\n");
                    fgets(status_temp, sizeof(status_temp), stdin);
                      status_temp[strcspn(status_temp, "\r""\n")] = '\0'; 

                   fprintf(arc, " %s;%s;%s;%s;%s;%s;%.2f;%.2f;%s;%s;%s\n", 
                                  placa_temp, 
                                  anomodelo_temp, 
                                  servico_temp, 
                                  cliente_temp, 
                                  data_temp, 
                                  hora_temp, 
                                  desconto_temp, 
                                  valor_temp, 
                                  status_temp, 
                                  nomeatendente, 
                                  CPF);  
                   fclose(arc);               
                   break;                
                } 
              rewind(arq); 
            
              if(strcspn(placa_cancelado, placa_temp) == 0){
                excluido = 1; 
                }
            }      

        fclose(arq);
        fclose(temp);

        if (excluido == 1){
          remove(AGENDAR);
          rename(TEMP, AGENDAR);
          printf("Servico cancelado.\n"); 
           } else {
             remove(TEMP);
              printf("Nao foi posivel alterar\n"); 
            }
}
      