// Proyecto_OMP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>
 
int main()
{
    //definir el tamaño de los arreglos
    const int N = 1000;

    //crear los arreglos
    std::vector<int> Arreglo_A(N), Arreglo_B(N), Arreglo_R(N);

    //iniciarlizar la semilla para los números aleatorios
    std::srand(static_cast<unsigned int>(std::time(0)));

    //llenar los arreglos con números aleatorios ente 0 y 99
    for (int i = 0; i < N; i++) {
        Arreglo_A[i] = std::rand() % 100;
        Arreglo_B[i] = std::rand() % 100;
    }

    //realizar la suma de arreglos de forma paralelo con OpenMP
#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        Arreglo_R[i] = Arreglo_A[i] + Arreglo_B[i];
    }

    // imprimir los primeros 10 elementos de los arreglos para verificar
    std::cout << "Primeros 10 elementos de los arreglos y su suma:\n";
    std::cout << "Arreglo_A: ";
    for (int i = 0; i < 10; i++) {
        std::cout << Arreglo_A[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Arreglo_B: ";
    for (int i = 0; i < 10; i++) {
        std::cout << Arreglo_B[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Arreglo_R: ";
    for (int i = 0; i < 10; i++) {
        std::cout << Arreglo_R[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
