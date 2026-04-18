//El problema de los fumadores de cigarrillos (Patil 1971). 
// Considere un sistema con tres procesos fumadores y un proceso agente. 
// Cada fumador está continuamente armando y fumando cigarrillos. Sin embargo, para armar un cigarrillo, el fumador necesita tres ingredientes: tabaco, papel y fósforos. 
// Uno de los procesos fumadores tiene papel, otro tiene el tabaco y el tercero los fósforos. 
// El agente tiene una cantidad infinita de los tres materiales. 
// El agente coloca dos de los ingredientes sobre la mesa. 
// El fumador que tiene el ingrediente restante armaría un cigarrillo y se lo fuma, avisando al agente cuando termina. 
// Entonces, el agente coloca dos de los tres ingredientes y se repite el ciclo. 
// Escriba un programa para sincronizar al agente y los fumadores utilizando semáforos.


sem_t agente = 1;
sem_t puede_fumar_tabaco = 0;
sem_t puede_fumar_papel = 0;
sem_t puede_fumar_fosforos = 0;

void proceso_agente() {
    while (1) {
        sem_wait(&agente);

        int opcion = rand() % 3;

        switch (opcion) {
            case 0:
                // pone papel + fósforos
                sem_post(&puede_fumar_tabaco);
                break;
            case 1:
                // pone tabaco + fósforos
                sem_post(&puede_fumar_papel);
                break;
            case 2:
                // pone tabaco + papel
                sem_post(&puede_fumar_fosforos);
                break;
        }
    }
}


void fumador_tabaco() {
    while (1) {
        sem_wait(&puede_fumar_tabaco);
        armar();
        fumar();
        sem_post(&agente);
    }
}

void fumador_papel() {
    while (1) {
        sem_wait(&puede_fumar_papel);
        armar();
        fumar();
        sem_post(&agente);
    }
}

void fumador_fosforos() {
    while (1) {
        sem_wait(&puede_fumar_fosforos);
        armar();
        fumar();
        sem_post(&agente);
    }
}