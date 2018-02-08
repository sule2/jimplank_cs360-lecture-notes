/* ls5a.c
   Jim Plank
   CS360 -- Spring, 1994

   This is the same as ls5.c except the maximum length of the file size
   is calculated so that we don't have to use %10d in the printf statement.
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
  int maxsize;
  char ssize[20];

  d = opendir(".");
  if (d == NULL) {
    fprintf(stderr, "Couldn't open \".\"\n");
    exit(1);
  }
  
  maxlen = 0;
  maxsize = 0;
  files = make_jrb();

  for (de = readdir(d); de != NULL; de = readdir(d)) {
    if (strlen(de->d_name) > maxlen) maxlen = strlen(de->d_name);
    exists = stat(de->d_name, &buf);
    if (exists < 0) {
      fprintf(stderr, "%s not found\n", de->d_name);
    } else {
      sprintf(ssize, "%ld", buf.st_size);
      if (strlen(ssize) > maxsize) maxsize = strlen(ssize);
      jrb_insert_str(files, strdup(de->d_name), new_jval_s(strdup(ssize)));
    }
  }
  closedir(d);

  jrb_traverse(tmp, files) {
    printf("%*s %*s\n", -maxlen, tmp->key.s, maxsize, tmp->val.s);
  }
}
