#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

// Declaraci�n de la funci�n para imprimir un arreglo
void imprimeArreglo(int* d, int mostrar);

int main()
{
    // Declarar las variables que eran definidas por #define
    int N=1000, chunk=100, mostrar=10, rango;

    std::cout << "Ingrese el rango de valores aleatorios (RANGO): ";
    std::cin >> rango;  // L�mite superior para los n�meros aleatorios (0 a RANGO-1)

    // Declarar los arreglos din�micamente seg�n el tama�o especificado por el usuario
    int* a = new int[N];  // Arreglo A
    int* b = new int[N];  // Arreglo B
    int* c = new int[N];  // Arreglo C (resultado de la suma A + B)

    std::cout << "Sumando Arreglos en Paralelo!\n";

    // Inicializaci�n de los arreglos con valores aleatorios
    srand(time(0));  // Establecer la semilla para generar n�meros aleatorios
    for (int i = 0; i < N; i++) {
        a[i] = rand() % rango;  // Valores aleatorios para el arreglo A
        b[i] = rand() % rango;  // Valores aleatorios para el arreglo B
    }

    // Paralelizaci�n del ciclo de suma utilizando OpenMP
#pragma omp parallel for shared(a, b, c) schedule(static, chunk)
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];  // Realizar la suma elemento a elemento
    }

    // Imprimir los primeros 'MOSTRAR' elementos de los arreglos para verificar los resultados
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo A: " << std::endl;
    imprimeArreglo(a, mostrar);

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo B: " << std::endl;
    imprimeArreglo(b, mostrar);

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo C: " << std::endl;
    imprimeArreglo(c, mostrar);

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