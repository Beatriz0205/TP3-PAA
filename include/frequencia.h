#ifndef FREQUENCIA_H
#define FREQUENCIA_H

// Definição da estrutura
typedef struct {
    char letra;
    int contagem;
    float frequencia;
} LetraInfo;

// Função principal que faz a contagem, mostra a tabela e atualiza a chave
void realizarAnaliseFrequencia(const char *textoCriptografado, char chave[26]);

#endif