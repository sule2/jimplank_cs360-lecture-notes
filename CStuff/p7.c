
int main()
{
  char *s;

  s = (char *) malloc(10);
  strcpy(s, "Jim");
  printf("s = %s\n", s); 
  exit(0);
}

