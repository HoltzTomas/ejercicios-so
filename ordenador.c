Un ordenador está conectado a un servidor de tres impresoras idénticas. 
El estado del servidor se define mediante un vector llamado printers[]. 
Cada elemento corresponde a una impresora.
 El valor -1 inicial significa que la impresora está libre. 
Un proceso que desea usar la impresora debe ejecutar un procedimiento Get_Printer(pid). 
Cuando finaliza debe ejecutar otro procedimiento llamado Release_Printer(pid). 
En el cuadro adjunto se muestra el uso típico de una impresora.

TAREA: Escribir el código de ambos procedimientos e implementar con semáforos las sincronizaciones necesarias para que se cumplan estos requisitos://

- Si un proceso quiere utilizar una impresora y no hay ninguna disponible, el proceso debe esperar hasta que alguna impresora quede libre.
- No puede haber más de un proceso utilizando una misma impresora.
- Mientras un proceso está utilizando una impresora, en la posición del vector printers debe almacenarse su pid.

int printers[3] = {-1, -1, -1};
sem_t mutex = 1;
sem_t hay_libres = 3;

void Get_Printer(int pid) {

    sem_wait(hay_libres);
    sem_wait(mutex);

    for (int i = 0; i < 3; i++) {
        if (printers[i] == -1) {
            printers[i] = pid;
            break;
        }
    }

    sem_post(mutex);

}


void Release_Printer(int pid) {
    wait(mutex);

    for (int i = 0; i < 3; i++) {
        if (printers[i] == pid) {
            printers[i] = -1;
            break;
        }
    }

    post(mutex);
    post(hay_libres);
}