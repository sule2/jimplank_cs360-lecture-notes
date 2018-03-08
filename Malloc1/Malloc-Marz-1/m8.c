#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <unistd.h>

int main()
{
	int *p;
	printf ("Current heap location = 0x%x\n", (unsigned int)sbrk(0));

	p = malloc(4096);

	printf("Current heap location = 0x%x\n", (unsigned int)sbrk(0));
	

	free(p);

	p = 0;
	*p = 33;


	return 0;
}
