#ifndef ALUNO
#define ALUNO
typedef struct aluno{
    int disciplinaNotas[2];
} aluno;

double calculoMedia(aluno aluno);
int determinarAprovacao(aluno aluno);
#endif
