#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define BUFFER_SIZE 10

typedef struct {
char type; // 0=fried chicken, 1=French fries
int amount; // pieces or weight
char unit; // 0=piece, 1=gram
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;


void produce(item *i) {
	while ((first + 1) % BUFFER_SIZE == last) {
	// do nothing -- no free buffer item
	}
	memcpy(&buffer[first], i, sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
}

item *consume() {
	item *i = malloc(sizeof(item));
	while (first == last) {
		// do nothing -- nothing to consume
	}
	memcpy(i, &buffer[last], sizeof(item));
	last = (last + 1) % BUFFER_SIZE;
	return i;
}

void *producer(void *param){
	item i1,i2,i3;
	i1.type = '0';
	i1.amount = 5 ;
	i1.unit = '0';
	produce(&i1);
	printf("Log values of first = %d, last = %d \n", first,last);
	i2.type = '1';
	i2.amount = 10;
	i2.unit = '1';
	produce(&i2);
	printf("Log values of first = %d, last = %d \n", first,last);
	i3.type = '1';
	i3.amount = 20;
	i3.unit = '1';
	produce(&i3);
	printf("Log values of first = %d, last = %d \n", first,last);
	
}

void *consumer(void *param){
	consume();
	printf("Log values of first = %d, last = %d \n", first,last);
	consume();
	printf("Log values of first = %d, last = %d \n", first,last);
	
}



int main(){
	pthread_t tid;
	pthread_create(&tid, NULL, producer, NULL);
	pthread_create(&tid, NULL, consumer, NULL);
	pthread_join(tid, NULL);
}

