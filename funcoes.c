#include <stdio.h> 
#include <ctype.h> 
#include <string.h> 



void limpar_buffer(void){
    int c;
    while((c = getchar()) != '\n' && c != EOF){}
  }