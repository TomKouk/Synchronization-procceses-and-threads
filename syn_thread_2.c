#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "display.h"
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>


enum { STATE_A, STATE_B } state = STATE_A;
pthread_cond_t      condA  = PTHREAD_COND_INITIALIZER;
pthread_cond_t      condB  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t     mutex = PTHREAD_MUTEX_INITIALIZER;

void *writeloop(void *arg){
int i;
for (i=0;i<10;i++) {
pthread_mutex_lock(&mutex);
 while (state != STATE_A) {
pthread_cond_wait(&condA, &mutex);
}
pthread_mutex_unlock(&mutex); 
display("ab");
pthread_mutex_lock(&mutex);
state = STATE_B;
pthread_cond_signal(&condB);
pthread_mutex_unlock(&mutex);
}
return 0;
}

void *writeloop1(void *arg){
int i;
for (i=0;i<10;i++) {
 pthread_mutex_lock(&mutex);
        while (state != STATE_B)
            pthread_cond_wait(&condB, &mutex);
        pthread_mutex_unlock(&mutex);

        //do stuff
        display("cd\n");

        /* Set state to A and wake up thread A */
        pthread_mutex_lock(&mutex);
        state = STATE_A;
        pthread_cond_signal(&condA);
        pthread_mutex_unlock(&mutex);
}


}





int main()
{ 
  int ras,rad;
  pthread_t tad;
  pthread_t tid;
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&condA, NULL);
  pthread_cond_init(&condB, NULL);
 rad=pthread_create(&tid, NULL, writeloop, NULL);
  rad=pthread_create(&tad, NULL, writeloop1, NULL);
  pthread_join(tid, NULL);
  pthread_join(tad, NULL);
  pthread_mutex_destroy(&mutex);
  pthread_exit(&tid);
  pthread_exit(&tad);
  return 0;
}
