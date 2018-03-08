//Using CHUNK to store data
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct chunk {
	int psize;
	int size;

	struct chunk *next;
	struct chunk *prev;
} CHUNK, *PCHUNK;

int *round_up(int *ptr, unsigned int by)
{
	unsigned int addr = (unsigned int)ptr;

	addr = (addr + (by-1)) & -by;

	return (int*)addr;
}

int main()
{
	char *ptr;
	PCHUNK pc;

	printf("Sizeof CHUNK = %d\n", sizeof(CHUNK));

	ptr = malloc(64);

	//Convert this into a PCHUNK by backing up by 8 bytes
	pc = (PCHUNK)(ptr - 8);

	printf("Chunk (size = %d, prev = %d)\n", pc->size, pc->psize);

	printf("Why %d? Because last three bits are used for bookkeeping\n", pc->size);

	printf("Real size = %d\n", pc->size & ~7);

	return 0;
}
