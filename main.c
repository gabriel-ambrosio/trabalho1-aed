#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "receitas.h"

int main() {
    Receita* listaReceitas;
    listaReceitas = criaListaDeReceitasVazia();
    listaReceitas = adidionarReceita(listaReceitas);
    listaReceitas = adidionarReceita(listaReceitas);

    //listaReceitas = removeReceita(listaReceitas);
    int teste = modificaFavorita(listaReceitas, 0);
    imprimeReceita(listaReceitas, 1);

    printf("\nlista completa\n");
    imprimeReceita(listaReceitas, 0);
    


    return 0;
}