#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

// Declaración de la función para imprimir un arreglo
void imprimeArreglo(int* d, int mostrar);

int main()
{
    // Declarar las variables que eran definidas por #define
    int N, CHUNK, MOSTRAR, RANGO;

    // Pedir al usuario los valores de las variables
    std::cout << "Ingrese el tamaño del arreglo (N): ";
    std::cin >> N;  // Tamaño de los arreglos

    std::cout << "Ingrese el tamaño del bloque de trabajo (CHUNK): ";
    std::cin >> CHUNK;  // Tamaño del bloque de iteraciones por thread

    std::cout << "Ingrese el número de elementos a mostrar (MOSTRAR): ";
    std::cin >> MOSTRAR;  // Número de elementos a imprimir

    std::cout << "Ingrese el rango de valores aleatorios (RANGO): ";
    std::cin >> RANGO;  // Límite superior para los números aleatorios (0 a RANGO-1)

    // Declarar los arreglos dinámicamente según el tamaño especificado por el usuario
    int* a = new int[N];  // Arreglo A
    int* b = new int[N];  // Arreglo B
    int* c = new int[N];  // Arreglo C (resultado de la suma A + B)

    std::cout << "Sumando Arreglos en Paralelo!\n";

    // Inicialización de los arreglos con valores aleatorios
    srand(time(0));  // Establecer la semilla para generar números aleatorios
    for (int i = 0; i < N; i++) {
        a[i] = rand() % RANGO;  // Valores aleatorios para el arreglo A
        b[i] = rand() % RANGO;  // Valores aleatorios para el arreglo B
    }

    // Paralelización del ciclo de suma utilizando OpenMP
#pragma omp parallel for shared(a, b, c) schedule(static, CHUNK)
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];  // Realizar la suma elemento a elemento
    }

    // Imprimir los primeros 'MOSTRAR' elementos de los arreglos para verificar los resultados
    std::cout << "Imprimiendo los primeros " << MOSTRAR << " valores del arreglo A: " << std::endl;
    imprimeArreglo(a, MOSTRAR);

    std::cout << "Imprimiendo los primeros " << MOSTRAR << " valores del arreglo B: " << std::endl;
    imprimeArreglo(b, MOSTRAR);

    std::cout << "Imprimiendo los primeros " << MOSTRAR << " valores del arreglo C: " << std::endl;
    imprimeArreglo(c, MOSTRAR);

    // Liberar la memoria dinámica
    delete[] a;
    delete[] b;
    delete[] c;

    return 0;
}

// Función para imprimir los primeros 'mostrar' elementos de un arreglo
void imprimeArreglo(int* d, int mostrar)
{
    for (int x = 0; x < mostrar; x++) {
        std::cout << d[x] << " - ";  // Imprime cada elemento seguido de un guion
    }
    std::cout << std::endl;  // Salto de línea al final
}