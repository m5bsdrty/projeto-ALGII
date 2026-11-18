#ifndef DISCIPLINA
#define DISCIPLINA
#include "dependencias.h"
#include "codigoPrerequisitos.h"
typedef struct disciplina{
    int primeiroPreRequisitoCriado;
    int codigo;
    codigoPrerequisitos* primeiroCodigoPrerequisitos;
    struct disciplina* ptrAnteriorDisciplina;
    struct disciplina* ptrProximaDisciplina;
} disciplina;
disciplina* buscarDisciplinaPorCodigo(disciplina* x, int codigo);
int inserirDisciplina(disciplina* primeiraDisciplina, disciplina* novaDisciplina);
void deletarDisciplina(disciplina* primeiro, int ra);

#endif
