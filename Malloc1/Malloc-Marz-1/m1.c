//File memory mapping
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>


int main()
{
	char *file;
	char buf[1000];
	int pos;

	size_t len;
	int prot;
	int flags;
	int fd;
	off_t offset;

	fd = open("test.txt", O_RDONLY);

	if (fd < 0) {
		printf("Unable to open test.txt\n");
		return -1;
	}

	//Get the size of the file by seeking to the end
	len = lseek(fd, 0, SEEK_END);

	//Rewind the file back to the beginning
	lseek(fd, 0, SEEK_SET);

	//First, normal read:
	pos = read(fd, buf, 1000);
	buf[pos] = '\0';
	printf("File contains: '%s'\n", buf);


	//Now, mmap read
	lseek(fd, 0, SEEK_SET);
	prot = PROT_READ;
	flags = MAP_SHARED;
	offset = 0;

	//Memory mapping was originally to make a file look like memory
	file = mmap(NULL,  // Where do we want the kernel to map this? NULL for we don't care
		    len,   // The length of the file
 		    prot,  // Protection (PROT_EXEC, READ, WRITE, NONE)
		    flags, // MAP_UNINITIALIZED, MAP_HUGETLB (huge pages), MAP_FIXED
		    fd,    // File descriptor to map
		    offset // Offset to start the map in the file
		   );

	if (file == MAP_FAILED) {
		printf("Unable to map file: %s\n", strerror(errno));
		return -1;
	}

	printf("Mmapped file contains: '%s'\n", file);
	file[0] = 'C';
	//Unmap
	munmap(file, len);

	return 0;
}
