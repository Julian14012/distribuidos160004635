#ifndef WORKER_H
#define WORKER_H

#include <pthread.h>

struct WorkerArgs {
    const char *texto_original;
    int identificador;
    int ceros;
    int *encontrado;
    pthread_mutex_t *candado;
    int tam_vacio;
    int inicio;
    int fin;
};

void *ejecutar_worker(void *arg);

#endif
