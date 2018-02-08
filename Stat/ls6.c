/* ls6.c
   Jim Plank
   CS360 -- Spring, 1994

   Ls6.c performs the same function as "ls -F".  That
   is, it prints directories with a "/" at the end, symbolic
   (soft) links with a "@", and executable files with a "*".
   We are able to do this by interpreting the "st_mode" field
   of the "struct buf".  Look over the code.   */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include "jrb.h"

int main(int argc, char **argv)
{
  struct stat buf;
  int exists;
  DIR *d;
  struct dirent *de;
  JRB r, tmp;
  char *fn;

  r = make_jrb();
  d = opendir(".");
  if (d == NULL) {
    fprintf(stderr, "Couldn't open \".\"\n");
    exit(1);
  }
  
  for (de = readdir(d); de != NULL; de = readdir(d)) {
    fn = strdup(de->d_name);
    jrb_insert_str(r, fn, JNULL);
  }
  closedir(d);

  jrb_traverse(tmp, r) {
    exists = lstat(tmp->key.s, &buf);
    if (exists < 0) {
      fprintf(stderr, "%s not found\n", tmp->key.s);
    } else if (S_ISDIR(buf.st_mode)) {
      printf("%s/\n", tmp->key.s);
    } else if (S_ISLNK(buf.st_mode)) {
      printf("%s@\n", tmp->key.s);
    } else if (buf.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) {
      printf("%s*\n", tmp->key.s);
    } else {
      printf("%s\n", tmp->key.s);
    }
  }
}
