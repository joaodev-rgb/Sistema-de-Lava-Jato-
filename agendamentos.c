#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define AGENDAR "agendamentos.txt"
#define SERVICOS "servicos.txt"
#include "agendamentos.h"
#include "login.h"
#include "funcoes.h"
#include "servicos.h"


 Agendar agendar;
 char ver[256];
 float auxiliar; 

void cabecalhoa_agendamentos(void){
  FILE *arq = fopen(AGENDAR, "r"); 
 
      if (arq == NULL){
          arq = fopen(AGENDAR, "w"); 
      if (arq == NULL){
        printf("Erro ai tentar criar arquivo.\n");
        return; 
      }    

            fprintf(arq, "Placa;Ano-modelo;Servico;Cliente;Data;Hora;Desconto;Valor;Status;Atendente;Cpf-atendente\n"); 
      }
      fclose(arq);  
      }  




void agendamentos(void){
         
     cabecalhoa_agendamentos();

     FILE *arc = fopen(AGENDAR, "a");
     FILE *arq = fopen(SERVICOS, "r"); 
        
          if (arc == NULL || arq == NULL){
            printf("Erro ao abrir o arquivo.\n");
          }

           for (int j = 0; j < 1; j++){

             printf("Placa do veiculo:\n");
              fgets(agendar[j].placa, sizeof(agendar[j].placa), stdin);
                agendar[j].placa[strcspn(agendar[j].placa, "\r""\n")] = '\0'; 
            
             printf("Ano do Modelo:\n");
              fgets(agendar[j].ano_modelo, sizeof(agendar[j].ano_modelo), stdin);
                agendar[j].ano_modelo[strcspn(agendar[j].ano_modelo, "\r""\n")] = '\0'; 
                
              printf("Qual o servico:\n\n\n");
              
               fgets(ver, sizeof(ver), arq);

            printf("\n%-10s||%-40s||%-10s||%-10s||%-15s\n", "ID", "Servico", "Valor", "desconto", "Tempo");
            printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");

             while(fscanf(arq, " %d;%49[^;\r\n];%f;%f;%9[^;\r\n]", &id_temp, &tipo_temp, &valor_temp, &desconto_temp, &tempo_temp) == 5) {
              printf("%-10d  %-40s %-11.2f %-11.2f %s\n", id_temp, tipo_temp, valor_temp, desconto_temp, tempo_temp);
             }
            printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
            
              rewind(arq); //<- Volta para o incio do arquivo. 

              scanf(" %d", &id_r); 
               limpar_buffer();

               fgets(ver, sizeof(ver), arq); 
             
              while(fscanf(arq, " %d;%49[^;\r\n];%f;%f;%9[^;\r\n]", &id_temp, &tipo_temp, &valor_temp, &desconto_temp, &tempo_temp) == 5){
                    if( id_r == id_temp){
                     strcpy(agendar[j].servico, tipo_temp); 
                    }
              }

              printf("Cliente:\n");
               fgets(agendar[j].cliente, sizeof(agendar[j].cliente), stdin);
                agendar[j].cliente[strcspn(agendar[j].cliente, "\r""\n")] = '\0'; 
              
              printf("Data de entrada:\n");
               fgets(agendar[j].data, sizeof(agendar[j].data), stdin);
                agendar[j].data[strcspn(agendar[j].data, "\r""\n")] = '\0';   

              printf("Horario de entrega:\n");
               fgets(agendar[j].hora, sizeof(agendar[j].hora), stdin);
                agendar[j].hora[strcspn(agendar[j].hora, "\r""\n")] = '\0'; 

               // Condição de desconto 
              if(desconto_temp == 0){
                printf("Desconto:\n");
               scanf(" %f", &agendar[j].descont);
                limpar_buffer(); 
              } else {
                agendar[j].descont = desconto_temp;
              }
          
           if (agendar[j].descont == 0){
                agendar[j].valor = valor_temp; 
           } else {
              
                 auxiliar = (valor_temp * (agendar[j].descont / 100)); 
                 agendar[j].valor = (valor_temp - auxiliar);
           }   

            printf("Status:\n");
             fgets(agendar[j].status, sizeof(agendar[j].status), stdin);      
                agendar[j].status[strcspn(agendar[j].status, "\r""\n")] = '\0'; 

                //opção de confirmar, antes de salvar
                

                  

                 







             }

  

}