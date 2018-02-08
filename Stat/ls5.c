/* ls5.c
   James S. Plank
   CS360 -- Spring, 1994

   This is the same as ls4.c except the filenames are sorted.
*/
  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "jrb.h"

int main(int argc, char **argv)
{
  struct stat buf;
  int exists;
  DIR *d;
  struct dirent *de;
  JRB files, tmp;
  int maxlen;

  d = opendir(".");
  if (d == NULL) {
    fprintf(stderr, "Couldn't open \".\"\n");
    exit(1);
  }
  
  maxlen = 0;
  files = make_jrb();

  for (de = readdir(d); de != NULL; de = readdir(d)) {
    jrb_insert_str(files, strdup(de->d_name), new_jval_i(0));
    if (strlen(de->d_name) > maxlen) maxlen = strlen(de->d_name);
  }
  closedir(d);

  jrb_traverse(tmp, files) {
    exists = stat(tmp->key.s, &buf);
    if (exists < 0) {
      fprintf(stderr, "%s not found\n", tmp->key.s);
    } else {
      printf("%*s %10lld\n", -maxlen, tmp->key.s, buf.st_size);
    }
  }
  return 0;
}
