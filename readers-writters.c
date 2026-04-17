// Puede haber muchos readers leyendo a la vez.
// Los writers escriben de a uno.
// Nunca puede haber readers y writers accediendo a la base al mismo tiempo.
// Si llega un writer, no deben seguir entrando readers nuevos hasta que escriban los writers pendientes.
// La solución debe evitar hambre de writers.

int rc = 0;
int wc = 0;

sem_t rc_mutex = 1, wc_mutex = 1;
sem_t turnstile = 1;
sem_t db_access = 1;

void reader() {
    //Primero chequeo torniquerte
    sem_wait(turnstile);
    sem_post(turnstile);

    // Entrada de readers
    sem_wait(&mutex_rc);
    if (rc == 0) {
        // el primer reader bloquea la base para writers
        sem_wait(&db_access);
    }
    rc++;
    sem_post(&mutex_rc);

    //LECTURA

    // Salida de readers
    sem_wait(&mutex_rc);
    rc--;
    if (rc == 0) {
        // el último reader libera la base
        sem_post(&db_access);
    }
    sem_post(&mutex_rc);
}

void writer() {

    //Primero indicamos que hay un writter pendiente
    sem_wait(&mutex_wc);
    if (wc == 0) {
        // el primer writer cierra el torniquete
        sem_wait(&turnstile);
    }
    wc++;
    sem_post(&mutex_wc);

    // Acceso exclusivo a la base
    sem_wait(&db);

    // ESCRITURA

    sem_post(&db);


    // Al terminar, actualiza la cantidad de writers
    sem_wait(&mutex_wc);
    wc--;
    if (wc == 0) {
        // el último writer reabre el torniquete
        sem_post(&turnstile);
    }
    sem_post(&mutex_wc);

}