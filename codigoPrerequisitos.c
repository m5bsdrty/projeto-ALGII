#include "dependencias.h"
typedef struct codigoPrerequisitos{
    int codigo;
    struct codigoPrerequisitos* ptrAnteriorCodigoPrerequisitos;
    struct codigoPrerequisitos* ptrProximoCodigoPrerequisitos;
} codigoPrerequisitos;

codigoPrerequisitos* buscarPreRequisitoPorCodigo(codigoPrerequisitos* x, int codigo){
    while(x && x->codigo != codigo) x = x->ptrProximoCodigoPrerequisitos;
    return x;
}
int inserirPreRequisito(codigoPrerequisitos* primeiroPreRequisito, codigoPrerequisitos* novoPreRequisito) {
    codigoPrerequisitos* x = primeiroPreRequisito;
    while(x->ptrProximoCodigoPrerequisitos){
        x = x->ptrProximoCodigoPrerequisitos;
    }
    x->ptrProximoCodigoPrerequisitos = novoPreRequisito;
    novoPreRequisito->ptrAnteriorCodigoPrerequisitos = x;
    return 0;
}
void deletarTodosPreRequisitos(codigoPrerequisitos* ptrPrimeiroPreRequisito){
    codigoPrerequisitos* x = ptrPrimeiroPreRequisito->ptrProximoCodigoPrerequisitos;
    while(x->ptrProximoCodigoPrerequisitos){
        free(x->ptrAnteriorCodigoPrerequisitos);
        x = x->ptrProximoCodigoPrerequisitos;
    }
    free(x);
}

void deletarPreRequisitoEspecifico(codigoPrerequisitos* ptrPrimeiroPreRequisito){
    codigoPrerequisitos* anterior = ptrPrimeiroPreRequisito->ptrAnteriorCodigoPrerequisitos;
    codigoPrerequisitos* proxima = ptrPrimeiroPreRequisito->ptrProximoCodigoPrerequisitos;
    anterior->ptrProximoCodigoPrerequisitos = proxima;
    proxima->ptrAnteriorCodigoPrerequisitos = anterior;
    free(ptrPrimeiroPreRequisito);
}