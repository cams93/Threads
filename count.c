#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

int cnt = 0;
sem_t s;

void * count (void * a)
{
   int tmp, i;
   for (i=0; i<2000000; i++)
   {
      sem_wait(&s);
      tmp = cnt;
      tmp += 1;
      cnt = tmp;
      sem_post(&s);
   }
}

int main(int argc, char *argv[])
{
   sem_init(&s,0,1);
   pthread_t threads1;
   pthread_t threads2;

   pthread_create(&threads1, NULL, count, NULL);
   pthread_create(&threads2, NULL, count, NULL);
   
   pthread_join(threads1,NULL);
   pthread_join(threads2,NULL);
   
   printf("Counter = %d\n",cnt);
   
   pthread_exit(NULL);
}

  