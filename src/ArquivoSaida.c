#include "../include/ArquivoSaida.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void registrarChave(char* chave,const char *nome_ar){
    char nome_arquivo[100];
    strcpy(nome_arquivo,nome_ar);
    strcat(nome_arquivo, ".txt");
    char outputArquivo[100];
    sprintf(outputArquivo, "SaidaFinal/%s", nome_arquivo);
    FILE *arquivo = fopen(outputArquivo, "w");
    if (arquivo) {
        fprintf(arquivo, "Chave de Criptografia: %s\n", chave);
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo de saída!\n");
    }
}


