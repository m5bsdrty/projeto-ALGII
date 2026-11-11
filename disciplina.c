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
int inserirDisciplina(disciplina* primeiraDisciplina, disciplina* novaDisciplina) {
    disciplina* x = primeiraDisciplina;
    while(x->ptrProximaDisciplina){
        x = x->ptrProximaDisciplina;
    }
    x->ptrProximaDisciplina = novaDisciplina;
    novaDisciplina->ptrAnteriorDisciplina = x;
    return 0;
}
int adicionarPrerequisitos(disciplina* disciplina, int codigoPrerequisito){
    codigoPrerequisitos* x;
    x = disciplina->primeiroCodigoPrerequisitos;
    if(x->codigo == -1){
        x->codigo = codigoPrerequisito;
    }
    else{
            while(!x->ptrProximoCodigoPrerequisitos)
                x = x->ptrProximoCodigoPrerequisitos;
            x->ptrProximoCodigoPrerequisitos = malloc(sizeof(codigoPrerequisitos));
            x = x->ptrProximoCodigoPrerequisitos;
            x->codigo = codigoPrerequisito;
    }

}
