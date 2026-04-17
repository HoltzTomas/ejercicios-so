// Procesos perro y cazador
// Hay un cazador y varios perros.

// Los perros comen de un recipiente que puede contener como máximo M piezas de comida.
// Cada perro, cuando quiere comer, toma una pieza y después la come.
// Los perros deben poder comer simultáneamente.

// El cazador rellena el recipiente solamente cuando está vacío, dejándolo nuevamente con M piezas.

// Se pide sincronizar los procesos usando semáforos.

#define M 5


int piezas = 0;          // asumimos que el recipiente arranca vacío

sem_t mutex = 1;         // exclusión mutua para acceder a piezas
sem_t waitForEmpty = 0;  // aviso al cazador de que el recipiente está vacío
sem_t refill = 0;        // aviso a los perros de que ya se rellenó

void perro() {
    while(1) {
        sem_wait(&mutex);

        if (piezas == 0) {
            sem_post(&waitForEmpty);   // avisa al cazador
            sem_wait(&refill);         // espera a que lo llenen
        }

        piezas--;                      // agarra una pieza
        sem_post(&mutex);

        comer();                       // la come fuera de la sección crítica
    }
}

void cazador() {
    while(1) {
        sem_wait(&waitForEmpty);   // espera aviso de recipiente vacío

        fill();                    // rellena el recipiente
        piezas = M;

        sem_post(&refill);         // habilita que continúen los perros
    }
}

// 2. ¿Por qué el perro libera el mutex antes de comer()?

// Porque tomar una pieza y comerla son cosas distintas.

// La parte crítica es sacar la pieza:

// piezas--;

// Una vez que el perro ya “agarró” su pieza, puede comer en paralelo con los demás.
// Eso cumple la condición del enunciado de que los perros puedan comer simultáneamente.