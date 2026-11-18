#include "dependencias.h"
#include "aluno.h"
#include "disciplina.h"
#include "disciplinaCursada.h"
#include "sgad.h"
/* Le um inteiro do teclado. Retorna 1 se leu, 0 se a entrada era invalida (descartada) e -1 se a entrada acabou. */
int lerInteiro(int* valor){
    int resultado = scanf("%d", valor), c;
    if(resultado == 1) return 1;
    if(resultado == EOF) return -1;
    while((c = getchar()) != '\n' && c != EOF);
    return 0;
}
/* Le um double do teclado. Retorna 1 se leu, 0 se a entrada era invalida (descartada) e -1 se a entrada acabou. */
double lerDouble(double *valor){
    double resultado = scanf("%lf", valor), c;
    if(resultado == 1) return 1;
    if(resultado == EOF) return -1;
    while((c = getchar()) != '\n' && c != EOF);
    return 0;
}

void main(){
    int opcao, ra, maisUm, leitura = 1;
    aluno* primeiroAluno = malloc(sizeof(aluno));
    int primeiroAlunoCriado = 0;
    aluno* novoAluno;

    disciplinaCursada* novaDisciplinaCursada;

    disciplina* primeiraDisciplina;
    int primeiraDisciplinaCriada = 0;
    disciplina* novaDisciplina;

    aluno* alunoUsado;
    disciplinaCursada* disciplinaEditada;
    disciplina* disciplinaUsada;

    while(leitura != 0){
        printf("Sistema gerenciador de alunos e disciplinas\n");
        printf("\nEscolha:\n1:Adicionar alunos\n2:Editar disciplinas de aluno\n3:Deletar aluno e suas disciplinas cursadas\n4:Adicionar disciplinas\n5: Deletar disciplinas\n6:Editar disciplinas pre-requisito\n7:Gerar arquivo com todos os alunos\n8:Gerar arquivo com todas as disciplinas\n9:Gerar boletim individual de aluno\n10:Carregar alunos e disciplinas dos arquivos\n0:Sair do programa\n");
        leitura = lerInteiro(&opcao);
        if(leitura == -1){ printf("Aviso: entrada encerrada inesperadamente. Saindo do programa.\n"); return; }
        if(leitura == 0){ printf("Aviso: entrada invalida, digite apenas numeros.\n"); continue; }
        switch(opcao){
            case 0:return;
            case 1:
                maisUm = 1;
                while(maisUm != 0){
                    novoAluno = calloc(1, sizeof(aluno));
                    if(novoAluno == NULL){
                        printf("Aviso: memoria insuficiente para criar o aluno.\n");
                        break;
                    }
                    printf("Digite o ra do aluno:\t");
                    if(lerInteiro(&ra) != 1 || buscarAlunoPorRa(primeiroAluno,ra)){
                        printf("Aviso: ra invalido ou ja existe, novo aluno nao inserido.\n");
                        free(novoAluno);
                        break;
                    }
                    novoAluno->ra = ra;
                    if(primeiroAlunoCriado == 0){//TO DO:o adequado seria que a funcao inserirAluno(), realizasse isso, no entanto sera necessario a sua conversao para o uso de primeiroAluno**
                        primeiroAluno = novoAluno;
                        primeiroAlunoCriado = 1;
                    }else
                        inserirAluno(primeiroAluno, novoAluno);
                    printf("Aluno inserido com sucesso!\n");


                    printf("Adicionar disciplinas para este aluno \n1 Sim\n0 Nao\n");
                    while(lerInteiro(&opcao) == 1 && opcao == 1){
                        disciplinaCursada* novaDisciplinaCursada = calloc(1,sizeof(disciplinaCursada));
                        if(novaDisciplinaCursada == NULL){
                            printf("Aviso: memoria insuficiente para criar disciplina.\n");
                            break;
                        }
                        printf("Digite o codigo da disciplina\n");
                        if(lerInteiro(&ra) != 1 || buscarDisciplinaCursadaPorCodigo(novoAluno->ptrPrimeiraDisciplina, ra)){
                            printf("Valor inserido invalido ou ja existe uma disciplina cursada com este codigo");
                            break;
                        }
                        novaDisciplinaCursada->codigo = ra;
                        while(1){
                            printf("Digite um valor valido para a primeira nota\n");
                            if(!lerDouble(&novaDisciplinaCursada->nota[0])){
                                printf("valor invalido inserido");
                                continue;
                            }
                            printf("Digite um valor valido para a segunda nota\n");
                            if(!lerDouble(&novaDisciplinaCursada->nota[1])){
                                printf("valor invalido inserido");
                                continue;
                            }
                            break;
                        }

                        if(!novoAluno->primeiraDisciplinaCursadaCriada){
                            novoAluno->ptrPrimeiraDisciplina = novaDisciplinaCursada;
                            novoAluno->primeiraDisciplinaCursadaCriada = 1;
                        }else{
                            inserirDisciplinaCursada(novoAluno->ptrPrimeiraDisciplina, novaDisciplinaCursada);
                        }
                        printf("\nAdicionar mais disciplinas para este aluno \n1 Sim\n0 Nao\n");
                        }
                        printf("\nAdicionar mais um aluno \n1 Sim \n0 Nao\n");
                        if(lerInteiro(&maisUm) != 1){
                            printf("Aviso: opcao invalida, voltando ao menu.\n");
                            maisUm = 0;
                        }
                }
                break;
            case 2:
                printf("\nO que voce deseja fazer\n1:Adicionar disciplina cursada a aluno\n2:Editar disciplina cursada existente\n3:Deletar disciplina cursada\n");
                if(lerInteiro(&opcao) != 1){
                    printf("\n Opcao invalida");
                    break;
                }
                switch(opcao){
                    case 1:
                            printf("Digite o RA do aluno:\n");
                            while(lerInteiro(&opcao) != 1)
                                printf("\nValor invalido inserido\n");
                            alunoUsado = buscarAlunoPorRa(primeiroAluno, opcao);
                            if(!alunoUsado){
                                printf("Este aluno nao existe");
                                break;
                            }
                            printf("\nAluno encontrado\n");
                            disciplinaCursada* novaDisciplinaCursada = calloc(1,sizeof(disciplinaCursada));
                            if(novaDisciplinaCursada == NULL){
                                printf("Aviso: memoria insuficiente para criar disciplina.\n");
                                break;
                            }
                            printf("Digite o codigo da disciplina\n");
                            if(lerInteiro(&ra) != 1){
                                printf("Valor inserido invalido");
                                break;
                            }
                            novaDisciplinaCursada = buscarDisciplinaCursadaPorCodigo(alunoUsado->ptrPrimeiraDisciplina, ra);
                            if(novaDisciplinaCursada){
                                printf("Esta disciplina ja existe\n");
                                break;
                            }
                            do{
                                printf("\nDigite um valor valido para a primeira nota\n");
                            }while(lerDouble(&novaDisciplinaCursada->nota[0]) != 1);
                            
                            do{
                                printf("\nDigite um valor valido para a segunda nota\n");
                            }while(lerDouble(&novaDisciplinaCursada->nota[1]) != 1);
                            if(!alunoUsado->primeiraDisciplinaCursadaCriada){
                                    alunoUsado->ptrPrimeiraDisciplina = novaDisciplinaCursada;
                                    alunoUsado->primeiraDisciplinaCursadaCriada = 1;
                                }else{
                                    inserirDisciplinaCursada(alunoUsado->ptrPrimeiraDisciplina, novaDisciplinaCursada);
                                }
                        break;
                    case 2:
                            printf("Digite o RA do aluno\n");
                            if(lerInteiro(&opcao) != 1){
                                printf("\nValor invalido inserido");
                                break;
                            }
                            alunoUsado = buscarAlunoPorRa(primeiroAluno,opcao);
                            if(!alunoUsado){
                                printf("Aluno nao existe");
                                break;
                            }
                            printf("Digite o codigo da disciplina\n");
                            if(lerInteiro(&opcao) != 1){
                                printf("\nValor invalido");
                                break;
                            }
                            disciplinaEditada = buscarDisciplinaCursadaPorCodigo(alunoUsado->ptrPrimeiraDisciplina, opcao);
                            if(disciplinaEditada == NULL){
                                printf("Disciplina nao esta sendo cursada por aluno\n");
                                break;
                            }
                            printf("Nota 1:%lf\nNota 2:%lf\n",disciplinaEditada->nota[0],disciplinaEditada->nota[1]);
                            do{
                                printf("\nDigite um valor valido para a primeira nota");
                            }while(lerDouble(&disciplinaEditada->nota[0]) != 1);
                            
                            do{
                                printf("\nDigite um valor valido para a segunda nota");
                            }while(lerDouble(&disciplinaEditada->nota[1]) != 1);
                        break;
                    case 3:
                        printf("Digite o RA do aluno\n");
                        if(lerInteiro(&opcao) != 1){
                            printf("\nValor invalido inserido");
                            break;
                        }
                        alunoUsado = buscarAlunoPorRa(primeiroAluno,opcao);
                        if(!alunoUsado){
                            printf("Aluno nao existe");
                            break;
                        }
                        printf("Digite o codigo da disciplina\n");
                        disciplinaEditada = buscarDisciplinaCursadaPorCodigo(alunoUsado->ptrPrimeiraDisciplina,ra);
                        if(lerInteiro(&ra) != 1 || !disciplinaEditada){
                            printf("\nValor invalido inserido ou este aluno nao esta cursando esta discipliina");
                            break;
                        }
                        if(!disciplinaEditada->ptrProximaDisciplina)
                            alunoUsado->primeiraDisciplinaCursadaCriada = 0;
                        deletarDisciplinaEspecifica(disciplinaEditada);
                        break;
                }
                break;

            
            case 3:
                printf("Digite o RA do aluno\n");
                if(lerInteiro(&opcao) != 1){
                    printf("\nValor invalido inserido");
                    break;
                }

                deletarAluno(primeiroAluno,ra);
                if(!primeiroAluno)
                    primeiroAlunoCriado = 0;
                break;
            case 4:       
                printf("Digite o codigo da disciplina:");
                if(lerInteiro(&ra) != 1 || buscarDisciplinaPorCodigo(primeiraDisciplina, ra))
                {
                    printf("Aviso: codigo invalido ou disciplina ja existe, disciplina nao inserida.\n");
                    break;
                }
            
                novaDisciplina = calloc(1, sizeof(disciplina));
                if(novaDisciplina == NULL){
                    printf("Aviso: memoria insuficiente para criar a disciplina.\n");
                    break;
                }
                novaDisciplina->codigo = ra;
                if(primeiraDisciplinaCriada == 0){
                    primeiraDisciplina = novaDisciplina;
                    primeiraDisciplinaCriada = 1;
                }else
                    inserirDisciplina(primeiraDisciplina, novaDisciplina);
                do{
                    printf("Digite o codigo da disciplina pre requisito. Caso queira adicionar nenhuma, digite -1\n");
                    if(lerInteiro(&ra) != 1)
                        printf("Aviso: codigo invalido.\n");
                    else{
                        codigoPrerequisitos* novoPreRequisito = calloc(1,sizeof(codigoPrerequisitos));
                        inserirPreRequisito(novaDisciplina->primeiroCodigoPrerequisitos,novoPreRequisito);

                    }
                }while(ra != -1);
                break;
            case 5: 
                printf("Digite o codigo da disciplina:");
                if(lerInteiro(&ra) != 1)
                {
                    printf("Aviso: codigo invalido.\n");
                    break;
                }
                deletarDisciplina(primeiraDisciplina,ra);
                break;
                
            case 6:
                printf("\nO que voce deseja fazer\n1:Adicionar disciplina pre-requisito\n2:Deletar disciplina pre requisito\n");
                if(lerInteiro(&opcao) != 1){
                    printf("\n Opcao invalida");
                    break;
                }
                switch(opcao){
                    case 1:
                        printf("Digite o codigo da disciplina:\n");
                        while(lerInteiro(&opcao) != 1){
                            printf("\nValor invalido inserido\n");
                        }
                        disciplinaUsada = buscarDisciplinaPorCodigo(primeiraDisciplina, opcao);
                        if(!disciplinaUsada){
                            printf("Esta disciplina nao existe");
                            break;
                        }
                        printf("\nDisciplina encontrada\n");
                        codigoPrerequisitos* novoPrerequisito = calloc(1,sizeof(codigoPrerequisitos));
                        if(novoPrerequisito == NULL){
                            printf("Aviso: memoria insuficiente para criar pre-requisito.\n");
                            break;
                        }
                        printf("Digite o codigo da disciplina\n");
                        if(lerInteiro(&ra) != 1){
                            printf("Valor inserido invalido");
                            break;
                        }
                        novoPrerequisito = buscarPreRequisitoPorCodigo(disciplinaUsada->primeiroCodigoPrerequisitos, ra);
                        if(novoPrerequisito){
                            printf("Esta disciplina ja existe\n");
                            break;
                        }
                        if(!disciplinaUsada->primeiroPreRequisitoCriado){
                                disciplinaUsada->primeiroCodigoPrerequisitos = novoPrerequisito;
                                disciplinaUsada->primeiroPreRequisitoCriado = 1;
                            }else{
                                inserirPreRequisito(disciplinaUsada->primeiroCodigoPrerequisitos, novoPrerequisito);
                            }
                        break;        
                    case 2:
                        printf("Digite o codigo da disciplina:\n");
                        while(lerInteiro(&opcao) != 1){
                            printf("\nValor invalido inserido\n");
                        }
                        disciplinaUsada = buscarDisciplinaPorCodigo(primeiraDisciplina, opcao);
                        if(!disciplinaUsada){
                            printf("Esta disciplina nao existe");
                            break;
                        }
                        printf("Digite o codigo da disciplina\n");
                        if(lerInteiro(&ra) != 1){
                            printf("Valor inserido invalido");
                            break;
                        }
                        codigoPrerequisitos* deletadoPreRequisito = buscarPreRequisitoPorCodigo(disciplinaUsada->primeiroCodigoPrerequisitos, ra); 
                        if(!deletadoPreRequisito){
                            printf("Esta disciplina nao existe\n");
                            break;
                        }
                        if(!deletadoPreRequisito->ptrProximoCodigoPrerequisitos)
                            disciplinaUsada->primeiroPreRequisitoCriado = 0;
                        deletarPreRequisitoEspecifico(deletadoPreRequisito);
                        break; 
                }
                break;
            case 7:
                if(primeiroAlunoCriado == 0)
                    printf("Aviso: nenhum aluno cadastrado ainda. Adicione ou carregue alunos antes.\n");
                else
                    gerarListaAlunos(primeiroAluno);
                break;
            case 8:
                if(primeiraDisciplinaCriada == 0)
                    printf("Aviso: nenhuma disciplina cadastrada ainda. Adicione ou carregue antes.\n");
                else
                    gerarListaDisciplinas(primeiraDisciplina);
                break;
            case 9:
                if(primeiroAlunoCriado == 0)
                    printf("Aviso: nenhum aluno cadastrado ainda. Adicione ou carregue alunos antes.\n");
                else{
                    printf("digite o ra do aluno:\n");
                if(lerInteiro(&ra) != 1)
                    printf("Aviso: ra invalido.\n");
                else
                    boletimIndividual(primeiroAluno, ra);
                }
            case 10:
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
                break;
        }
    }
}