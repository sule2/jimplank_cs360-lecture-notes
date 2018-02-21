int x(int **p, int i, int j)
{
  return p[i+2][j-2];
}

int main()
{
  int a[3], b[3], c[3];
  int *d[3];
  int e;

  a[0] = 1; a[1] = 2; a[2] = 3;
  b[0] = 4; b[1] = 5; b[2] = 6;
  c[0] = 7; c[1] = 8; c[2] = 9;

  d[0] = a; d[1] = b; d[2] = c;

  e = x(d, 0, 3);
}
