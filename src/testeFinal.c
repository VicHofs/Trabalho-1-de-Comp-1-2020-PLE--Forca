#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

/* definir o limite de letras por palavra */
#define MAX_LETRASPORPALAVRA 32

/* definir o limite de "vidas" ou chaces */
#define CHANCES_MAX 5

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
unsigned int Log2n(unsigned int n) 
{ 
    return (n > 1) ? 1 + Log2n(n / 2) : 0; 
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
        int x = Log2n(i) - (j - k);
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
    char* nomeArquivoEntrada = "minhasPalavras.txt";
    char **vocabulario;
    FILE* arquivoPalavrasEntrada;
    int alfabeto[26] = {0}, contador = 0, chances = CHANCES_MAX, letrasFaltantes, vezesNaPalavra = 0, i = 0;
    char palavraDisplay[32], *palavraChave, letraSugeridaUsuario;
    int numeroDePalavrasNoArquivo = 0;
    if(!(arquivoPalavrasEntrada = fopen(nomeArquivoEntrada, "r"))) return 1;
    vocabulario = monta_vocabulario(arquivoPalavrasEntrada);
    numeroDePalavrasNoArquivo = quantasPalavrasHaNoArquivoDeEntrada(arquivoPalavrasEntrada);
    

    /* imprimir todas as palavras do arquivo
    for(int i =0; i < numeroDePalavrasNoArquivo; i++)
    {
        printf("%s\n", vocabulario[i]);
    } */

   
    

    /* ---- JOGABILIDADE BASICA ---- */

    
    /* escolher a palavra chave da vez */
    palavraChave = escolheUmaPalavraAleatoria(vocabulario,numeroDePalavrasNoArquivo);
    printf("palavra chave = %s\n", palavraChave);


    /* preencher todas as letras da palavra com asteristicos 
    asteristicos somem conforme usuário acerta */
    for (i = 0; i < 32; i++)
    {
        palavraDisplay[i] = '*';
    }

    /* numero de letras da palavraChave - serve de contador para quantas letras faltam adivinhar */
    letrasFaltantes = strlen(palavraChave);

    /* preprocessamento da palavra chave para facilitar identificacão de letras e suas posições na palavra */
    for(;contador < 26;contador++)
    {
        alfabeto[contador] = preProcessamentoPalavra(palavraChave, (char) 97 + contador);
    } 


    while (letrasFaltantes > 0 && chances > 0)
    {   
        while(1)
        {
            puts("Entre com uma letra: ");
            scanf("%c", &letraSugeridaUsuario);
            while ( getchar() != '\n' );
            letraSugeridaUsuario = tolower(letraSugeridaUsuario);

            if((int)letraSugeridaUsuario < 97 || (int) letraSugeridaUsuario > 122)
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
            printf("Voce perdeu uma chance. %c nao esta na palavra.\n", letraSugeridaUsuario);
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
            printf("Parabens, voce VENCEU!!!!\n");
        }

        /* imprimir mensagem de perda */
        if (chances == 0)
        {
            printf("Puxa, voce PERDEU!\n");
        }
        
    }

    fclose(arquivoPalavrasEntrada);

    return 0;
}