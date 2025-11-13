#include <stdio.h>

int main() {
    printf("Hola, mundo en C!\n");
    return 0;
}

// Para compilar: CTRL + ALT + N

/*
EJECUTAR VARIOS HILOS
---------------------
export OMP_NUM_THREADS=1
./distancias

export OMP_NUM_THREADS=4
./distancias

export OMP_NUM_THREADS=8
./distancias
*/