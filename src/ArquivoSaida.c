#include "../include/ArquivoSaida.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void registrarChave(int chave,const char *nome_ar){
    if (!chave || !nome_ar) {
            printf("Erro: chave ou nome_ar é NULL!\n");
            return;
        }

    char nome_arquivo[200];
    strcpy(nome_arquivo,nome_ar);
    strcat(nome_arquivo, ".txt");
    char outputArquivo[300];
    sprintf(outputArquivo, "SaidaFinal/%s", nome_arquivo);
    FILE *arquivo = fopen(outputArquivo, "w");
    if (arquivo) {
        fprintf(arquivo, "Chave de Criptografia: %d\n", chave);
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo de saída!\n");
    }
}


