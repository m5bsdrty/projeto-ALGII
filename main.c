#include "dependencias.h"
#include "aluno.h"
#include "sgad.h"
void main(){
    int esc = 0;
    aluno primeiroAluno;
    primeiroAluno.ptrProximoAluno = NULL;
    disciplina* listaDisciplinas = NULL;
    int tamanhoListaDisciplinas = 0;

    int ra;
    do{
        printf("Sistema gerenciador de alunos e disciplinas\n");
        printf("\nEscolha:\n1:Adicionar alunos\n2:Adicionar disciplinas\n3:Gerar boletim individual de aluno\n4:Gerar arquivo com todos os alunos\n5:Gerar arquivo com todas as disciplinas\n0:Sair do programa\n");

        scanf("%d", &esc);
        switch(esc){
            case 0:break;
            case 1:
                do{
                    aluno* novoAluno = calloc(1, sizeof(aluno));
                    printf("Digite o ra do aluno");
                    scanf("%d", &ra);
                    novoAluno->ra = ra;
                    /*
                    printf("digite a nota dele no 1 semestre:");
                    scanf("%d", &novoAluno.disciplinaNotas[0]);

                    printf("digite a nota dele no 2 semestre:");
                    scanf("%d", &novoAluno.disciplinaNotas[1]);
                    substituir por submenu onde podem ser adicionados novos alunos
                    */

                    inserirAluno(primeiroAluno, novoAluno);
                    printf("Aluno inserido com sucesso!");

                    printf("Adicionar mais um aluno 0 Sim 1 Nao");
                }while(esc != 1);
                break;
            case 2:
                printf("Digite o codigo da disciplina:");
                scanf("%d", &ra);
                disciplina novaDisciplina;
                novaDisciplina.codigo = ra;
                novaDisciplina.numCodigoPrerequisitos = 0;
                inserirDisciplina(&listaDisciplinas, &tamanhoListaDisciplinas, novaDisciplina);
                do{
                    printf("Digite o codigo da disciplina pre requisito. Caso nao tenha nenhuma, digite -1\n");
                    scanf("%d", &ra);
                    adicionarPrerequisitos(&listaDisciplinas[tamanhoListaDisciplinas-1],ra);
                }while(ra != -1);

                break;
            case 3:
                printf("digite o ra do aluno:");
                scanf("%d", &ra);
                boletimIndividual(primeiroAluno, ra);
                break;
            case 4:
                gerarListaAlunos(listaAlunos,tamanhoListaAlunos);
                break;
            case 5:
                gerarListaDisciplinas(listaDisciplinas,tamanhoListaDisciplinas);
                break;

        }
    }while(esc != 0);
}   