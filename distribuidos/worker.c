#include "worker.h"
#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

static void crear_fragmento(char *resultado, int numero, int longitud) {
    const char letras[] = "abcdefghijklmnopqrstuvwxyz";
    int base = 26;
    for (int i = longitud - 1; i >= 0; i--) {
        resultado[i] = letras[numero % base];
        numero /= base;
    }
    resultado[longitud] = '\0';
}

void *ejecutar_worker(void *arg) {
    struct WorkerArgs *data = (struct WorkerArgs *)arg;
    char buffer[512];
    int base = 26;

    for (int i = data->inicio; i < data->fin; i++) {
        pthread_mutex_lock(data->candado);
        if (*data->encontrado) {
            pthread_mutex_unlock(data->candado);
            return NULL;
        }
        pthread_mutex_unlock(data->candado);

        char fragmento[data->tam_vacio + 1];
        crear_fragmento(fragmento, i, data->tam_vacio);

        strcpy(buffer, data->texto_original);
        char *pos = strstr(buffer, "???");
        if (pos) strncpy(pos, fragmento, data->tam_vacio);

        unsigned int h = generar_hash(buffer);

        if (hash_con_ceros(h, data->ceros)) {
            pthread_mutex_lock(data->candado);
            if (!*data->encontrado) {
                *data->encontrado = 1;
                printf("\n Hilo %d halló coincidencia:\n", data->identificador);
                printf("    Texto: %s\n    Hash: %u\n", buffer, h);
            }
            pthread_mutex_unlock(data->candado);
            return NULL;
        }
    }

    printf("Hilo %d terminó sin resultados válidos.\n", data->identificador);
    return NULL;
}
