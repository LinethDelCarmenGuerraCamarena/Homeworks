#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

// Declaraci�n de la funci�n para imprimir un arreglo
void imprimeArreglo(int* d, int mostrar);

int main()
{
    // Declarar las variables que eran definidas por #define
    int N, CHUNK, MOSTRAR, RANGO;

    // Pedir al usuario los valores de las variables
    std::cout << "Ingrese el tama�o del arreglo (N): ";
    std::cin >> N;  // Tama�o de los arreglos

    std::cout << "Ingrese el tama�o del bloque de trabajo (CHUNK): ";
    std::cin >> CHUNK;  // Tama�o del bloque de iteraciones por thread

    std::cout << "Ingrese el n�mero de elementos a mostrar (MOSTRAR): ";
    std::cin >> MOSTRAR;  // N�mero de elementos a imprimir

    std::cout << "Ingrese el rango de valores aleatorios (RANGO): ";
    std::cin >> RANGO;  // L�mite superior para los n�meros aleatorios (0 a RANGO-1)

    // Declarar los arreglos din�micamente seg�n el tama�o especificado por el usuario
    int* a = new int[N];  // Arreglo A
    int* b = new int[N];  // Arreglo B
    int* c = new int[N];  // Arreglo C (resultado de la suma A + B)

    std::cout << "Sumando Arreglos en Paralelo!\n";

    // Inicializaci�n de los arreglos con valores aleatorios
    srand(time(0));  // Establecer la semilla para generar n�meros aleatorios
    for (int i = 0; i < N; i++) {
        a[i] = rand() % RANGO;  // Valores aleatorios para el arreglo A
        b[i] = rand() % RANGO;  // Valores aleatorios para el arreglo B
    }

    // Paralelizaci�n del ciclo de suma utilizando OpenMP
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

    // Liberar la memoria din�mica
    delete[] a;
    delete[] b;
    delete[] c;

    return 0;
}

// Funci�n para imprimir los primeros 'mostrar' elementos de un arreglo
void imprimeArreglo(int* d, int mostrar)
{
    for (int x = 0; x < mostrar; x++) {
        std::cout << d[x] << " - ";  // Imprime cada elemento seguido de un guion
    }
    std::cout << std::endl;  // Salto de l�nea al final
}