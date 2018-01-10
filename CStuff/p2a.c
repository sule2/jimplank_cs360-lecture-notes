#include <stdio.h>
#include <stdlib.h>

/* This sets any lower-case letter in a to upper case. */

void change_case(char a[20])
{
  int i;

  for (i = 0; a[i] != '\0'; i++) {
    if (a[i] >= 'a' && a[i] <= 'z') a[i] += ('A' - 'a');
  }
}

/* This sets a string to 19 characters and then calls change_case(). */

int main()
{
  int i;
  char s[20];
  
  /* Set s to "abcdefghijklmnopqrs". */

  for (i = 0; i < 19; i++) s[i] = 'a' + i;
  s[19] = '\0';

  printf("First, S is %s.\n", s);
  change_case(s);
  printf("Now, S is   %s.\n", s);

  return 0;
}
