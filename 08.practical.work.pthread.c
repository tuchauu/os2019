#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 10

typedef struct {
        char type;  // 0 = fried chicken, 1 = French fries
        int amount; // piesces or weights
        char unit;  // 0 = piece, 1 = gram
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void produce(item *i){
        while ((first + 1) % BUFFER_SIZE == last) {
                // do nothing -- no free buffer item
        }
        memcpy(&buffer[first], i, sizeof(item));
        first = (first + 1) % BUFFER_SIZE;
}

item *consume() {
        item *i = (item*)malloc(sizeof(item));
        while (first == last) {
  
        }
        memcpy(i, &buffer[last], sizeof(item));
        last = (last + 1) % BUFFER_SIZE;

       
        return i;
}

item *initItem(char type, int amount, char unit){
        item *i = malloc(sizeof(item));
        i->amount = amount;
        i->type = type;
        i->unit = unit;
        return i;
}


void *produceThread(void *param){
        item *input1 = initItem('0', 2, '0');
        item *input2 = initItem('1', 2, '1');
        item *input3 = initItem('0', 3, '1');

        produce(input1);
        printf("\nProduce item 1: %c, %d, %c \nFirst: %d, Last: %d\n", input1->type, input1->amount, input1->unit, first, last);
        produce(input2);
        printf("\nProduce item 2: %c, %d, %c \nFirst: %d, Last: %d\n", input2->type, input2->amount, input2->unit, first, last);
        produce(input3);
        printf("\nProduce item 3: %c, %d, %c \nFirst: %d, Last: %d\n", input3->type, input3->amount, input3->unit, first, last);
}

void *consumerThread(void *param){
        item *consItem;
        for (int i = 0; i < 3; ++i) {
                consItem = consume();
                printf("\nConsumed item %d: %c, %d, %c\n", i, consItem->type, consItem->amount, consItem->unit);
                printf("First: %d, Last: %d\n", first, last);
        }
}

int main(int argc, char const *argv[]) {
        printf("Item: type, amount, unit");
        pthread_t tid1, tid2;
        pthread_create(&tid1, NULL, produceThread, NULL );
        pthread_create(&tid2, NULL, consumerThread,NULL);
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);
        return 0;
}
