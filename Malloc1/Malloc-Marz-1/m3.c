//Demonstrate malloc
//Demonstrate segmentation fa ult
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

//sbrk
#include <unistd.h>

void seg(int val)
{
	printf("Yep, you caused a seg fault... :[\n");
	exit(11);
}

void ph()
{
	printf("Current heap location = 0x%x\n", (unsigned int)sbrk(0));
}

int main()
{
	int *p;

	signal(11, seg);

	ph();
	p = malloc(4096);
	printf("P = 0x%x\n", (unsigned int)p);
	ph();


	fprintf(stderr, "Let's try to address an invalid memory address: \n");

	p = 0;
	*p = 33;

	return 0;
}
