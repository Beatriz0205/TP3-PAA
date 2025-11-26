#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "../include/Arquivo.h"
#include "../include/ArquivoSaida.h"
#include "../include/Cripto.h"
#include "../include/Frequencia.h"
#include "../include/Casamento.h"




// int main(){
//     //////////////////////////////
//     //Para quando for o caso de ler os 12 arquivos criar um vetor com os 12 nomes e por para rodar ele
//     //como cada grupo vai ter seu txt e o leitor não vai adicionar mais podemos por diretamente o nome do nosso quando for preciso

//     /////////////////////////////


//     //usado para ler o arquivo

//     char chave[26];
//     inicializarChave(chave);


//     char nome_arquivo[256];
//     char caminho_arquivo[150] = "arq/";
//     printf("Nome do arquivo: ");
//     scanf("%s", nome_arquivo);
//     strcat(nome_arquivo, ".txt");
//     strcat(caminho_arquivo, nome_arquivo);
//     char *conteudo = ler_arquivo(caminho_arquivo);
//     printf("Texto : %s\n",conteudo);
//     printf("\n");

//     //vai ser usado para salvar o texto criptografado
//     //pelo que vi no menu teremos apenas os 12 textos
//     //o nosso é esse
//     escrever_arquivo("HysilensCripto.txt", conteudo);
//     mostrarEstado(conteudo, chave);


//     //Essa vai ser para a opção 6
//     int chave = 9;
//     printf("Nome do arquivo para guardar a chave: ");
//     scanf("%s", nome_arquivo);
//     strcat(nome_arquivo, ".txt");
//     registrarChave(chave,nome_arquivo);
//     printf("Confira na pasta SaidaFinal.\n");
//     return 0;
// }

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

                char caminho_arquivo[150] = "arqCripto/"; 
                
                printf("Nome do arquivo (sem .txt, ex: Hysilens): ");
                scanf("%s", nome_arquivo);

                strcat(nome_arquivo, ".txt");
                strcat(caminho_arquivo, nome_arquivo);

                conteudo = ler_arquivo(caminho_arquivo);
                if (!conteudo) {
                    printf("Erro ao ler arquivo!\n");
                    return 1;
                }
                //printf("Texto Original: %s\n\n", conteudo);

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
                    char padrao[strlen(conteudo)];
                    int posicoesOcorrenciasExatas[strlen(conteudo)];
                    printf("Qual o padrao utilizado?\n");
                    scanf("%s",padrao);
                    getchar();

                    int qntOcorrenciasExatas= boyerMooreHorspool(conteudo,padrao,posicoesOcorrenciasExatas);

                    printf("Ocorrencias %d\n\n",qntOcorrenciasExatas);
                    printf("");
                    exibirOcorrencias(conteudo,posicoesOcorrenciasExatas,strlen(padrao),qntOcorrenciasExatas);

                    printf("\n\nDeseja buscar outro padrão? (s/n): ");
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
                    int posicoesOcorrenciasAprox[strlen(conteudo)];
                    printf("Qual o padrao e a tolerancia (k) utilizados?\n");
                    scanf("%s %d",padrao,&k);
                    getchar();

                    int qntOcorrenciasAprox= ShiftAndAproximado(conteudo,padrao,k,posicoesOcorrenciasAprox);

                    printf("Ocorrencias %d\n\n",qntOcorrenciasAprox);
                    printf("");
                    exibirOcorrencias(conteudo,posicoesOcorrenciasAprox,strlen(padrao),qntOcorrenciasAprox);

                    printf("\n\nDeseja buscar outro padrão? (s/n): ");
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
