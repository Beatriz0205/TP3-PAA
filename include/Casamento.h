#ifndef CASAMENTO_H
#define CASAMENTO_H

void computarUltimaOcorrencia(const char* padrao,int tabela[]);
int boyerMooreHorspool(const char* texto, const char* padrao, int localOcorrencia[]);
int ShiftAndAproximado(const char* texto, const char* padrao, int k, int localOcorrencia[]);

float frequenciaPalavras(int ocorrenciasP, int qntPalavras);
float frequenciaLetras(int ocorrenciasP, int tamPadrao, int qntLetras);

int contaCaracteres(char* texto);
int contaPalavras(char* texto);

void exibirOcorrencias(char* texto, int posicoes[], int tamPadrao, int qOcorrencias);

#endif
