#ifndef DISCIPLINACURSADA
#define DISCIPLINACURSADA
#include "dependencias.h"
typedef struct disciplinaCursada{
    int codigo;
    double nota[2];
    struct disciplinaCursada* ptrProximaDisciplina;
    struct disciplinaCursada* ptrAnteriorDisciplina;
}  disciplinaCursada;
disciplinaCursada* buscarDisciplinaCursadaPorCodigo(disciplinaCursada* x, int codigo);

void inserirDisciplinaCursada(disciplinaCursada* primeiro, disciplinaCursada* novo);
void deletarTodasDisciplinasCursadas(disciplinaCursada* ptrPrimeiraDisciplina);
void deletarDisciplinaEspecifica(disciplinaCursada* ptrDisciplina);



#endif