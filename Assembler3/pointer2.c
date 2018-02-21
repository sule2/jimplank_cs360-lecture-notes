int a(int *p)
{
  return *p;
}

int main()
{
  int i, j;

  j = 15;
  i = a(&j);
}
