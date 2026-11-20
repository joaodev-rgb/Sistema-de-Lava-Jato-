#ifndef AGENDAMENTOS_H
#define AGENDAMENTOS_H

 
 void cabecalhoa_agendamentos(void);


 typedef struct{
     
     char placa[9];
     char ano_modelo[10];
     unsigned int dia, mes, ano; 
     char hora[8]; 
 } Agendar[100]; 
 

  

 extern char placa_temp[9];
 extern char anomodelo_temp[10];
 extern char hora_temp[8];
 extern unsigned dia_temp, mes_temp, ano_temp; 













#endif
