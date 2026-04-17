// Asumiendo que dispone de semaforos en su sistema

// `init(sem_t s, int value);`

// `down(sem_t s);`

// `up(sem_t s)` 

// Implemente su propia libreria de semaforos haciendo uso de la ya disponible

// `my_init(int *s, int initial_value)`

// `my_down(int *s)`

// `my_up(int *s);`

// - Notar que por simplicidad esta nueva libreria puede tomar un int* en lugar de sem_t
// - Se puede apuntar a una variable global por simplicidad
// - Puede recurrir a espera activa (busy waiting) para simular el bloqueo usual de un proceso al ejectuar down

int valor;
sem_t mutex;

void my_init(int* s, int initial_value) {
    *s = initial_value;
    init(mutex, 1);
}

void my_down(int* s){

    //Yo lo que quiero es que el proceso quede trabado en un while
    while(1) {
        down(&mutex);
        if(*s > 0) {
            *s--;
            up(&mutex);
            break;
        }
        up(mutex);
    }
}

void my_up(int* s) {

    //Yo lo que quiero es hacer valor++;
    down(&mutex);
    valor++;
    up(&mutex)
}