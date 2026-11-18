#include "dependencias.h"
#include <string.h>
#include "aluno.h"
#include "disciplina.h"

#define TAMANHO_LINHA 256

int linhaEmBranco(const char* l){ return l[strspn(l, " \t\r\n")] == '\0'; }





int imprimirAluno(aluno a1, int ra, FILE *fptr){
    fprintf(fptr, "RA:%d\n", ra);
    for(disciplinaCursada* d = a1.ptrPrimeiraDisciplina; d; d = d->ptrProximaDisciplina){
        fprintf(fptr, "Codigo da disciplina:%d\n", d->codigo);
        fprintf(fptr, "Nota do 1 semestre:%lf\n", d->nota[0]);
        fprintf(fptr, "Nota do 2 semestre:%lf\n", d->nota[1]);
    }
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
    for(disciplina* x = primeiraDisciplina; x; x = x->ptrProximaDisciplina){
        fprintf(fptr, "Codigo da disciplina:%d\n", x->codigo);
        for(codigoPrerequisitos* p = x->primeiroCodigoPrerequisitos; p; p = p->ptrProximoCodigoPrerequisitos)
            fprintf(fptr, "Codigo do pre-requisito:%d\n", p->codigo);
    }
    fclose(fptr);
}

/* Le binarios/listaAlunos.txt ("RA:<numero>", seguido das disciplinas cursadas e notas do aluno) e insere na lista. *primeiroAluno e NULL se vazia. */
int carregarListaAlunos(aluno** primeiroAluno){
    char linha[TAMANHO_LINHA];
    int numLinha = 0, carregados = 0, ra, codigo;
    double nota;
    aluno* atual = NULL;
    disciplinaCursada* atualDisc = NULL;
    if(!primeiroAluno){ fprintf(stderr, "Aviso: ponteiro invalido ao carregar alunos.\n"); return -1; }
    FILE *fptr = fopen("binarios/listaAlunos.txt", "r");
    if(!fptr){ fprintf(stderr, "Aviso: nao foi possivel abrir binarios/listaAlunos.txt (gere o arquivo pela opcao 4).\n"); return -1; }
    while(fgets(linha, sizeof(linha), fptr)){
        numLinha++;
        if(sscanf(linha, "RA:%d", &ra) != 1){
            if(sscanf(linha, "Codigo da disciplina:%d", &codigo) == 1){
                atualDisc = NULL;
                if(!atual){ fprintf(stderr, "Aviso: linha %d de listaAlunos.txt ignorada (disciplina sem aluno valido).\n", numLinha); continue; }
                if(buscarDisciplinaCursadaPorCodigo(atual->ptrPrimeiraDisciplina, codigo)){
                    fprintf(stderr, "Aviso: disciplina %d repetida para o RA %d (linha %d), ignorada.\n", codigo, atual->ra, numLinha);
                    continue;
                }
                disciplinaCursada* novaDisciplinaCursada = calloc(1, sizeof(disciplinaCursada));
                if(!novaDisciplinaCursada){ fprintf(stderr, "Aviso: memoria insuficiente, carregamento interrompido na linha %d.\n", numLinha); break; }
                novaDisciplinaCursada->codigo = codigo;
                if(!atual->primeiraDisciplinaCursadaCriada){
                    atual->ptrPrimeiraDisciplina = novaDisciplinaCursada;
                    atual->primeiraDisciplinaCursadaCriada = 1;
                }else
                    inserirDisciplinaCursada(atual->ptrPrimeiraDisciplina, novaDisciplinaCursada);
                atualDisc = novaDisciplinaCursada;
            }else if(sscanf(linha, "Nota do 1 semestre:%lf", &nota) == 1){
                if(atualDisc) atualDisc->nota[0] = nota;
                else fprintf(stderr, "Aviso: linha %d de listaAlunos.txt ignorada (nota sem disciplina valida).\n", numLinha);
            }else if(sscanf(linha, "Nota do 2 semestre:%lf", &nota) == 1){
                if(atualDisc) atualDisc->nota[1] = nota;
                else fprintf(stderr, "Aviso: linha %d de listaAlunos.txt ignorada (nota sem disciplina valida).\n", numLinha);
            }else if(!linhaEmBranco(linha))
                fprintf(stderr, "Aviso: linha %d de listaAlunos.txt ignorada (formato inesperado).\n", numLinha);
            continue;
        }
        atual = NULL;
        atualDisc = NULL;
        if(buscarAlunoPorRa(*primeiroAluno, ra)){
            fprintf(stderr, "Aviso: RA %d repetido (linha %d), ignorado.\n", ra, numLinha);
            continue;
        }
        aluno* novoAluno = calloc(1, sizeof(aluno));
        if(!novoAluno){ fprintf(stderr, "Aviso: memoria insuficiente, carregamento interrompido na linha %d.\n", numLinha); break; }
        novoAluno->ra = ra;
        if(!*primeiroAluno) *primeiroAluno = novoAluno;
        else inserirAluno(*primeiroAluno, novoAluno);
        atual = novoAluno;
        carregados++;
    }
    fclose(fptr);
    if(!carregados) fprintf(stderr, "Aviso: nenhum aluno valido encontrado em listaAlunos.txt.\n");
    return carregados;
}

/* Le binarios/listaDisciplinas.txt ("Codigo da disciplina:<numero>", seguido dos "Codigo do pre-requisito:<numero>" dela) e insere na lista. *primeiraDisciplina e NULL se vazia. */
int carregarListaDisciplinas(disciplina** primeiraDisciplina){
    char linha[TAMANHO_LINHA];
    int numLinha = 0, carregadas = 0, codigo;
    disciplina* atual = NULL;
    if(!primeiraDisciplina){ fprintf(stderr, "Aviso: ponteiro invalido ao carregar disciplinas.\n"); return -1; }
    FILE *fptr = fopen("binarios/listaDisciplinas.txt", "r");
    if(!fptr){ fprintf(stderr, "Aviso: nao foi possivel abrir binarios/listaDisciplinas.txt (o arquivo existe?).\n"); return -1; }
    while(fgets(linha, sizeof(linha), fptr)){
        numLinha++;
        if(sscanf(linha, "Codigo da disciplina:%d", &codigo) != 1){
            if(sscanf(linha, "Codigo do pre-requisito:%d", &codigo) == 1){
                if(!atual){ fprintf(stderr, "Aviso: linha %d de listaDisciplinas.txt ignorada (pre-requisito sem disciplina valida).\n", numLinha); continue; }
                if(buscarPreRequisitoPorCodigo(atual->primeiroCodigoPrerequisitos, codigo)){
                    fprintf(stderr, "Aviso: pre-requisito %d repetido para a disciplina %d (linha %d), ignorado.\n", codigo, atual->codigo, numLinha);
                    continue;
                }
                codigoPrerequisitos* novoPreRequisito = calloc(1, sizeof(codigoPrerequisitos));
                if(!novoPreRequisito){ fprintf(stderr, "Aviso: memoria insuficiente, carregamento interrompido na linha %d.\n", numLinha); break; }
                novoPreRequisito->codigo = codigo;
                if(!atual->primeiroPreRequisitoCriado){
                    atual->primeiroCodigoPrerequisitos = novoPreRequisito;
                    atual->primeiroPreRequisitoCriado = 1;
                }else
                    inserirPreRequisito(atual->primeiroCodigoPrerequisitos, novoPreRequisito);
            }else if(!linhaEmBranco(linha))
                fprintf(stderr, "Aviso: linha %d de listaDisciplinas.txt ignorada (formato inesperado).\n", numLinha);
            continue;
        }
        atual = NULL;
        if(buscarDisciplinaPorCodigo(*primeiraDisciplina, codigo)){
            fprintf(stderr, "Aviso: disciplina %d repetida (linha %d), ignorada.\n", codigo, numLinha);
            continue;
        }
        disciplina* novaDisciplina = calloc(1, sizeof(disciplina));
        if(!novaDisciplina){ fprintf(stderr, "Aviso: memoria insuficiente, carregamento interrompido na linha %d.\n", numLinha); break; }
        novaDisciplina->codigo = codigo;
        if(!*primeiraDisciplina) *primeiraDisciplina = novaDisciplina;
        else inserirDisciplina(*primeiraDisciplina, novaDisciplina);
        atual = novaDisciplina;
        carregadas++;
    }
    fclose(fptr);
    if(!carregadas) fprintf(stderr, "Aviso: nenhuma disciplina valida encontrada em listaDisciplinas.txt.\n");
    return carregadas;
}
