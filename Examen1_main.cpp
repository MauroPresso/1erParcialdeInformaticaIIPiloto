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
    
    // Llenando e imprimiendo vector 1.
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

    // Llenando e imprimiendo vector 2.
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

    float *vector_rendimiento_1 = new float[(total_count/2)];
    float *vector_rendimiento_2 = new float[(total_count/2)];

    printf("\n");
    float area_en_mm_cuad;
    area_en_mm_cuad = (width*height)*1.0;
    printf("\nArea en mm^2: %0.2f mm^2", area_en_mm_cuad);
    float area_en_m_cuad = (area_en_mm_cuad)*(0.000001);
    printf("\nArea en m^2: %0.2f m^2", area_en_m_cuad);
    printf("\n\n");
    // Llenando e imprimiendo vector_rendimiento_1
    printf("\n\nVector de rendimientos del panel 1:");
    for(uint8_t i = 0 ; i < (total_count/2) ; i++)
    {
        vector_rendimiento_1[i] = ((vector1[i].voltage)*(vector1[i].current))/(((area_en_m_cuad)*(vector1[i].radiation)))*100;
        printf("\nrendimiento_[%u] = %0.2f por ciento", i, vector_rendimiento_1[i]);
    }

    // Llenando e imprimiendo vector_rendimiento_2
    printf("\n\nVector de rendimientos del panel 2:");
    for(uint8_t i = 0 ; i < (total_count/2) ; i++)
    {
        vector_rendimiento_2[i] = (((vector2[i].voltage)*(vector2[i].current))/((area_en_m_cuad)*(vector2[i].radiation)))*100;
        printf("\nrendimiento_[%u] = %0.2f por ciento", i, vector_rendimiento_2[i]);
    }

    float rendimiento_max_panel_1;
    float rendimiento_max_panel_2;

    float rendimiento_min_panel_1;
    float rendimiento_min_panel_2;

    float suma_rendimientos_panel_1 = 0;
    float suma_rendimientos_panel_2 = 0;
    
    float rendimiento_prom_panel_1;
    float rendimiento_prom_panel_2;

    // Calculando rendimiento maximo, minimo y promedio para el panel 1.
    for(uint8_t i = 0 ; i < (total_count/2) ; i++)
    {
        if(i == 0)
        {
            rendimiento_max_panel_1 = vector_rendimiento_1[i];
            rendimiento_min_panel_1 = vector_rendimiento_1[i];
        }
        else
        {
            if(vector_rendimiento_1[i] > rendimiento_max_panel_1)
            {
                rendimiento_max_panel_1 = vector_rendimiento_1[i];
            }
            else
            {
                if(vector_rendimiento_1[i] < rendimiento_min_panel_1)
                {
                    rendimiento_min_panel_1 = vector_rendimiento_1[i];
                }
            }
        }
        suma_rendimientos_panel_1 = suma_rendimientos_panel_1 + vector_rendimiento_1[i];
    }
    rendimiento_prom_panel_1 = (suma_rendimientos_panel_1)/((total_count/2)*1.0);

    // Calculando rendimiento maximo, minimo y promedio para el panel 2.
    for(uint8_t i = 0 ; i < (total_count/2) ; i++)
    {
        if(i == 0)
        {
            rendimiento_max_panel_2 = vector_rendimiento_2[i];
            rendimiento_min_panel_2 =  vector_rendimiento_2[i];
        }
        else
        {
            if(vector_rendimiento_2[i] > rendimiento_max_panel_2)
            {
                rendimiento_max_panel_2 = vector_rendimiento_2[i];
            }
            else
            {
                if(vector_rendimiento_2[i] < rendimiento_min_panel_2)
                {
                    rendimiento_min_panel_2 =  vector_rendimiento_2[i];
                }
            }
        }
        suma_rendimientos_panel_2 = suma_rendimientos_panel_2 + vector_rendimiento_2[i];
    }
    rendimiento_prom_panel_2 = (suma_rendimientos_panel_2)/((total_count/2)*1.0);

    printf("\n\n");
    // Imprimiendo rendimiento maximo, minimo y promedio para el panel 1.
    printf("\nRendimiento maximo del panel 1: %0.2f por ciento", rendimiento_max_panel_1);
    printf("\nRendimiento minimo del panel 1: %0.2f por ciento", rendimiento_min_panel_1);
    printf("\nRendimiento promedio del panel 1: %0.2f por ciento", rendimiento_prom_panel_1);
    printf("\n");
    // Calculando rendimiento maximo, minimo y promedio para el panel 2.
    printf("\nRendimiento maximo del panel 2: %0.2f por ciento", rendimiento_max_panel_2);
    printf("\nRendimiento minimo del panel 2: %0.2f por ciento", rendimiento_min_panel_2);
    printf("\nRendimiento promedio del panel 2: %0.2f por ciento", rendimiento_prom_panel_2);


    fclose(pf);
    
    // Liberar memoria.
    delete[] vector1;
    delete[] vector2;
    delete[] vector_rendimiento_1;
    delete[] vector_rendimiento_2;
    // Anulando punteros;
    vector1 = NULL;
    vector2 = NULL;
    vector_rendimiento_1 = NULL;
    vector_rendimiento_2 = NULL;
    printf("\n\n\nTHE END");
    return 0;
}