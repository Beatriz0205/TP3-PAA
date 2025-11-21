#include <stdio.h>
#include <string.h>

#define BLUE  "\x1b[34m"
#define RESET "\x1b[0m"

void computarUltimaOcorrencia(const char* padrao,int tabela[]){

    int m = strlen(padrao);

    for (int i=0;i<128;i++){
        tabela[i]=-1;// inicializa a tabela vazia para todos os caracteres ASCII 128
    }
    for (int i=0;i<m-1;i++){
        tabela[(unsigned char)padrao[i]]=i; // guarda a ultima posicao em q cada caractere aparece
    }
}

int boyerMooreHorspool(const char* texto, const char* padrao, int localOcorrencia[]){

    int tabela[128];
    int m = strlen(padrao);
    int n = strlen(texto);
    int indiceInicial = 0;
    int indiceComparacao;
    int quantOcorrencias = 0;

    computarUltimaOcorrencia(padrao, tabela); //inicializa tabela

    while (indiceInicial <= n-m){  //enquanto ainda cabe o padrao no texto
        indiceComparacao = m-1;

        while(padrao[indiceComparacao] == texto[indiceInicial + indiceComparacao]){ //se nao tem colisao, continua comparando
            indiceComparacao--;
            if (indiceComparacao < 0){ //achou o padrao

                localOcorrencia[quantOcorrencias]=indiceInicial; //guarda a posicao onde teve a ocorrencia

                quantOcorrencias++; //contabiliza a ocorrencia
                indiceInicial+=m; // continua verificando no restante do texto para encontrar mais ocorrencias do padrao

                continue;
            }
        }
        indiceInicial+= (m-1) - tabela[(unsigned char)texto[indiceInicial + (m-1)]]; //houve colisao, calcula o deslocamento com base na 
    }
    return quantOcorrencias;
}


//apenas testando 
// int main() {
//     const char *T = "pandapamelaaulapampamelapamelefanteanimalpamelaabcdefpamelapamelsaaaapalomalapalavrapamonha";
//     const char *P = "pamela";

//     int posicoes[strlen(T)];
//     int j=0;

//     int pos = boyerMooreHorspool(T, P, posicoes);

//     printf("Quant ocorrencias do padrao: %d\n",pos);
//     for (int i=0;i<strlen(T);i++){
//         if (i==posicoes[j]){
//             printf(BLUE "%c" RESET, T[i]);
//             j++;
//         }
//         else{
//             printf("%c", T[i]); 
//         }
//     }

//     return 0;
// }