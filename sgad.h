#ifndef SGAD
#define SGAD
#include "aluno.h"
#include "disciplina.h"
#include "dependencias.h"

void inserirAluno(aluno primeiroAluno, aluno* novoAluno);
int imprimirAluno(aluno a1, int ra, FILE *fptr);
int boletimIndividual(aluno primeiroAluno, int ra);
void gerarListaAlunos(aluno listaAlunos[], int tamanhoListaAlunos);

int inserirDisciplina(disciplina** listaDisciplina, int* tamanhoListaDisciplina, disciplina novaDisciplina);
void mostrarDisciplinas(disciplina listaDisciplina);
void gerarListaDisciplinas(disciplina listaDisciplina[], int tamanhoListaDisciplina);
#endif
