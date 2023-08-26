#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

class GasStation {
public:
    GasStation(pthread_mutex_t* fuelMutex, pthread_cond_t* fuelCond, int* fuel)
        : fuelMutex(fuelMutex), fuelCond(fuelCond), fuel(fuel) {}

    void fuelFilling() {
        for (int i = 0; i < 5; i++) {
            pthread_mutex_lock(fuelMutex);
            *fuel += 30;
            std::cout << "Filled fuel... " << *fuel << std::endl;
            pthread_mutex_unlock(fuelMutex);
            pthread_cond_broadcast(fuelCond);
            sleep(1);
        }
    }

private:
    pthread_mutex_t* fuelMutex;
    pthread_cond_t* fuelCond;
    int* fuel;
};

void* fuelFillingThread(void* arg) {
    GasStation* gasStation = reinterpret_cast<GasStation*>(arg);
    gasStation->fuelFilling();
    return nullptr;
}

class Car {
public:
    Car(pthread_mutex_t* fuelMutex, pthread_cond_t* fuelCond, int* fuel) 
        : fuelMutex(fuelMutex), fuelCond(fuelCond), fuel(fuel) {}

    void drive() {
        pthread_mutex_lock(fuelMutex);
        while (*fuel < 40) {
            std::cout << "No fuel. Waiting..." << std::endl;
            pthread_cond_wait(fuelCond, fuelMutex);
        }
        *fuel -= 40;
        std::cout << "Got fuel. Now left: " << *fuel << std::endl;
        pthread_mutex_unlock(fuelMutex);
    }

private:
    pthread_mutex_t* fuelMutex;
    pthread_cond_t* fuelCond;
    int* fuel;
};

void* carThread(void* arg) {
    Car* car = reinterpret_cast<Car*>(arg);
    car->drive();
    return nullptr;
}

int main(int argc, char* argv[]) {
    pthread_t th[6];
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);

    // Creazione dei thread
    for (int i = 0; i < 6; i++) {
        if (i == 4 || i == 5) {
            if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0) {
                perror("Failed to create thread");
            }
        } else {
            if (pthread_create(&th[i], NULL, &car, NULL) != 0) {
                perror("Failed to create thread");
            }
        }
    }

    // Attesa del termine dei thread
    for (int i = 0; i < 6; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }

    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);

    return 0; // Termina il programma con successo
}


// g++ -o provaThreadCondition provaThreadCondition.cpp -lpthread && ./provaThreadCondition && rm provaThreadCondition
