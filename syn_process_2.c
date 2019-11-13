#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "display.h"
#include <semaphore.h>
#include <fcntl.h>
int main()
{
sem_unlink("/sema");
sem_unlink("/semi");
   sem_t *sem;
   sem_t *sam;
   sem = sem_open("/sema", O_CREAT, 0644, 1);
   sem_unlink("/sema");
   sam = sem_open("/semi", O_CREAT, 0644, 0);
   sem_unlink("/semi");



   int i;

  if (fork())
  {
    for (i=0;i<10;i++) {
     sem_wait(sem); 
     display("ab");
     sem_post(sam);
	}
    wait(NULL);
  }
  else
  {
    for (i=0;i<10;i++) {
      sem_wait(sam); 
      display("cd\n");
      sem_post(sem);
}
  }
  sem_destroy(sem);
  sem_destroy(sam);
  return 0;
}
