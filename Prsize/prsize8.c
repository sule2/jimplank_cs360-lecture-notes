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

/* Add a comparison function for longs, so that the jrb library can work on inodes. */

int long_comp(Jval v1, Jval v2)
{
  if (v1.l < v2.l) return -1;
  if (v1.l > v2.l) return 1;
  return 0;
}

/* This procedure returns the number of bytes in files that are
   reachable from fn.  It does not double-count hard links to
   the same file, and it counts the size of soft links, not the 
   files to which they point. */

int get_size(char *fn, JRB inodes)
{
  DIR *d;
  struct dirent *de;
  struct stat buf;
  int exists;
  int total_size;
  char *s;
  Dllist directories, tmp;

  /* Open the directory for reading. */

  d = opendir(fn);
  if (d == NULL) {
    perror("prsize");
    exit(1);
  }
 
  /* We use s to store file names that are of the form 
     "directory/filename" -- the maximum length filename is
     256 bytes, so this makes sure that the buffer s is 
     big enough. */

  total_size = 0;
  directories = new_dllist();
  s = (char *) malloc(sizeof(char)*(strlen(fn)+258));

  /* Read each filename in the current directory.  
     Construct s as "directory/filename" and call lstat to
     get the inode information about the file. */

  for (de = readdir(d); de != NULL; de = readdir(d)) {
    sprintf(s, "%s/%s", fn, de->d_name);
    exists = lstat(s, &buf);
    if (exists < 0) {
      fprintf(stderr, "Couldn't stat %s\n", s);
      exit(1);

    /* Look up the inode in the inodes tree.  If it's there,
       you ignore it, because you've seen it before.  Otherwise,
       put it into the tree and process it. */

    } else {
      if (jrb_find_gen(inodes, new_jval_l(buf.st_ino), long_comp) == NULL) {
        total_size += buf.st_size;
        jrb_insert_gen(inodes, new_jval_l(buf.st_ino), new_jval_i(0), long_comp);
      }
    }

    /* If the file is a directory, and not . or .., then append
       it to the directories list so that you don't make recursive
       calls while the directory is opened. */

    if (S_ISDIR(buf.st_mode) && strcmp(de->d_name, ".") != 0 && 
        strcmp(de->d_name, "..") != 0) {
      dll_append(directories, new_jval_s(strdup(s)));
    }
  }

  /* Close the directory, and then make recursive calls to all of
     the directories.  You'll note, I free the directory name after
     the recursive call returns.  I do this to avoid having a memory
     leak due to the strdup() calls above. */

  closedir(d);
  dll_traverse(tmp, directories) {
     total_size += get_size(tmp->val.s, inodes);
     free(tmp->val.s);
  }
   
  /* Perform final free() calls again to avoid memory leaks. */

  free_dllist(directories);
  free(s);

  return total_size;
}

int main()
{
  JRB inodes;

  inodes = make_jrb();
  printf("%d\n", get_size(".", inodes));
  return 0;
}
