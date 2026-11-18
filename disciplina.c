#include "dependencias.h"
#include "codigoPrerequisitos.h"
typedef struct disciplina{
    int primeiroPreRequisitoCriado;
    int codigo;
    codigoPrerequisitos* primeiroCodigoPrerequisitos;
    struct disciplina* ptrAnteriorDisciplina;
    struct disciplina* ptrProximaDisciplina;
} disciplina;
disciplina* buscarDisciplinaPorCodigo(disciplina* x, int codigo){
    while(x && x->codigo != codigo) x = x->ptrProximaDisciplina;
    return x;
}
int inserirDisciplina(disciplina* primeiraDisciplina, disciplina* novaDisciplina) {
    disciplina* x = primeiraDisciplina;
    while(x->ptrProximaDisciplina){
        x = x->ptrProximaDisciplina;
    }
    x->ptrProximaDisciplina = novaDisciplina;
    novaDisciplina->ptrAnteriorDisciplina = x;
    return 0;
}

void deletarDisciplina(disciplina* primeiro, int ra){
    disciplina* x = buscarDisciplinaPorCodigo(primeiro, ra);
    if(!x)
    {
        printf("Não existe disciplina com este RA.");
        return;
    }
    disciplina* anterior = x->ptrAnteriorDisciplina;
    disciplina* proximo = x->ptrProximaDisciplina;
    anterior->ptrProximaDisciplina = proximo;
    proximo->ptrAnteriorDisciplina = anterior;
    
    deletarTodosPreRequisitos(x->primeiroCodigoPrerequisitos);
    
    free(x);
    
}

