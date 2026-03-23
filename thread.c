//this is a program to demo how to create thread in linux
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg) {
    printf("%s", (char *)arg);
    return NULL;
}

int main () {
    printf("Hello, World!\n");
    pthread_t thread_id_1, thread_id_2;
    pthread_create(&thread_id_1, NULL, thread_function, "This is thread A\n");
    pthread_create(&thread_id_2, NULL, thread_function, "This is thread B\n");
    pthread_join(thread_id_1, NULL);
    pthread_join(thread_id_2, NULL);
    printf("Hello, World!\n");
    return 0;
}