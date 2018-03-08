//Demonstrate "bookkeeping" 8 bytes
//above the pointer
#include <stdio.h>
#include <stdlib.h>

//sbrk
#include <unistd.h>

void ph()
{
	printf("Current heap location = 0x%x\n", (unsigned int)sbrk(0));
}

int main()
{
	int *p;
	int size;
	int prev;

	ph();
	p = malloc(64);

	prev = *(p - 2) & 0xfffffff8;
	size = *(p - 1) & 0xfffffff8;

	printf("P = 0x%x (prev = %d, size = %d)\n", (unsigned int)p, prev, size);

	ph();

	return 0;
}
