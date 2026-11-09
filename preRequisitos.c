#include <stdlib.h>
#include "preRequisitos.h"

int verificarRecursivo(disciplina lista[], int n, int codigo, int visitados[])
{
    int i, j;

    for (i = 0; i < n; i++)
        if (lista[i].codigo == codigo)
            break;

    if (i == n || visitados[i] == 1)
        return 0;

    if (visitados[i] == 2)
        return 1;

    visitados[i] = 1;

    for (j = 0; j < lista[i].numCodigoPrerequisitos; j++)
        if (!verificarRecursivo(lista, n, lista[i].codigoPrerequisitos[j], visitados))
            return 0;

    visitados[i] = 2;
    return 1;
}

int verificarCadeiaPrerequisitos(disciplina lista[], int n, int codigo)
{
    int i, resultado;
    int *visitados = malloc(n * sizeof(int));

    if (visitados == NULL)
        return 0;

    for (i = 0; i < n; i++)
        visitados[i] = 0;

    resultado = verificarRecursivo(lista, n, codigo, visitados);

    free(visitados);
    return resultado;
}