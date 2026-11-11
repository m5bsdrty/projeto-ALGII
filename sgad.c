#include "dependencias.h"
#include "aluno.h"
#include "disciplina.h"


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
int boletimIndividual(aluno* primeiroAluno, int ra){
    FILE *fptr;
    fptr = fopen("binarios/boletimIndividual.txt", "w");
    if (fptr == NULL)
        return 1;

    aluno* x;
    
    x = primeiroAluno;
    if(primeiroAluno->ra != ra){
        while(x->ra != ra && x->ptrProximoAluno != NULL)//adicionar condicao caso o aluno nao exista
            x = x->ptrProximoAluno;
        if(x->ptrProximoAluno == NULL && x->ra != ra)
            return -1;
    }
    imprimirAluno(*x, x->ra, fptr);
    fclose(fptr);
    return 0;
}
void gerarListaAlunos(aluno* primeiroAluno){
    FILE *fptr;
    fptr = fopen("binarios/listaAlunos.txt", "w");
        if (fptr == NULL) {
        return;
    }
    aluno* x = primeiroAluno;
    do{
        imprimirAluno(*x, x->ra, fptr);
        fprintf(fptr,"\n\n");
        //fato curioso caso alguem esteja lendo isso: eu esqueci de adicionar x = x->ptrProximoAluno, o que resultou no meu computador travar enquanto tentava escrever um arquivo de +100mb.
    }while(x->ptrProximoAluno != NULL, x = x->ptrProximoAluno);

    fclose(fptr);
}


void gerarListaDisciplinas(disciplina* primeiraDisciplina){
    FILE *fptr;
    fptr = fopen("binarios/listaDisciplinas.txt", "w");
        if (fptr == NULL) {
        return;
    }
    if(!primeiraDisciplina)
        return;
    disciplina* x = primeiraDisciplina->ptrProximaDisciplina;
    do{
        x = x->ptrProximaDisciplina;
        fprintf(fptr,"Codigo da disciplina:%d\n",x->codigo);

    } while(!x->ptrProximaDisciplina);
    /*for(int i = 0; i < tamanhoListaDisciplinas;i++){
        fprintf(fptr,"Codigo da disciplina:%d\n",i);
        fprintf(fptr,"Disciplinas pre-requisito:\n");
        for(int j = 0; j < listaDisciplinas[i].numCodigoPrerequisitos;j++){
            fprintf(fptr,"%d,",listaDisciplinas[i].codigoPrerequisitos[j]);
        }
        fprintf(fptr,"\n\n");
    }*/

    fclose(fptr);
}
