#ifndef AGENDAMENTOS_H
#define AGENDAMENTOS_H

 void listar_agendamentos(void); 
 void atualizar_agendamento(void);
 void cabecalho_agendamentos(void);
 void agendamentos(void);
 int conferir_placa();  
 int consultar_por_placa(void);

 typedef struct{
     
     char placa[9];
     char ano_modelo[10];
     char data[20];
     char hora[8]; 
     char cliente[50];
     char status[50];
     char servico[50]; 
     float descont; 
     float valor; 

 } Agendar[100]; 
 
 extern char placa_temp[9];
 extern char anomodelo_temp[10];
 extern char hora_temp[8];
 extern char data_temp[20]; 
 extern char cliente_temp[50];
 extern char status_temp[50];
 extern char servico_temp[50];
 extern char nomeatendente[100];
 extern char CPF[15];
 extern float desconto_temp;
 extern float valor_temp; 
#endif
