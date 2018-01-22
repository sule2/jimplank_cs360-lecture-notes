#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"

int main(int argc, char **argv)
{
  IS is;
  int i;
  char *penultimate_word;
  char *last_word;

  if (argc != 2) {
    fprintf(stderr, "usage: badword filename\n");
    exit(1);
  }
 
  is = new_inputstruct(argv[1]);
  if (is == NULL) {
    perror(argv[1]);
    exit(1);
  }

  penultimate_word = NULL;
  last_word = NULL;

  while(get_line(is) >= 0) {
    if (penultimate_word != NULL) {  /* This prevents you from having a memory leak. */
      free(penultimate_word);
    }
    penultimate_word = last_word;
    if (is->NF > 0) {
      last_word = strdup(is->fields[0]);  /* This does make a copy of the word. */
    } else {
      last_word = NULL;
    }
  }

  if (penultimate_word != NULL) printf("%s\n", penultimate_word);
  jettison_inputstruct(is);
  exit(0);
}
