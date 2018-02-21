a(int i, int j, int k, int l)
{
  int m;

  m = i + j + k + l;
}

int b(int i)
{
  int p[5];

  return p[i];
}

int main()
{
  int x;

  a(5, 6, 7, 8);
  x = b(2);
}
