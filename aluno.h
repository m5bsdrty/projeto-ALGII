#ifndef ALUNO
#define ALUNO
#include "disciplinaCursada.h"

typedef struct aluno{
    disciplinaCursada* ptrPrimeiraDisciplina;
    int primeiraDisciplinaCursadaCriada;
    struct aluno* ptrAnteriorAluno;
    struct aluno* ptrProximoAluno;

    int ra;
} aluno;

aluno* buscarAlunoPorRa(aluno* x, int ra);
void inserirAluno(aluno* primeiroAluno, aluno* novoAluno);
void deletarAluno(aluno* primeiroLista, int ra);
void editarAluno(aluno* primeiroLista, int ra, aluno novoAluno);
double calculoMedia(aluno aluno, int codigoDisciplina);
int determinarAprovacao(aluno aluno, int codigoDisciplina);
#endif
