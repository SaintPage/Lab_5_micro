#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 131072

long count_key(long start, long end, long *a, long key) {
    long count = 0;
    if (end - start <= 1024) { // Caso base, umbral de tamaño de problema pequeño
        for (long i = start; i < end; i++) {
            if (a[i] == key) count++;
        }
    } else { // Dividir el trabajo
        long mid = (start + end) / 2;
        long left_count = 0, right_count = 0;

        #pragma omp task shared(left_count) // Crear tarea para la mitad izquierda
        left_count = count_key(start, mid, a, key);

        #pragma omp task shared(right_count) // Crear tarea para la mitad derecha
        right_count = count_key(mid, end, a, key);

        #pragma omp taskwait // Esperar a que ambas tareas completen
        count = left_count + right_count;
    }
    return count;
}

int main() {
    long a[N], key = 42, nkey = 0;
    for (long i = 0; i < N; i++) a[i] = rand() % N;
    a[N % 43] = key;
    a[N % 73] = key;
    a[N % 3] = key;

    // Inicializar OpenMP
    omp_set_num_threads(4); // Ajustar al número de hilos deseado

    #pragma omp parallel
    {
        #pragma omp single
        nkey = count_key(0, N, a, key); // Ejecutar en paralelo
    }

    printf("Numero de veces que 'key' aparece en paralelo: %ld\n", nkey);

    return 0;
}
