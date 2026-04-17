// * solo puede haber o ratones o el gato en la cocina
// * puede haber un máximo de 3 ratones en la cocina a la vez
// * no se tiene que dar que el gato espere eternamente a que se vayan los ratones

//Necesito un semaforo torniquete que evite que sigan entrando ratones

#include <semaphore.h>

int ratones_count = 0;
sem_t count_mutex = 1;
sem_t cat_turnstile = 1, ratones = 3, cocina_access = 1;

void raton() {
    sem_wait(&cat_turnstile);
    sem_post(&cat_turnstile); // chequea si el torniquete está abierto

    sem_wait(&ratones); // espera a que haya lugar entre los 3 cupos

    sem_wait(&count_mutex);
    if (ratones_count == 0) sem_wait(&cocina_access); // si es el primero, bloquea al gato
    ratones_count++;
    sem_post(&count_mutex);

    // COCINA

    sem_wait(&count_mutex);
    ratones_count--;
    if (ratones_count == 0) sem_post(&cocina_access); // si es el último, libera la cocina
    sem_post(&count_mutex);

    sem_post(&ratones); // libera un cupo
}

void gato() {
    sem_wait(&cat_turnstile); // cierra el paso a nuevos ratones

    sem_wait(&cocina_access); // espera a que se vayan todos los ratones y entra

    // COCINA

    sem_post(&cocina_access);
    sem_post(&cat_turnstile);
}