#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* hello(void* arg){
    printf("Ciao\n");
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, &hello, NULL);

}
