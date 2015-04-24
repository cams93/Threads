#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#define BSIZE 10

int buffer[BSIZE];
int pos_consumer = 0;
int pos = 0;
sem_t s;
sem_t t;
pthread_mutex_t lock_posc;

void * producer (void * a)
{
    int temp;
    while(1)
    {
        sem_wait(&s);
        pthread_mutex_lock(&lock_posc);
        buffer[pos]=rand();
        temp = buffer[pos];
        //sleep(2);
        pos++;
        pos=pos%9;
        pthread_mutex_unlock(&lock_posc);
        sem_post(&t);
        printf("producer: %d\n", temp);
    }
}

void * consumer (void * a)
{
    int b;
    while(1)
    {
        sem_wait(&t);
        pthread_mutex_lock(&lock_posc);
        b=buffer[pos_consumer];
        sleep(2);
        pos_consumer++;
        pos_consumer=pos_consumer%9;
        pthread_mutex_unlock(&lock_posc);
        sem_post(&s);
        printf("consumer: %d\n", b);
    }
}

int main()
{ 
   sem_init(&s,0,10);
   sem_init(&t,0,0);
   pthread_t threads1;
   pthread_t threads2;
   pthread_t threads3;
   pthread_t threads4;
   
   pthread_create(&threads1, NULL, consumer, NULL);
   pthread_create(&threads2, NULL, producer, NULL);
   pthread_create(&threads3, NULL, consumer, NULL);
   pthread_create(&threads4, NULL, producer, NULL);
   
   pthread_join(threads1,NULL);
   pthread_join(threads2,NULL);
   pthread_join(threads3,NULL);
   pthread_join(threads4,NULL);
   
   pthread_exit(NULL);
}