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
    char seletor[100];
    imprimeReceita(listaReceitas, 0);
    
    printf("Escolha a receita: ");
    scanf("%s", seletor);
    setbuf(stdin, NULL);
    
    Receita* aux;
    aux = listaReceitas;

    char auxNome[200];
    printf("Digite o novo ingrediente: ");
    scanf("%s", auxNome);
    setbuf(stdin, NULL);

    while(aux != NULL) {
        if(strcmp(aux->nome, seletor) == 0) {
            aux->listaIngredientes = adicionarIngrediente(aux->listaIngredientes, auxNome);
            break;  
        } else {
            aux = aux->proxReceita;
        }
    }

    imprimeIngredientes(listaReceitas);     


    return 0;
}