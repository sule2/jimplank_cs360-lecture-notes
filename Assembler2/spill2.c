int a(int i, int j)
{
  int k;

  k = (i+2)*(j-5);
  return k;
}

int main()
{
  int i;

  i = (a(10, 20) + a(30, 40));
}
