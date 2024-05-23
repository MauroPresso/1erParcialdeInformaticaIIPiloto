#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "binary_operations_lib.h"
#include "dinamic_arrays_lib.h"
#include <math.h>


int main()
{
    FILE *pf;
    pf = fopen("C:\\Users\\MAURO\\Documents\\1erParcialdeInformaticaIIPiloto\\swt_data.dat","rb");
    if (pf == NULL)
    {
        printf("\nError 404: Not Found\n");
        return 0;
    }
    else
    {
        printf("\nFile opening was OK. Continue with the procedure\n");
    }
    
    uint32_t header;
    uint32_t tipo;
    uint32_t cant;
    uint32_t cant_TOTAL = 0;
    float data;

    rewind(pf);
    while( fread(&header, sizeof(uint32_t), 1, pf) != 0 )
    {
        tipo = extract_bits_segment32(header, 30, 31);
        cant = extract_bits_segment32(header, 0, 29);
        if(tipo == 0b00 )
        {
            printf("\ntype: torque");
            printf("\ncnt: %u", cant);
            cant_TOTAL = cant_TOTAL + cant;
            for(uint8_t i = 0 ; i < cant ; i++)
            {
                fread(&data, sizeof(float), 1, pf);
                printf("\n%0.3f Nm", data);
            }
        }
        if(tipo == 0b01)
        {
            printf("\ntype: vel");
            printf("\ncnt: %u", cant);
            cant_TOTAL = cant_TOTAL + cant;
            for(uint8_t i = 0 ; i < cant ; i++)
            {
                fread(&data, sizeof(float), 1, pf);
                printf("\n%0.3f rad/s", data);
            }
        }
        if(tipo == 0b10)
        {
            printf("\ntype: power");
            printf("\ncnt: %u", cant);
            cant_TOTAL = cant_TOTAL + cant;
            for(uint8_t i = 0 ; i < cant ; i++)
            {
                fread(&data, sizeof(float), 1, pf);
                printf("\n%0.3f Watts", data);
            }
        }
        printf("\n");
        for(uint8_t i = 0 ; i < 12 ; i++)
        {
            printf("-");
        }
    }

    //printf("\ncant_TOTAL = %u", cant_TOTAL);
    uint32_t cantMuestras = (cant_TOTAL/3);
    //printf("\ncantMuestras = %u", cantMuestras);
    
    float *vectorTorque = new float[cantMuestras];
    float *vectorVel = new float[cantMuestras];
    float *vectorPower = new float[cantMuestras];

    uint8_t ult_pos_Torque = 0;
    uint8_t ult_pos_Vel = 0;
    uint8_t ult_pos_Power = 0;

    rewind(pf);
    while( fread(&header, sizeof(uint32_t), 1, pf) != 0 )
    {
        uint8_t k;
        tipo = extract_bits_segment32(header, 30, 31);
        cant = extract_bits_segment32(header, 0, 29);
        if(tipo == 0b00 ) // Torque
        {
            for(k = ult_pos_Torque ; k < (ult_pos_Torque + cant) ; k++)
            {
                fread(&vectorTorque[k], sizeof(float), 1, pf);
            }
            ult_pos_Torque = k;
        }
        if(tipo == 0b01) // Vel
        {
            for(k = ult_pos_Vel ; k < (ult_pos_Vel + cant) ; k++)
            {
                fread(&vectorVel[k], sizeof(float), 1, pf);
            }
            ult_pos_Vel = k;
        }
        if(tipo == 0b10) // Power
        {
            for(k = ult_pos_Power ; k < (ult_pos_Power + cant) ; k++)
            {
                fread(&vectorPower[k], sizeof(float), 1, pf);
            }
            ult_pos_Power = k;
        }
    }
    
    
    // Printing vectors
    printf("\n");
    printf("\nTorque:\n");
    for(uint8_t i = 0 ; i < cantMuestras ; i++)
    {
        printf("\nTorque[%u] = %0.3f Nm", i, vectorTorque[i]);
    }
    printf("\n");
    printf("\nVel:\n");
    for(uint8_t i = 0 ; i < cantMuestras ; i++)
    {
        printf("\nVel[%u] = %0.3f rad/s", i, vectorVel[i]);
    }
    printf("\n");
    printf("\nPower:\n");
    for(uint8_t i = 0 ; i < cantMuestras ; i++)
    {
        printf("\nPower[%u] = %0.3f Watts", i, vectorPower[i]);
    }
    

    // Encontrando la potencia maxima.
    float max_power;
    uint8_t pos_max_power;
    for(uint8_t i = 0 ; i < cantMuestras ; i++)
    {
        if(i == 0)
        {
            max_power = vectorPower[i];
            pos_max_power = i;
        }
        else
        {
            if(vectorPower[i] > max_power)
            {
                max_power = vectorPower[i];
                pos_max_power = i;
            }
        }
    }
    printf("\n\nLa potencia maxima es: %0.3f y se encuentra en la posicion %u", max_power, pos_max_power);
    float RPM_max_power = (vectorVel[pos_max_power])*(60/(2*3.1416));
    printf("\nLa correspondientes RPM para la potencia maxima es: %0.3f", RPM_max_power);

    // Calculando ERROR relativo.
    printf("\n");
    float *vectorError_rel = new float[cantMuestras];
    for(uint8_t i = 0 ; i < cantMuestras ; i++)
    {
        if(vectorPower[i] != 0)
        {
            vectorError_rel[i] = (abs((((vectorTorque[i])*(vectorVel[i]))-(vectorPower[i]))/(vectorPower[i])))*100;
        }
    }
    printf("\nError_rel:\n");
    for(uint8_t i = 0 ; i < cantMuestras ; i++)
    {
        if(vectorPower[i] != 0)
        {
            printf("\nError_rel[%u] = %0.2f por ciento", i, vectorError_rel[i]);
        }
        else
        {
            printf("\nError_rel[%u] -> No se pudo calcular por causa de una division por cero.", i);
        }
    }

    fclose(pf);
    
    // Liberando memoria
    delete []vectorTorque;
    delete []vectorVel;
    delete []vectorPower;
    delete []vectorError_rel;
    // Anulando punteros
    vectorTorque = NULL;
    vectorVel = NULL;
    vectorPower = NULL;
    vectorError_rel = NULL;
    

    // THE END
    printf("\n\nTHE END\n");
    return 0;
}