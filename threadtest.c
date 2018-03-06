#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void* printHello(){
    printf("Hello wolrd \n");
    pthread_exit(NULL);
}


int main(){

// printf("hello world from here\n");

pthread_t  thread[5];
int i;
for( i = 0; i<5; i++){
pthread_create(&thread[1], NULL, printHello, NULL);
}

pthread_exit(NULL);
    return 0;
}