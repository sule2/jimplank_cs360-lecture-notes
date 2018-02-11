/* prsize8.c
   Jim Plank
   Fall, 1996
   CS360
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "jrb.h"
#include "dllist.h"

int get_size(char *fn, JRB inodes)
{
  DIR *d;
  struct dirent *de;
  struct stat buf;
  int exists;
  int total_size;
  char *s;
  Dllist directories, tmp;

  d = opendir(fn);
  if (d == NULL) {
    perror("prsize");
    exit(1);
  }
 
  total_size = 0;
  s = (char *) malloc(sizeof(char)*(strlen(fn)+258));

  directories = new_dllist();
  for (de = readdir(d); de != NULL; de = readdir(d)) {
    /* Look for fn/de->d_name */
    sprintf(s, "%s/%s", fn, de->d_name);
    exists = lstat(s, &buf);
    if (exists < 0) {
      fprintf(stderr, "Couldn't stat %s\n", s);
    } else {
      if (jrb_find_int(inodes, buf.st_ino) == NULL) {
        total_size += buf.st_size;
        jrb_insert_int(inodes, buf.st_ino, new_jval_i(0));
      }
    }
    if (S_ISDIR(buf.st_mode) && strcmp(de->d_name, ".") != 0 && 
        strcmp(de->d_name, "..") != 0) {
      dll_append(directories, new_jval_s(strdup(s)));
    }
  }
  closedir(d);
  dll_traverse(tmp, directories) {
     total_size += get_size(tmp->val.s, inodes);
     /* This keeps the program from overgrowing its memory */
     free(tmp->val.s);
  }
   
  /* As does this */
  free_dllist(directories);
  free(s);
  return total_size;
}

int main()
{
  JRB inodes;

  inodes = make_jrb();
  printf("%d\n", get_size(".", inodes));
}
