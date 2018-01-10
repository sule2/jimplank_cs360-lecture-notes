#include <stdio.h>

typedef unsigned long UL;

int main () {

  /* I used unsigned variables to shut up the compiler
    and to prevent preservation of negative integers when
    examining the contents of the array when viewed as
    individual bytes.
  */
  unsigned int arr[4];  /* An array of 4 integers */
  unsigned char* bp;    /* Pointer to be used to examine byte order */
  unsigned int* arrp;   /* Pointer to offset array */

  int i;  /* generic */

  /*
    Each byte in the array will be uniquely identified by a sequence
    two hex digits.  This was arbitrarily chosen as to ease visual
    identification of individual bytes;
  */
  arr[0] = 0x00112233;
  arr[1] = 0x44556677;
  arr[2] = 0x8899AABB;
  arr[3] = 0xCCDDEEFF;

  printf( "\nINT array: 0x%08lX\n", (UL) arr );
  for ( i = 0; i < 4; i++ ) {
    printf( "Index %d - Location: 0x%08lX  Size:%2d  Contents: 0x%08lX\n",
            i, (UL) (arr+i), (int) sizeof(int), (UL) arr[i] );
  }


  /*
    This section sets bp equal to arr.
    We may now use bp to access the array as individual bytes.
  */

  bp = (unsigned char *) arr;
  printf( "\nBYTE array: 0x%08lX\n", (UL) bp );
  for ( i = 0; i < 16; i++ ) {
    printf( "Index %2d - Location: 0x%08lX  Contents: 0x%02X\n", i, (UL) (bp+i), bp[i] );
  }
  printf( "\n\n" );



  /*
    Here we first increment the character pointer by one.
  */
  arrp = (unsigned int *) ( bp + 1 );
  printf( "Original array begin: 0x%08lX\n", (UL) arr );
  printf( "Offset array begin:   0x%08lX\n", (UL) arrp );
  printf( "Byte offset:          %ld\n", ((UL)arrp)-((UL)arr) );
  for ( i = 0; i < 4; i++ ) {
    printf( "Index %d - Location: 0x%08lX  Size:%2d  Contents: 0x%08lX\n",
            i, (UL) (arrp+i), (int) sizeof(int), (UL) arrp[i] );
  }
  printf( "\n" );

  return 0;
}
