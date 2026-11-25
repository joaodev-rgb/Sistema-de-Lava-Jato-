#include <stdio.h> 
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "login.h"
#include "agendamentos.h"
#include "servicos.h"
#include "concluidos.h"
#include "funcoes.h"
#include "relatorio.h"
int adm = 1234;  
int adm_s;



int main(){

 
    short int opcao; 

  do { 

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
    printf("|         LavaFlow         | \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");

    printf("1-Login. \n"
           "2-Configuracao de Colaboradores.\n"
           "3-Configuracao de servicos.\n"
           "4-Relatorio\n"
           "5-Fechar programa\n");

       scanf(" %hd", &opcao);
           limpar_buffer();

         switch (opcao)
       {
             case 1:

                  if (login() == 1){
                           
                           do { 
                                     printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
                                     printf("|         LavaFlow         | \n");
                                     printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
                                     printf("\n\n\n");
                                     printf("1-Agendar:\n"
                                            "2-Adicionar:\n"
                                            "3-Cancelar:\n"
                                            "4-Concluido:\n"
                                            "5-Agendados:\n"
                                            "6-Consulta:\n"
                                            "7-Sair:\n");   

                                             memset(&opcao, 0, sizeof(opcao)); 
                                            scanf(" %hd", &opcao);
                                             limpar_buffer();
                                             
                                     switch (opcao){
                                            case 1:
                                                  agendamentos();
                                                  break;
                                            case 2:
                                                  atualizar_agendamento();
                                                  break;
                                            case 3:  
                                                  break;      
                                            case 4:
                                                  servico_concluidos(); 
                                                  break; 
                                            case 5: 
                                                  listar_agendamentos();
                                                  break;
                                            case 6:
                                                  consultar_por_placa();
                                                  break;
                                            case 7:
                                                  printf("Saindo do menu...\n"); 
                                                  break;                        
                                            default:
                                              printf("Opcao invalida!!\n");
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

                                printf("Acesso liberado...\n\n\n");
                                do{
                                  printf("1-Cadastrar Funcionario\n"
                                         "2- Atualizar dados do funcionario\n"
                                          "3- Excluir do banco de cadastro.\n"
                                          "4- Sair do menu Configuracao de colaboradores.\n");
                                            scanf(" %hd", &opcao); 
                                             limpar_buffer();
 
                                             switch (opcao)
                                             {
                                             case 1:
                                                cadastrar_login();
                                                break;
                                             case 2:
                                                atualizar_funcionario(); 
                                                break;
                                             case 3: 
                                                excluir_funcionario();
                                                break; 
                                             case 4:  
                                                  printf("Saindo do menu.....\n"); 
                                                 break;    
                                             
                                             default:
                                                 printf("Opcao invalida!\n");
                                                break;
                                             }
                                          }while(opcao != 4);
                                  
                                    return 1;
                            } else{
                                printf("Senha errada.\n");
                             }
                       
               break;

             case 3: 
                     
                    memset(&adm_s, 0, sizeof(adm_s));
                 printf("Configuracao de Servicos:\n"); 
                    
                      printf("Senha ADM:\n"); 
                         scanf(" %d", &adm_s);
                           limpar_buffer();
                   
                          if(adm_s == adm){

                             printf("Acesso liberado...\n");
                                           
                                            memset(&opcao, 0, sizeof(opcao));
                                      do{ 
                                          printf("1-Cadastro de servicos:\n2-Atualizar servico:\n3-Excluir servico:\n4-Sair:\n");  

                                          
                                               scanf(" %d", &opcao);  
                                                limpar_buffer(); 

                                             switch (opcao)
                                             {
                                                case 1:
                                                     tipo_servicos();
                                                      break;
                                                
                                                case 2:
                                                      atualizar_servicos();
                                                       break;
                                                
                                                 case 3:
                                                       excluir_servico(); 
                                                        break; 
                                                 case 4: 
                                                   printf("Saindo...\n");
                                                    break;
                                             default:
                                                  printf("Opcao invalida.\n");
                                                 
                                             }
                                          }while(opcao != 4); 
                                            
                                return 1;
                           } else{
                               printf("Senha errada.\n");
                            }
                 break;
             
             case 4:
                 printf("Relatorio.\n"); 
            
                   memset(&adm_s, 0, sizeof(adm_s));

                    printf("Senha ADM:\n"); 
                       scanf(" %d", &adm_s);
                         limpar_buffer();
                   
                            if(adm_s == adm){

                                printf("Acesso liberado...\n");
                                   gerar_relatorio(); 
                                    return 1;
                            } else{
                                printf("Senha errada.\n");
                             }
                break;
             case 5: 
                 printf("Fechando o programa...\n");
                 break;

             default:
                 printf("Opcao invalida \n"); 
       }

}while(opcao != 5); 

    return 0; 
}