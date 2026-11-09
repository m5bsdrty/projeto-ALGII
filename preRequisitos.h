#ifndef PRE_REQUISITOS_H
#define PRE_REQUISITOS_H

#include "disciplina.h"

/* Retorna 1 se a cadeia for valida e 0 se houver algum problema. */
int verificarCadeiaPrerequisitos(
    disciplina lista[],
    int quantidade,
    int codigo
);

#endif
