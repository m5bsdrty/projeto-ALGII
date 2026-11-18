#ifndef SGAD
#define SGAD
#include "aluno.h"
#include "disciplina.h"
#include "dependencias.h"

int imprimirAluno(aluno a1, int ra, FILE *fptr);
int boletimIndividual(aluno* primeiroAluno, int ra);
void gerarListaAlunos(aluno* primeiroAluno);
/* Carregam os arquivos txt para a lista. Retornam a quantidade carregada ou -1 se nao foi possivel abrir o arquivo. */
int carregarListaAlunos(aluno** primeiroAluno);
int carregarListaDisciplinas(disciplina** primeiraDisciplina);

void gerarListaDisciplinas(disciplina* primeiraDisciplina);
#endif
