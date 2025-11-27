#include "../include/Arquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para ler o conteúdo de um arquivo e retornar como uma string.
char* ler_arquivo(const char *nome_ar) {
    char caminho_arquivo[150] = "arq/";
    char nome_arquivo[100];
    strcpy(nome_arquivo, nome_ar);
    strcat(nome_arquivo, ".txt");
    strcat(caminho_arquivo, nome_arquivo);
    FILE *arquivo = fopen(caminho_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    char *conteudo = (char*)malloc(tamanho + 1);
    if (!conteudo) {
        fclose(arquivo);
        perror("Erro ao alocar memoria");
        return NULL;
    }

    fread(conteudo, 1, tamanho, arquivo);
    conteudo[tamanho] = '\0';

    for (int i = 0; conteudo[i] != '\0'; i++) {
        if (conteudo[i] == '\n') {
            conteudo[i] = ' ';   // OU: conteudo[i] = ' ';
        }
    }

    fclose(arquivo);
    return conteudo;
}

// Função para escrever uma string em um arquivo.
void escrever_arquivo(const char *nome_ar, const char *conteudo) {
    char nome_arquivo[100];
    strcpy(nome_arquivo,nome_ar);
    strcat(nome_arquivo, ".txt");
    char caminho_arquivo[150] = "arqCripto/";
    strcat(caminho_arquivo, nome_arquivo);
    FILE *arquivo = fopen(caminho_arquivo, "w");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");

    }
    fprintf(arquivo, "%s", conteudo);
    fclose(arquivo);
    printf("Escrito com sucesso!\n");

}