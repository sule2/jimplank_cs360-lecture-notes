#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char b;
  int i;
} S1;

typedef struct {
  int i;
  char b;
} S1B;

typedef struct {
  char b1;
  int i1;
  char b2;
  int i2;
} S2;


typedef struct {
  char b1;
  char b2;
  int i1;
  int i2;
} S3;


int main()
{
  printf("%ld %ld %ld %ld\n", sizeof(S1), sizeof(S2), sizeof(S3), sizeof(S1B));
  exit(0);
}

