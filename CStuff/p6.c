extern char *malloc();

int main()
{
  char *s;

  s = malloc(10);
  strcpy(s, "Jim");
  printf("s = %s\n", s); 
  exit(0);
}

