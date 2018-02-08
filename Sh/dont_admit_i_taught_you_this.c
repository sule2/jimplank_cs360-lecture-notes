#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void v(int i) 
{ 
  char s[100];

  sprintf(s, "Here's my error message.  V was called with %d\n", i);
  write(9, s, strlen(s));
}

void u() { printf("Blah blah blah blah blah blah.\n");  v(4); }
void t() { printf("Blah blah blah blah blah blah.\n");  u(); }
void s() { printf("Blah blah blah blah blah blah.\n");  u(); t(); }
void r() { printf("Blah blah blah blah blah blah.\n");  u(); s(); }
void q() { printf("Blah blah blah blah blah blah.\n");  u(); r(); }
void p() { printf("Blah blah blah blah blah blah.\n");  q(); q(); v(5); }
void o() { printf("Blah blah blah blah blah blah.\n");  p(); }
void n() { printf("Blah blah blah blah blah blah.\n");  o(); }
void m() { printf("Blah blah blah blah blah blah.\n");  n(); }
void l() { printf("Blah blah blah blah blah blah.\n");  m(); }
void k() { printf("Blah blah blah blah blah blah.\n");  l(); m(); v(6); }
void j() { printf("Blah blah blah blah blah blah.\n");  k(); }
void i() { printf("Blah blah blah blah blah blah.\n");  j(); }
void h() { printf("Blah blah blah blah blah blah.\n");  i(); }
void g() { printf("Blah blah blah blah blah blah.\n");  h(); }
void f() { printf("Blah blah blah blah blah blah.\n");  g(); }
void e() { printf("Blah blah blah blah blah blah.\n");  f(); v(7); }
void d() { printf("Blah blah blah blah blah blah.\n");  e(); }
void c() { printf("Blah blah blah blah blah blah.\n");  d(); }
void b() { printf("Blah blah blah blah blah blah.\n");  c(); }
void a() { printf("Blah blah blah blah blah blah.\n");  b(); v(8); }


int main()
{
  a();
  return 0;
}
