#include "dependencias.h"
#include "aluno.h"
#include "sgad.h"
void main(){
    int esc = 0;
    aluno* primeiroAluno = malloc(sizeof(aluno));
    int primeiroAlunoCriado = 0;
    disciplina* primeiraDisciplina;
    int primeiraDisciplinaCriada = 0;
    int ra;

    aluno* novoAluno; 
    disciplina* novaDisciplina;
    do{
        printf("Sistema gerenciador de alunos e disciplinas\n");
        printf("\nEscolha:\n1:Adicionar alunos\n2:Adicionar disciplinas\n3:Gerar boletim individual de aluno\n4:Gerar arquivo com todos os alunos\n5:Gerar arquivo com todas as disciplinas\n0:Sair do programa\n");

        scanf("%d", &esc);
        switch(esc){
            case 0:break;
            case 1:
                do{
                    novoAluno = calloc(1, sizeof(aluno));
                    printf("Digite o ra do aluno:\t");
                    scanf("%d", &ra);
                    novoAluno->ra = ra;
                    /*
                    printf("digite a nota dele no 1 semestre:");
                    scanf("%d", &novoAluno.disciplinaNotas[0]);

                    printf("digite a nota dele no 2 semestre:");
                    scanf("%d", &novoAluno.disciplinaNotas[1]);
                    substituir por submenu onde podem ser adicionados novos alunos
                    */
                    if(primeiroAlunoCriado == 0)//TO DO:o adequado seria que a funcao inserirAluno(), realizasse isso, no entanto sera necessario a sua conversao para o uso de primeiroAluno**
                    {
                        primeiroAluno = novoAluno;
                        primeiroAlunoCriado = 1;
                    }    
                    else
                        inserirAluno(primeiroAluno, novoAluno);
                    printf("Aluno inserido com sucesso!\n");

                    printf("Adicionar mais um aluno \n1 Sim \n0 Nao\n");
                    scanf("%d", &esc);
                }while(esc != 0);
                esc = 1;
                break;
            case 2:
                printf("Digite o codigo da disciplina:");
                scanf("%d", &ra);
                novaDisciplina = malloc(sizeof(disciplina));
                novaDisciplina->codigo = ra;
                if(primeiraDisciplinaCriada == 0){
                    primeiraDisciplina = novaDisciplina;
                    primeiraDisciplinaCriada = 1;
                }
                else
                    inserirDisciplina(primeiraDisciplina, novaDisciplina);
                do{
                    printf("Digite o codigo da disciplina pre requisito. Caso queira adicionar nenhuma, digite -1\n");
                    scanf("%d", &ra);
                    if(ra != -1)
                       adicionarPrerequisitos(novaDisciplina,ra);
                }while(ra != -1);
                break;
            case 3:
                printf("digite o ra do aluno:");
                scanf("%d", &ra);
                boletimIndividual(primeiroAluno, ra);
                break;
            case 4:
                gerarListaAlunos(primeiroAluno);
                break;
            case 5:
                //gerarListaDisciplinas(listaDisciplinas,tamanhoListaDisciplinas);
                break;

        }
    }while(esc != 0);
}   