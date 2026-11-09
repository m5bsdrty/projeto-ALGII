#ifndef DISCIPLINA
#define DISCIPLINA
#include "dependencias.h"


typedef struct disciplina{
    int codigo;
    int* codigoPrerequisitos;
    int numCodigoPrerequisitos;

}disciplina;
void adicionarPrerequisitos(disciplina* disciplina, int codigoPrerequisitos);
#endif
