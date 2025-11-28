#include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <limits.h>

#define GREEN "\x1b[1;32m"
#define ORANGE "\x1b[1;38;5;208m"
#define RED "\x1b[1;31m"
#define RESET "\x1b[0m"
#define Maxchar 256
#define NumMaxErros 32

int contaCaracteres(char* texto) {
    int cont = 0;
    while (texto[cont] != '\0') {
        cont++;
    }
    return cont;
}

int contaPalavras(char* texto) {
    int cont = 0;
    int dentro = 0;

    for (int i = 0; texto[i] != '\0'; i++) {
        if (texto[i] != ' ') {
            if (!dentro) {
                cont++;
                dentro = 1;
            }
        } 
        else {
            dentro = 0;
        }
    }
    return cont;
}


void computarUltimaOcorrencia(const char* padrao,int tabela[]){

    int m = strlen(padrao);

    for (int i=0;i<128;i++){
        tabela[i]=-1;// inicializa a tabela vazia p todos os caracteres ASCII 128
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

                localOcorrencia[quantOcorrencias]=indiceInicial; //guarda a posicao onde começa a ocorrencia

                quantOcorrencias++; //contabiliza a ocorrencia
                indiceInicial+=m; // continua verificando no restante do texto para encontrar mais ocorrencias do padrao

                continue;
            }
        }
        int deslocamento = (m-1) - tabela[(unsigned char)texto[indiceInicial + (m-1)]]; //houve colisao, calcula o deslocamento com base na 
        if (deslocamento<=0) deslocamento=1;

        indiceInicial+=deslocamento;
    }
    return quantOcorrencias;
}

int ShiftAndAproximado(const char* texto, const char* padrao, int k, int localOcorrencia[]) {

    int m = strlen(padrao); //tam do padrao
    int n = strlen(texto);  //tam do texto

    int quantOcorrencias = 0;
    unsigned long Masc[Maxchar];  //mascaras de bits de cada caractere
    unsigned long i, j; 
    unsigned long Ri; //inicio do casamento
    unsigned long Rant;  // R no nivel anterior
    unsigned long Rnovo;  // R apos processar o caractere atual
    unsigned long R[NumMaxErros + 1]; //estados, R[j] representa o estado com até j substituições

    for (i = 0; i < Maxchar; i++)
        Masc[i] = 0; //inicializando com zeros

    for (i = 1; i <= m; i++)
    { 
        Masc[padrao[i-1] + 127] |= 1 << (m - i);  // faz a tabela M do bitmask, colocando 1 em cada lugar q o caractere existe
    }

    R[0] = 0; //inicializa R vazio
    Ri = 1 << (m - 1);  // desloca 1 bit

    for (j = 1; j <= k; j++)
        R[j] = (1 << (m - j)) | R[j-1]; //ja computa a tolerancia de erros, ativando k bits

    for (i = 0; i < n; i++) //percorre cada caractere no texto
    {
        Rant = R[0]; // salva R anterior
        Rnovo = ((((unsigned long)Rant) >> 1) | Ri) & Masc[texto[i] + 127]; //avança no padrao + possibiliadde de um novo casamento + validacao com a tabela de bitmask
        R[0] = Rnovo; // atualiza estado
        
        for (j = 1; j <= k; j++)
        {
            Rnovo = ((((unsigned long)R[j]) >> 1) & Masc[texto[i] + 127]) | //match
            ((((unsigned long)Rant) >> 1)); // substituicao

            Rant = R[j]; //salva pra proxima verificacao
            R[j] = Rnovo | Ri; //atualiza
        }
        int cAproximado = (R[k] & 1) != 0; //casamento aproximado
        int cExato = (R[0] & 1) != 0; //casamento exato

        if (cAproximado && ! cExato){ //testa se o ultimo bit esta ativo(casamento aconteceu)
            localOcorrencia[quantOcorrencias]=i-m+1; //salva onde comeca a ocorrencia do casamento aprox no texto
            quantOcorrencias+=1; //contabiliza um casamento
        }
    }
    return quantOcorrencias;
}

float frequenciaPalavras(int ocorrenciasP, int qntPalavras){
    return (float)ocorrenciasP / (float)qntPalavras;
}

float frequenciaLetras(int ocorrenciasP, int tamPadrao, int qntLetras){
    return ((float)ocorrenciasP * (float)tamPadrao) / (float)qntLetras;
}

void exibirOcorrencias(char* texto, int posicoes[], int tamPadrao, int qOcorrencias){
    
    int n = strlen(texto);

    for (int i = 0; i < n; i++) {

        int ehInicio = 0;
        int ehFim = 0;

        for (int k = 0; k < qOcorrencias; k++) {
            if (i == posicoes[k]) {
                ehInicio = 1;
                break;
            }
        }

        for (int k = 0; k < qOcorrencias; k++) {
            if (i == posicoes[k] + tamPadrao - 1) {
                ehFim = 1;
                break;
            }
        }

        if (ehInicio && ehFim)
            printf(ORANGE "%c" RESET, texto[i]);
        else if (ehInicio)
            printf(GREEN "%c" RESET, texto[i]);
        else if (ehFim)
            printf(RED "%c" RESET, texto[i]);
        else
            printf("%c", texto[i]);
    }
}

//testes
// int main() {
//     const char *T = "computador comutador campotador computodor comutodor";
//     const char *P = "computador";

//     int k = 2;

//     aqui testa o shift and aproximado

//     int j=0;

//     int posicoes[100];

//     ShiftAndAproximado(T,P,k,posicoes);

//     printf("padrao: %s, k: %d \n",P,k);
//     printf("Quant ocorrencias do padrao: %d\n",count);

//     printf("posicoes: ");
//     for (int i=0;i<count;i++){
//         printf("%d ",posicoes[i]);
//     }
//     printf("\n");
//     for (int i=0;i<strlen(T);i++){
//         if (i==posicoes[j]){
//             printf(BLUE "%c" RESET, T[i]);
//             j++;
//         }
//         else{
//             printf("%c", T[i]); 
//         }
//     }


//     aqui testa o bmh

//     int pos[strlen(T)];
//     int j=0;

//     int vpos = boyerMooreHorspool(T, P, vpos);

//     printf("Quant ocorrencias do padrao: %d\n",pos);
//     for (int i=0;i<strlen(T);i++){
//         if (i==vpos[j]){
//             printf(BLUE "%c" RESET, T[i]);
//             j++;
//         }
//         else{
//             printf("%c", T[i]); 
//         }
//     }

//     return 0;
// }