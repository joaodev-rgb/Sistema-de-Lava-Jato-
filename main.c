#include <stdio.h> 
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "login.h"
#include "agendamentos.h"
int adm = 1234;  
int adm_s;



int main(){

 
    short int opcao; 

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
    printf("|         LavaFlow         | \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");

    printf("1-Login. \n"
           "2-Cadastrar \n"
           "3-Configuração de serviços:\n"
           "4-Fechando programa...\n");

    do {

       scanf(" %hd", &opcao);
           limpar_buffer();

         switch (opcao)
       {
             case 1:


                  if (login() == 1){
                           
                           memset(&opcao, 0, sizeof(opcao)); 

                                     printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
                                     printf("|         LavaFlow         | \n");
                                     printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
                                     printf("\n\n\n\n\n");
                                     printf("1-Agendar:\n"
                                            "2-Adicionar:\n"
                                            "3-Cancelar:\n"
                                            "4-Concluido:\n"
                                            "5-Agendados:\n"
                                            "6-Relatorio:\n"
                                            "7-Sair:\n");   
                               do {       
                                            scanf(" %hd", &opcao);
                                     switch (opcao){
                                     
                                            case 1:
                                        
                                                  break;

                                            case 2:

                                                  break;

                                            case 3:  
                                                  break;      
                                            
                                            case 4:

                                                  break; 

                                            case 5: 
                                                 
                                                  break;

                                            case 6:

                                                  break;

                                            case 7:

                                                  break;  

                                         

                                                              
                                            default:
                                     
                            
                                           }  
                               }while(opcao != 7);      

                  } else {
                     return 0;
                  }

                  break; 

             case 2: 
                
                   memset(&adm_s, 0, sizeof(adm_s));

                    printf("Senha ADM:\n"); 
                       scanf(" %d", &adm_s);
                         limpar_buffer();
                   
                            if(adm_s == adm){

                                printf("Acesso liberado...\n");
                                  cadastrar_login();
                                    return 1;
                            } else{
                                printf("Senha errada.\n");
                             }
                       
               break;

             case 3: 
                     
                    memset(&adm_s, 0, sizeof(adm_s));
                 printf("Configuração de Serviços:\n"); 
                    
                      printf("Senha ADM:\n"); 
                         scanf(" %d", &adm_s);
                           limpar_buffer();
                   
                          if(adm_s == adm){

                             printf("Acesso liberado...\n");
                               ///  cadastrar_login();
                                return 1;
                           } else{
                               printf("Senha errada.\n");
                            }
                 break;  
         
             case 4: 
                 printf("Fechando o programa...\n");
                 break;

             default:
                 printf("Opcao invalida \n"); 
       }

}while(opcao != 3); 


    

    return 0; 
}