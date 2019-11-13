#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "display.h"
#include <semaphore.h>
#include <fcntl.h>


int main()
{
  sem_t *sem;
  int i;
  sem = sem_open("/sema", O_CREAT, 0644, 1);
  sem_unlink("/sema");
  if (fork())
  {
    for (i=0;i<10;i++){
     sem_wait(sem); 
     display("Hello world\n");
     sem_post(sem);
     wait(NULL);
    }
  }
  else
  {
    for (i=0;i<10;i++) {
       sem_wait(sem);
       display("Kalimera kosme\n");
       sem_post(sem);
     }
   }
  sem_destroy(sem);
  return 0;
}
