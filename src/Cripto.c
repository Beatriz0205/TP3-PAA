#include "Cripto.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/Arquivo.h"

const char *TODOS_ARQUIVOS[] = {
    "Aglaea", "Anaxa", "Castorice", "Cerydra", "Cipher", "Cyrene",
    "Dang Heng - Terravox", "Hyacine", "Hysilens", "Mydei", "Phainon", "Tribios"
};


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


void editarChaveManual(char chave[26]) {
    char original, cifrada;
    
    printf("\n=== Alterar Chave Manualmente ===\n");
    printf("Informe a letra ORIGINAL (Portugues), seguida da letra CRIPTOGRAFADA.\n");
    printf("Exemplo: Se voce acha que o 'X' do texto eh na verdade um 'A', digite: A X\n");
    printf("> ");
    
    scanf(" %c %c", &original, &cifrada);

    original = toupper(original);
    cifrada = toupper(cifrada);

    // Validação básica
    if (isalpha(original) && isalpha(cifrada)) {
        // A Lógica Inversa:
        // O vetor chave é indexado pela letra CRIPTOGRAFADA.
        // Então se A virou X (Original A, Cifrada X):
        // Vamos na gaveta do X (cifrada) e guardamos o A (original).
        
        int indice = cifrada - 'A';
        chave[indice] = original;
        
        printf("Sucesso! Registrado que '%c' (no texto cifrado) sera traduzido como '%c'.\n", cifrada, original);
    } else {
        printf("Erro: Por favor, digite apenas letras validas.\n");
    }
}

void cifraDeslocamento(const char* nomeArquivo, char* texto, int x){

    int n = strlen(texto);
    char textoCripto[n + 1];

    for (int i = 0; i < n; i++) {
        char c = texto[i];

        if (isalpha(c)) {
            c = toupper(c); // converte para maiúscula
            textoCripto[i] = ((c - 'A' + x) % 26 + 26) % 26 + 'A'; //faz deslocameento
        } else {
            textoCripto[i] = c; // mantém caracteres especiais
        }
    }
    textoCripto[n] = '\0';//fim d srting

    escrever_arquivo(nomeArquivo,textoCripto);

}

void aplicarCifraMemoria(char *texto, int deslocamento) {
    for (int i = 0; texto[i] != '\0'; i++) {
        char c = texto[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            // Garante que o deslocamento seja positivo e dentro de 0-25
            texto[i] = ((c - base + deslocamento) % 26 + 26) % 26 + base;
        }
    }
}

char* gerarTextoGlobal(int deslocamento) {
    char *textoGlobal = malloc(1); // Começa vazio
    if (!textoGlobal) return NULL;
    
    textoGlobal[0] = '\0';
    long tamanhoTotal = 0;

    printf("\n--- Lendo e processando os 12 arquivos para comparacao ---\n");

    for (int i = 0; i < 12; i++) {
        // Lê o arquivo original da pasta arq/ 
        char *temp = ler_arquivo(TODOS_ARQUIVOS[i]); 
        
        if (temp) {
            // Aplica a mesma criptografia usada no arquivo principal
            aplicarCifraMemoria(temp, deslocamento);

            long tamTemp = strlen(temp);
            // Realoca memória para caber o novo texto
            char *novoPtr = realloc(textoGlobal, tamanhoTotal + tamTemp + 2); 
            
            if (!novoPtr) {
                printf("Erro de memoria ao juntar arquivos!\n");
                free(temp);
                return textoGlobal; // Retorna o que conseguiu até agora
            }
            textoGlobal = novoPtr;

            // Concatena
            strcat(textoGlobal, temp);
            strcat(textoGlobal, "\n"); // Adiciona quebra de linha
            
            tamanhoTotal += tamTemp + 1;
            free(temp); // Limpa a memória do arquivo individual
        }
    }
    return textoGlobal;
}




