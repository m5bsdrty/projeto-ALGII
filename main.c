#include "dependencias.h"
#include "aluno.h"
#include "sgad.h"
/* Le um inteiro do teclado. Retorna 1 se leu, 0 se a entrada era invalida (descartada) e -1 se a entrada acabou. */
static int lerInteiro(int *valor){
    int resultado = scanf("%d", valor), c;
    if(resultado == 1) return 1;
    if(resultado == EOF) return -1;
    while((c = getchar()) != '\n' && c != EOF);
    return 0;
}
void main(){
    int opcao, ra, maisUm, leitura;
    aluno* primeiroAluno = malloc(sizeof(aluno));
    int primeiroAlunoCriado = 0;
    disciplina* primeiraDisciplina;
    int primeiraDisciplinaCriada = 0;
    aluno* novoAluno;
    disciplina* novaDisciplina;
    while(1){
        printf("Sistema gerenciador de alunos e disciplinas\n");
        printf("\nEscolha:\n1:Adicionar alunos\n2:Adicionar disciplinas\n3:Gerar boletim individual de aluno\n4:Gerar arquivo com todos os alunos\n5:Gerar arquivo com todas as disciplinas\n6:Carregar alunos e disciplinas dos arquivos\n0:Sair do programa\n");
        leitura = lerInteiro(&opcao);
        if(leitura == -1){ printf("Aviso: entrada encerrada inesperadamente. Saindo do programa.\n"); return; }
        if(leitura == 0){ printf("Aviso: entrada invalida, digite apenas numeros.\n"); continue; }
        if(opcao == 0) return;
        else if(opcao == 1){
            maisUm = 1;
            while(maisUm != 0){
                novoAluno = calloc(1, sizeof(aluno));
                if(novoAluno == NULL){
                    printf("Aviso: memoria insuficiente para criar o aluno.\n");
                    maisUm = 0;
                }else{
                    printf("Digite o ra do aluno:\t");
                    if(lerInteiro(&ra) != 1){
                        printf("Aviso: ra invalido, aluno nao inserido.\n");
                        free(novoAluno);
                        maisUm = 0;
                    }else{
                        novoAluno->ra = ra;
                        if(primeiroAlunoCriado == 0){//TO DO:o adequado seria que a funcao inserirAluno(), realizasse isso, no entanto sera necessario a sua conversao para o uso de primeiroAluno**
                            primeiroAluno = novoAluno;
                            primeiroAlunoCriado = 1;
                        }else
                            inserirAluno(primeiroAluno, novoAluno);
                        printf("Aluno inserido com sucesso!\n");
                        printf("Adicionar mais um aluno \n1 Sim \n0 Nao\n");
                        if(lerInteiro(&maisUm) != 1){
                            printf("Aviso: opcao invalida, voltando ao menu.\n");
                            maisUm = 0;
                        }
                    }
                }
            }
        }else if(opcao == 2){
            printf("Digite o codigo da disciplina:");
            if(lerInteiro(&ra) != 1)
                printf("Aviso: codigo invalido, disciplina nao inserida.\n");
            else{
                novaDisciplina = calloc(1, sizeof(disciplina));
                if(novaDisciplina == NULL)
                    printf("Aviso: memoria insuficiente para criar a disciplina.\n");
                else{
                    novaDisciplina->codigo = ra;
                    if(primeiraDisciplinaCriada == 0){
                        primeiraDisciplina = novaDisciplina;
                        primeiraDisciplinaCriada = 1;
                    }else
                        inserirDisciplina(primeiraDisciplina, novaDisciplina);
                    do{
                        printf("Digite o codigo da disciplina pre requisito. Caso queira adicionar nenhuma, digite -1\n");
                        if(lerInteiro(&ra) != 1){
                            printf("Aviso: codigo invalido, encerrando a adicao de pre requisitos.\n");
                            ra = -1;
                        }
                        if(ra != -1)
                            adicionarPrerequisitos(novaDisciplina,ra);
                    }while(ra != -1);
                }
            }
        }else if(opcao == 3){
            if(primeiroAlunoCriado == 0)
                printf("Aviso: nenhum aluno cadastrado ainda. Adicione ou carregue alunos antes.\n");
            else{
                printf("digite o ra do aluno:");
                if(lerInteiro(&ra) != 1)
                    printf("Aviso: ra invalido.\n");
                else
                    boletimIndividual(primeiroAluno, ra);
            }
        }else if(opcao == 4){
            if(primeiroAlunoCriado == 0)
                printf("Aviso: nenhum aluno cadastrado ainda. Adicione ou carregue alunos antes.\n");
            else
                gerarListaAlunos(primeiroAluno);
        }else if(opcao == 5){
            //gerarListaDisciplinas(listaDisciplinas,tamanhoListaDisciplinas);
        }else if(opcao == 6){
            aluno* listaAlunos = primeiroAlunoCriado ? primeiroAluno : NULL;
            disciplina* listaDisciplinas = primeiraDisciplinaCriada ? primeiraDisciplina : NULL;
            int qtdAlunos = carregarListaAlunos(&listaAlunos);
            int qtdDisciplinas = carregarListaDisciplinas(&listaDisciplinas);
            if(listaAlunos != NULL){
                primeiroAluno = listaAlunos;
                primeiroAlunoCriado = 1;
            }
            if(listaDisciplinas != NULL){
                primeiraDisciplina = listaDisciplinas;
                primeiraDisciplinaCriada = 1;
            }
            if(qtdAlunos > 0)
                printf("%d aluno(s) carregado(s).\n", qtdAlunos);
            if(qtdDisciplinas > 0)
                printf("%d disciplina(s) carregada(s).\n", qtdDisciplinas);
        }else
            printf("Aviso: opcao %d invalida.\n", opcao);
    }
}
