#include <stdio.h>
#include <stdlib.h>
#include "dinamic_arrays_lib.h"

void mostrar(int *vec, int cant)
{
    for(int i = 0 ; i < cant ; i++)
    {
        printf("%d\t", vec[i]);
    }
}


int* resize(int* old_vector, int old_size, int new_size)
{
    int* new_vector = new int[new_size];
    if(new_size > old_size) // El nuevo vector es más grande. 
    {
        for(int k = 0 ; k < old_size ; k++)
        {
            new_vector[k] = old_vector[k];
        }
    }
    if(new_size < old_size) // El nuevo vector es más chico. 
    {
        for(int k = 0 ; k < new_size ; k++)
        {
            new_vector[k] = old_vector[k];
        }
    }
    delete []old_vector; // Deleteo el vector viejo que mandé desde mi main.
    old_vector = NULL; // Me aseguro que el puntero no quede apuntando a memoria que ya no pertenece a mi programa.
    return new_vector;
}

int* removeItem(int* vec,int vec_size,int item_pos)
{
    int aux;
    int* resulting_vector = new int[vec_size - 1];
    for(int k = 0 ; k < item_pos ; k++)
    {
        resulting_vector[k]=vec[k];
    }
    aux = vec[item_pos + 1];
    for(int k = item_pos + 1 ; k < vec_size - 1 ; k++)
    {
        if(k == item_pos + 1)
        {
            resulting_vector[item_pos] = aux;
        }
        resulting_vector[k]=vec[k+1]; // vec[] solo llega hasta vec_size. Pues, (vec_size - 1) + 1 = vec_size.
    }
    delete []vec; // Deleteo el vector viejo que mandé desde mi main.
    vec = NULL; // Me aseguro que el puntero no quede apuntando a memoria que ya no pertenece a mi programa.
    return resulting_vector;
}

int* insertItem(int* vec,int vec_size,int insert_pos,int insert_value)
{
    int aux;
    int* resulting_vector = new int[vec_size + 1];
    for(int k = 0 ; k < insert_pos ; k++)
    {
        resulting_vector[k]=vec[k];
    }
    aux = vec[insert_pos];
    resulting_vector[insert_pos] = insert_value;
    for(int k = insert_pos + 1 ; k < vec_size + 1 ; k++)
    {
        if(k == insert_pos + 1)
        {
            resulting_vector[insert_pos + 1] = aux;
            k++;
        }
        resulting_vector[k]=vec[k-1]; // vec[] solo llega hasta vec_size. Pues, (vec_size + 1) - 1 = vec_size.
    }
    delete []vec; // Deleteo el vector viejo que mandé desde mi main.
    vec = NULL; // Me aseguro que el puntero no quede apuntando a memoria que ya no pertenece a mi programa.
    return resulting_vector;
}

int* concat(int* vec_left,int left_size,int* vec_right,int right_size)
{
    int* resulting_vector = new int[left_size + right_size];
    // Copying the values of the vec_left in the resulting_vector
    int k;
    for(k = 0 ; k < left_size ; k++)
    {
        resulting_vector[k]=vec_left[k];
    }
    // Copying the values of the vec_right in the resulting_vector
    int m;
    for(m = 0 ; m < right_size; m++)
    {
        resulting_vector[m+k]=vec_left[m];
    }
    delete []vec_left; // Deleteo el vector viejo que mandé desde mi main.
    vec_left = NULL; // Me aseguro que el puntero no quede apuntando a memoria que ya no pertenece a mi programa
    delete []vec_right; // Deleteo el vector viejo que mandé desde mi main.
    vec_right = NULL; // Me aseguro que el puntero no quede apuntando a memoria que ya no pertenece a mi programa
    return resulting_vector;
}

