#include <cstdio>
#include <iostream>
using namespace std;

struct intdouble {
  int i;
  double d;
  void Print();
};

void intdouble::Print()
{
  printf("   %d %.2lf\n", i, d);
}
  
int main()
{
  intdouble id1, id2;

  id1.i = 5;
  id1.d = 3.14;

  id2 = id1;
  id2.i += 5;
  id2.d += 5;

  id1.Print();
  id2.Print();
}
