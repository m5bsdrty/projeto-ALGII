#include "dependencias.h"
#include "aluno.h"
#include "disciplina.h"
int inserirAluno(aluno** listaAlunos, int* tamanhoListaAlunos, aluno novoAluno) {
    aluno* temp = realloc(*listaAlunos, sizeof(aluno) * (*tamanhoListaAlunos + 1));
    
    if (temp == NULL) {
        return -1; 
    }
    *listaAlunos = temp;
    (*listaAlunos)[*tamanhoListaAlunos] = novoAluno;
    
    (*tamanhoListaAlunos)++;

    return 0;
}
int boletimIndividual(aluno a1, int ra){
    FILE *fptr;
    fptr = fopen("boletimIndividual.txt", "w");
        if (fptr == NULL) {
        return 1;
    }
    
    fprintf(fptr,"RA:%d\n",ra);
    fprintf(fptr,"Nota do 1 semestre:%d\n",a1.disciplinaNotas[0]);
    fprintf(fptr,"Nota do 2 semestre:%d\n",a1.disciplinaNotas[1]);
    fprintf(fptr,"Media:%lf\n",calculoMedia(a1));
    fprintf(fptr,"situacao:");
    if(determinarAprovacao(a1) == 1)
        fprintf(fptr,"aprovado");
    else
        fprintf(fptr, "reprovado");
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
        fprintf(fptr,"RA:%d\n",i);
        fprintf(fptr,"Nota do 1 semestre:%d\n",listaAlunos[i].disciplinaNotas[0]);
        fprintf(fptr,"Nota do 2 semestre:%d\n",listaAlunos[i].disciplinaNotas[1]);
        fprintf(fptr,"Media:%lf\n",calculoMedia(listaAlunos[i]));
        fprintf(fptr,"situacao:");
        if(determinarAprovacao(listaAlunos[i]) == 1)
            fprintf(fptr,"aprovado");
        else
            fprintf(fptr, "reprovado");
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
