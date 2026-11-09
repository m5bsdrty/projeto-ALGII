#ifndef SGAD
#define SGAD
#include "aluno.h"
#include "disciplina.h"
#include "dependencias.h"

int inserirAluno(aluno** listaAlunos, int* tamanhoListaAlunos, aluno novoAluno);
void mostrarAlunos(aluno listaAlunos);
void boletimIndividual(aluno aluno, int ra);
void gerarListaAlunos(aluno listaAlunos[], int tamanhoListaAlunos);

int inserirDisciplina(disciplina** listaDisciplina, int* tamanhoListaDisciplina, disciplina novaDisciplina);
void mostrarDisciplinas(disciplina listaDisciplina);
void gerarListaDisciplinas(disciplina listaDisciplina[], int tamanhoListaDisciplina);
#endif
