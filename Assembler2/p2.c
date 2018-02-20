int a(int i, int j)
{
  int k;

  i++;
  j -= 2;
  k = i * j;
  return k;
}

int main()
{
  int i, j, k;

  i = 3;
  j = 4;
  k = a(j+1, i);
  return 0;
}
