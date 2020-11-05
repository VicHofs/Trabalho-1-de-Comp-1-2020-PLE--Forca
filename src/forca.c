 /* Trabalho de Final de Curso - Computacao 1 - MAB120 - UFRJ PLE 2020

 Alunos autores:
 Joao Pedro Silveira - DRE 120019402
 Riquelme Gomes - DRE ?
 Victor Hofsetter - DRE ?

Sob orientacao dos professores: Andre Brito e Valeria Bastos

Descriçao: Versao simplificada do jogo popular de tabuleiro forca */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

/* definir o limite de letras por palavra */
#define MAX_LETRASPORPALAVRA 32

/* definir o limite de "vidas" ou chaces */
#define CHANCES_MAX 6

/* funcao que imprime o desenho da forca */
void hangman(int strikes) 
{
  char head = strikes == 6 ? '0' : 'O', torso = '|', l_arm = '/', r_arm = '\\', l_leg = '/', r_leg = '\\';

  printf(
" ________\n\
 |      |\n\
 |      %c\n\
 |     %c%c%c\n\
 |     %c %c\n\
 |\n\
---\n", 
     strikes >= 1 ? head : ' ', 
     strikes >= 3 ? l_arm : ' ', 
     strikes >= 2 ? torso : ' ', 
     strikes >= 4 ? r_arm : ' ', 
     strikes >= 5 ? l_leg : ' ', 
     strikes >= 6 ? r_leg : ' '
    );
}

/* funcao que retorna o numero de palavras no arquivo de entrada */
int quantasPalavrasHaNoArquivoDeEntrada(FILE* arquivoEntrada)
{
    int contador = 0; 
    char buffer[MAX_LETRASPORPALAVRA];

    rewind(arquivoEntrada);

    while(!feof(arquivoEntrada))
    {

        fscanf(arquivoEntrada, "%s", buffer);
        contador++;
    }

    return contador;
}

/* funcao que retorna uma string com as palavras que estavam no arquivo de entrada */
char** monta_vocabulario(FILE* arquivoEntrada)
{
    int numeroDePalavras = quantasPalavrasHaNoArquivoDeEntrada(arquivoEntrada), i = 0;
    char buffer[MAX_LETRASPORPALAVRA];
    char** palavras = malloc(sizeof(char*) * numeroDePalavras);

    rewind(arquivoEntrada);
    for (i = 0; i < numeroDePalavras; i++)
    {   
        fscanf(arquivoEntrada, "%s", buffer);
        palavras[i] = (char*)malloc(strlen(buffer)+1);
        strcpy(palavras[i], buffer); 
    }
    return palavras;

}

/* funcao que escolhe uma palavra aleatoria do arquivo de entrada com base na string que contem as palavras
que estavam nele */
char* escolheUmaPalavraAleatoria(char** vocabulario, int numeroPalavras)
{
    int indexAleatorio = 0;
    srand(time(NULL));
    indexAleatorio = rand() % numeroPalavras;

    return vocabulario[indexAleatorio];
}

/* funcao de suporte que calcula o logaritmo na base 2 de n recursivamente */
unsigned int logaritmoBase2(unsigned int n) 
{ 
    return (n > 1) ? 1 + logaritmoBase2(n / 2) : 0; 
} 

/* funcao que pre-processa a palavra chave para facilitar a validacao da sugestao/entrada do usuario */ 
int preProcessamentoPalavra(char*palavra, char letraDesejada)
{
    int contador = 0, minhaStringBinaria = 0;
    int letrasFaltantes = strlen(palavra);
    for (contador = 0; contador < letrasFaltantes; contador++)
    {
        if (palavra[contador] == letraDesejada)
        {
            minhaStringBinaria = minhaStringBinaria | 1;
            
        }

        if (contador != letrasFaltantes -1)
        {
            minhaStringBinaria = minhaStringBinaria << 1;
        }
    }

    return minhaStringBinaria;

}

/* funcao que retorna quantas vezes certa letra sugerida pelo usuario esta na palavra chave*/
int displayProcesso(char* palavra, int alfabetoDaPalavra[], char letraInput)
{
    int codigoLetra = (int) letraInput - 97;
    int contador = 0;
    int n = alfabetoDaPalavra[codigoLetra];
    unsigned i, j = 31, k = 0; 
    if(n == 0) return 0;
    
    for (i = 1 << 31; i > 0; i = i / 2, j--, k++) 
    {
        int x = logaritmoBase2(i) - (j - k);
        if (n & i)
        {
            palavra[x] = letraInput;
            contador++;
        }
    }
    return contador;
}

int main(void) 
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

        scanf("%hi", &categoria);
        while ((getchar()) != '\n');

        /* validacao da escolha de categoria */
        if (categoria < 1 || categoria > 3)
        {
            printf("Usage error: entrada deve ser um numero valido entre 1 e 3, inclusive.\n");
            continue;
        }
        
        /* leitura do arquivo pertinente à categoria escolhida */
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

            printf("palavra chave = %s\n", palavraChave);


            /* preencher todas as letras da palavra com asteristicos 
            asteristicos estes, que somem conforme usuário acerta */
            for (i = 0; i < 32; i++)
            {
                palavraDisplay[i] = '*';
            }

            /* numero de letras da palavraChave - serve de contador para quantas letras faltam adivinhar */
            letrasFaltantes = strlen(palavraChave);


            chances = CHANCES_MAX;

            /* preprocessamento da palavra chave para facilitar identificacão de letras e suas posições na palavra */
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
                }
                
            }

            /* perguntar ao usuario se deseja prosseguir para a proxima palavra do mesmo tema */
            while (1)
            {
                printf("Deseja ir para a próxima palavra -do mesmo tema-?(y / n) ");
                scanf("%c", &querProximaPalavra);
                while ( getchar() != '\n' );
                querProximaPalavra = tolower(querProximaPalavra);

                if (querProximaPalavra != 'y' && querProximaPalavra != 'n')
                {
                    printf("Usage error: entrada invalida, escolha y ou n\n");
                }
                else break;    
            }   

            /* se sim, continuar para proxima palavra do tema(proximo laço do loop) */
            if (querProximaPalavra == 'y')
            {
                continue;
            }

            /* se nao, voltar ao menu inicial(encerrar loop atual e voltar ao "superior") */
            else break;

        }

        /* perguntar ao usuario se deseja encerrar o jogo (caso não,voltar ao menu inicial) */
        while(1)
        {
            printf("Deseja ir para o menu inicial(se não, o jogo sera encerrado)?(y / n) ");
            scanf("%c", &querProximaPalavra);
            while ( getchar() != '\n' );
            querProximaPalavra = tolower(querProximaPalavra);

            if (querProximaPalavra != 'y' && querProximaPalavra != 'n')
            {
                printf("Usage error: entrada invalida, escolha y ou n\n");
            }
            else break;    
        } 

        /* se sim, continuar para menu inicial(proximo laço do loop) */
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
