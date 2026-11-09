typedef struct aluno{
    int disciplinaNotas[2];
} aluno;

double calculoMedia(aluno a1){
    return (a1.disciplinaNotas[0] + a1.disciplinaNotas[1])/2;
}
int determinarAprovacao(aluno aluno){
    if(calculoMedia(aluno) >= 6)
        return 1;
    else
        return 0;
}
