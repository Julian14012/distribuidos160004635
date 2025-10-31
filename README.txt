

Julian Esteban Rios Rojas-160004635
Parcial 2 - Sistemas distrinuidos  

---

Descripción

Este programa es un simulador de minería de hashes escrito en C.
Su propósito es demostrar cómo varios hilos de ejecución pueden trabajar en paralelo para encontrar una combinación de caracteres que cumpla una condición específica sobre un valor hash.

El usuario define un texto base en un archivo (texto.txt) que contiene una secuencia de signos de interrogación (?).
Cada ? representa una letra desconocida que el programa intentará reemplazar por todas las combinaciones posibles de letras minúsculas (de a a z) hasta que encuentre una que genere un hash con la cantidad de ceros solicitados.
---

Requisitos

Compilador C (por ejemplo, gcc)

Sistema operativo compatible con pthreads (Linux, macOS o WSL en Windows)

---

Funcionamiento

El programa lee el contenido de archivo.txt.

Identifica la secuencia de ? y calcula cuántas combinaciones posibles existen.

Crea varios hilos (workers) que se reparten el trabajo de probar distintas combinaciones.

Cada hilo calcula el hash del texto modificado y verifica si termina con la cantidad de ceros indicada.

Cuando alguno de los hilos encuentra una coincidencia, la muestra en pantalla

---

## Compilación

Ejecuta en la terminal:

```bash
gcc main.c worker.c hash.c -lpthread -o miner
```

---
Ejecución

Ejemplo con 3 hilos:

```bash
./miner 3
```

---

Ejemplo de salida

```
Texto original: El codigo secreto es ?????.

Hash inicial: 2396186417

Buscando combinacion que genere hash con 3 ceros...
Fragmento de longitud: 5  |  Total de combinaciones: 11881376

 Hilo 1 hallo coincidencia:
    Texto: El codigo secreto es aablh.

    Hash: 2073301000

 Proceso completado.
```
