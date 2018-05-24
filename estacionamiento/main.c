#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fun.h"

#define TAMP 20
#define TAMC 50
#define ALPHA 1
#define FERRARI 2
#define AUDI 3
#define OTROS 4

int main()
{
    ePropietario propietarios[TAMP];
    eCoche coches[TAMC];
    int opcion = 0;
    int indexPropietario;
    int indexCoche;
    char confirmacion;
    int auxIdPropietario;
    int auxIdCoche;
    int estadia;
    int monto;

    inicializarPropietario(propietarios, TAMP);
    inicializarCoche(coches, TAMC);
    cargarRegistrosPropietarios(propietarios);
    cargarRegistrosCoches(coches);

    do
    {
        printf("\n1.-Ingreso propietario\n2.-Modificacion propietario\n3.-Baja propietario\n4.-Listar propietarios\n5.-Alta coche\n6.-Egreso coche\n7.-Listar coches\n8.-Recaudacion total\n9.-Recaudacion por marca\n10.-Listar coches de propietario\n11.-Listar propietarios AUDI\n12.-Listar coches y propietarios\n15.-Salir\n");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            indexPropietario = buscarEspacioPropietario(propietarios, TAMP);
            if(indexPropietario == -1)
            {
                printf("No hay mas espacio\n");
                break;
            }
            propietarios[indexPropietario].id = obtenerIdPropietario(propietarios, TAMP);
            pedirNombrePropietario(propietarios, indexPropietario);
            pedirTarjetaPropietario(propietarios, indexPropietario);
            pedirDireccionPropietario(propietarios, indexPropietario);
            propietarios[indexPropietario].estado = 1;

            break;

        case 2:
            printf("\nId: ");
            scanf("%d", &auxIdPropietario);
            indexPropietario = buscarIndexPropietario(propietarios, auxIdPropietario, TAMP);
            if(indexPropietario == -1)
            {
                printf("\nId inexistente");
                break;
            }
            printf("\n¿Esta seguro que quiere modificar al usuario? s/n\n");
            fflush(stdin);
            scanf("%c", &confirmacion);
            if(confirmacion == 'n')
                break;
            pedirTarjetaPropietario(propietarios, indexPropietario);
            break;

        case 3:
            printf("\nId: ");
            scanf("%d", &auxIdPropietario);
            indexPropietario = buscarIndexPropietario(propietarios, auxIdPropietario, TAMP);
            if(indexPropietario == -1)
            {
                printf("\nId inexistente");
                break;
            }
            printf("\n¿Esta seguro que quiere eliminar al usuario? s/n\n");
            fflush(stdin);
            scanf("%c", &confirmacion);
            if(confirmacion == 'n')
                break;
            propietarios[indexPropietario].estado = 0;
            break;

        case 4:
            listarPropietarios(propietarios, TAMP);
            break;

        case 5:
            indexCoche = buscarEspacioCoche(coches, TAMC);
            if(indexCoche == -1)
            {
                printf("\nNo hay mas lugar\n");
                break;
            }
            printf("\nId del propietario: \n");
            scanf("%d", &auxIdPropietario);
            if(buscarIndexPropietario(propietarios, auxIdPropietario, TAMP) == -1)
            {
                printf("\nNo existe ese usuario\n");
                break;
            }
            coches[indexCoche].id = obtenerIdCoche(coches, TAMC);
            coches[indexCoche].propietario = auxIdPropietario;
            coches[indexCoche].marca = pedirMarca();
            pedirPatente(coches, indexCoche);
            coches[indexCoche].estado = 1;
            break;

        case 6:
            printf("\nId del coche: \n");
            scanf("%d", &auxIdCoche);
            indexCoche = buscarIndexCoche(coches, auxIdCoche, TAMC);
            if(indexCoche == -1)
            {
                printf("\nNo existe ese vehiculo\n");
                break;
            }
            estadia = devolverHorasEstadia();

            if(coches[indexCoche].marca == ALPHA)
                monto = estadia * 150;

            if(coches[indexCoche].marca == FERRARI)
                monto = estadia * 175;

            if(coches[indexCoche].marca == AUDI)
                monto = estadia * 200;

            if(coches[indexCoche].marca == OTROS)
                monto = estadia * 250;

            imprimirTicket(coches, indexCoche, propietarios, TAMP, monto);
            coches[indexCoche].estado = 0;
            break;

        case 7:
            listarCoches(coches, TAMC, propietarios, TAMP);
            break;

        case 8:
            monto = calcularRecaudacionTotal(coches, TAMC);
            printf("\nLa recaudacion total es: %d\n", monto);
            break;

        case 9:
            monto = calcularRecaudacionMarca(coches, TAMC, ALPHA);
            printf("\nLa recaudacion de ALPHA es: %d\n", monto);

            monto = calcularRecaudacionMarca(coches, TAMC, FERRARI);
            printf("\nLa recaudacion de FERRARI es: %d\n", monto);

            monto = calcularRecaudacionMarca(coches, TAMC, AUDI);
            printf("\nLa recaudacion de AUDI es: %d\n", monto);

            monto = calcularRecaudacionMarca(coches, TAMC, OTROS);
            printf("\nLa recaudacion de OTROS es: %d\n", monto);
            break;

        case 10:
            printf("\nId del propietario: \n");
            scanf("%d", &auxIdPropietario);
            indexPropietario = buscarIndexPropietario(propietarios, auxIdPropietario, TAMP);
            if(indexPropietario == -1)
            {
                printf("\nNo existe ese usuario\n");
                break;
            }

            printf("\nPropietario: %s\n",propietarios[indexPropietario].nya);
            listarCochesPropietario(coches, TAMC, auxIdPropietario);

            break;

        case 11:
            listarPropietariosAudi(propietarios, TAMP, coches, TAMC);
            break;

        case 12: // LISTAR AUTOS POR PATENTE CON PROPIETARIO
            ordenarCoches(coches, TAMC);
            imprimirCochesYPropietarios(coches, TAMC, propietarios, TAMP);
            break;

        case 15:
            printf("Programa finalizado");
            break;

        default:
            printf("Opcion invalida\n");
        }
    }
    while(opcion != 15);
    return 0;
}
