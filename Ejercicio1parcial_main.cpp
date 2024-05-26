#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "binary_operations_lib.h"
#include "dinamic_arrays_lib.h"

struct Tarifa
{
    uint32_t parte_entera;
    uint32_t parte_decimal;
};

struct Fecha
{
    uint32_t dia;
    uint32_t mes;
    uint32_t ano;
};

struct Registro
{
    uint32_t ID_asoc;
    struct Fecha fecha_ult_consumo;
    struct Tarifa tarifa_del_kWh;
    float ult_consumo;
    uint32_t cant_periodos_impagos;
    float *consumos_adeudados = new float[cant_periodos_impagos];
};


int main()
{
    FILE *pf;
    pf = fopen("C:\\Users\\MAURO\\Documents\\1erParcialdeInformaticaIIPiloto\\registro_copelco_3.dat","rb");
    if (pf == NULL)
    {
        printf("\nError 404: Not Found\n");
        return 0;
    }
    else
    {
        printf("\nFile opening was OK. Continue with the procedure\n");
    }
    
    uint32_t encabezado;
    uint32_t cant_registros = 0;
    uint32_t cant_consumos_adeudados;
    rewind(pf);
    while( fread(&encabezado, sizeof(uint32_t), 1, pf) != 0 ) // Mientras lea encabezados va a seguir en el bucle.
    {
        cant_consumos_adeudados = extract_bits_segment32(encabezado, 16, 20);
        fseek(pf, ((sizeof(uint32_t)) + sizeof(float) + ((cant_consumos_adeudados)*(sizeof(float)))), SEEK_CUR);
        cant_registros++;
    }
    
    struct Registro *vector = new struct Registro[cant_registros];

    rewind(pf);
    // Llenando vector.
    for(uint8_t i = 0; i < cant_registros; i++)
    {
        // Encabezado
        fread(&encabezado, sizeof(uint32_t), 1, pf);
        vector[i].tarifa_del_kWh.parte_entera = extract_bits_segment32(encabezado, 26, 31);
        vector[i].tarifa_del_kWh.parte_decimal = extract_bits_segment32(encabezado, 21, 25);
        vector[i].cant_periodos_impagos = extract_bits_segment32(encabezado, 16, 20);
        vector[i].fecha_ult_consumo.ano = extract_bits_segment32(encabezado, 9, 15);
        vector[i].fecha_ult_consumo.mes = extract_bits_segment32(encabezado, 5, 8);
        vector[i].fecha_ult_consumo.dia = extract_bits_segment32(encabezado, 0, 4);
        // ID del asociado
        fread(&vector[i].ID_asoc, sizeof(uint32_t), 1, pf);
        // Ultimo consumo
        fread(&vector[i].ult_consumo, sizeof(float), 1, pf);
        // Consumos adeudados
        if(vector[i].cant_periodos_impagos > 0)
        {
            for(uint8_t j = 0; j < (vector[i].cant_periodos_impagos) ; j++)
            {
                fread(&vector[i].consumos_adeudados[j], sizeof(float), 1, pf);
            }
        }
    }
    printf("\n");
    // Imprimiendo vector
    printf("\nregistro_copelco_3.dat");
    printf("\n");
    for(uint8_t i = 0 ; i < 40 ; i++)
    {
        printf("=");
    }
    printf("\nList size: %u", cant_registros);
    for(uint8_t i = 0; i < cant_registros; i++)
    {
        printf("\n");
        for(uint8_t i = 0 ; i < 30 ; i++)
        {
            printf("-");
        }
        printf("\nID asociado: %u", vector[i].ID_asoc);
        printf("\nFecha del ultimo consumo: %u/%u/%u ", vector[i].fecha_ult_consumo.ano, vector[i].fecha_ult_consumo.mes, vector[i].fecha_ult_consumo.dia);
        printf("\nTarifa: $%u,%u", vector[i].tarifa_del_kWh.parte_entera, vector[i].tarifa_del_kWh.parte_decimal);
        printf("\nUltimo consumo: $%0.2f", vector[i].ult_consumo);
        if(vector[i].cant_periodos_impagos > 0)
        {
            printf("\nPeriodos impagos: %u", vector[i].cant_periodos_impagos);
            for(uint8_t j = 0; j < (vector[i].cant_periodos_impagos) ; j++)
            {
                printf("\nConsumos adeudados: $%0.2f", vector[i].consumos_adeudados[j]);
            }
        }
        else
        {
            printf("\nPeriodos impagos: 0");
        }
    }
    printf("\n");
    for(uint8_t i = 0 ; i < 30 ; i++)
    {
        printf("-");
    }
    
    // Total a cobrar
    printf("\n");
    float total_a_cobrar = 0;
    for(uint8_t i = 0; i < cant_registros; i++)
    {
        total_a_cobrar = total_a_cobrar + ((vector[i].tarifa_del_kWh.parte_entera)*(vector[i].ult_consumo));
        for(uint8_t j = 0; j < (vector[i].cant_periodos_impagos) ; j++)
        {
            total_a_cobrar = total_a_cobrar + ((vector[i].tarifa_del_kWh.parte_entera)*(vector[i].consumos_adeudados[j]));
        }

    }
    printf("\nTotal a cobrar (en pesos): $%0.2f", total_a_cobrar);

    fclose(pf);
    // Libero memoria.
    delete[] vector;
    // Anulo puntero
    vector = NULL;
    
    printf("\n\n\nTHE END");
    return 0;
}