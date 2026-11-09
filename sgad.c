#include "dependencias.h"
#include "aluno.h"
#include "disciplina.h"

void inserirAluno(aluno primeiroAluno, aluno* novoAluno) {
    if(primeiroAluno.ptrProximoAluno != NULL){
        aluno* x = primeiroAluno.ptrProximoAluno;
        do{
            x = x->ptrProximoAluno;
        }while(x->ptrProximoAluno != NULL);
        x->ptrProximoAluno = novoAluno;
        novoAluno->ptrAnteriorAluno = x;

    }
    else{
        primeiroAluno.ptrProximoAluno = novoAluno;
        novoAluno->ptrAnteriorAluno = &primeiroAluno;
    }

}
int imprimirAluno(aluno a1, int ra, FILE *fptr){
    fprintf(fptr,"RA:%d\n",ra);
     /* for(int i = 0;i < a1.numDisciplinasCursadas;i++){
          disciplinaCursada* disciplinasCursadas;
    int numDisciplinasCursadas;
    aluno* ptrAnteriorAluno
    aluno* ptrProximoAluno
        fprintf(fptr,"Codigo da disciplina:%d",disciplinasCursadas);
        fprintf(fptr,"Nota do 1 semestre:%d\n",a1.disciplinaNotas[0]);
        fprintf(fptr,"Nota do 2 semestre:%d\n",a1.disciplinaNotas[1]);
        fprintf(fptr,"Media:%lf\n",calculoMedia(a1));
        fprintf(fptr,"situacao:");
        if(determinarAprovacao(a1) == 1)
            fprintf(fptr,"aprovado");
        else
            fprintf(fptr, "reprovado");

        if(a1.ptrProximoAluno == -1){

        }
    }
        */

        //TO DO:adicionar disciplinas

}
int boletimIndividual(aluno primeiroAluno, int ra){
    FILE *fptr;
    fptr = fopen("boletimIndividual.txt", "w");
    if (fptr == NULL)
        return 1;

    aluno* x = NULL;
    
    x = &primeiroAluno;
    if(primeiroAluno.ra != ra){
        while(x->ra != ra && x->ptrProximoAluno != NULL)//adicionar condicao caso o aluno nao exista
            x = x->ptrProximoAluno;
        if(x->ptrProximoAluno == NULL && x->ra != ra)
            return -1;
    }
    imprimirAluno(*x, x->ra, *fptr);
    fclose(fptr);
    return 0;
}
void gerarListaAlunos(aluno listaAlunos[], int tamanhoListaAlunos){
    FILE *fptr;
    fptr = fopen("listaAlunos.txt", "w");
        if (fptr == NULL) {
        return;
    }
    
    for(int i = 0; i < tamanhoListaAlunos;i++){
        imprimirAluno(listaAlunos[i], i, *fptr);
        fprintf(fptr,"\n\n");
    }

    fclose(fptr);
}

int inserirDisciplina(disciplina** listaDisciplinas, int* tamanhoListaDisciplinas, disciplina novaDisciplina) {
    disciplina* temp = realloc(*listaDisciplinas, sizeof(disciplina) * (*tamanhoListaDisciplinas + 1));
    
    if (temp == NULL) {
        return -1; 
    }
    *listaDisciplinas = temp;
    (*listaDisciplinas)[*tamanhoListaDisciplinas] = novaDisciplina;
    
    (*tamanhoListaDisciplinas)++;

    return 0;
}
void gerarListaDisciplinas(disciplina listaDisciplinas[], int tamanhoListaDisciplinas){
    FILE *fptr;
    fptr = fopen("listaDisciplinas.txt", "w");
        if (fptr == NULL) {
        return;
    }
    
    for(int i = 0; i < tamanhoListaDisciplinas;i++){
        fprintf(fptr,"Codigo da disciplina:%d\n",i);
        fprintf(fptr,"Disciplinas pre-requisito:\n");
        for(int j = 0; j < listaDisciplinas[i].numCodigoPrerequisitos;j++){
            fprintf(fptr,"%d,",listaDisciplinas[i].codigoPrerequisitos[j]);
        }
        fprintf(fptr,"\n\n");
    }

    fclose(fptr);
}
