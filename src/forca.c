#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "utils.h"

#define MAXW 168

char *categorias[3] = {"animais", "artistas", "objetos"}, *words[MAXW], filename[20], input[20]; 

int main( void ) {
  printf("Selecione a categoria que deseja jogar: \n");
  for (int i = 0; i < 3; i++) {
    printf("%d-%s\n", i + 1, categorias[i]);
  }
  int interaction = getch() - 49;
  strcat(filename, categorias[interaction]); strcat(filename, ".in");
  FILE *istream = fopen(filename, "r");

  if (istream == NULL) {
    perror("Erro");
    exit(1);
  }
  int i = 0;
  while (fgets(input, sizeof(input), istream) != NULL) {
    fputs(input, stdout);
  }

  fclose(istream);

  for (int i = 0; i < MAXW; i++) {
    printf("%s\n", words[i]);
  }

  return 0;
}