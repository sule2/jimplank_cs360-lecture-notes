//Demonstrate unaligned access
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <emmintrin.h>


int main(int argc, char *argv[])
{
	int align_it;
	int *ptr;
	unsigned int p;
	__m128d m;

	if (argc >= 2) {
		align_it = atoi(argv[1]);
	}
	else {
		align_it = 0;
	}

	ptr = (int*)((char*)malloc(24));

	*ptr = 123456789;

	printf("Got number (0x%x):  %d\n", (unsigned int)ptr, *ptr);

	p = (unsigned int)ptr;

	if (align_it) {
		//Align it?
		printf("Aligned 0x%x to", p);
		p = (p+15) & -16;
		printf(" 0x%x\n", p);
	}
	else {
		printf("Try unaligned access (this may segfault!):\n");
	}

	m = _mm_load_pd((double*)p);

	printf("PD = [%lf] [%lf]\n", m[0], m[1]);

	return 0;
}
