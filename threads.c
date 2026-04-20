Enunciado

Hay un vector global de N enteros que debe ser sumado concurrentemente por dos hilos.

Hay que proponer una solución con semáforos cumpliendo:

a. Cada número no puede sumarse dos veces.
b. Cada hilo va tomando elementos consecutivos del vector y los suma, siempre asegurándose de no usar elementos ya sumados por el otro hilo.
c. Uno de los hilos y sólo uno debe mostrar la suma total.
d. El proceso pesado que crea los hilos debe mostrar un mensaje al comenzar la prueba y otro cuando los hilos hayan terminado.

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 10

int vector[N] = {1,2,3,4,5,6,7,8,9,10};
int pos = 0;
int suma = 0;
int imprimio = 0;

sem_t mutex;

void* sumar(void* arg) {
    while (1) {
        sem_wait(&mutex);

        if (pos >= N) {
            if (!imprimio) {
                printf("Suma total: %d\n", suma);
                imprimio = 1;
            }
            sem_post(&mutex);
            break;
        }

        suma += vector[pos];
        pos++;

        sem_post(&mutex);
    }

    return NULL;
}

int main() {
    pthread_t t1, t2;

    sem_init(&mutex, 0, 1);

    printf("Comienza la prueba\n");

    pthread_create(&t1, NULL, sumar, NULL);
    pthread_create(&t2, NULL, sumar, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Finaliza la prueba\n");

    sem_destroy(&mutex);
    return 0;
}