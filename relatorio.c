#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "agendamentos.h"
#include "login.h"
#include "funcoes.h"
#include "servicos.h"
#define CONCLUSAO "concluidos.txt"
#define CANCELADO "cancelados.txt"
#define AGENDAR "agendamentos.txt"
#define EXPORTAR "relatorio_exportado.txt"

static char ver_rel[256];
static char placa_rel[10];
static char anomodelo_rel[10];
static char servico_rel[50];
static char cliente_rel[50];
static char data_rel[20];
static char hora_rel[8];
static char status_rel[50];
static char atendente_rel[100];
static char cpf_rel[15];
static float desconto_rel;
static float valor_rel;

static char servicos_lista[50][50];
static int servicos_qtd[50];
static float servicos_faturamento[50];
static int total_servicos_lista = 0;

int converter_data_rel(char *data_texto) {
    int dia, mes, ano;
    sscanf(data_texto, "%d/%d/%d", &dia, &mes, &ano);
    return ano * 10000 + mes * 100 + dia;
}

void contar_servico_rel(char *servico, float valor) {
    for (int i = 0; i < total_servicos_lista; i++) {
        if (strcmp(servicos_lista[i], servico) == 0) {
            servicos_qtd[i]++;
            servicos_faturamento[i] += valor;
            return;
        }
    }
    strcpy(servicos_lista[total_servicos_lista], servico);
    servicos_qtd[total_servicos_lista] = 1;
    servicos_faturamento[total_servicos_lista] = valor;
    total_servicos_lista++;
}

void gerar_relatorio(void) {
    char inicio_txt[20], fim_txt[20];
    char filtro_servico[50];
    char filtro_status[50];
    char op_exportar;
    char tempserv[50];
    char tempstatus[50];
    int inicio, fim;
    int total_concluidos = 0;
    int total_cancelados = 0;
    int total_pendentes = 0;
    float faturamento = 0;
    char servico_mais_saiu[50] = "Nenhum";
    int maior_qtd = 0;

    total_servicos_lista = 0;
    printf("Escolha o intervalo de tempo que deseja emitir o relatorio.\n");

    printf("Data inicial (DD/MM/AAAA):\n");
    fgets(inicio_txt, sizeof(inicio_txt), stdin);
    inicio_txt[strcspn(inicio_txt, "\r""\n")] = '\0';

    printf("Data final (DD/MM/AAAA):\n");
    fgets(fim_txt, sizeof(fim_txt), stdin);
    fim_txt[strcspn(fim_txt, "\r""\n")] = '\0';

    // Filtro de serviços -- Todos para não filtrar
    printf("Filtrar por servico (digite TODOS para todos):\n");
    fgets(tempserv, sizeof(tempserv), stdin);
     tempserv[strcspn(tempserv, "\r""\n")] = '\0';
       for(int x = 0; tempserv[x] != '\0'; x++){
         tempserv[x] = tolower(tempserv[x]);}
       strcpy(filtro_servico, tempserv); 

    // Filtro de status -- digite TODOS / CONCLUIDO / CANCELADO
    printf("Filtrar por status (TODOS / CONCLUIDO / CANCELADO):\n");
    fgets(tempstatus, sizeof(tempstatus), stdin);
    tempstatus[strcspn(tempstatus, "\r""\n")] = '\0';
     for(int i = 0; tempstatus[i] != '\0'; i++){
        tempstatus[i] = tolower(tempstatus[i]);}
      strcpy(filtro_status, tempstatus);

    inicio = converter_data_rel(inicio_txt);
    fim = converter_data_rel(fim_txt);

    FILE *exp = fopen(EXPORTAR, "w");
    if (exp != NULL) {
        fprintf(exp, "RELATORIO - %s ate %s\n", inicio_txt, fim_txt);
        fprintf(exp, "--------------------------------------------\n");
    }

    printf("\n---------------- DETALHAMENTO ----------------\n");
    printf("%-10s || %-15s || %-15s || %-12s || %-10s || %-15s\n", "Placa", "Servico", "Cliente", "Data", "Valor", "Atendente");
    if (exp != NULL) {
        fprintf(exp, "Placa;Servico;Cliente;Data;Valor;Atendente;Status\n");
    }

    // --- CONCLUIDOS ---
    FILE *arc = fopen(CONCLUSAO, "r");
    if (arc != NULL) {
        fgets(ver_rel, sizeof(ver_rel), arc);
        while (fscanf(arc, " %9[^;\r\n];%9[^;\r\n];%49[^;\r\n];%49[^;\r\n];%19[^;\r\n];%7[^;\r\n];%f;%f;%49[^;\r\n];%99[^;\r\n];%14[^;\r\n]",
                             placa_rel,
                             anomodelo_rel, 
                             servico_rel, 
                             cliente_rel, 
                             data_rel, 
                             hora_rel,
                             &desconto_rel, 
                             &valor_rel, 
                             status_rel, 
                             atendente_rel, 
                             cpf_rel) == 11) {

            int data_item = converter_data_rel(data_rel);
        
            if (data_item >= inicio && data_item <= fim) {
                if (strcmp(filtro_servico, "todos") != 0 && strcmp(filtro_servico, servico_rel) != 0)
                 {
                    continue;
                    }
                if (strcmp(filtro_status, "todos") != 0 && strcmp(filtro_status, status_rel) != 0) 
                {
                    continue;
                  }

                total_concluidos++;
                faturamento = faturamento + valor_rel;
                contar_servico_rel(servico_rel, valor_rel);

                printf("%-10s || %-15s || %-15s || %-12s || %-10.2f || %-15s\n", placa_rel, servico_rel, cliente_rel, data_rel, valor_rel, atendente_rel);
                printf("   -> Cliente: %s || Atendente: %s || Status: %s || Hora: %s\n", cliente_rel, atendente_rel, status_rel, hora_rel);
                if (exp != NULL) {
                    fprintf(exp, "%s;%s;%s;%s;%.2f;%s;%s\n", placa_rel, servico_rel, cliente_rel, data_rel, valor_rel, atendente_rel, status_rel);
                }
            }
        }
        fclose(arc);
    }

    // --- CANCELADOS ---
    FILE *arc2 = fopen(CANCELADO, "r");
    if (arc2 != NULL) {
        fgets(ver_rel, sizeof(ver_rel), arc2);
        while (fscanf(arc2, " %9[^;\r\n];%9[^;\r\n];%49[^;\r\n];%49[^;\r\n];%19[^;\r\n];%7[^;\r\n];%f;%f;%49[^;\r\n];%99[^;\r\n];%14[^;\r\n]",
                              placa_rel, 
                              anomodelo_rel, 
                              servico_rel, 
                              cliente_rel, 
                              data_rel, 
                              hora_rel,
                              &desconto_rel, 
                              &valor_rel, 
                              status_rel, 
                              atendente_rel, 
                              cpf_rel) == 11) {

            int data_item = converter_data_rel(data_rel);
            if (data_item >= inicio && data_item <= fim) {
                if (strcmp(filtro_servico, "TODOS") != 0 && strcmp(filtro_servico, servico_rel) != 0)
                 {
                    continue;
                   }
                if (strcmp(filtro_status, "TODOS") != 0 && strcmp(filtro_status, status_rel) != 0) 
                  {
                    continue;
                    }

                total_cancelados++;
                printf("%-10s || %-15s || %-15s || %-12s || %-10.2f || %-15s\n", placa_rel, servico_rel, cliente_rel, data_rel, valor_rel, atendente_rel);
                printf("   -> Cliente: %s || Atendente: %s || Status: %s || Hora: %s\n", cliente_rel, atendente_rel, status_rel, hora_rel);
                if (exp != NULL) {
                    fprintf(exp, "%s;%s;%s;%s;%.2f;%s;%s\n", placa_rel, servico_rel, cliente_rel, data_rel, valor_rel, atendente_rel, status_rel);
                }
            }
        }
        fclose(arc2);
    }

    // --- PENDENTES (agendamentos.txt) ---
    FILE *arc3 = fopen(AGENDAR, "r");
    if (arc3 != NULL) {
        fgets(ver_rel, sizeof(ver_rel), arc3);
        while (fscanf(arc3, " %9[^;\r\n];%9[^;\r\n];%49[^;\r\n];%49[^;\r\n];%19[^;\r\n];%7[^;\r\n];%f;%f;%49[^;\r\n];%99[^;\r\n];%14[^;\r\n]",
            placa_rel, anomodelo_rel, servico_rel, cliente_rel, data_rel, hora_rel,
            &desconto_rel, &valor_rel, status_rel, atendente_rel, cpf_rel) == 11) {
            int data_item = converter_data_rel(data_rel);
            if (data_item >= inicio && data_item <= fim) {
                total_pendentes++;
            }
        }
        fclose(arc3);
    }

    for (int i = 0; i < total_servicos_lista; i++) {
        if (servicos_qtd[i] > maior_qtd) {
            maior_qtd = servicos_qtd[i];
            strcpy(servico_mais_saiu, servicos_lista[i]);
        }
    }

    int total_geral = total_concluidos + total_cancelados;

    printf("\n---------------- RESUMO ----------------\n");
    printf("Periodo: %s ate %s\n", inicio_txt, fim_txt);
    printf("Total geral: %d\n", total_geral);
    printf("Concluidos: %d\n", total_concluidos);
    printf("Cancelados: %d\n", total_cancelados);
    printf("Pendentes: %d\n", total_pendentes);
    if (total_geral > 0) {
        printf("Taxa de conclusao: %.2f%%\n", (total_concluidos * 100.0) / total_geral);
        printf("Taxa de cancelamento: %.2f%%\n", (total_cancelados * 100.0) / total_geral);
    }
    printf("Faturamento total: R$ %.2f\n", faturamento);
    printf("Servico que mais saiu: %s (%d vezes)\n", servico_mais_saiu, maior_qtd);

    printf("\n--- Faturamento individual por servico ---\n");
    for (int i = 0; i < total_servicos_lista; i++) {
        printf("%s - %d vezes - R$ %.2f\n", servicos_lista[i], servicos_qtd[i], servicos_faturamento[i]);
    }

    // --- EXPORTAR  IMPRESSAO ---
    if (exp != NULL) {
        fprintf(exp, "\nTotal: %d | Concluidos: %d | Cancelados: %d | Pendentes: %d\n", total_geral, total_concluidos, total_cancelados, total_pendentes);
        fprintf(exp, "Faturamento: R$ %.2f\n", faturamento);
        fprintf(exp, "Servico mais realizado: %s (%d vezes)\n", servico_mais_saiu, maior_qtd);
        fclose(exp);
        printf("\nRelatorio exportado para relatorio_exportado.txt\n");
    }

    printf("\nDeseja imprimir? (S/N)\n");
    scanf(" %c", &op_exportar);
    limpar_buffer();
    if (tolower(op_exportar) == 's') {
        printf("\n========== IMPRESSAO ==========\n");
        printf("RELATORIO %s ate %s\n", inicio_txt, fim_txt);
        printf("Total: %d | Concluidos: %d | Cancelados: %d | Pendentes: %d\n", total_geral, total_concluidos, total_cancelados, total_pendentes);
        printf("Faturamento: R$ %.2f\n", faturamento);
        printf("===============================\n");
        printf("Enviando para impressora...\n");
    }
}


