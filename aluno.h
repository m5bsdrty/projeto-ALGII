#ifndef ALUNO
#define ALUNO
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
void inserirAluno(aluno* primeiroAluno, aluno* novoAluno);
double calculoMedia(aluno aluno, int codigoDisciplina);
int determinarAprovacao(aluno aluno, int codigoDisciplina);
#endif
