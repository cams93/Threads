#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#define BSIZE 10

int buffer[BSIZE];
int pos_consumer = 0;
sem_t s;
sem_t t;

void * producer (void * a)
{
    int pos = 0;
    while(1)
    {
        sem_wait(&s);
        buffer[pos]=rand();
        printf("producer: %d\n", buffer[pos]);
        //sleep(2);
        pos++;
        pos=pos%9;
        sem_post(&t);
    }
}

void * consumer (void * a)
{
    int b;
    while(1)
    {
        sem_wait(&t);
        b=buffer[pos_consumer];
        printf("consumer: %d\n", buffer[pos_consumer]);
        sleep(2);
        pos_consumer++;
        pos_consumer=pos_consumer%9;
        sem_post(&s);
    }
}

int main()
{ 
   sem_init(&s,0,10);
   sem_init(&t,0,0);
   pthread_t threads1;
   pthread_t threads2;
   pthread_t threads3;
   
   pthread_create(&threads1, NULL, consumer, NULL);
   pthread_create(&threads2, NULL, producer, NULL);
   pthread_create(&threads3, NULL, consumer, NULL);
   
   pthread_join(threads1,NULL);
   pthread_join(threads2,NULL);
   pthread_join(threads3,NULL);
   
   pthread_exit(NULL);
}