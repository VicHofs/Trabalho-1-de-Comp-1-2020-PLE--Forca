/* funcao que imprime o desenho da forca */
void hangman(int strikes);
/* funcao que retorna o numero de palavras no arquivo de entrada */
int quantasPalavrasHaNoArquivoDeEntrada(FILE* arquivoEntrada);
/* funcao que retorna uma string com as palavras que estavam no arquivo de entrada */
char** monta_vocabulario(FILE* arquivoEntrada);
/* funcao que escolhe uma palavra aleatoria do arquivo de entrada com base na string que contem as palavras que estavam nele */
char* escolheUmaPalavraAleatoria(char** vocabulario, int numeroPalavras);
/* funcao de suporte que calcula o logaritmo na base 2 de n recursivamente */
unsigned int logaritmoBase2(unsigned int n);
/* funcao que pre-processa a palavra chave para facilitar a validacao da sugestao/entrada do usuario */ 
int preProcessamentoPalavra(char*palavra, char letraDesejada);
/* funcao que retorna quantas vezes certa letra sugerida pelo usuario esta na palavra chave*/
int displayProcesso(char* palavra, int alfabetoDaPalavra[], char letraInput);
