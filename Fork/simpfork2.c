#include <stdio.h>
#include <unistd.h>

int main()
{
  int i;

  i = fork();
  if (i == 0) {
    printf("Child.  getpid() = %d, getppid() = %d\n", getpid(), getppid());
    sleep(5);
    printf("After sleeping.  getpid() = %d, getppid() = %d\n", 
            getpid(), getppid());
  } else {
    printf("Parent exiting now\n");
  }
   return 0;   
}
