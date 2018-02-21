void a(int *p)
{
  int i;
 
  i = p[0];
  i = p[3];
  i = p[i];
}

int main()
{
  int array[5];

  array[0] = 10;
  array[1] = 11;
  array[2] = 12;
  array[3] = 2;
  array[4] = 15;

  a(array);
}

