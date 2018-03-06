int main()
{
  char *s;
  char c;

  s = (char *) 0;
  c = *s;           /* The segmentation violation happens here. */
  return 0;
}
