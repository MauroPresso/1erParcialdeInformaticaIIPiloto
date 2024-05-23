#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "binary_operations_lib.h"



int main()
{
    uint32_t val;
    
    // Probando set_bit32().
    // TRUE.
    val = 255;
    printf("\nValor == 255:\n");
    show_bin32(val); 
    val = set_bit32(val, 3, true);
    printf("\nValor modificado con set_bit32 con el dato booleano == true:\n");
    show_bin32(val);

    val = 0;
    printf("\nValor == 0:\n");
    show_bin32(val);
    val = set_bit32(val, 3, true);
    printf("\nValor modificado con set_bit32 con el dato booleano == true:\n");
    show_bin32(val);
    // set_bit32() funciona bien para TRUE.

    // FALSE.
    val = 255;
    printf("\nValor == 255:\n");
    show_bin32(val); 
    val = set_bit32(val, 3, false);
    printf("\nValor modificado con set_bit32 con el dato booleano == false:\n");
    show_bin32(val);

    val = 0;
    printf("\nValor == 0:\n");
    show_bin32(val);
    val = set_bit32(val, 3, false);
    printf("\nValor modificado con set_bit32 con el dato booleano == false:\n");
    show_bin32(val);
    // set_bit32() funciona bien para FALSE.

    // Probando toggle_bit32().
    val = 255;
    printf("\nValor == 255:\n");
    show_bin32(val); 
    val = toggle_bit32(val, 3);
    printf("\nValor modificado con toggle_bit32:\n");
    show_bin32(val);

    val = 0;
    printf("\nValor == 0:\n");
    show_bin32(val);
    val = toggle_bit32(val, 3);
    printf("\nValor modificado con toggle_bit32:\n");
    show_bin32(val);
    // toggle_bit32() FUNCIONA BIEN.

    // Probando carry_rotate32().
    
    // Rotando a la IZQUIERDA.
    val = 4278190080;
    printf("\nValor == 4278190080:\n");
    show_bin32(val); 
    printf("\nValor == 4278190080 rotado 4 veces a la IZQUIERDA:\n");
    val = carry_rotate32(val, 4);
    show_bin32(val);
    
    // Rotando a la DERECHA.
    val = 255;
    printf("\nValor == 255:\n");
    show_bin32(val); 
    printf("\nValor == 255 rotado 4 veces a la DERECHA:\n");
    val = carry_rotate32(val, -4);
    show_bin32(val);
    
    // carry_rotate32() funciona bien tanto para la derecha como para la izquierda.

    // Probando extract_bits_segment32().
    val = 247;
    printf("\nValor == 247:\n");
    show_bin32(val);
    printf("\nSegmento de Valor == 247:\n");
    val = extract_bits_segment32(val, 0, 5);
    show_bin32(val);
    // extract_bits_segment32() FUNCIONA BIEN.

    return 0;
}

// The void show_bin32() works OK.