#include "../include/ArquivoSaida.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void registrarChave(int chave,const char *nome_arquivo ){
    char outputArquivo[100];
    sprintf(outputArquivo, "SaidaFinal/%s", nome_arquivo);
    FILE *arquivo = fopen(outputArquivo, "w");
    if (arquivo) {
        fprintf(arquivo, "Chave de Criptografia: %d\n", chave);
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo de saída!\n");
    }
}