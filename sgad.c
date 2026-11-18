#include "dependencias.h"
#include <string.h>
#include "aluno.h"
#include "disciplina.h"

#define TAMANHO_LINHA 256

int linhaEmBranco(const char* l){ return l[strspn(l, " \t\r\n")] == '\0'; }

aluno* buscarAlunoPorRa(aluno* x, int ra){
    while(x && x->ra != ra) x = x->ptrProximoAluno;
    return x;
}

disciplina* buscarDisciplinaPorCodigo(disciplina* x, int codigo){
    while(x && x->codigo != codigo) x = x->ptrProximaDisciplina;
    return x;
}

int imprimirAluno(aluno a1, int ra, FILE *fptr){
    fprintf(fptr, "RA:%d\n", ra);
    //TO DO: adicionar disciplinas (base antiga, a adaptar)
    /* for(int i = 0; i < a1.numDisciplinasCursadas; i++){
        fprintf(fptr, "Codigo da disciplina:%d", disciplinasCursadas);
        fprintf(fptr, "Nota do 1 semestre:%d\n", a1.disciplinaNotas[0]);
        fprintf(fptr, "Nota do 2 semestre:%d\n", a1.disciplinaNotas[1]);
        fprintf(fptr, "Media:%lf\n", calculoMedia(a1));
        fprintf(fptr, "situacao:%s", determinarAprovacao(a1) == 1 ? "aprovado" : "reprovado");
    } */
    return 0;
}

int boletimIndividual(aluno* primeiroAluno, int ra){
    if(!primeiroAluno){ fprintf(stderr, "Aviso: nao ha alunos cadastrados para gerar o boletim.\n"); return -1; }
    aluno* x = buscarAlunoPorRa(primeiroAluno, ra);
    if(!x){ fprintf(stderr, "Aviso: aluno com RA %d nao encontrado.\n", ra); return -1; }
    FILE *fptr = fopen("binarios/boletimIndividual.txt", "w");
    if(!fptr){ fprintf(stderr, "Aviso: nao foi possivel criar binarios/boletimIndividual.txt (a pasta binarios existe?).\n"); return 1; }
    imprimirAluno(*x, x->ra, fptr);
    fclose(fptr);
    return 0;
}

void gerarListaAlunos(aluno* primeiroAluno){
    FILE *fptr = fopen("binarios/listaAlunos.txt", "w");
    if(!fptr){ fprintf(stderr, "Aviso: nao foi possivel criar binarios/listaAlunos.txt (a pasta binarios existe?).\n"); return; }
    if(!primeiroAluno) fprintf(stderr, "Aviso: nao ha alunos cadastrados.\n");
    for(aluno* x = primeiroAluno; x; x = x->ptrProximoAluno){ //nao esquecer de avancar x (ja travou o PC com +100mb)
        imprimirAluno(*x, x->ra, fptr);
        fprintf(fptr, "\n\n");
    }
    fclose(fptr);
}

void gerarListaDisciplinas(disciplina* primeiraDisciplina){
    FILE *fptr = fopen("binarios/listaDisciplinas.txt", "w");
    if(!fptr){ fprintf(stderr, "Aviso: nao foi possivel criar binarios/listaDisciplinas.txt (a pasta binarios existe?).\n"); return; }
    if(!primeiraDisciplina) fprintf(stderr, "Aviso: nao ha disciplinas cadastradas.\n");
    for(disciplina* x = primeiraDisciplina; x; x = x->ptrProximaDisciplina)
        fprintf(fptr, "Codigo da disciplina:%d\n", x->codigo);
    fclose(fptr);
}

/* Le binarios/listaAlunos.txt ("RA:<numero>") e insere na lista. *primeiroAluno e NULL se vazia. */
int carregarListaAlunos(aluno** primeiroAluno){
    char linha[TAMANHO_LINHA];
    int numLinha = 0, carregados = 0, ra;
    if(!primeiroAluno){ fprintf(stderr, "Aviso: ponteiro invalido ao carregar alunos.\n"); return -1; }
    FILE *fptr = fopen("binarios/listaAlunos.txt", "r");
    if(!fptr){ fprintf(stderr, "Aviso: nao foi possivel abrir binarios/listaAlunos.txt (gere o arquivo pela opcao 4).\n"); return -1; }
    while(fgets(linha, sizeof(linha), fptr)){
        numLinha++;
        if(sscanf(linha, "RA:%d", &ra) != 1){
            if(!linhaEmBranco(linha)) fprintf(stderr, "Aviso: linha %d de listaAlunos.txt ignorada (formato inesperado).\n", numLinha);
            continue;
        }
        if(buscarAlunoPorRa(*primeiroAluno, ra)){
            fprintf(stderr, "Aviso: RA %d repetido (linha %d), ignorado.\n", ra, numLinha);
            continue;
        }
        aluno* novoAluno = calloc(1, sizeof(aluno));
        if(!novoAluno){ fprintf(stderr, "Aviso: memoria insuficiente, carregamento interrompido na linha %d.\n", numLinha); break; }
        novoAluno->ra = ra;
        if(!*primeiroAluno) *primeiroAluno = novoAluno;
        else inserirAluno(*primeiroAluno, novoAluno);
        carregados++;
    }
    fclose(fptr);
    if(!carregados) fprintf(stderr, "Aviso: nenhum aluno valido encontrado em listaAlunos.txt.\n");
    return carregados;
}

/* Le binarios/listaDisciplinas.txt ("Codigo da disciplina:<numero>") e insere na lista. *primeiraDisciplina e NULL se vazia. */
int carregarListaDisciplinas(disciplina** primeiraDisciplina){
    char linha[TAMANHO_LINHA];
    int numLinha = 0, carregadas = 0, codigo;
    if(!primeiraDisciplina){ fprintf(stderr, "Aviso: ponteiro invalido ao carregar disciplinas.\n"); return -1; }
    FILE *fptr = fopen("binarios/listaDisciplinas.txt", "r");
    if(!fptr){ fprintf(stderr, "Aviso: nao foi possivel abrir binarios/listaDisciplinas.txt (o arquivo existe?).\n"); return -1; }
    while(fgets(linha, sizeof(linha), fptr)){
        numLinha++;
        if(sscanf(linha, "Codigo da disciplina:%d", &codigo) != 1){
            if(!linhaEmBranco(linha)) fprintf(stderr, "Aviso: linha %d de listaDisciplinas.txt ignorada (formato inesperado).\n", numLinha);
            continue;
        }
        if(buscarDisciplinaPorCodigo(*primeiraDisciplina, codigo)){
            fprintf(stderr, "Aviso: disciplina %d repetida (linha %d), ignorada.\n", codigo, numLinha);
            continue;
        }
        disciplina* novaDisciplina = calloc(1, sizeof(disciplina));
        if(!novaDisciplina){ fprintf(stderr, "Aviso: memoria insuficiente, carregamento interrompido na linha %d.\n", numLinha); break; }
        novaDisciplina->codigo = codigo;
        if(!*primeiraDisciplina) *primeiraDisciplina = novaDisciplina;
        else inserirDisciplina(*primeiraDisciplina, novaDisciplina);
        carregadas++;
    }
    fclose(fptr);
    if(!carregadas) fprintf(stderr, "Aviso: nenhuma disciplina valida encontrada em listaDisciplinas.txt.\n");
    return carregadas;
}
