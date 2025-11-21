#include "Cripto.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void inicializarChave(char chave[26]) {
    for (int i = 0; i < 26; i++) {
        chave[i] = ' ';  // letra ainda desconhecida
    }
}

char* aplicarChaveParcial(const char *texto, const char chave[26]) {
    int n = strlen(texto);

    char *saida = malloc(n + 1);
    if (!saida) {
        printf("Erro de memória.\n");
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        char c = texto[i];

        if (isalpha(c)) {
            char maius = toupper(c);
            int idx = maius - 'A';

            if (chave[idx] != ' ') {
                // substitui pela letra parcialmente decifrada
                saida[i] = chave[idx];
            } else {
                // mantém criptografado
                saida[i] = c;
            }
        } else {
            saida[i] = c;
        }
    }

    saida[n] = '\0';
    return saida;
}

void mostrarEstado(const char *textoCriptografado, const char chave[26]) {

    printf("\n=== Texto criptografado ===\n%s\n\n", textoCriptografado);

    // imprime a chave
    printf("=== Chave ===\n");
    printf("ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");

    for (int i = 0; i < 26; i++) {
        if (chave[i] != ' ')
            printf("%c", chave[i]);
        else
            printf(" ");
    }
    printf("\n\n");

    printf("=== Texto parcialmente decifrado ===\n");

    char *parcial = aplicarChaveParcial(textoCriptografado, chave);

    // imprime com cor roxa quando letra foi substituída
    for (int i = 0; parcial[i] != '\0'; i++) {
        char c = textoCriptografado[i];
        char p = parcial[i];

        if (isalpha(c) && c != p) {
            // letra decifrada → roxo
            printf("\033[35m%c\033[0m", p);
        } else {
            // letra normal → sem cor
            printf("%c", p);
        }
    }

    printf("\n\n");
    free(parcial);
}


