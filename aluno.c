#include "dependencias.h"
typedef struct disciplinaCursada{
    int codigo;
    double nota[2];
    struct disciplinaCursada* ptrProximaDisciplina;
    struct disciplinaCursada* ptrAnteriorDisciplina;
}  disciplinaCursada;
typedef struct aluno{
    disciplinaCursada disciplinasCursadas;
    disciplinaCursada* ptrPrimeiraDisciplina;
    struct aluno* ptrAnteriorAluno;
    struct aluno* ptrProximoAluno;

    int ra;
} aluno;

void inserirAluno(aluno* primeiroAluno, aluno* novoAluno) {
    aluno* x = primeiroAluno;
    while(x->ptrProximoAluno){
        x = x->ptrProximoAluno;
    }
    x->ptrProximoAluno = novoAluno;
    novoAluno->ptrAnteriorAluno = x;
}
double calculoMedia(aluno a1, int codigoDisciplina){
    disciplinaCursada* ptrDisciplina = a1.ptrPrimeiraDisciplina;
    int x = ptrDisciplina->codigo;
    do{
        if(x == codigoDisciplina)
            break;
        
        ptrDisciplina = ptrDisciplina->ptrProximaDisciplina;
    }while(ptrDisciplina != NULL);
    if(ptrDisciplina == NULL);//TO DO:adicionar condicao caso disciplina nao seja cursada pelo aluno
    return (ptrDisciplina->nota[0] + ptrDisciplina->nota[1])/2; /* */
}
int determinarAprovacao(aluno aluno, int codigoDisciplina){
    if(calculoMedia(aluno,codigoDisciplina) >= 6)
        return 1;
    else
        return 0;
}
