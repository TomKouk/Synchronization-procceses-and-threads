#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "display.h"
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>



pthread_mutex_t mutex;
void *writeloop(void *arg) {
int i;
for (i=0;i<10;i++){
     pthread_mutex_lock(&mutex);
     display("Hello world\n");
     pthread_mutex_unlock(&mutex);
     }

}


void *writeloop1(void *arg){
int i;
for (i=0;i<10;i++) {
       pthread_mutex_lock(&mutex);
       display("Kalimera kosme\n");
       pthread_mutex_unlock(&mutex);
     }
}

int main()
{
  pthread_mutex_init(&mutex, NULL);
  pthread_t tid;
  pthread_t tad;
  pthread_create(&tid, NULL, writeloop, NULL);
  pthread_create(&tad, NULL, writeloop1, NULL);
  pthread_join(tad, NULL);
  pthread_join(tid, NULL);
  pthread_mutex_destroy(&mutex);

  return 0;
}
