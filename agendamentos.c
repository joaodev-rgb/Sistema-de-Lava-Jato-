#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define AGENDAR "agendamentos.txt"
#define SERVICOS "servicos.txt"
#define TEMP "temp.txt"
#include "agendamentos.h"
#include "login.h"
#include "funcoes.h"
#include "servicos.h"


 Agendar agendar;
 int j;
 char ver[256];
 float auxiliar_valor, auxiliar_dec, auxiliar; 
 char sair;
 char sair_s;
 char placa_temp[9];
 char anomodelo_temp[10];
 char hora_temp[8];
 char data_temp[20]; 
 char cliente_temp[50];
 char status_temp[50];
 char servico_temp[50];
 char nomeatendente[100];
 char CPF[15];
 static char placabuca[9];
 static short int atualizado = 0;
 

void cabecalho_agendamentos(void){
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


int conferir_placa(){

  FILE *arc = fopen(AGENDAR, "r");
    if (arc == NULL){
        printf("Erro ao abrir o arquivo.\n");
    }

    fgets(ver, sizeof(ver), arc); 
      while(fscanf(arc, " %9[^;\r\n];%9[^;\r\n];%49[^;\r\n];%49[^;\r\n];%19[^;\r\n];%7[^;\r\n];%f;%f;%49[^;\r\n];%99[^;\r\n];%14[^;\r\n]",
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
           
        if (strcmp(agendar[j].placa, placa_temp) == 0){
          printf("Carro com servico em andamento.\n");
           printf("Placa: %s\n", placa_temp);
           fclose(arc);
           return 1;
        }                                                                                                     
      }
      fclose(arc);  
      return 0; 
  }




void agendamentos(void){
         
     cabecalho_agendamentos();

     FILE *arc = fopen(AGENDAR, "a");
     FILE *arq = fopen(SERVICOS, "r"); 
        
          if (arc == NULL || arq == NULL){
            printf("Erro ao abrir o arquivo.\n");
          }

           for (j = 0; j < 1; j++){

             printf("Placa do veiculo:\n");
              fgets(agendar[j].placa, sizeof(agendar[j].placa), stdin);
                agendar[j].placa[strcspn(agendar[j].placa, "\r""\n")] = '\0'; 
                //precisa da verificação de placas repetidas com o mesmo status 
                  if (conferir_placa() == 1){
                    return;
                  }
            
             printf("Ano do Modelo:\n");
              fgets(agendar[j].ano_modelo, sizeof(agendar[j].ano_modelo), stdin);
                agendar[j].ano_modelo[strcspn(agendar[j].ano_modelo, "\r""\n")] = '\0'; 
                
              printf("Qual o servico:\n\n\n");
              
               fgets(ver, sizeof(ver), arq);

            printf("\n%-10s||%-40s||%-10s||%-10s||%-15s\n", "ID", "Servico", "Valor", "desconto", "Tempo");
            printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");

             while(fscanf(arq, " %d;%49[^;\r\n];%f;%f;%9[^;\r\n]", 
                                 &id_temp, 
                                 &tipo_temp, 
                                 &valor_temp, 
                                 &desconto_temp, 
                                 &tempo_temp) == 5) {
              printf("%-10d  %-40s %-11.2f %-11.2f %s\n", 
                      id_temp, 
                      tipo_temp, 
                      valor_temp, 
                      desconto_temp, 
                      tempo_temp);
             }
            printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
            
              rewind(arq); //<- Volta para o incio do arquivo. 

              scanf(" %d", &id_r); 
               limpar_buffer();

               fgets(ver, sizeof(ver), arq); 
             
              while(fscanf(arq, " %d;%49[^;\r\n];%f;%f;%9[^;\r\n]", 
                                 &id_temp, 
                                 &tipo_temp, 
                                 &valor_temp, 
                                 &desconto_temp, 
                                 &tempo_temp) == 5){
                    if( id_r == id_temp){
                     strcpy(agendar[j].servico, tipo_temp); 
                     break;
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
                 /*Bom, desistir de deixar isso automatico, pois eu teria uma fila de espera e isso só seria valido 
                     se tivesse como automatizar o os colaboradores que estão em operacao.*/

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
            printf("Confirmar:\nS\nN\n");
             scanf(" %c", &sair);
              limpar_buffer();
             sair_s = tolower(sair); 
             if (sair_s == 's'){
               printf("Agendando...\n"); 
               fprintf(arc, " %s;%s;%s;%s;%s;%s;%.2f;%.2f;%s;%s;%s\n",
                             agendar[j].placa, 
                             agendar[j].ano_modelo, 
                             agendar[j].servico, 
                             agendar[j].cliente, 
                             agendar[j].data, 
                             agendar[j].hora, 
                             agendar[j].descont, 
                             agendar[j].valor, 
                             agendar[j].status, 
                             nome_temp, 
                             cpf_temp);   
                
                fflush(arc);                                                
             } 
                                                            
             }
             fclose(arc);
             fclose(arq); 
}

void listar_agendamentos(void){
    FILE *arc = fopen(AGENDAR, "r");
    if (arc == NULL){
        printf("Nenhum agendamento encontrado.\n");
        return;
       }

    fgets(ver, sizeof(ver), arc);

    printf("\n%-10s || %-12s || %-20s || %-20s || %-12s || %-8s || %-10s || %-10s || %-15s\n", "Placa", "Ano-modelo", "Servico", "Cliente", "Data", "Hora", "Desconto", "Valor", "Status");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    while(fscanf(arc, " %9[^;\r\n];%9[^;\r\n];%49[^;\r\n];%49[^;\r\n];%19[^;\r\n];%7[^;\r\n];%f;%f;%49[^;\r\n];",
                        placa_temp,
                        anomodelo_temp,
                        servico_temp,
                        cliente_temp,
                        data_temp,
                        hora_temp,
                        &desconto_temp,
                        &valor_temp,
                        status_temp) == 9){

           printf("%-10s %-12s %-20s %-20s %-12s %-8s %-10.2f %-10.2f %-15s \n",
                   placa_temp,
                   anomodelo_temp,
                   servico_temp,
                   cliente_temp,
                   data_temp,
                   hora_temp,
                   desconto_temp,
                   valor_temp,
                   status_temp);
           }
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    fclose(arc);
}
void atualizar_agendamento(void){
  FILE *arc = fopen(AGENDAR, "r");
  FILE *temp = fopen(TEMP, "w");
      if(arc == NULL || temp == NULL){
        printf("Arquivo não encontrado\n");
        if(arc != NULL){fclose(arc);}
        if(temp != NULL){fclose(temp);}
        return; 
      }
      
      fgets(ver, sizeof(ver), stdin);
      fputs(ver, temp); 
       while(fscanf(arc, " %9[^;\r\n];%9[^;\r\n];%49[^;\r\n];%49[^;\r\n];%19[^;\r\n];%7[^;\r\n];%f;%f;%49[^;\r\n];%99[^;\r\n];%14[^;\r\n]",
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


        if(strcmp(placabuca, placa_temp) == 0){
            
              printf("Qual o servico:\n");
               fgets(servico_temp, sizeof(servico_temp), stdin);
                servico_temp[strcspn(servico_temp, "\r""\n")] = '\0';

              printf("Cliente:\n");
               fgets(cliente_temp, sizeof(cliente_temp), stdin);
                cliente_temp[strcmp(cliente_temp, "\r""\n")] = '\0';
                
              printf("Data:\n");
               fgets(data_temp, sizeof(data_temp), stdin); 
                data_temp[strcmp(data_temp, "\r""\n")] = '\0'; 
              
              printf("Hora:\n");
               fgets(hora_temp, sizeof(hora_temp), stdin);
                hora_temp[strcmp(hora_temp, "\r""\n")] = '\0';

                  // Condição de desconto 
              if(desconto_temp == 0){
                printf("Desconto:\n");
               scanf(" %f", &auxiliar_dec);
                limpar_buffer(); 
              } else {
                auxiliar_dec = desconto_temp;
              }
          
           if (auxiliar_dec == 0){
                auxiliar_valor = valor_temp; 
           } else {
              
                 auxiliar = (valor_temp * (auxiliar_dec / 100)); 
                 auxiliar_valor = (valor_temp - auxiliar);
           } 
           fprintf(arc, " %s;%s;%s;%s;%s;%s;%.2f;%.2f;%s;%s;%s\n",
                             placa_temp, 
                             anomodelo_temp, 
                             servico_temp, 
                             cliente_temp, 
                             data_temp, 
                             hora_temp, 
                             auxiliar_dec, 
                             auxiliar_valor, 
                             status_temp, 
                             nomeatendente, 
                             CPF);     
          atualizado = 1;
          break; 
        }else{
              fprintf(temp, "%s;%s;%s;%s;%s;%s;%.2f;%.2f;%s;%s;%s\n",
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
        }                    
           }
           fclose(arc);
           fclose(temp);

         if(atualizado == 1){
           remove(AGENDAR);
           rename(TEMP, AGENDAR);
           printf("Agendamento atualizado com sucesso\n");
         } else {
            remove(TEMP);
            printf("Nao foi possivel atualizar\n");
         }


}