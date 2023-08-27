#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

// Dichiarazione delle variabili globali
int nThread = 5; // Numero totale di thread
int nJoined = 0; // Nunero di thread che hanno raggiunto la barriera

pthread_mutex_t mutex; // Mutex per proteggere le variabili condivise
pthread_cond_t cond; // Variabile di condizione per la sincronizzazione

// Inizializza la barriera
void initBarrier(){
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
}

// Funzione di barriera
void barrier(){
    pthread_mutex_lock(&mutex);
    nJoined++; // Incrementa il numero di thread che hanno raggiunto la barriera

    // Attendi finché tutti i thread non hanno raggiunto la barriera
    while(nJoined < nThread){
        pthread_cond_wait(&cond, &mutex); // Attendi sulla variabile di condizione
    }

    pthread_mutex_unlock(&mutex); // Sblocca il mutex
    pthread_cond_broadcast(&cond); // Inizia un segnale a tutti i thread in attesa
}

// Distruggi la barriera e rilascia le risorse
void destroyBarrier(){
    pthread_mutex_destroy(&mutex); // Sblocca il mutex
    pthread_cond_destroy(&cond); // Invia un segnale a tutti i thread in attesa
}

void* threadFunc(void* arg){     
    printf("inizio\n");     
    barrier();     
    printf("fine\n");     
    return NULL; 
}   

int main(int argc, char* argv[]){     
    pthread_t th[nThread];     
    initBarrier();     
    for (int i = 0; i < nThread; i++){
        pthread_create(&th[i], NULL, &threadFunc, NULL);      
    }      
    for (int i = 0; i < nThread; i++) {         
        pthread_join(th[i], NULL);     
    }     
    destroyBarrier();     
    return 0; 
}