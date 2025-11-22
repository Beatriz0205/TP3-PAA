#include "../include/Frequencia.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Função auxiliar para ordenar (do maior para o menor)
// Necessária para a função qsort 
int compararFrequencia(const void *a, const void *b) {
    LetraInfo *la = (LetraInfo *)a;
    LetraInfo *lb = (LetraInfo *)b;
    
    // Se a contagem de B for maior que A, B vem primeiro (ordem decrescente)
    return (lb->contagem - la->contagem);
}

void realizarAnaliseFrequencia(const char *textoCriptografado, char chave[26]) {
    LetraInfo lista[26];
    int totalLetras = 0;

    // Inicializar a lista 
    for (int i = 0; i < 26; i++) {
        lista[i].letra = 'A' + i; 
        lista[i].contagem = 0;
        lista[i].frequencia = 0.0;
    }

    //Contar as letras do texto
    for (int i = 0; textoCriptografado[i] != '\0'; i++) {
        char c = textoCriptografado[i];
        // Se for letra (ignora espaço e pontuação)
        if (isalpha(c)) {
            c = toupper(c); // Transforma em maiúscula
            int indice = c - 'A'; // A vira 0, B vira 1...
            lista[indice].contagem++;
            totalLetras++;
        }
    }

    //Calcular a porcentagem
    if (totalLetras > 0) {
        for (int i = 0; i < 26; i++) {
            lista[i].frequencia = (float)lista[i].contagem / totalLetras * 100.0;
        }
    }

    //Ordenar a  lista baseada na contagem
    qsort(lista, 26, sizeof(LetraInfo), compararFrequencia);

    // Mostrar a Tabela bonitinha
    printf("\n=== Analise de Frequencia ===\n");
    printf("Letra | Cont. | Freq. \n");
    printf("----------------------\n");
    for (int i = 0; i < 26; i++) {
        if (lista[i].contagem > 0) {
            printf("  %c   |  %3d  | %.2f%%\n", 
                   lista[i].letra, lista[i].contagem, lista[i].frequencia);
        }
    }
    printf("----------------------\n");

    // Faz o chute (Mapear com a tabela do Português)
    const char frequenciaPortugues[] = "AEOSRDIUMTCLPVGHQBFZJXKWYN";

    printf("\n=== Tentativa de Adivinhacao (Chute) ===\n");
    
    for (int i = 0; i < 26; i++) {
        char letraCripto = lista[i].letra;      
        char letraChute = frequenciaPortugues[i]; 
        
        int indiceNaChave = letraCripto - 'A';
        chave[indiceNaChave] = letraChute;
    }
    
    printf("Chave atualizada com base na frequencia!\n");
    printf("Use a Opcao 1 para ver como o texto ficou com esse chute.\n");
}