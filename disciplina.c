#include "dependencias.h"


typedef struct disciplina{
    int codigo;
    int* codigoPrerequisitos;
    int numCodigoPrerequisitos;
} disciplina;
int adicionarPrerequisitos(disciplina* disciplina, int codigoPrerequisitos){
    int* x = realloc(disciplina->codigoPrerequisitos, sizeof(disciplina->codigoPrerequisitos)+sizeof(int));
    if(x == NULL)
        return -1;
    else{
        disciplina->codigoPrerequisitos = x;
        disciplina->numCodigoPrerequisitos++;
        return 0;
    }
}
