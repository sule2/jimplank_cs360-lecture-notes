#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int a[1000];
} SID;

void a(SID s)
{
  s.a[999] = -1;
}


int main()
{
  SID s1, s2;
  int i;

  for (i = 0; i < 1000; i++) s1.a[i] = i;
  s2 = s1;

  a(s1);
  for (i = 0; i < 1000; i++) printf("%4d %4d\n", s1.a[i], s2.a[i]);
 
  exit(0);
}
