#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include <semaphore.h>


#define BUFFER_SIZE 10


typedef struct {
  char type; 
  int amount;
  char unit;
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;
sem_t s;

void produce(item *i){
  while ((first + 1) % BUFFER_SIZE == last){
    
    printf("No free buffer item!\n");
  }
  memcpy(&buffer[first], i, sizeof(item));
  first = (first + 1) % BUFFER_SIZE;
  logValues();
}

item* consume(){
  item* i = malloc(sizeof(item));
  while (first == last){
   
    printf("Nothing to consume!\n");
  }
  memcpy(i, &buffer[last], sizeof(item));
  last = (last + 1) % BUFFER_SIZE;
  logValues();
  return i;
}

void logValues(){
  printf("first : %d\t last : %d\n", first, last);
  return;
}

item* init(char type, int amount, char unit){
  item* i = malloc(sizeof(item));
  i->type = type;
  i->amount = amount;
  i->unit = unit;
  return i;
}




void *threadProduce(void *param){
  printf("Producing thread....\n");
  sem_wait(&s);
  produce(init('1',5,'0'));
  produce(init('0',3,'1'));
  produce(init('1',4,'0'));
  sem_post(&s);
}


void *threadConsume(void *param){
  printf("Consuming thread....\n");
  sem_wait(&s);
  consume();
  consume();
  sem_post(&s);
}

int main(){
  pthread_t tid1, tid2;
  sem_init(&s,0,1);
      printf("Log Initialization:\nfirst : %d\tlast : %d\n\n", first, last);

 
  if(pthread_create(&tid1, NULL, threadProduce, NULL) != 0){
    perror("pthread_created() error");
  }
  if(pthread_create(&tid2, NULL, threadConsume, NULL) != 0){
    perror("pthread_created() error");
  }
  
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  sem_destroy(&s);
  return 0;
}
