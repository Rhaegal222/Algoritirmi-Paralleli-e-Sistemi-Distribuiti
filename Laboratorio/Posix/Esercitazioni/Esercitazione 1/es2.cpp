#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <chrono>
#include <iostream>

void* run(void* arg) {
    int* p = (int*)arg;
    sleep(1);
    sleep(4 - (*p));
    return NULL;
}

int main(int argc, char* argv[]) {
    auto start_time = std::chrono::high_resolution_clock::now();

    pthread_t thid;
    int i = 1;

    pthread_create(&thid, NULL, &run, &i);

    sleep(1);
    i++;
    sleep(i);

    pthread_join(thid, NULL);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);  // Cambiato in chrono::seconds

    std::cout << "Tempo di esecuzione totale: " << duration.count() << " secondi" << std::endl;  // Cambiato il formato di stampa

    return 0;
}
