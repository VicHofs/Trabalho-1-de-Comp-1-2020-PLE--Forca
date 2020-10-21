#include <stdio.h>
#include "utils.h"
//vamos colocar todas as utilidades do jogo nesse arquivo
//lembrar de incluir a prototipagem no header para cada uma

void hangman(int strikes) {
  char head = strikes == 6 ? '0' : 'O', torso = '|', l_arm = '/', r_arm = '\\', l_leg = '/', r_leg = '\\';

  printf(
" ________\n\
 |      |\n\
 |      %c\n\
 |     %c%c%c\n\
 |     %c %c\n\
 |\n\
---", 
     strikes >= 1 ? head : ' ', 
     strikes >= 3 ? l_arm : ' ', 
     strikes >= 2 ? torso : ' ', 
     strikes >= 4 ? r_arm : ' ', 
     strikes >= 5 ? l_leg : ' ', 
     strikes >= 6 ? r_leg : ' '
    );

}