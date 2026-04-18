const int N = ...;
class Zapato { ... }
class Cesto {
    Cesto (int capacidad);
    void meterZapatoDerecho(Zapato);
    void meterZapatoIzquierdo(Zapato);
    Zapato sacarZapatoDerecho();
    Zapato sacarZapatoIzquierdo();
}

Cesto cesto = new Cesto(N);

sem_t mutex = 1;
sem_t lugaresLibres = N;
sem_t hayPar = 0;

int zapatoIzq = 0;
int zapatoDer = 0;


// hilos productores
void ObreroDerechos() {
    while (true) {
        Zapato z;
        ... fabricar zapato derecho z

        wait(lugaresLibres);
        wait(mutex);

        cesto.meterZapatoDerecho(z);
        zapatoDer++;

        if (zapatoDer >= 1 && zapatoIzq >= 1) {
            post(hayPar);
        }

        post(mutex);
    }
}

void ObreroIzquierdos() {
    while (true) {
        ... fabricar un zapato izquierdo Z
        cesto.meterZapatoIzquierdo(Z);
    }
}

// hilo empaquetador
void Empaquetador() {
    while (true) {
        Zapato izq, dch;
        izq = cesto.sacarZapatoIzquierdo();
        dch = cesto.sacarZapatoDerecho();
        ... empaquetar zapatos (izq, dch)
    }
}