#include <stdio.h> 
#include <ctype.h> 
#include <string.h> 
#include "login.h"
#include "funcoes.h"
#define MASTERLOGIN "banco_login.txt"
#define TEMPO "logintemp.txt"

  cadastrologin cadastro; 
 char ler[256]; 
 char nome_temp[100], nome_r[100];
 char email_temp[100], email_r[100];
 char cpf_temp[15], cpf_r[15]; 
 char senha_temp[10], senha_r[10]; 
 int i = 0;
 static short int ok = 0; 
 
 
void garantir_cabecalho(void){
  FILE *arq = fopen(MASTERLOGIN, "r"); 
 
      if (arq == NULL){
          arq = fopen(MASTERLOGIN, "w"); 
      if (arq == NULL){
        printf("Erro ai tentar criar arquivo.\n");
        return; 
      }    

            fprintf(arq, "Nome;Email;CPF;Senha\n"); 
      }
      fclose(arq);  
      }  
      

int validacao_cadatro(){

      FILE *arq = fopen(MASTERLOGIN, "r");

             if (arq == NULL){
                printf("Erro ao abrir arquivo. \n");
                return 0;
              }

           fgets(ler, sizeof(ler), arq); 
        
      while(fscanf(arq, " %99[^;\r\n];%99[^;\r\n];%14[^;\r\n];%9[^;\r\n]", nome_temp,email_temp, cpf_temp, senha_temp) == 4){

               if(strcmp(email_temp, cadastro[i].email) == 0){
                   printf("Email ja existe!\n"
                          "Tente novamente.\n");
                           return 1; 
                   
               } 
               if (strcmp(cpf_temp, cadastro[i].cpf) == 0){
                     printf("CPF invalido!\n"
                            "Tente novamente.\n");
                            return 1; 

               }
            }

           fclose(arq);
           return 0; 

}     
      
int conferir_login(){

    ok = 0; 

    FILE *arq = fopen(MASTERLOGIN, "r");

        if (arq == NULL){
            printf("Erro ao abrir arquivo. \n");
            return 0;
          }

           fgets(ler, sizeof(ler), arq); 
        
        while(fscanf(arq, " %99[^;\r\n];%99[^;\r\n];%14[^;\r\n];%9[^;\r\n]", nome_temp, email_temp, cpf_temp, senha_temp) == 4){

               if(strcmp(email_temp, email_r) == 0 && strcmp(senha_temp, senha_r) == 0){
                   ok = 1; 
                   break;
               } 
            }

           fclose(arq); 

          if (ok == 1){
            printf("Bem vindo %s\n", nome_temp);
            return 1;
          } else {
            printf("Cadastro nao encontrado!\n"
                   "Tente novamente ou faca um cadastro\n");
                    return 0;
          }          
  }

 int login(){

      printf("Email:\n");
        fgets(email_r, sizeof(email_r), stdin);
          email_r[strcspn(email_r, "\r""\n")] = '\0'; 

      printf("Senha:\n"); 
        fgets(senha_r, sizeof(senha_r), stdin);
          senha_r[strcspn(senha_r,"\r" "\n")] = '\0'; 

           return conferir_login(); 
  }

void cadastrar_login(void){  
   
   garantir_cabecalho(); 
   
   FILE *arc = fopen(MASTERLOGIN, "a"); 
    
      if (arc == NULL){
        printf("Erro ao abrir arquivo.\n");
        return; 
      }
       
      for( i = 0; i < 1; i++){

        printf("Nome:\n");
         fgets(cadastro[i].nome, sizeof(cadastro[i].nome), stdin);
          cadastro[i].nome[strcspn(cadastro[i].nome, "\r" "\n")] = '\0'; 


        printf("Email:\n"); 
         fgets(cadastro[i].email, sizeof(cadastro[i].email), stdin);
          cadastro[i].email[strcspn(cadastro[i].email, "\r" "\n")] = '\0';
            if (validacao_cadatro() != 0){
              break;
            }


        printf("CPF:\n");
         fgets(cadastro[i].cpf, sizeof(cadastro[i].cpf), stdin);
           cadastro[i].cpf[strcspn(cadastro[i].cpf, "\r" "\n")] = '\0'; 
              if (validacao_cadatro() != 0){
              break;
            }
 
        printf("Senha de 6 digitos:\n");
         fgets(cadastro[i].senha, sizeof(cadastro[i].senha), stdin); 
          cadastro[i].senha[strcspn(cadastro[i].senha, "\r" "\n")] = '\0'; 

  
          fprintf(arc, "%s;%s;%s;%s\n", cadastro[i].nome, 
                                        cadastro[i].email, 
                                        cadastro[i].cpf, 
                                        cadastro[i].senha); 
          fflush(arc); 
      }
      
      fclose(arc); 

}

int atualizar_funcionario(void){
    char novo_nome[100];
    char novo_cpf[15];
    char nova_senha[10];

    printf("Digite o CPF atual do funcionario:\n");
    fgets(cpf_r, sizeof(cpf_r), stdin);
    cpf_r[strcspn(cpf_r, "\r""\n")] = '\0';

    FILE *arq = fopen(MASTERLOGIN, "r");
    FILE *temp = fopen(TEMPO, "w");

    if(arq == NULL || temp == NULL){
        printf("Erro ao abrir arquivo.\n");
        return 0;
    }

    fgets(ler, sizeof(ler), arq);
    fputs(ler, temp); 

    ok = 0;

    while(fscanf(arq, " %99[^;\r\n];%99[^;\r\n];%14[^;\r\n];%9[^;\r\n]", nome_temp, email_temp, cpf_temp, senha_temp) == 4){
        if(strcmp(cpf_temp, cpf_r) == 0){
            ok = 1;

            printf("Digite o novo nome:\n");
            fgets(novo_nome, sizeof(novo_nome), stdin);
            novo_nome[strcspn(novo_nome, "\r""\n")] = '\0';

            printf("Digite o novo CPF:\n");
            fgets(novo_cpf, sizeof(novo_cpf), stdin);
            novo_cpf[strcspn(novo_cpf, "\r""\n")] = '\0';

            printf("Digite a nova senha:\n");
            fgets(nova_senha, sizeof(nova_senha), stdin);
            nova_senha[strcspn(nova_senha, "\r""\n")] = '\0';

            fprintf(temp, "%s;%s;%s;%s\n", novo_nome, email_temp, novo_cpf, nova_senha);
        } else {
            fprintf(temp, "%s;%s;%s;%s\n", nome_temp, email_temp, cpf_temp, senha_temp);
        }
    }

    fclose(arq);
    fclose(temp);

    if(ok == 1){
        remove(MASTERLOGIN);
        rename(TEMPO, MASTERLOGIN);
        printf("Funcionario atualizado!\n");
        return 1;
    } else {
        remove(TEMPO);
        printf("CPF nao encontrado!\n");
        return 0;
    }
}
int excluir_funcionario(void){
    printf("Digite o CPF do funcionario para excluir:\n");
    fgets(cpf_r, sizeof(cpf_r), stdin);
    cpf_r[strcspn(cpf_r, "\r""\n")] = '\0';

    FILE *arq = fopen(MASTERLOGIN, "r");
    FILE *temp = fopen(TEMPO, "w");

    if(arq == NULL || temp == NULL){
        printf("Erro ao abrir arquivo.\n");
        return 0;
    }

    fgets(ler, sizeof(ler), arq);
    fputs(ler, temp); 
    ok = 0;

    while(fscanf(arq, " %99[^;\r\n];%99[^;\r\n];%14[^;\r\n];%9[^;\r\n]", nome_temp, email_temp, cpf_temp, senha_temp) == 4){
        if(strcmp(cpf_temp, cpf_r) == 0){
            ok = 1;
            printf("Funcionario %s excluido!\n", nome_temp);
            // nao escreve no temp, ou seja, apaga
        } else {
            fprintf(temp, "%s;%s;%s;%s\n", nome_temp, email_temp, cpf_temp, senha_temp);
        }
    }

    fclose(arq);
    fclose(temp);

    if(ok == 1){
        remove(MASTERLOGIN);
        rename(TEMPO, MASTERLOGIN);
        return 1;
    } else {
        remove(TEMPO);
        printf("CPF nao encontrado!\n");
        return 0;
    }
}
