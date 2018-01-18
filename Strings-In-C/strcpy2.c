#include <stdio.h>
#include <string.h>

typedef unsigned long UL;

int main()
{
  char give[5];
  char him[5];
  char six[5];

  printf("give: 0x%lx  him: 0x%lx  six: 0x%lx\n", (UL) give, (UL) him, (UL) six);

  strcpy(give, "Give");
  strcpy(him, "Him");
  strcpy(six, "Six!");

  printf("%s %s %s\n", give, him, six);

  strcpy(him, "T.J. Houshmandzadeh");

  printf("%s %s %s\n", give, him, six);
  return 0;
}
