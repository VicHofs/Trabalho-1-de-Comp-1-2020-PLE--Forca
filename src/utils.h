//*header com as declarações das utilidades do jogo

//retorna um número inteiro entre os limites lower (inclusivo) e upper
int randint(int lower, int upper);

//revela algumas das letras da palavra sorteada para inicializar o gameplay
void tip(char *word, int *guessed, int *revealed);

//imprime no stdout o progresso do jogo baseado no número de erros (strikes)
void hangman(int strikes);

//imprime no stdout o progresso de acertos na palavra
void word_progress(char *word, int *revealed, int *done);

/*
checa se o caracter var é válido e se encontra na palavra,
  - caso seja inválido, requisita outro input
  - incrementa o número de erros se não for encontrado
  - marca como testado e o revela na palavra caso contrário
*/
void test_char(char *var, int *present, int *revealed, int *guessed, int *strikes);