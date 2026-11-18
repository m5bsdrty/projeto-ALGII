#include "dependencias.h"
#include "disciplinaCursada.h"
typedef struct aluno{
    disciplinaCursada* ptrPrimeiraDisciplina;
    int primeiraDisciplinaCursadaCriada;
    struct aluno* ptrAnteriorAluno;
    struct aluno* ptrProximoAluno;

    int ra;
} aluno;

aluno* buscarAlunoPorRa(aluno* x, int ra){
    while(x && x->ra != ra) x = x->ptrProximoAluno;
    return x;
}

void inserirAluno(aluno* primeiroAluno, aluno* novoAluno) {
    aluno* x = primeiroAluno;
    while(x->ptrProximoAluno){
        x = x->ptrProximoAluno;
    }
    x->ptrProximoAluno = novoAluno;
    novoAluno->ptrAnteriorAluno = x;

    novoAluno->primeiraDisciplinaCursadaCriada = 0;
}

void deletarAluno(aluno* primeiro, int ra){
    aluno* x = buscarAlunoPorRa(primeiro, ra);
    if(!x)
    {
        printf("Não existe aluno com este RA.");
        return;
    }
    aluno* anterior = x->ptrAnteriorAluno;
    aluno* proximo = x->ptrProximoAluno;
    anterior->ptrProximoAluno = proximo;
    proximo->ptrAnteriorAluno = anterior;
    
    deletarTodasDisciplinasCursadas(x->ptrPrimeiraDisciplina);
    
    free(x);
    
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

int determinarAprovacaoTotal(disciplinaCursada* disciplina){
    printf("\nDisciplina:%d\n",disciplina->codigo);
    int aprovacao = (disciplina->nota[0]+disciplina->nota[1])/2.0 >= 6;
    if(aprovacao)
        printf("Aprovado");
    else
        printf("Reprovado");
    if(!disciplina->ptrProximaDisciplina)
        return aprovacao;
    else 
        return aprovacao + determinarAprovacaoTotal(disciplina->ptrProximaDisciplina);
}