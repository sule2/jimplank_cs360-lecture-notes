#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int switch_algorithms;        /* This will be set to one by the alarm handler. */
int selection_index;          /* The index of selection sort. */
int insertion_index;          /* The index of insertion sort. */

/* The alarm handler sets switch_algorithms to one, prints out the two 
   indices, and then sets up SIGLARM to be generated again in another second. */

void alarm_handler(int dummy)
{
  switch_algorithms = 1;
  printf("Selection_index: %10d        - Insertion_index: %10d\n", selection_index, insertion_index);
  signal(SIGALRM, alarm_handler);
  alarm(1);
}

/* This generates two identical integer arrays, sorts one by
   selection sort and the other by insertion sort.  */

int main(int argc, char **argv)
{
  int *array1, *array2;
  int size;
  int i, j, tmp, best;

  if (argc != 2) {
    fprintf(stderr, "usage: sort_compare size\n");
    exit(1);
  }
  size = atoi(argv[1]);
  array1 = (int *) malloc(sizeof(int) * size);
  array2 = (int *) malloc(sizeof(int) * size);
    
  for (j = 0; j < size; j++) {
    array1[j] = rand();
    array2[j] = array1[j];
  }

  /* Set the two indices, and set it so that SIGLARM 
     is generated in a second.  */

  selection_index = 0;
  insertion_index = 0;

  signal(SIGALRM, alarm_handler);
  alarm(1);

  /* While one of the sorts is not complete: */

  while (selection_index < size || insertion_index < size) {

    /* First do selection sort on array1, checking the switch_algorithms
       variables at each interation of the main loop. */

    switch_algorithms = 0;
    while (!switch_algorithms && selection_index < size) {
      best = selection_index;
      for (j = selection_index+1; j < size; j++) {
        if (array1[j] < array1[best]) best = j;
      }
      tmp = array1[best];
      array1[best] = array1[selection_index];
      array1[selection_index] = tmp;
      selection_index++;
    }

    /* Second, do insertion sort on array2, checking the switch_algorithms
       variables at each interation of the main loop. */

    switch_algorithms = 0;
    while (!switch_algorithms && insertion_index < size) {
      tmp = array2[insertion_index];
      for (j = insertion_index-1; j >= 0 && array2[j] > tmp; j--) array2[j+1] = array2[j];
      j++;
      array2[j] = tmp;
      insertion_index++;
    }
  }

  printf("Done\n");
  // for (i = 0; i < size; i++) printf("%10d %10d\n", array1[i], array2[i]);
  return 0;
}
