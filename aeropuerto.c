#include <semaphore.h>
#include <stdio.h>

sem_t mutex;              // protege depositos y esperando
sem_t aviones;            // cola de aviones bloqueados
sem_t surtidores;         // uso exclusivo de los surtidores

float deposito_fuel = 1000;
float deposito_aceite = 1000;
int esperando = 0;

void repostar(float litros_fuel, float litros_aceite) {
    sem_wait(&surtidores);   // nadie más opera mientras este avión intenta repostar
    sem_wait(&mutex);

    while (litros_fuel > deposito_fuel || litros_aceite > deposito_aceite) {
        esperando++;
        sem_post(&mutex);
        sem_post(&surtidores);   // libero surtidores para que el camión pueda reponer

        sem_wait(&aviones);      // espero reposición

        sem_wait(&surtidores);
        sem_wait(&mutex);
        esperando--;
    }

    // acciones físicas de repostaje
    deposito_fuel -= litros_fuel;
    deposito_aceite -= litros_aceite;

    sem_post(&mutex);
    sem_post(&surtidores);
}

void reponer_fuel(float litros_fuel) {
    sem_wait(&surtidores);   // mientras repone, nadie más opera
    sem_wait(&mutex);

    deposito_fuel += litros_fuel;

    for (int i = 0; i < esperando; i++) {
        sem_post(&aviones);
    }

    sem_post(&mutex);
    sem_post(&surtidores);
}

void reponer_aceite(float litros_aceite) {
    sem_wait(&surtidores);   // mientras repone, nadie más opera
    sem_wait(&mutex);

    deposito_aceite += litros_aceite;

    for (int i = 0; i < esperando; i++) {
        sem_post(&aviones);
    }

    sem_post(&mutex);
    sem_post(&surtidores);
}