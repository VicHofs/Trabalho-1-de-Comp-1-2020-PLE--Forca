 /* Trabalho de Final de Curso - Computacao 1 - MAB120 - UFRJ PLE 2020

 Alunos autores:
 *Joao Pedro Silveira - DRE 120019402
 Riquelme Gomes - DRE ?
 Victor Hofsetter - DRE 120062120

Sob orientacao dos professores: Andre Brito e Valeria Bastos

DescriÃ§ao: Versao simplificada do jogo popular de tabuleiro forca */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "utils.h"

/* definir o limite de "vidas" ou chances */
#define CHANCES_MAX 6

int main(int argc, char *argv[ ]) 
{
    char *categories[3] = {"animais", "artistas", "objetos"}, nomeArquivoEntrada[20];
    short int categoria;
    FILE* arquivoPalavrasEntrada;
    char **vocabulario;
    int alfabeto[26] = {0}, contador = 0, chances = CHANCES_MAX, letrasFaltantes, vezesNaPalavra = 0, i = 0;
    char palavraDisplay[32], *palavraChave, letraSugeridaUsuario, querProximaPalavra;
    int numeroDePalavrasNoArquivo = 0;


    /* mensagem de introducao ao jogo */
    printf("Bem vindo ao Jogo da Forca!\n");


    /* loop que controla a execucao do jogo no geral, comecando pelo menu inicial de temas */
    while(1)
    {
        /* escolha de categoria */
        printf("Selecione a categoria que deseja jogar: \n");
        for (i = 0; i < 3; i++) 
        {
            printf("%d-%s\n", i + 1, categories[i]);
        }

        printf("\nSua resposta: ");
        scanf("%hi", &categoria);
        while ((getchar()) != '\n');

        /* validacao da escolha de categoria */
        if (categoria < 1 || categoria > 3)
        {
            printf("Usage error: entrada deve ser um numero valido entre 1 e 3, inclusive.\n");
            continue;
        }
        
        /* leitura do arquivo pertinente Ã  categoria escolhida */
        sprintf(nomeArquivoEntrada,"%s.in", categories[categoria-1]);

        if (!(arquivoPalavrasEntrada = fopen(nomeArquivoEntrada, "r"))) 
        {
            perror("Erro ao abrir arquivos com palavras. ");
            return 1;
        }

        vocabulario = monta_vocabulario(arquivoPalavrasEntrada);
        numeroDePalavrasNoArquivo = quantasPalavrasHaNoArquivoDeEntrada(arquivoPalavrasEntrada);

        fclose(arquivoPalavrasEntrada);
        /* inicio do jogo com palavra do tema escolhido */

        /* loop que controla a execucao do jogo com palavras do mesmo tema */
        while (1)
        {

            /* escolher a palavra chave da vez */
            palavraChave = escolheUmaPalavraAleatoria(vocabulario,numeroDePalavrasNoArquivo);

            if(argc == 2)
            {
                if(strcmp(argv[1],"teste")== 0)
                {
                    printf("\npalavra chave = %s\n", palavraChave);
                }
            }


            /* preencher todas as letras da palavra com asteristicos 
            asteristicos estes, que somem conforme usuÃ¡rio acerta */
            for (i = 0; i < 32; i++)
            {
                palavraDisplay[i] = '*';
            }

            /* numero de letras da palavraChave - serve de contador para quantas letras faltam adivinhar */
            letrasFaltantes = strlen(palavraChave);


            chances = CHANCES_MAX;

            /* preprocessamento da palavra chave para facilitar identificacÃ£o de letras e suas posiÃ§Ãµes na palavra */
            for(contador = 0;contador < 26;contador++)
            {
                alfabeto[contador] = preProcessamentoPalavra(palavraChave, (char) 97 + contador);
            } 

            /* inicio da gameplay de fato */

            while (letrasFaltantes > 0 && chances > 0)
            {   
                /* informar status */

                printf("\nResumo: %i chances restantes e ", chances);
                printf("faltam %i letras a serem adivinhadas.\n", letrasFaltantes);
                
                /* imprimir o boneco da forca */

                hangman(chances);

                /* ler entrada do usuario e validar */

                while(1)
                {
                    puts("Entre com uma letra: ");
                    scanf("%c", &letraSugeridaUsuario);
                    while ( getchar() != '\n' );
                    letraSugeridaUsuario = tolower(letraSugeridaUsuario);

                    if ((int)letraSugeridaUsuario < 97 || (int) letraSugeridaUsuario > 122)
                    {
                        printf("Usage error: entrada invalida\n");
                    }

                    else break;
                }

                vezesNaPalavra = displayProcesso(palavraDisplay, alfabeto, letraSugeridaUsuario);

                /* checar se a letra escolhida esta palavra */
                
                if (vezesNaPalavra == 0)
                {
                    chances--;
                    printf("Voce perdeu uma chance. %c nao esta na palavra, veja!\n", letraSugeridaUsuario);
                }

                /* checar quantas vezes a letra escolhida esta palavra */
                else
                {
                    letrasFaltantes -= vezesNaPalavra;
                    printf("Parabens, voce acertou. %c esta %i vezes na palavra, veja!\n", letraSugeridaUsuario, vezesNaPalavra);
                }

                /* imprimir progresso */
                for (contador = 0; contador < 32; contador++)
                {
                    if (contador >= 32 - strlen(palavraChave))
                    contador == 31? printf("%c\n", palavraDisplay[contador]): printf("%c", palavraDisplay[contador]);
                }

                /* imprimir mensagem de vitoria */
                if (letrasFaltantes == 0)
                {
                    printf("Parabens, voce VENCEU!!!! :-)\n");
                }

                /* imprimir mensagem de perda */
                if (chances == 0)
                {
                    printf("Puxa, voce PERDEU! ;-)\n");
                    printf("A palavra-chave era %s\n", palavraChave);
                }
                
            }

            /* perguntar ao usuario se deseja prosseguir para a proxima palavra do mesmo tema */
            while (1)
            {
                printf("Deseja ir para a prÃ³xima palavra -do mesmo tema-?(y / n) ");
                scanf("%c", &querProximaPalavra);
                while ( getchar() != '\n' );
                querProximaPalavra = tolower(querProximaPalavra);

                if (querProximaPalavra != 'y' && querProximaPalavra != 'n')
                {
                    printf("Usage error: entrada invalida, escolha y ou n\n");
                }
                else break;    
            }   

            /* se sim, continuar para proxima palavra do tema(proximo laÃ§o do loop) */
            if (querProximaPalavra == 'y')
            {
                continue;
            }

            /* se nao, voltar ao menu inicial(encerrar loop atual e voltar ao "superior") */
            else break;

        }

        /* perguntar ao usuario se deseja encerrar o jogo (caso nÃ£o,voltar ao menu inicial) */
        while(1)
        {
            printf("Deseja ir para o menu inicial(se nÃ£o, o jogo sera encerrado)?(y / n) ");
            scanf("%c", &querProximaPalavra);
            while ( getchar() != '\n' );
            querProximaPalavra = tolower(querProximaPalavra);

            if (querProximaPalavra != 'y' && querProximaPalavra != 'n')
            {
                printf("Usage error: entrada invalida, escolha y ou n\n");
            }
            else break;    
        } 

        /* se sim, continuar para menu inicial(proximo laÃ§o do loop) */
        if (querProximaPalavra == 'y')
        {
            free(vocabulario);
            continue;
        }

        /* se nao, encerrar jogo(encerrar loop) */
        else break;

    } 
    printf("\n--FIM DE JOGO--\n");
    printf("\nMuito obrigado por jogar nosso jogo da forca\n");
    printf("-Joao, Victor e Riquelme\n");
    
    return 0;

}
