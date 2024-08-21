#include <stdio.h>
#include <omp.h>

#define N 1000000

int main() {
    int sum = 0;

    // Obtener el tiempo inicial
    double start_time = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= N; i++) {
        sum += i;
    }

    // Obtener el tiempo final
    double end_time = omp_get_wtime();

    printf("La suma de los primeros %d numeros naturales es: %d\n", N, sum);
    printf("Tiempo de ejecucion: %f segundos\n", end_time - start_time);

    return 0;
}
