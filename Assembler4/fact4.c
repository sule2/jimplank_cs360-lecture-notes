int fact(int i)
{
  if (i == 0) return 1;
  return fact(i-1)*i;
}

int main()
{
  int i;

  i = fact(4);
}
