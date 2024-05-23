#include "dinamic_arrays_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void llenar(int *vec, int cant);

int main()
{
    int *v = new int[10];
    int *u = new int[5];


    // vector dinamico V
    llenar(v, 10);
    printf("\nVector V:\n");
    mostrar(v, 10);

    // vector dinamico U
    llenar(u, 5);
    printf("\nVector U:\n");
    mostrar(u, 5);

    // Concatenar
    int *cad = new int[15];
    cad = concat(v, 10, u, 5);
    printf("\nVector concatenado:\n");
    mostrar(cad, 15);
    // It works OK.

    // Resizing vector V.
    // new_size < old_size
    v = resize(v, 10, 5);
    printf("\nVector V resized (new_size < old_size):\n");
    mostrar(v, 5);
    // It works OK.
    
    // Resizing vector V.
    // new_size > old_size
    v = resize(v, 5, 10);
    printf("\nVector V resized (new_size > old_size):\n");
    llenar(v, 10);
    mostrar(v, 10);
    // It works OK.

    // Inserting an item in vector V.
    v = insertItem(v, 10, 7, 137);
    printf("\nVector V (with a new item):\n");
    mostrar(v, 11);
    // It works OK.

    // Removing an item from vector V.
    v = removeItem(v, 11, 7);
    printf("\nVector V (without an old item):\n");
    mostrar(v, 10);
    // It works OK.

    delete []v; // Por cada new tiene que haber un delete.
    v = NULL; // Me aseguro que el puntero no quede apuntando a memoria que ya no pertenece a mi programa.
    
    delete []u; // Por cada new tiene que haber un delete.
    u = NULL; // Me aseguro que el puntero no quede apuntando a memoria que ya no pertenece a mi programa.

    delete []cad; // Por cada new tiene que haber un delete.
    cad = NULL; // Me aseguro que el puntero no quede apuntando a memoria que ya no pertenece a mi programa.

    return 0;
}

void llenar(int *vec, int cant)
{
    srand(time(NULL));
    for(int i = 0 ; i < cant ; i++)
    {
        vec[i] = rand()%100;
    }
}

