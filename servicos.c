#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "servicos.h"
#define SERVICOS "servicos.txt"
#define SERVTEMP "arqtemposerv.txt"


Configurar config; 
int j, id_r;
short int op = 0; 
char ler[256]; 
float valor_temp;
float desconto_temp;

void limpar_buffer(void){
    int c;
    while((c = getchar()) != '\n' && c != EOF){}
  }

void cabecalho_servicos(void){
  FILE *arq = fopen(SERVICOS, "r"); 
 
      if (arq == NULL){
          arq = fopen(SERVICOS, "w"); 
      if (arq == NULL){
        printf("Erro ai tentar criar arquivo.\n");
        return; 
      }    

            fprintf(arq, "Id;Tipo;Valor;Desconto;Tempo\n"); 
      }
      fclose(arq);  
      }  


 void tipo_servicos(void){

    FILE *arc = fopen(SERVICOS, "a");
       if (arc == NULL){
            printf("Erro ao abrir o arquivo.\n");
            return;
       }

          for(j = 0; j < 50; j++){

            config[j].id = j + 1; 
          
             printf("Tipo:\n"); 
              fgets(config[j].tipo, sizeof(config[j].tipo), stdin);
                config[j].tipo[strcspn(config[j].tipo, "\r""\r")] = '\0';
             
             printf("Valor:\n");
               scanf(" %f", &config[j].valor);
                limpar_buffer();

             printf("Desconto:\n");
                scanf(" %f", &config[j].desconto);
                  limpar_buffer();
           
             printf("Tempo:\n");
               fgets(config[j].tempo, sizeof(config[j].tempo), stdin);
                config[j].tempo[strcspn(config[j].tempo, "\r""\n")] = '\0';

              fprintf(arc, "%d;%s;%.2f;%.2f;%s\n", config[j].id, config[j].tipo, config[j].valor, config[j].desconto, config[j].tempo);  
              fflush(arc); 

              printf("Novo cadastro?\n1-Sim.\n2-Nao.\n");
                scanf(" %hd", &op);
                  if(op == 1){
                    return; 
                  }
                  if(op == 2){
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
      return;
     }

     printf("Qual o indice:\n"); 
      scanf(" %d", &id_r);
       limpar_buffer(); 

    
         fgets(ler, sizeof(ler), arq); 
         fputs(ler, temp); 

      while(fscanf(arq, " %d; %49[^;];%.2f;%.2f;9[^;]", &id_temp, &tipo_temp, &valor_temp, &desconto_temp, &tempo_temp) == 5){
                if(id_r == id_temp){
                  printf("Cadastro encontrado.\n");
                            
                        printf("Tipo do serviço:\n");
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
                   fprintf(temp,"%d;%s;%.2f;%.2f;%s\n", config[j].id, config[j].tipo, config[j].valor, config[j].desconto, config[j].tempo);
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
  
 }