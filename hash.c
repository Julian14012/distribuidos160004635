#include "hash.h"
#include <stdio.h>

unsigned int generar_hash(const char *cadena) {
    unsigned int resultado = 5381;
    int ch;
    while ((ch = *cadena++)) {
        resultado = ((resultado << 5) + resultado) ^ ch;  
    }
    return resultado;
}

int hash_con_ceros(unsigned int valor, int ceros) {
    unsigned int divisor = 1;
    for (int i = 0; i < ceros; i++) divisor *= 10;
    return (valor % divisor == 0);
}
