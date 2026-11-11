#ifndef DISCIPLINA
#define DISCIPLINA
#include "dependencias.h"


typedef struct codigoPrerequisitos{
    int codigo;
    struct codigoPrerequisitos* ptrAnteriorCodigoPrerequisitos;
    struct codigoPrerequisitos* ptrProximoCodigoPrerequisitos;
} codigoPrerequisitos;
typedef struct disciplina{
    int codigo;
    codigoPrerequisitos* primeiroCodigoPrerequisitos;
    struct disciplina* ptrAnteriorDisciplina;
    struct disciplina* ptrProximaDisciplina;
} disciplina;
int inserirDisciplina(disciplina* primeiraDisciplina, disciplina* novaDisciplina);
void adicionarPrerequisitos(disciplina* disciplina, int codigoPrerequisito);


#endif
