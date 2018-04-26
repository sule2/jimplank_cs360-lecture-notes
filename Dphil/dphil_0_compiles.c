/* dphil_0_compiles.c
   James S. Plank
   April, 2016
   CS360 - Systems Programming

   Null solution to the dining philosophers.
 */

#include <stdio.h>
#include <pthread.h>
#include "dphil.h"

/* Each of these does nothing. */

void *initialize_v(int phil_count) { return NULL; }
void i_am_hungry(void *v, int philosopher) {}
void i_am_done_eating(void *v, int philosopher) {}
