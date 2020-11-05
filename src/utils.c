#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include "utils.h"
/* definir o limite de letras por palavra */
#define MAX_LETRASPORPALAVRA 32
//vamos colocar todas as utilidades do jogo nesse arquivo
//lembrar de incluir a prototipagem no header para cada uma

/* funcao que imprime o desenho da forca */
void hangman(int strikes) {
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
