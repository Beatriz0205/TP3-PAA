#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_PADRAO 256

#include "../include/Arquivo.h"
#include "../include/ArquivoSaida.h"
#include "../include/Cripto.h"
#include "../include/frequencia.h"
#include "../include/Casamento.h"


void voltarMenu() {
    int op;
    printf("Digite 1 para voltar ao menu: \n");
    scanf("%d", &op);

    while (getchar() != '\n');

    if (op != 1) {
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
    char nome_arquivo[100];

    int deslocamentoAtual = 0; 
    int arquivoCarregado = 0;

    srand(time(NULL));
    
    printf("=== SISTEMA DE CRIPTOANÁLISE ===\n\n");

    do {
        printf("============= MENU ============\n\n");
        printf("1. Ler arquivo (Criptografado ou nao)\n");
        printf("2. Criptografar texto\n");
        printf("3. Mostrar estado da cripoanalise\n");
        printf("4. Chute baseado na analise de frequencia\n");
        printf("5. Casamento exato\n");
        printf("6. Casamento aproximado\n");
        printf("7. Alterar chave de criptografia\n");
        printf("8. Exportar resultado e sair\n");
        printf("0. Digite qualquer outro valor para encerrar\n");

        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: {
                // Limpa a chave anterior se houver
                inicializarChave(chave);

                printf("Nome do arquivo (sem .txt, ex: Hysilens): ");
                scanf("%s", nome_arquivo);

                // Se já tinha algo carregado, libera a memória antes
                if (conteudo) free(conteudo);

                conteudo = ler_arquivo(nome_arquivo);

                if (!conteudo) {
                    printf("Erro ao ler arquivo! Verifique se ele existe na pasta 'arq/'.\n");
                } else {
                    printf("\nArquivo carregado com sucesso para a memoria!\n");
                    printf("Texto Original: %s\n", conteudo);

                    
                    // Inicializa contadores
                    qntCaracteres = contaCaracteres(conteudo);
                    qntPalavras = contaPalavras(conteudo);
                    arquivoCarregado = 1;
                }

                voltarMenu();
                break;
            }
            case 2: {
                // Verificação 
                if (conteudo == NULL) {
                    printf("\n[!] Erro: Nenhum texto carregado. Use a Opcao 1 primeiro para ler um arquivo.\n");
                    voltarMenu();
                    break;
                }

                char nomeArquivoSaida[256];

                printf("\n=== CRIPTOGRAFAR TEXTO ATUAL ===\n");
                printf("Informe o nome para salvar o arquivo criptografado (sem .txt): ");
                scanf("%s", nomeArquivoSaida);
                while (getchar() != '\n'); // Limpar buffer do teclado

                // Gerar chave aleatória 
                // Gera um número entre 1 e 25
                deslocamentoAtual = (rand() % 25) + 1;

                printf("\n-> Gerando chave aleatoria...\n");
                printf("-> Deslocamento sorteado: %d (Anote para conferir depois!)\n", deslocamentoAtual);

                // Salva no disco 
                // Isso cria o arquivo físico na pasta arqCripto/
                cifraDeslocamento(nomeArquivoSaida, conteudo, deslocamentoAtual);

                //Atualiza na memória 
                // Isso garante que se você for na Opção 4 agora, vai analisar o texto já criptografado
                aplicarCifraMemoria(conteudo, deslocamentoAtual);

                printf("\n[Sucesso] Arquivo salvo em 'arqCripto/%s.txt'.\n", nomeArquivoSaida);
                printf("[Aviso] O texto na memoria do programa foi atualizado para a versao criptografada.\n");
                printf("Agora voce pode usar as opcoes de Analise (3, 4, 5...) neste texto.\n");
                
                // Atualiza estatísticas do novo texto
                qntCaracteres = contaCaracteres(conteudo);
                qntPalavras = contaPalavras(conteudo);

                arquivoCarregado = 1;

                voltarMenu();
                break;
            }

            case 3: {
                if (!arquivoCarregado) {
                    printf("Carregue um arquivo antes (Opcao 1)!\n");
                } else {
                    mostrarEstado(conteudo, chave);
                }
                voltarMenu();
                break;
        }
            

            case 4: {
                if (!arquivoCarregado) {
                    printf("Carregue e criptografe um arquivo antes (Opcao 1)!\n");
                    voltarMenu();
                    break;
                }

                printf("\n==============================================\n");
                printf(" ANALISE 1: ARQUIVO INDIVIDUAL (%s)\n", nome_arquivo);
                printf("==============================================\n");
                
                realizarAnaliseFrequencia(conteudo, chave);
                
                printf("\nPressione ENTER para ver a Analise Global (12 Arquivos)...\n");
                getchar();

                printf("\n==============================================\n");
                printf(" ANALISE 2: TODOS OS 12 ARQUIVOS (CONJUNTO)\n");
                printf("==============================================\n");
                printf("Gerando mega-texto com o mesmo deslocamento (%d)...\n", deslocamentoAtual);

                if (deslocamentoAtual == 0) {
                    printf("[Aviso] Voce ainda nao criptografou o texto (Opcao 2).\n");
                    printf("Usando deslocamento 0 (Texto Original) para a comparacao.\n");
                } else {
                    printf("Gerando mega-texto com o mesmo deslocamento (%d)...\n", deslocamentoAtual);
                }

                char *textoGlobal = gerarTextoGlobal(deslocamentoAtual);
                
                if (textoGlobal) {
                    realizarAnaliseFrequencia(textoGlobal, chave);
                    free(textoGlobal);
                    
                    printf("\n[DICA] A analise do conjunto costuma ser mais precisa!\n");
                    printf("A chave foi atualizada com base na estatistica global.\n");
                } else {
                    printf("Erro ao gerar texto global.\n");
                }
                
                voltarMenu();
                break;
            }
               
            case 5:{

                if (!arquivoCarregado){
                    printf("Carregue um arquivo antes\n");
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

                    if (qntPalavras > 0)
                        printf("\n\nFreq. rel. palavras: %.2f%%", frequenciaPalavras(qntOcorrenciasExatas, qntPalavras) * 100);
                    if (qntCaracteres > 0)
                        printf("\nFreq. rel. letras: %.2f%%\n", frequenciaLetras(qntOcorrenciasExatas, tamPadrao, qntCaracteres) * 100);

                    free(posicoesOcorrenciasExatas);

                    printf("\nDeseja buscar outro padrão? (s/n): ");
                    scanf("%c", &continua);
                    getchar();

                } while (continua == 's' || continua == 'S');
                voltarMenu();
                break;
            }

            case 6:{

                if (!arquivoCarregado){
                    printf("Carregue um arquivo antes\n");
                    voltarMenu();
                    break;
                }

                char *textoBusca = aplicarChaveParcial(conteudo, chave);
                if (textoBusca) {
                    escrever_arquivo("TextoParcial", textoBusca);
                    printf("\n[Info] Busca sera feita no 'arqCripto/TextoParcial.txt' (Texto Parcialmente Decifrado).\n");
                } else {
                    printf("Erro de memoria.\n");
                    break;
                }

                char continua;

                do{
                    char padrao[256];
                    int k;
                    int *posicoes = malloc(strlen(textoBusca) * sizeof(int));
                    

                    printf("Qual o padrao e a tolerancia (k) utilizados?\n");
                    scanf(" %255s %d", padrao, &k);
                    
                    getchar();

                    for (int i = 0; padrao[i] != '\0'; i++) {
                        padrao[i] = toupper((unsigned char)padrao[i]);
                    }

                    int tamPadrao=strlen(padrao);

                    int ocorrencias = ShiftAndAproximado(textoBusca, padrao, k, posicoes);

                    printf("\nOcorrencias Aproximadas %d\n\n",ocorrencias);
                    printf("");
                    exibirOcorrencias(textoBusca, posicoes, tamPadrao, ocorrencias);

                    free(posicoes);

                    if (qntPalavras > 0)
                        printf("\n\nFreq. rel. palavras: %.2f%%", frequenciaPalavras(ocorrencias, qntPalavras) * 100);
                    if (qntCaracteres > 0)
                        printf("\nFreq. rel. letras: %.2f%%", frequenciaLetras(ocorrencias, tamPadrao, qntCaracteres) * 100);


                    printf("\nDeseja buscar outro padrão? (s/n): ");
                    scanf("%c", &continua);
                    getchar();

                } while (continua == 's' || continua == 'S');

                free(textoBusca);

                voltarMenu();
                break;
            }
            case 7: {
                if (arquivoCarregado) {
                    editarChaveManual(chave);
                    mostrarEstado(conteudo, chave);
                } else {
                    printf("Carregue um arquivo antes.\n");
                }
                voltarMenu();
                break;
            }
            case 8: {
                printf("Nome do arquivo para guardar a chave: ");
                scanf("%s", nome_arquivo);
                registrarChave(deslocamentoAtual,nome_arquivo);
                printf("Confira na pasta SaidaFinal.\n");
            }

            default:
                printf("Programa encerrado.\n");        
                exit(0);
        }

    } while (1);
    return 0;
}

