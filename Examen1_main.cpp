#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "binary_operations_lib.h"
#include "dinamic_arrays_lib.h"

struct Panel
{
    float voltage;
    float current;
    float radiation;
    int32_t next_index;
};


int main()
{
    FILE *pf;
    pf = fopen("C:\\Users\\MAURO\\Documents\\1erParcialdeInformaticaIIPiloto\\pv_data.dat","rb");
    if (pf == NULL)
    {
        printf("\nError 404: Not Found\n");
        return 0;
    }
    else
    {
        printf("\nFile opening was OK. Continue with the procedure\n");
    }
    
    
    rewind(pf);
    uint32_t header;
    uint32_t width;
    uint32_t height;
    uint32_t total_count;

    fread(&header, sizeof(uint32_t), 1, pf);
    width = extract_bits_segment32(header, 21, 31);
    height = extract_bits_segment32(header, 10, 20);
    total_count = extract_bits_segment32(header, 0, 9);

    printf("\nWidth: %u mm",width);
    printf("\nHeight: %u mm",height);
    printf("\nTotal Count: %u", total_count);

    struct Panel *vector1 = new struct Panel[(total_count/2)];
    struct Panel *vector2 = new struct Panel[(total_count/2)];

    printf("\n");
    // Hasta acá, solo llevo leido el Header.

    int32_t start_index_panel_1;
    int32_t start_index_panel_2;

    
    
    fread(&start_index_panel_1, sizeof(int32_t), 1, pf);
    printf("\nStart Index Panel #1: %d", start_index_panel_1);
    fread(&start_index_panel_2, sizeof(int32_t), 1, pf);
    printf("\nStart Index Panel #2: %d", start_index_panel_2);
    printf("\n");
    printf("\n");
    // Hasta acá, solo llevo leido el Header y los dos start Index para los dos paneles.
    
    // Llenando vector 1.
    printf("\n");
    for(uint8_t i = 0 ; i < 40 ; i++)
    {
        printf("-");
    }
    printf("\nData corresponding to Solar Panel #1:");
    printf("\n");
    for(uint8_t i = 0 ; i < 40 ; i++)
    {
        printf("-");
    }
    for (uint8_t i = 0; i < (total_count/2); i++) 
    {
        if(i == 0)
        {
            fseek(pf, (sizeof(uint32_t) + 2*sizeof(int32_t) + (start_index_panel_1)*sizeof(struct Panel)), SEEK_SET);
            
        }
        // Leyendo y cargando datos.
        printf("\n[%u]", i);
        fread(&vector1[i].voltage, sizeof(float), 1, pf);
        printf("\nVoltage: %0.3f V", vector1[i].voltage);
        fread(&vector1[i].current, sizeof(float), 1, pf);
        printf("\nCurrent: %0.3f A", vector1[i].current);
        fread(&vector1[i].radiation, sizeof(float), 1, pf);
        printf("\nRadiation: %0.3f W/m^2", vector1[i].radiation);
        fread(&vector1[i].next_index, sizeof(int32_t), 1, pf);
        printf("\nNext Index: %d", vector1[i].next_index);
        fseek(pf, (sizeof(uint32_t) + 2*sizeof(int32_t) + (vector1[i].next_index)*sizeof(struct Panel)), SEEK_SET);
        printf("\n");
        for(uint8_t i = 0 ; i < 30 ; i++)
        {
            printf("-");
        }
        // Si nextIndex es -1, hemos llegado al final de los datos del panel.
        if (vector1[i].next_index == (-1)) 
        {
            break;
        } 
    }
    printf("\n");

    // Llenando vector 2.
    printf("\n");
    for(uint8_t i = 0 ; i < 40 ; i++)
    {
        printf("-");
    }
    printf("\nData corresponding to Solar Panel #2:");
    printf("\n");
    for(uint8_t i = 0 ; i < 40 ; i++)
    {
        printf("-");
    }
    for (uint8_t i = 0; i < (total_count/2); i++) 
    {
        if(i == 0)
        {
            fseek(pf, (sizeof(uint32_t) + 2*sizeof(int32_t) + (start_index_panel_2)*sizeof(struct Panel)), SEEK_SET);
            
        }
        // Leyendo y cargando datos.
        printf("\n[%u]", i);
        fread(&vector2[i].voltage, sizeof(float), 1, pf);
        printf("\nVoltage: %0.3f V", vector2[i].voltage);
        fread(&vector2[i].current, sizeof(float), 1, pf);
        printf("\nCurrent: %0.3f A", vector2[i].current);
        fread(&vector2[i].radiation, sizeof(float), 1, pf);
        printf("\nRadiation: %0.3f W/m^2", vector2[i].radiation);
        fread(&vector2[i].next_index, sizeof(int32_t), 1, pf);
        printf("\nNext Index: %d", vector2[i].next_index);
        fseek(pf, (sizeof(uint32_t) + 2*sizeof(int32_t) + (vector2[i].next_index)*sizeof(struct Panel)), SEEK_SET);
        printf("\n");
        for(uint8_t i = 0 ; i < 30 ; i++)
        {
            printf("-");
        }
        // Si nextIndex es -1, hemos llegado al final de los datos del panel.
        if (vector2[i].next_index == (-1)) 
        {
            break;
        } 
    }
    printf("\n");


    fclose(pf);
    
    // Liberar memoria.
    delete[] vector1;
    delete[] vector2;

    // Anulando punteros;
    vector1 = NULL;
    vector2 = NULL;

    printf("\n\nTHE END");
    return 0;
}