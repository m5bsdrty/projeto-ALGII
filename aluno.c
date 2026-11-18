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
    if(ptrDisciplina == NULL){
        printf("Aviso: o aluno de RA %d nao cursou nenhuma disciplina.\n", a1.ra);
        return -1;
    }
    while(ptrDisciplina != NULL && ptrDisciplina->codigo != codigoDisciplina)
        ptrDisciplina = ptrDisciplina->ptrProximaDisciplina;
    if(ptrDisciplina == NULL){
        printf("Aviso: o aluno de RA %d nao cursou a disciplina %d.\n", a1.ra, codigoDisciplina);
        return -1;
    }
    return (ptrDisciplina->nota[0] + ptrDisciplina->nota[1])/2; /* */
}
/* Retorna 1 se aprovado, 0 se reprovado e -1 se a media nao pode ser calculada. */
int determinarAprovacao(aluno aluno, int codigoDisciplina){
    double media = calculoMedia(aluno,codigoDisciplina);
    if(media < 0)
        return -1;
    if(media >= 6)
        return 1;
    else
        return 0;
}
