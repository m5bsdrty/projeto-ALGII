
#ifndef PREREQUISITO
#define PREREQUISITO
#include "dependencias.h"
typedef struct codigoPrerequisitos{
    int codigo;
    struct codigoPrerequisitos* ptrAnteriorCodigoPrerequisitos;
    struct codigoPrerequisitos* ptrProximoCodigoPrerequisitos;
} codigoPrerequisitos;

codigoPrerequisitos* buscarPreRequisitoPorCodigo(codigoPrerequisitos* x, int codigo);

int inserirPreRequisito(codigoPrerequisitos* primeiroPreRequisito, codigoPrerequisitos* novoPreRequisito);
void deletarTodosPreRequisitos(codigoPrerequisitos* ptrPrimeiroPreRequisito);
void deletarPreRequisitoEspecifico(codigoPrerequisitos* ptrPrimeiroPreRequisito);
#endif
