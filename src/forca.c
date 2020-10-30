#if defined(_WIN32) || defined(_WIN64)
  #define CLEAR "cls"
#elif defined(__unix__) || defined(__APPLE__)
  #define CLEAR "clear"
#endif

#define MAXW 168

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "utils.h"

char *categories[3] = {"animais", "artistas", "objetos"}, *words[MAXW], filename[20], word[30], guess;
int revealed[26] = {0}, guessed[26] = {0}, present[26] = {0}, strikes = 0, done = 0, pick;

int main( void ) {
  //escolha de categoria
  printf("Selecione a categoria que deseja jogar: \n");
  for (int i = 0; i < 3; i++) {
    printf("%d-%s\n", i + 1, categories[i]);
  }
  int interaction = getch() - 49;
  strcat(filename, categories[interaction]); strcat(filename, ".in");

  //leitura do arquivo pertinente à categoria escolhida
  FILE *istream = fopen(filename, "r");
  if (istream == NULL) {
    perror("Erro");
    exit(1);
  }
  int n = 0;
  while (fgets(word, sizeof(word), istream) != NULL) {
    if (word[strlen(word)-1] == '\n') word[strlen(word)-1] = '\0';
    words[n] = (char *) malloc(strlen(word) + 1);
    strcpy(words[n], word);
    n++;
  }
  rewind(istream);
  fclose(istream);

  pick = randint(0, n);

  //começo do jogo
  for (int i = 0; i <= strlen(words[pick]); i++) {
    word[i] = words[pick][i];
    present[word[i] - 65] = 1;
  }

  tip(word, guessed, revealed);

  while (1) {
    if (done) break;
    system(CLEAR);
    if (strikes == 6) {
      hangman(6);
      break;
    }
    hangman(strikes);
    for (int i = 0; i < 26; i++) if (!guessed[i]) printf("%c ", (char)(i + 65));
    printf("\n\n");
    word_progress(word, revealed, &done);
    if (done) break;
    test_char(&guess, present, revealed, guessed, &strikes);
  }

  printf("%s\n", (done ? "Bom trabalho!\a" : "F"));
  if (!done) printf("A resposta era: %s\n", word);
  printf("Gostaria de jogar novamente? S/N\n");
  do 
    guess = getch();
  while (guess != 'S' && guess != 's' && guess != 'N' && guess != 'n');
  (guess == 'S' || guess == 's' ? system("forca.exe") : exit(0));

  return 0;
}