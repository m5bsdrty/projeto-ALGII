#ifndef SGAD
#define SGAD
#include "aluno.h"
#include "disciplina.h"
#include "dependencias.h"

int imprimirAluno(aluno a1, int ra, FILE *fptr);
int boletimIndividual(aluno* primeiroAluno, int ra);
void gerarListaAlunos(aluno* primeiroAluno);

void gerarListaDisciplinas(disciplina primeiraDisciplina);
#endif
