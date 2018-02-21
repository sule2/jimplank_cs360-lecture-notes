int a(int i, int j)
{
  int k;

  if (i < j) {
    k = i;
  } else {
    k = j;
  }
  return k;
}

int main()
{
  return a(3, 4);
}
