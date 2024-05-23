#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "binary_operations_lib.h"

void show_bin32(uint32_t value)
{
    uint32_t aux;
    uint32_t mask = 1; // 0000 0000 - 0000 0000 - 0000 0000 - 0000 0001
    mask = mask << 31; // 1000 0000 - 0000 0000 - 0000 0000 - 0000 0000
    for(uint8_t i = 1 ; i <= 32 ; i++)
    {
        aux = value & mask; // Extrae el bit que necesitas.
        if(aux != 0)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
        mask = mask >> 1; // 0100 0000 - 0000 0000 - 0000 0000 - 0000 0000 // mask es un 'desplazador'
        if(i%4==0)
        {
            printf(" ");
            if(i%8==0 && i!=32)
            {
                printf("- ");
            }
        }
    }
    
}

uint32_t set_bit32(uint32_t data, uint8_t bit_pos, bool bit_value)
{
    uint32_t aux;
    uint32_t mask = 1; // 0000 0000 - 0000 0000 - 0000 0000 - 0000 0001 // ~mask == 1111 1111 - 1111 1111 - 1111 1111 - 1111 1110
    mask = mask << bit_pos; // Me lleva el 1 de la variable mask hasta la posicion del bit que quiero setear.
    // bit_value es un dato booleano (o es 'true' o es 'false'). 
    if (bit_value == true) // El bit de bit_pos te lo hace '1' sea lo que sea. // Funciona (lo probamos en papel con Marita).
    {
        aux = data | mask; // '|' == 'Alt + 124'. // Esta linea hace un OR bit a bit entre los bits de la variable data y la variable mask.
        data = aux; // Reemplazo el dato original por el dato modificado.
    }
    else // El bit de bit_pos te lo hace '0' sea lo que sea. // Funciona (lo probamos en papel con Marita).
    {
        aux = data & (~mask); // '~' == 'Alt + 126'
        data = aux; // Reemplazo el dato original por el dato modificado.
    }
    return data;
}

uint32_t toggle_bit32(uint32_t data, uint8_t bit_pos)
{
    uint32_t aux;
    uint32_t mask = 1; // 0000 0000 - 0000 0000 - 0000 0000 - 0000 0001
    mask = mask << bit_pos; // Me lleva el 1 de la variable mask hasta la posicion del bit que quiero togglear.
    aux = data ^ mask; // '^' == 'Alt + 94'.
    // Si data tiene un 0 en bit_pos, en aux me queda un 1. Si data tiene un 1 en bit_pos, en aux me queda un 0.
    data = aux;
    return data;
}

uint32_t carry_rotate32(uint32_t data, int N)
{
    uint32_t auxA;
    uint32_t auxB;
    uint32_t maskA;
    uint32_t maskB;
    if(N < (-31) && N > 31)
    {
        printf("Error: Valor de rotacion invalido.");
        return 0;
    }
    if(N == 0)
    {
        return data; // No hay rotación necesaria.
    }
    if(N > (-31) && N < 0) // Rotacion a la DERECHA.
    {
        N = -N; // Hacer N positivo.
        maskA = 1; // maskA = 0000 0000 - 0000 0000 - 0000 0000 - 0000 0001.    
        for(uint8_t i = 0 ; i < N ; i++)
        {
            auxA = data & maskA ; // Rescato el bit que quiero.
            auxA = auxA << 31 ; // Corro el bit rescatado en aux hasta el final.
            data = data >> 1 ; // Corro data un lugar, para poner luego el bit que quiero.
            data = data | auxA ; // El bit que rescate antes, lo pongo al final.
        }    
        return data;
    }
    else 
    {
        if(N > 0 && N < 31) // Rotacion a la IZQUIERDA.
        {
            maskB = 1; // mask = 0000 0000 - 0000 0000 - 0000 0000 - 0000 0001.
            maskB = maskB << 31; // maskB = 1000 0000 - 0000 0000 - 0000 0000 - 0000 0000.
            for(uint8_t i = 0 ; i < N ; i++)
            {
                auxB = data & maskB ; // Rescato el bit que quiero.
                auxB = auxB >> 31 ; // Corro el bit rescatado en aux hasta el final.
                data = data << 1 ; // Corro data un lugar, para poner luego el bit que quiero.
                data = data | auxB ; // El bit que rescate antes, lo pongo al final.
            }
            return data;
        }
    }
}

uint32_t extract_bits_segment32(uint32_t value, uint8_t startBit, uint8_t endBit) 
{
    if(endBit > 31 || startBit > endBit)
    {
        printf("\nError: Posiciones de bits invalidas\n");
        return 0;
    }
    else
    {
        if(startBit <= endBit) // Si startBit = endBit, solo me extrae 1 bit.
        {
            uint32_t left;
            left = ((sizeof(uint32_t)*8) - 1) - endBit;
            uint32_t segment;
            segment = value << left;
            uint32_t aux;
            aux = segment >> (left + startBit);
            segment = aux;
            return segment;
        }
    }

    /*uint32_t left = ((sizeof(uint32_t)*8) - 1) - endBit;
    uint32_t res = data << left;
    res = res >> (left + startBit);
    return res;*/
}