//header com as declarações das utilidades do jogo
int randint(int lower, int upper);

void tip(char *word, int *guessed, int *revealed);

void hangman(int strikes);

void word_progress(char *word, int *revealed, int *done);

void test_char(char *var, int *present, int *revealed, int *guessed, int *strikes);