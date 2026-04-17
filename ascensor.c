// Un ascensor tiene una capacidad máxima de 6 personas y 450 kilogramos.
// Se quiere simular el comportamiento del ascensor mediante un conjunto de hilos que actúan como personas que entran y salen del aparato. Para ello, tiene usted que implementar dos operaciones, sube_persona(peso) y baja_persona(peso).
// Estas dos operaciones serán invocadas por los hilos que simulan las personas.
// La operación de subir debe dejar bloqueado al proceso que hace la llamada mientras el ascensor esté lleno, o bien la carga en kilos no permita que el proceso se monte en el ascensor.
// La operación de bajar debe actualizar el estado del ascensor y, si es el caso, inducir el desbloqueo de otras personas que puedan estar esperando para entrar.
// TAREA. Debe usted implementar mediante semáforos las acciones de sincronización de estas operaciones de subir y bajar. Introduzca las variables auxiliares que considere necesarias.
// NO hay que implementar el sistema completo, ni los hilos: sólo el código de sincronización de estas dos operaciones.

int pesoActual = 0;
int personasActual = 0;
int esperando = 0;

sem_t mutex = 1;
sem_t bloquear_persona = 0;

void sube_persona(int peso) {
    sem_wait(&mutex);

    while (pesoActual + peso > 450 || personasActual == 6) {
        esperando++;
        sem_post(&mutex);

        sem_wait(&bloquear_persona);

        sem_wait(&mutex);
        esperando--;
    }

    personasActual++;
    pesoActual += peso;

    sem_post(&mutex);
}

void baja_persona(int peso) {
    sem_wait(&mutex);

    personasActual--;
    pesoActual -= peso;

    int n = esperando;

    sem_post(&mutex);

    for (int i = 0; i < n; i++) {
        sem_post(&bloquear_persona);
    }
}