#include <stdio.h> 
#include <ctype.h> 
#include <string.h> 

char leitura[256];

void limpar_buffer(void){
    int c;
    while((c = getchar()) != '\n' && c != EOF){}
  }
  void limpar_tela(void){
    printf("\033[2J\033[H");
}