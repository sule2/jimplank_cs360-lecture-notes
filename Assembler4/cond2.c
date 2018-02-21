int a(int k)
{
  int i, j;

  j = 0;

  for (i = 1; i <= k; i++) j += i;

  return j;
}

int main()
{
  int i;

  i = a(4);
}
