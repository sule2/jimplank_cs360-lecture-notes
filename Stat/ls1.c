/* ls1.c
   James S. Plank
   CS360

   This program lists each program on its command line together with
   its size.  It does this by opening each file, lseeking to the
   end, and printing the value of the file pointer. */

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  int i;
  int fd;
  off_t size;

  for (i = 1; i < argc; i++) {
    fd = open(argv[i], O_RDONLY);
    if (fd < 0) {
      printf("Couldn't open %s\n", argv[i]);
    } else {
      size = lseek(fd, (off_t) 0, SEEK_END);
      printf("%10lld %s\n", size, argv[i]);
      close(fd);
    }
  }
  return 0;
}

