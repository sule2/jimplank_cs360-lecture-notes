/* ls4.c
   Jim Plank
   CS360 -- Spring, 1994

   This is the same as ls3.c except the input is formatted so that 
   all the filenames are padded to the size of the largest one.
*/
  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "dllist.h"

int main(int argc, char **argv)
{
  struct stat buf;
  int exists;
  DIR *d;
  struct dirent *de;
  Dllist files, tmp;
  int maxlen;

  d = opendir(".");
  if (d == NULL) {
    fprintf(stderr, "Couldn't open \".\"\n");
    exit(1);
  }
  
  maxlen = 0;
  files = new_dllist();

  for (de = readdir(d); de != NULL; de = readdir(d)) {
    dll_append(files, new_jval_s(strdup(de->d_name)));
    if (strlen(de->d_name) > maxlen) maxlen = strlen(de->d_name);
  }
  closedir(d);

  dll_traverse(tmp, files) {
    exists = stat(tmp->val.s, &buf);
    if (exists < 0) {
      fprintf(stderr, "%s not found\n", tmp->val.s);
    } else {
      printf("%*s %10ld\n", -maxlen, tmp->val.s, buf.st_size);
    }
  }
}
