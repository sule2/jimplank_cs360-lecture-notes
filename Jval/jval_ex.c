#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "jval.h"

typedef struct {
  char type;
  Jval value;
} Item;

int main()
{
  Item array[5];
  int i;
  IS is;

  is = new_inputstruct(NULL);

  /* Read in the items -- if "int", read it into array[i].i
                          if "float", read it into array[i].f
                          if "string", read it into array[i].s */

  for (i = 0; i < 5; i++) {
    if (get_line(is) != 2) exit(1); 

    if (strcmp(is->fields[0], "int") == 0) {
      array[i].type = 'i';
      if (sscanf(is->fields[1], "%d", &(array[i].value.i)) != 1) exit(1); 

    } else if (strcmp(is->fields[0], "float") == 0) {
      array[i].type = 'f';
      if (sscanf(is->fields[1], "%f", &(array[i].value.f)) != 1) exit(1); 

    } else if (strcmp(is->fields[0], "string") == 0) {
      array[i].type = 's';
      array[i].value.s = strdup(is->fields[1]);

    } else {
      exit(1);
    }
  }

  /* Write out the items. */

  for (i = 0; i < 5; i++) {
    printf("Item %d: Type %c -- ", i, array[i].type);
    if (array[i].type == 'i') {
      printf("Value: %d\n", array[i].value.i);
    } else if (array[i].type == 'f') {
      printf("Value: %f\n", array[i].value.f);
    } else if (array[i].type == 's') {
      printf("Value: %s\n", array[i].value.s);
    } else {
      exit(1);
    }
  }
 
  /* Print the size of the item struct */

  printf("\n");
  printf("Sizeof(Item): %d\n", sizeof(Item));
  exit(0);
}
