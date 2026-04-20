// Sleeping barber. Una barberia con 1 barbero y varias sillas. Si no hay clientes el barbero se duerme. 
// Si llegan clientes y el barbero esta ocupado, esperan en sillas (hay lugar). Si noy hay lugar se van.

int sillas = 5;
sem_t sillas_mutex = 1;
sem_t clientes = 0;

void barbero() {

    while(1) {
        //Si no hay nadie, se queda dormido acá
        sem_wait(clientes);

        //Una vez ya hay clientes les corta el pelo y libera silla
        corte();
        sem_wait(sillas_mutex);
        sillas++;
        sem_post(sillas_mutex).
    }

}

void cliente() {

    sem_wait(sillas_mutex);
    //Si quedan sillas, tomamos una
    if(sillas > 0) {
        sillas--;
        sem_post(clientes); //Despierta al barbero si no habia nada
    }
    sem_post(sillas_mutex);

    //Si no habia lugar, se va.
}