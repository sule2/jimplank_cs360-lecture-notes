int main()
{
  int *a, a2[3], i;

  i = 6;
  a = &i;
  a2[1] = i+2;
  *a = 2;
  *(a2+i) = i+5;
}

