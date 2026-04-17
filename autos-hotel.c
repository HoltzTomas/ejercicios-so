// Enunciado

// En un hotel hay vehículos automáticos pequeños y grandes, cada uno representado por un proceso concurrente.

// Se quiere controlar la entrada a un montacargas en el que pueden viajar como máximo:

// 4 vehículos pequeños, o
// 2 vehículos pequeños y 1 grande.

// Resolver el problema usando semáforos.

#define CAP 4

sem_t slots = 4;       // capacidad total del montacargas
sem_t big = 1;         // a lo sumo un grande simultáneamente
sem_t turnstile = 1;   // evita que los chicos se metan mientras un grande entra

void pequeno() {
    while (1) {
        sem_wait(&turnstile);   // pasa por el torniquete
        sem_post(&turnstile);   // lo libera enseguida

        sem_wait(&slots);       // ocupa 1 lugar

        //Montacargas

        sem_post(&slots);       // libera 1 lugar
    }
}

void grande() {
    while (1) {
        sem_wait(&big);         // asegura que no haya otro grande
        sem_wait(&turnstile);   // cierra el paso a nuevos chicos

        sem_wait(&slots);       // toma 2 lugares
        sem_wait(&slots); //Esperando a que salga uno chico

        sem_post(&turnstile);   // una vez adentro, ya pueden pasar otros

        //Montacargas

        sem_post(&slots);       // libera 2 lugares
        sem_post(&slots);
        sem_post(&big);
    }
}