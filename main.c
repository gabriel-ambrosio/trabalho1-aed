#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "receitas.h"

int main() {
    Receita* listaReceitas;
    listaReceitas = criaListaDeReceitasVazia();
    listaReceitas = adidionarReceita(listaReceitas);
    listaReceitas = adidionarReceita(listaReceitas);

    listaReceitas = removeReceita(listaReceitas);

    imprimeReceita(listaReceitas);

    


    return 0;
}