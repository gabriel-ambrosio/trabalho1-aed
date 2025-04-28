#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "receitas.h"

Receita* criaListaDeReceitasVazia() {
    return NULL;
}

Ingrediente* criaListaDeIngredientesVazia() {
    return NULL;
}

Ingrediente* adicionarIngrediente(Ingrediente* listaIngredientes, char auxNome[]) {
    Ingrediente* novoIngrediente;
    novoIngrediente = (Ingrediente *)malloc(sizeof(Ingrediente));
    strcpy(novoIngrediente->nome, auxNome);

    if(listaIngredientes == NULL) {
        novoIngrediente->proxIngrediente = NULL;
        novoIngrediente->antIngrediente = NULL;
    } else {
        novoIngrediente->proxIngrediente = listaIngredientes;
        listaIngredientes->antIngrediente = novoIngrediente;
    }
    return novoIngrediente;
}

Receita* adidionarReceita(Receita* listaReceitas) {
    Receita* novaReceita;
    novaReceita = (Receita *)malloc(sizeof(Receita));

    char auxNome[50];
    printf("\nDigite o nome da receita: ");
    scanf("%s", auxNome);
    setbuf(stdin, NULL);
    strcpy(novaReceita->nome, auxNome);

    novaReceita->listaIngredientes = criaListaDeIngredientesVazia();
    int numIngredientes;
    printf("\nDigite o numero de ingredientes: ");
    scanf("%d", &numIngredientes);

    for(int i = 0; i < numIngredientes; i++) {
        char auxNome[50];
        printf("\nDigite o nome do ingrediente: ");
        scanf("%s", auxNome);
        setbuf(stdin, NULL);

        novaReceita->listaIngredientes = adicionarIngrediente(novaReceita->listaIngredientes, auxNome);
        printf("Ingrediente adicionado!\n");
    }
    if(listaReceitas == NULL) {
        novaReceita->proxReceita = NULL;
    } else {
        novaReceita->proxReceita = listaReceitas;
    }
    return novaReceita;
}

void imprimeReceita(Receita* listaReceitas) {
    if(listaReceitas == NULL) {
        printf("Lista vazia!\n");
    } else {
        Receita* aux;
        aux = listaReceitas;
        printf("\nReceitas:\n");
        while(aux != NULL) {
            printf("%s\n", aux->nome);
            aux = aux->proxReceita;
        }

        char seletor[50];
        printf("\nDigite o nome da receita desejada: ");
        scanf("%s", seletor);
        setbuf(stdin, NULL);

        aux = listaReceitas;
        while(aux != NULL) {
            if(strcmp(seletor, aux->nome) == 0) {
                printf("\nReceita: %s\n", aux->nome);

                Ingrediente* auxIngrediente;
                auxIngrediente =  aux->listaIngredientes;

                printf("Ingredientes:\n");
                while(auxIngrediente != NULL) {
                    printf("%s\n", auxIngrediente->nome);
                    auxIngrediente = auxIngrediente->proxIngrediente;
                }
                break;
            } else {
                aux = aux->proxReceita;
            }
        }
        if(aux == NULL) {
            printf("Receita nao encontrada!\n");
        }
    }
    
}
