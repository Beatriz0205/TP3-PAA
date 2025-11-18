#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../include/Arquivo.h"
#include "../include/ArquivoSaida.h"


int main(){
    //usado para ler o arquivo
    char nome_arquivo[256];
    char caminho_arquivo[150] = "arq/";
    printf("Nome do arquivo: ");
    scanf("%s", nome_arquivo);
    strcat(nome_arquivo, ".txt");
    strcat(caminho_arquivo, nome_arquivo);
    char *conteudo = ler_arquivo(caminho_arquivo);
    printf("Texto : %s\n",conteudo);
    printf("\n");

    //vai ser usado para salvar o texto criptografado
    //pelo que vi no menu teremos apenas os 12 textos
    //o nosso é esse
    escrever_arquivo("HysilensCripto.txt", conteudo);

    //Essa vai ser para a opção 6
    int chave = 9;
    printf("Nome do arquivo para guardar a chave: ");
    scanf("%s", nome_arquivo);
    strcat(nome_arquivo, ".txt");
    registrarChave(chave,nome_arquivo);
    printf("Confira na pasta SaidaFinal.\n");
    return 0;
}

