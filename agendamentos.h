#ifndef AGENDAMENTOS_H
#define AGENDAMENTOS_H

 
 void cabecalhoa_agendamentos(void);


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
 

 void agendamentos(void);  

 extern char placa_temp[9];
 extern char anomodelo_temp[10];
 extern char hora_temp[8];
 extern unsigned dia_temp, mes_temp, ano_temp; 













#endif
