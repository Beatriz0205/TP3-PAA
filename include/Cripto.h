#ifndef CRIPTO_H
#define CRIPTO_H

// chave[i] representa: letra original (A+i) foi mapeada para chave[i]
// se chave[i] == ' ', então ela é desconhecida
void inicializarChave(char chave[26]);

// Constrói a versão parcialmente decifrada do texto
char* aplicarChaveParcial(const char *texto, const char chave[26]);

// Imprime estado completo
void mostrarEstado(const char *textoCriptografado, const char chave[26]);

void editarChaveManual(char chave[26]);

void cifraDeslocamento(const char* nomeArquivo, char* texto, int x);

// Aplica a cifra de César diretamente na memória 
void aplicarCifraMemoria(char *texto, int deslocamento);

// Lê os 12 arquivos, aplica a cifra e retorna um texto único concatenado
char* gerarTextoGlobal(int deslocamento);
#endif
