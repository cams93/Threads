  #include<stdio.h>
  #include<stdlib.h>
  #include<pthread.h>
  #include <semaphore.h>
  #define n_phil 20
  
  pthread_t philosopher[n_phil];
  pthread_mutex_t forks[n_phil];
  sem_t s;
  
  
unsigned int randr (unsigned int min, unsigned int max)
{
    double scaled = (double)rand()/RAND_MAX;
    return scaled*(max - min + 1) + min;
}

  void *func(void *id){
    long n = (long)id;
    while(1){
      printf("\nPhilosopher %ld is thinking ",n);
      sleep(randr(1,4));
      sem_wait(&s);
      pthread_mutex_lock(&forks[n]);  //solo uno puede acceder al recurso
      pthread_mutex_lock(&forks[(n+1)%n_phil]);
      printf("\nPhilosopher %ld is eating ",n);
      sleep(randr(1,4));
      pthread_mutex_unlock(&forks[n]);
      pthread_mutex_unlock(&forks[(n+1)%n_phil]);
      sem_post(&s);
      printf("\nPhilosopher %ld Finished eating ",n);
    }
  }
  
  int main(){
    sem_init(&s,0,n_phil-1);
    long i,k;
    void *msg;
    srand(time(NULL));
    for(i=1;i<=n_phil;i++)
    {
      k=pthread_mutex_init(&forks[i],NULL);
      if(k==-1) {
        printf("\n Mutex initialization failed");
        exit(1);
      }
    }
    for(i=1;i<=n_phil;i++){
      k=pthread_create(&philosopher[i],NULL,(void *)func,(void *)i);
      if(k!=0){
        printf("\n Thread creation error \n");
        exit(1);
      }
      
    }
    for(i=1;i<=n_phil;i++){
      k=pthread_join(philosopher[i],&msg);
      if(k!=0){
        printf("\n Thread join failed \n");
        exit(1);
      }
    }
    for(i=1;i<=n_phil;i++){
      k=pthread_mutex_destroy(&forks[i]);
      if(k!=0){
      printf("\n Mutex Destroyed \n");
      exit(1);
      }
    }
    return 0;
  }
      
  
