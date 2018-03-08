//Demonstrate bookkeeping and bits after
//several mallocs and frees
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
	int *j;
	int p_size;
	int p_prev;
	int p_sbits;
	int p_pbits;
	int j_size;
	int j_prev;
	int j_sbits;
	int j_pbits;

	ph();
	p = malloc(64);
	j = malloc(64);

	//Last three bits are used for bookkeeping
	p_prev = *(p - 2) & 0xfffffff8;
	p_size = *(p - 1) & 0xfffffff8;
	p_pbits = *(p - 2) & 3;
	p_sbits = *(p - 2) & 3;
	j_prev = *(j - 2) & 0xfffffff8;
	j_size = *(j - 1) & 0xfffffff8;
	j_pbits = *(j - 2) & 3;
	j_sbits = *(j - 1) & 3;

	fprintf(stderr, "P = 0x%x (prev = %d, size = %d, prev bits = %d, size bits = %d)\n", (unsigned int)p, p_prev, p_size, p_pbits, p_sbits);
	fprintf(stderr, "J = 0x%x (prev = %d, size = %d, prev bits = %d, size bits = %d)\n", (unsigned int)j, j_prev, j_size, j_pbits, j_sbits);

	printf("Free J\n");
	free(j);
	p_prev = *(p - 2) & 0xfffffff8;
	p_size = *(p - 1) & 0xfffffff8;
	p_pbits = *(p - 2) & 3;
	p_sbits = *(p - 2) & 3;
	j_prev = *(j - 2) & 0xfffffff8;
	j_size = *(j - 1) & 0xfffffff8;
	j_pbits = *(j - 2) & 3;
	j_sbits = *(j - 1) & 3;

	fprintf(stderr, "P = 0x%x (prev = %d, size = %d, prev bits = %d, size bits = %d)\n", (unsigned int)p, p_prev, p_size, p_pbits, p_sbits);
	fprintf(stderr, "J = 0x%x (prev = %d, size = %d, prev bits = %d, size bits = %d)\n", (unsigned int)j, j_prev, j_size, j_pbits, j_sbits);

	printf("Free P\n");
	free(p);
	p_prev = *(p - 2) & 0xfffffff8;
	p_size = *(p - 1) & 0xfffffff8;
	p_pbits = *(p - 2) & 3;
	p_sbits = *(p - 2) & 3;
	j_prev = *(j - 2) & 0xfffffff8;
	j_size = *(j - 1) & 0xfffffff8;
	j_pbits = *(j - 2) & 3;
	j_sbits = *(j - 1) & 3;

	fprintf(stderr, "P = 0x%x (prev = %d, size = %d, prev bits = %d, size bits = %d)\n", (unsigned int)p, p_prev, p_size, p_pbits, p_sbits);
	fprintf(stderr, "J = 0x%x (prev = %d, size = %d, prev bits = %d, size bits = %d)\n", (unsigned int)j, j_prev, j_size, j_pbits, j_sbits);

	ph();

	return 0;
}
