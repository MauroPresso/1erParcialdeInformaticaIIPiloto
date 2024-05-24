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
    int32_t next_index_panel_1;

    int32_t start_index_panel_2;
    int32_t next_index_panel_2;
    
    
    fread(&start_index_panel_1, sizeof(int32_t), 1, pf);
    printf("\nStart Index Panel #1: %d", start_index_panel_1);
    fread(&start_index_panel_2, sizeof(int32_t), 1, pf);
    printf("\nStart Index Panel #2: %d", start_index_panel_2);
    fseek(pf, (start_index_panel_1*sizeof(struct Panel)), SEEK_CUR);
    fread(&vector1[0].voltage, sizeof(float), 1, pf);
    printf("\nVoltage: %0.3f V", vector1[0].voltage);
    fread(&vector1[0].current, sizeof(float), 1, pf);
    printf("\nCurrent: %0.3f A", vector1[0].current);
    fread(&vector1[0].radiation, sizeof(float), 1, pf);
    printf("\nRadiation: %0.3f W/m^2", vector1[0].radiation);
    fread(&next_index_panel_1, sizeof(int32_t), 1, pf);
    printf("\nNext Index Panel #1: %d", next_index_panel_1);
    //fseek(pf, (next_index_panel_1*sizeof(struct Panel)), SEEK_CUR);    
    printf("\n");

    /*
    // Llenando vector 1.
    for (uint8_t i = 0; i < (total_count/2); i++) 
    {
        printf("\n\ni: %d", i);
        if(i == 0)
        {
            fread(&start_index_panel_1, sizeof(int32_t), 1, pf); // 1er vuelta: Donde está la posicion '0' para el panel 1.
            printf("\nStart Index Panel #1: %d", start_index_panel_1);
            fseek(pf, (sizeof(int32_t)), SEEK_SET);
            fseek(pf, (start_index_panel_1*sizeof(struct Panel)), SEEK_SET);
        }
        fread(&vector1[i].voltage, sizeof(float), 1, pf);
        fread(&vector1[i].current, sizeof(float), 1, pf);
        fread(&vector1[i].radiation, sizeof(float), 1, pf);
        fread(&next_index_panel_1, sizeof(int32_t), 1, pf);
        printf("\nNext Index Panel #1: %d", next_index_panel_1);
        // Mover el puntero del archivo al siguiente paquete
        if (next_index_panel_1 != (-1)) 
        {
            fseek(pf, (next_index_panel_1*sizeof(struct Panel)), SEEK_SET); // El indice del panel se cuenta desde el inicio del archivo
        } 
        else 
        {
            break; // Si nextIndex es -1, hemos llegado al final de los datos del panel
        }
    }
    
    // Llenando vector 2.
    for (uint8_t i = 0; i < (total_count/2); i++) 
    {
        printf("\n\ni: %d", i);
        if(i == 0)
        {
            fread(&start_index_panel_2, sizeof(int32_t), 1, pf); // 1er vuelta: Donde está la posicion '0' para el panel 1.
            printf("\nStart Index Panel #2: %d", start_index_panel_2);
            fseek(pf, (start_index_panel_2*sizeof(struct Panel)), SEEK_SET);
        }
        fread(&vector2[i].voltage, sizeof(float), 1, pf);
        fread(&vector2[i].current, sizeof(float), 1, pf);
        fread(&vector2[i].radiation, sizeof(float), 1, pf);
        fread(&next_index_panel_2, sizeof(int32_t), 1, pf);
        printf("\nNext Index Panel #2: %d", next_index_panel_2);
        // Mover el puntero del archivo al siguiente paquete
        if (next_index_panel_2 != (-1)) {
            fseek(pf, (next_index_panel_2*sizeof(struct Panel)), SEEK_SET); // El indice del panel se cuenta desde el inicio del archivo
        } 
        else 
        {
            break; // Si nextIndex es -1, hemos llegado al final de los datos del panel
        }
    }
    
    /*
    printf("\n");
    // Imprimiendo vector 1.
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
    for(uint8_t i = 0; i < (total_count/2); i++)
    {
        printf("\n[%u]:", i);
        printf("\nVoltage: %0.3f V", vector1[i].voltage);
        printf("\nCurrent: %0.3f A", vector1[i].current);
        printf("\nRadiation: %0.3f W/m^2", vector1[i].radiation);
        printf("\n");
        for(uint8_t i = 0 ; i < 30 ; i++)
        {
            printf("-");
        }
    } 
    
    
    printf("\n");
    // Imprimiendo vector 2.
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
    for(uint8_t i = 0; i < (total_count/2); i++)
    {
        printf("\n[%u]:", i);
        printf("\nVoltage: %0.3f V", vector2[i].voltage);
        printf("\nCurrent: %0.3f A", vector2[i].current);
        printf("\nRadiation: %0.3f W/m^2", vector2[i].radiation);
        printf("\n");
        for(uint8_t i = 0 ; i < 30 ; i++)
        {
            printf("-");
        }
    } 
    */


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