#include <stdio.h>
#include <omp.h>

int main() {
    int i;
    int variable1 = 0; // Compartida
    int variable2;     // Privada

    // Inicializar variable1 para observar cambios en paralelo
    variable1 = 10;

    // Paralelización del ciclo for
    #pragma omp parallel for shared(variable1) private(variable2)
    for (i = 0; i < 10; ++i) {
        variable2 = i; // Cada hilo tiene su propia copia de variable2
        variable1 += i; // Todos los hilos comparten variable1
        printf("Hilo %d: variable1 = %d, variable2 = %d\n", omp_get_thread_num(), variable1, variable2);
    }

    printf("Final variable1 = %d\n", variable1);

    return 0;
}
