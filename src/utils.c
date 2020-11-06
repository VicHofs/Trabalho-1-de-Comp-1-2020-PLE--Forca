//*definições das funções de utilidade do jogo
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include "utils.h"

//retorna um número inteiro entre os limites lower (inclusivo) e upper
int randint(int lower, int upper) {
  srand(time(0) + clock());
  return (rand() % (upper - lower + 1)) + lower;
}

//revela algumas das letras da palavra sorteada para inicializar o gameplay
void tip(char *word, int *guessed, int *revealed) {
  int iter = strlen(word) / 3;
  char c;
  for (int i = 0; i < iter; i++) {
    do
      c = word[randint(0, strlen(word) - 1)];
    while (revealed[c - 65]);
    guessed[c - 65] = 1;
    revealed[c - 65] = 1;
  }
}

//imprime no stdout o progresso do jogo baseado no número de erros (strikes)
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

//imprime no stdout o progresso de acertos na palavra
void word_progress(char *word, int *revealed, int *done) {
  *done = 1;
  for (int i = 0; i < strlen(word); i++) {
    if (word[i] < 65 || word[i] > 90) {
      printf("%c", word[i]);
    }
    else {
      if (revealed[word[i] - 65]) printf("%c", word[i]);
      else {
        printf("_");
        if (*done) *done = 0;
      }
    }
  }
  printf("\n");
}

/*
checa se o caracter var é válido e se encontra na palavra,
  - caso seja inválido, requisita outro input
  - incrementa o número de erros se não for encontrado
  - marca como testado e o revela na palavra caso contrário
*/
void test_char(char *var, int *present, int *revealed, int *guessed, int *strikes) {
  do 
    *var = getch();
  while (*var < 65 || (*var > 90 && *var < 97) || *var > 122);

  if (*var >= 97) *var -= 32;

  if (present[*var - 65]) revealed[*var - 65] = 1;

  else *strikes += 1;

  guessed[*var - 65] = 1;
}
