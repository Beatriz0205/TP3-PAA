#ifndef CRIPTO_H
#define CRIPTO_H

// chave[i] representa: letra original (A+i) foi mapeada para chave[i]
// se chave[i] == ' ', então ela é desconhecida
void inicializarChave(char chave[26]);

// Constrói a versão parcialmente decifrada do texto
char* aplicarChaveParcial(const char *texto, const char chave[26]);

// Imprime estado completo
void mostrarEstado(const char *textoCriptografado, const char chave[26]);

#endif
