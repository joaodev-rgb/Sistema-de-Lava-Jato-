#ifndef LOGIN_h
#define LOGIN_h
  

  extern char nome_temp[100];
  extern char email_temp[100];
  extern char cpf_temp[15];
  extern char senha_temp[10]; 
  
  
  typedef struct Login{

    char nome[100]; 
    char email[100];
    char cpf[15]; 
    char senha[10]; 

  } cadastrologin[10];
   
  
  int conferir_login();
  int login(); 
  int validacao_cadatro();
  void cadastrar_login(void);  
  int excluir_funcionario();
  int atualizar_funcionario(); 
  
  

 #endif