#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "servicos.h"
#include "funcoes.h"
#define SERVICOS "servicos.txt"
#define SERVTEMP "arqtemposerv.txt"


Configurar config; 
int id_r;
int id_temp;
char op, op_s; 
float valor_temp;
float desconto_temp;
char tipo_temp[50];
char tempo_temp[10];
char listar[256];



void cabecalho_servicos(void){
  FILE *arq = fopen(SERVICOS, "r"); 
 
      if (arq == NULL){
          arq = fopen(SERVICOS, "w"); 
      if (arq == NULL){
        printf("Erro ai tentar criar arquivo.\n");
        return; 
      }    

            fprintf(arq, " Id;Tipo;Valor;Desconto;Tempo\n"); 
      }
      fclose(arq);  
      }  


 void tipo_servicos(void){
    
   cabecalho_servicos(); 

    FILE *arc = fopen(SERVICOS, "a");
       if (arc == NULL){
            printf("Erro ao abrir o arquivo.\n");
            return;
       }

          for(int i = 0; i < 50; i++){
            
             printf("Indice:\n");
               scanf(" %d", &config[i].id);
                 limpar_buffer(); 
          
             printf("Tipo:\n"); 
              fgets(config[i].tipo, sizeof(config[i].tipo), stdin);
                config[i].tipo[strcspn(config[i].tipo, "\r""\n")] = '\0';
             
             printf("Valor:\n");
               scanf(" %f", &config[i].valor);
                limpar_buffer();

             printf("Desconto:\n");
                scanf(" %f", &config[i].desconto);
                  limpar_buffer();
           
             printf("Tempo:\n");
               fgets(config[i].tempo, sizeof(config[i].tempo), stdin);
                config[i].tempo[strcspn(config[i].tempo, "\r""\n")] = '\0';

              fprintf(arc, " %d;%s;%.2f;%.2f;%s\n", config[i].id, config[i].tipo, config[i].valor, config[i].desconto, config[i].tempo);  
              fflush(arc); 

              printf("Novo cadastro?\nDigite 's' -Sim.\nDigite 'n' -Nao.\n");
                scanf(" %c", &op);
                  limpar_buffer();

                op_s = tolower(op); 
              
                if ( op_s != 's'){
                  break;
                }
          
           }
           fclose(arc);
 }     


  void atualizar_servicos(void){
    
    short int atualizado = 0;   
    
    FILE *arq = fopen(SERVICOS, "r"); 
    FILE *temp = fopen(SERVTEMP, "w");

     if(arq == NULL || temp == NULL){
      printf("Erro ao abrir o arquivo.\n"); 
      if (arq != NULL){fclose(arq);}
      if (temp != NULL){fclose(temp);}
     }

     printf("Qual o indice:\n"); 
      scanf(" %d", &id_r);
       limpar_buffer(); 

    
         fgets(listar, sizeof(listar), arq); 
         fputs(listar, temp); 

      while(fscanf(arq, " %d;%49[^;\r\n];%f;%f;%9[^;\r\n]", &id_temp, &tipo_temp, &valor_temp, &desconto_temp, &tempo_temp) == 5){
                if(id_r == id_temp){
                  printf("Cadastro encontrado.\n");

                        printf("%d\n%s\n%.2f\n%.2f\n%s\n", id_temp, tipo_temp, valor_temp, desconto_temp, tempo_temp); 
                            
                        printf("Tipo do servico:\n");
                         fgets(tipo_temp, sizeof(tipo_temp), stdin);
                           tipo_temp[strcspn(tipo_temp, "\r""\n")] = '\0';
                           
                          printf("Valor:\n");
                           scanf(" %f", &valor_temp); 
                            limpar_buffer(); 

                       

                         printf("Desconto:\n"); 
                          scanf(" %f", &desconto_temp);
                            limpar_buffer();

                         printf("Tempo estimado:\n");
                          fgets(tempo_temp, sizeof(tempo_temp), stdin); 
                           tempo_temp[strcspn(tempo_temp, "\r""\n")] = '\0';    
                           

      
                   fprintf(temp,"%d;%s;%.2f;%.2f;%s\n", id_temp, tipo_temp, valor_temp, desconto_temp, tempo_temp);
                   atualizado = 1; 
                } else {
                   fprintf(temp,"%d;%s;%.2f;%.2f;%s\n", id_temp, tipo_temp, valor_temp, desconto_temp, tempo_temp);
                 }
       }
        fclose(arq);
        fclose(temp);

         if(atualizado == 1){
           remove(SERVICOS);
           rename(SERVTEMP, SERVICOS);
           printf("Cadastro atualizado com sucesso.\n");
         } else {
            remove(SERVTEMP);
            printf("Indice: %d nao encontrado \n", id_r);
         }


 }

 void excluir_servico(void){

  short int excluido = 0; 

     FILE *arq = fopen(SERVICOS, "r");
     FILE *temp = fopen(SERVTEMP, "w"); 

       if(arq == NULL || temp == NULL){
            printf("Erro ao abrir o arquivo.\n"); 
         if (arq != NULL){fclose(arq);}
         if (temp != NULL){fclose(temp);}
        } 

         

         printf("Indice:\n");
            scanf(" %d", &id_r);
             limpar_buffer();
              
        fgets(listar, sizeof(listar), arq); 
        fputs(listar, temp); 
       
     while(fscanf(arq, " %d;%49[^;\r\n];%f;%f;%9[^;\r\n]", &id_temp, &tipo_temp, &valor_temp, &desconto_temp, &tempo_temp) == 5){
          
         if(id_r == id_temp){
               excluido = 1; 
            } else {
             fprintf(temp,"%d;%s;%.2f;%.2f;%s\n", id_temp, tipo_temp, valor_temp, desconto_temp, tempo_temp);
           }
     }      

        fclose(arq);
        fclose(temp);

        if (excluido == 1){
          remove(SERVICOS);
          rename(SERVTEMP, SERVICOS);
          printf("Servico excluido com sucesso.\n"); 
        } else {
          remove(SERVTEMP);
          printf("Numero de indice %d nao encontrado.\n", id_temp); 
        }


 }