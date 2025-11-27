#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX_PADRAO 256

#include "../include/Arquivo.h"
#include "../include/ArquivoSaida.h"
#include "../include/Cripto.h"
#include "../include/frequencia.h"
#include "../include/Casamento.h"


void voltarMenu() {
    int op;
    printf("Digite 1 para voltar ao menu ou 0 para encerrar: \n");
    scanf("%d", &op);

    while (getchar() != '\n');

    if (op == 0) {
        printf("\nPrograma encerrado.\n");
        exit(0);
    }
}


int main() {

    int opcao;
    char *conteudo = NULL;
    char chave[26];
    int qntPalavras;
    int qntCaracteres;
    
    printf("=== SISTEMA DE CRIPTOANÁLISE ===\n\n");

    do {
        printf("============= MENU ============\n\n");
        printf("1. Ler arquivo\n");
        printf("2. Mostrar estado da cripoanalise\n");
        printf("3. Chute baseado na analise de frequencia\n");
        printf("4. Casamento exato\n");
        printf("5. Casamento aproximado\n");
        printf("6. Alterar chave de criptografia\n");
        printf("7. Exportar resultado e sair\n");
        printf("0. Digite qualquer outro valor para encerrar\n");

        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:{
                // inicializa chave parcial
                char chave[26];
                inicializarChave(chave);

                // ler arquivo
                char nome_arquivo[256];
                //char caminho_arquivo[150] = "arqCripto/";

                char caminho_arquivo[150] = "arq/";
                
                printf("Nome do arquivo (sem .txt, ex: Hysilens): ");
                scanf("%s", nome_arquivo);

                strcat(nome_arquivo, ".txt");
                strcat(caminho_arquivo, nome_arquivo);

                conteudo = ler_arquivo(caminho_arquivo);
                escrever_arquivo(nome_arquivo,conteudo);

                if (!conteudo) {
                    printf("Erro ao ler arquivo!\n");
                    return 1;
                }

                qntCaracteres=contaCaracteres(conteudo);
                qntPalavras=contaPalavras(conteudo);
                printf("Texto Original: %s\n\n", conteudo);

                voltarMenu();
                break;
            }
            case 2:
                //logica aaqui


                voltarMenu();
                break;

            case 3:

            case 4:{

                if (conteudo == NULL){
                    printf("Carregue um arquivo antes");
                    voltarMenu();
                    break;
                }
                char continua;

                do{
                    char padrao[MAX_PADRAO];
                    int n = strlen(conteudo);
                    int *posicoesOcorrenciasExatas = malloc(n * sizeof(int));

                    printf("Qual o padrao utilizado?\n");
                    scanf("%255s",padrao);
                    getchar();

                    int tamPadrao=strlen(padrao);
                    int qntOcorrenciasExatas= boyerMooreHorspool(conteudo,padrao,posicoesOcorrenciasExatas);

                    printf("\nOcorrencias %d\n\n",qntOcorrenciasExatas);
                    printf("");
                    exibirOcorrencias(conteudo,posicoesOcorrenciasExatas,tamPadrao,qntOcorrenciasExatas);

                    printf("\n\nFrequencia do padrao em relacao a quantidade de palavras do texto: %.2f %c \n",frequenciaPalavras(qntOcorrenciasExatas,qntPalavras),'%');

                    printf("Frequencia do padrao em relacao a quantidade de letras do texto: %.2f %c \n",frequenciaPalavras(qntOcorrenciasExatas,qntCaracteres),'%');

                    free(posicoesOcorrenciasExatas);

                    printf("\nDeseja buscar outro padrão? (s/n): ");
                    scanf("%c", &continua);
                    getchar();

                } while (continua == 's' || continua == 'S');
                
                voltarMenu();
                break;
            }
               
            case 5:{

                if (conteudo == NULL){
                    printf("Carregue um arquivo antes");
                    voltarMenu();
                    break;
                }

                char continua;

                do{
                    char padrao[strlen(conteudo)];
                    int k;
                    int n = strlen(conteudo);
                    int *posicoesOcorrenciasAprox = malloc(n * sizeof(int));

                    printf("Qual o padrao e a tolerancia (k) utilizados?\n");
                    scanf("%s %d",padrao,&k);
                    getchar();

                    int tamPadrao=strlen(padrao);
                    int qntOcorrenciasAprox= ShiftAndAproximado(conteudo,padrao,k,posicoesOcorrenciasAprox);

                    printf("\nOcorrencias %d\n\n",qntOcorrenciasAprox);
                    printf("");
                    exibirOcorrencias(conteudo,posicoesOcorrenciasAprox,tamPadrao,qntOcorrenciasAprox);


                    printf("\n\nFrequencia do padrao em relacao a quantidade de palavras do texto: %.2f%%\n",frequenciaPalavras(qntOcorrenciasAprox,qntPalavras));

                    printf("Frequencia do padrao em relacao a quantidade de letras do texto: %.2f%% \n",frequenciaPalavras(qntOcorrenciasAprox,qntCaracteres));

                    free(posicoesOcorrenciasAprox);

                    printf("\nDeseja buscar outro padrão? (s/n): ");
                    scanf("%c", &continua);
                    getchar();

                } while (continua == 's' || continua == 'S');

                voltarMenu();
                break;
            }
            case 6:
                //logica aaqui


                voltarMenu();
                break;

            case 7:
                //logica aaqui


                printf("Programa encerrado.\n");
                exit(0);

            default:
                printf("Programa encerrado.\n");
                exit(0);
        }

    } while (1);
}



//Main q eu fiz pra salvar a chave atual 

// void voltarMenu() {
//     int op;
//     printf("\nDigite 1 para voltar ao menu ou 0 para encerrar: ");
//     scanf("%d", &op);

//     while (getchar() != '\n');

//     if (op == 0) {
//         printf("\nPrograma encerrado.\n");
//         exit(0);
//     }
// }

// int main() {

//     int opcao;
//     char *conteudo = NULL;
//     char chave[26];       // *** chave principal do programa ***
//     inicializarChave(chave);   // inicializa só uma vez

//     printf("=== SISTEMA DE CRIPTOANÁLISE ===\n\n");

//     do {
//         printf("\n============= MENU ============\n");
//         printf("1. Ler arquivo\n");
//         printf("2. Mostrar estado da criptoanalise\n");
//         printf("3. Chute por análise de frequência\n");
//         printf("4. Casamento exato\n");
//         printf("5. Casamento aproximado\n");
//         printf("6. Alterar chave de criptografia\n");
//         printf("7. Exportar resultado e sair\n");
//         printf("0. Encerrar\n\n");

//         scanf("%d", &opcao);
//         getchar();

//         switch(opcao) {

//             case 1: {
//                 char nome_arquivo[256];
//                 char caminho_arquivo[150] = "arqCripto/";

//                 printf("Nome do arquivo (sem .txt, ex: Hysilens): ");
//                 scanf("%s", nome_arquivo);

//                 strcat(nome_arquivo, ".txt");
//                 strcat(caminho_arquivo, nome_arquivo);

//                 conteudo = ler_arquivo(caminho_arquivo);

//                 if (!conteudo) {
//                     printf("Erro ao ler arquivo!\n");
//                     voltarMenu();
//                     break;
//                 }

//                 printf("\nArquivo carregado com sucesso!\n");

//                 voltarMenu();
//                 break;
//             }

//             case 2: {
//                 if (!conteudo) {
//                     printf("Carregue um arquivo antes!\n");
//                 } else {
//                     mostrarEstado(conteudo, chave);   // mostra texto criptografado, chave parcial e texto parcial
//                 }
                
//                 voltarMenu();
//                 break;
//             }


//             case 3:
//                 printf("Função de análise de frequência ainda não implementada.\n");
//                 voltarMenu();
//                 break;

//             case 4: {
//                 if (!conteudo) {
//                     printf("Carregue um arquivo antes!\n");
//                     voltarMenu();
//                     break;
//                 }

//                 char continua;
//                 do {
//                     char padrao[strlen(conteudo)];
//                     int posicoes[strlen(conteudo)];

//                     printf("Padrão a buscar: ");
//                     scanf("%s", padrao);

//                     int qtd = boyerMooreHorspool(conteudo, padrao, posicoes);

//                     printf("Ocorrências: %d\n\n", qtd);
//                     exibirOcorrencias(conteudo, posicoes, strlen(padrao), qtd);

//                     printf("\nBuscar outro? (s/n): ");
//                     scanf(" %c", &continua);

//                 } while (continua == 's' || continua == 'S');

//                 voltarMenu();
//                 break;
//             }

//             case 5: {
//                 if (!conteudo) {
//                     printf("Carregue um arquivo antes!\n");
//                     voltarMenu();
//                     break;
//                 }

//                 char continua;

//                 do {
//                     char padrao[strlen(conteudo)];
//                     int k;
//                     int posicoes[strlen(conteudo)];

//                     printf("Padrão e tolerância k: ");
//                     scanf("%s %d", padrao, &k);

//                     int qtd = ShiftAndAproximado(conteudo, padrao, k, posicoes);

//                     printf("Ocorrências aproximadas: %d\n\n", qtd);
//                     exibirOcorrencias(conteudo, posicoes, strlen(padrao), qtd);

//                     printf("\nBuscar outro? (s/n): ");
//                     scanf(" %c", &continua);

//                 } while (continua == 's' || continua == 'S');

//                 voltarMenu();
//                 break;
//             }

//             case 6: {
//                 if (!conteudo) {
//                     printf("Carregue um arquivo antes!\n");
//                 } else {
//                     editarChaveManual(chave);
//                     printf("\nChave atual: ");
//                     for (int i = 0; i < 26; i++) {
//                         printf("%c", chave[i] == ' ' ? '_' : chave[i]);
//                     }
//                     printf("\n");
//                 }

//                 voltarMenu();
//                 break;
//             }

//             case 7: {
//                 printf("Função de exportação ainda será finalizada.\n");
//                 printf("Programa encerrado.\n");
//                 exit(0);
//             }

//             default:
//                 printf("Programa encerrado.\n");
//                 exit(0);
//         }

//     } while (1);
// }







   

    // realizarAnaliseFrequencia(conteudo, chave);

    // mostrarEstado(conteudo, chave);

    // ... depois de realizarAnaliseFrequencia ...

    // Loop de teste para a Opção 5
//     char opcao;
//     do {
//         printf("\nO texto esta legivel? (S/N) ou (E) para Editar chave: ");
//         scanf(" %c", &opcao);
        
//         if (toupper(opcao) == 'E') {
//             editarChaveManual(chave);
            
//             // Mostra como ficou o texto com a mudança
//             mostrarEstado(conteudo, chave);
//         }
        
//     } while (toupper(opcao) != 'S');
    
//     printf("\nTrabalho finalizado!\n");


//     // Limpeza
//     free(conteudo);
//     return 0;
// }



    //chave['A' - 'A'] = 'S';   // significa: A → S
    //chave['E' - 'A'] = 'H';   // significa: E → H

    //printf("Nome do arquivo: ");
    //scanf("%s", nome_arquivo);

    //strcat(nome_arquivo, ".txt");
    //strcat(caminho_arquivo, nome_arquivo);

    //char *conteudo = ler_arquivo(caminho_arquivo);
    //if (!conteudo) {
    //    printf("Erro ao ler arquivo!\n");
    //    return 1;
   // }

    //printf("Texto : %s\n\n", conteudo);

    // salvar texto criptografado (por enquanto o mesmo texto)
    //escrever_arquivo("HysilensCripto.txt", conteudo);

    // mostrar estado inicial da criptoanálise (etapa 1)
    //mostrarEstado(conteudo, chave);

    // opção 6: salvar chave encontrada
  //  int valorChave = 9;   // nome corrigido
   // printf("Nome do arquivo para guardar a chave: ");
   // scanf("%s", nome_arquivo);

   // strcat(nome_arquivo, ".txt");
   // registrarChave(valorChave, nome_arquivo);

    //printf("Confira na pasta SaidaFinal.\n");

    //free(conteudo);
   // return 0;
// }
