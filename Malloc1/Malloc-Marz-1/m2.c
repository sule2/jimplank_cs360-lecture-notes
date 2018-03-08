//Anonymous maps (don't map to a backing store)
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	char *page;
	size_t length;
	int prot;
	int flags;
	int fd;
	off_t offset;


	//I want to allocate 64 bytes
	length = 64;

	//Read and write to this
	prot = PROT_READ | PROT_WRITE;

	//Anonymous means that there is no backing store and it is
	//instead all contained in memory
	flags = MAP_ANONYMOUS | MAP_PRIVATE;

	//There is no FD
	fd = -1;

	//No offset
	offset = 0;

	//First, see where the heap is
	printf("Heap ends at 0x%x\n", (unsigned int)sbrk(0));

	//Get the page from the OS
	page = mmap((void*)sbrk(0), // Hint the map location at the end of the heap
		    length, // Size we want
		    prot,   // Protection flags
                    flags,  // Mapping flags
                    fd,     // File descriptor
		    offset  // Where to start
		   );

	if (page == MAP_FAILED) {
		printf("Error allocating page\n");
		return -1;
	}

	printf("We got page at address 0x%x\n", (unsigned int)page);
	printf("Heap now ends at 0x%x\n", (unsigned int)sbrk(0));

	//Free the memory
	munmap(page, length);

	return 0;
}
