#ifndef SERVICO_H
#define SERVICO_H





typedef struct{
    int id;
    char tipo[50];
    float valor; 
    float desconto; 
    char tempo[10];
} Configurar[50];

extern int id_temp, id_r;
extern char tipo_temp[50];
extern char tempo_temp[10];
extern float valor_temp;
extern float desconto_temp; 

void cabecalho_servicos(void); 
void tipo_servicos(void);
void atualizar_servicos(void);
void excluir_servico(void);


#endif