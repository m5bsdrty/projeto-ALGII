#include "dependencias.h"

typedef struct disciplinaCursada{
    int codigo;
    double nota[2];
    struct disciplinaCursada* ptrProximaDisciplina;
    struct disciplinaCursada* ptrAnteriorDisciplina;
}  disciplinaCursada;

disciplinaCursada* buscarDisciplinaCursadaPorCodigo(disciplinaCursada* x, int codigo){
    while(x && x->codigo != codigo) x = x->ptrProximaDisciplina;
    return x;
}

void inserirDisciplinaCursada(disciplinaCursada* primeiro, disciplinaCursada* novo) {
    disciplinaCursada* x = primeiro;
    while(x->ptrProximaDisciplina){
        x = x->ptrProximaDisciplina;
    }
    x->ptrProximaDisciplina = novo;
    novo->ptrAnteriorDisciplina = x;
}
void deletarTodasDisciplinasCursadas(disciplinaCursada* ptrPrimeiraDisciplina){
    disciplinaCursada* x = ptrPrimeiraDisciplina->ptrProximaDisciplina;
    do{
        free(x->ptrAnteriorDisciplina);
        x = x->ptrProximaDisciplina;
    }while(x->ptrProximaDisciplina);
    free(x);
}