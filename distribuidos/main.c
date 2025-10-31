#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include "worker.h"
#include "hash.h"

#define MAX_THREADS 5

char *cargar_texto(const char *ruta) {
    FILE *f = fopen(ruta, "r");
    if (!f) {
        perror("Error al abrir archivo");
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    long tam = ftell(f);
    rewind(f);

    char *buffer = malloc(tam + 1);
    fread(buffer, 1, tam, f);
    buffer[tam] = '\0';
    fclose(f);
    return buffer;
}

int longitud_placeholder(const char *texto) {
    const char *p = strchr(texto, '?');
    if (!p) return 0;
    int count = 0;
    while (*p == '?') {
        count++;
        p++;
    }
    return count;
}

int main(int argc, char *argv[]) {
    int ceros_objetivo = 2;  
    if (argc > 1) {
        ceros_objetivo = atoi(argv[1]);
        if (ceros_objetivo < 1) ceros_objetivo = 1;
    }

    char *texto = cargar_texto("archivo.txt");
    printf("Texto original: %s\n", texto);

    unsigned int hash_inicial = generar_hash(texto);
    printf("Hash inicial: %u\n", hash_inicial);

    int tam_vacio = longitud_placeholder(texto);
    if (tam_vacio == 0) {
        printf(" No hay espacios con '?'\n");
        free(texto);
        return 0;
    }

    int total_posibilidades = pow(26, tam_vacio);
    int por_thread = total_posibilidades / MAX_THREADS;

    printf("\nBuscando combinación que genere hash con %d ceros...\n", ceros_objetivo);
    printf("Fragmento de longitud: %d  |  Total de combinaciones: %d\n", tam_vacio, total_posibilidades);

    pthread_t hilos[MAX_THREADS];
    struct WorkerArgs args[MAX_THREADS];
    int hallado = 0;
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

    for (int i = 0; i < MAX_THREADS; i++) {
        args[i].texto_original = texto;
        args[i].identificador = i + 1;
        args[i].ceros = ceros_objetivo;
        args[i].encontrado = &hallado;
        args[i].candado = &lock;
        args[i].tam_vacio = tam_vacio;
        args[i].inicio = i * por_thread;
        args[i].fin = (i + 1) * por_thread;
        pthread_create(&hilos[i], NULL, ejecutar_worker, &args[i]);
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(hilos[i], NULL);
    }

    printf("\n Proceso completado.\n");
    free(texto);
    return 0;
}
