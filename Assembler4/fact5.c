int fact(int i, int val_so_far)
{
  if (i == 0) return val_so_far;
  return fact(i-1, val_so_far * i);
}

int main()
{
  int i;

  i = fact(5, 1);
}
