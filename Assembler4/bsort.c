void bsort(int *a, int size)
{
  int i, j, tmp;

  for (i = size-1; i > 0; i--) {
    for (j = 0; j < i; j++) {
      if (a[j] > a[j+1]) {
        tmp = a[j];
        a[j] = a[j+1];
        a[j+1] = tmp;
      }
    }
  }
}
      
int main()
{
  int array[4];
  array[0] = 6;
  array[1] = 2;
  array[2] = 1;
  array[3] = 4;

  bsort(array, 4);
}
