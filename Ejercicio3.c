#include <stdio.h>
#include <omp.h>

// Función para calcular el factorial de un número
void factorial(int n) {
    long long fact = 1;
    for (int i = 1; i <= n; ++i) {
        fact *= i;
    }
    printf("Factorial de %d es %lld\n", n, fact);
}

// Función para generar la serie de Fibonacci hasta n términos
void fibonacci(int n) {
    long long a = 0, b = 1, c;
    printf("Serie de Fibonacci hasta %d terminos: %lld %lld", n, a, b);
    for (int i = 2; i < n; ++i) {
        c = a + b;
        printf(" %lld", c);
        a = b;
        b = c;
    }
    printf("\n");
}

// Función para encontrar el máximo en un arreglo
void find_max(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    printf(" El maximo valor en el arreglo es %d\n", max);
}

int main() {
    int n_factorial = 3;        // Número para calcular el factorial
    int n_fibonacci = 10;       // Número de términos en la serie de Fibonacci
    int arr[] = {3, 7, 6, 8, 1}; // Arreglo para encontrar el máximo
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    // Paralelización con OpenMP
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            factorial(n_factorial);
        }

        #pragma omp section
        {
            fibonacci(n_fibonacci);
        }

        #pragma omp section
        {
            find_max(arr, arr_size);
        }
    }

    return 0;
}
