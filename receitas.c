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
    }
    
}

void imprimeIngredientes(Receita* listaReceitas) {
    imprimeReceita(listaReceitas);

    char seletor[50];
    printf("\nDigite o nome da receita desejada: ");
    scanf("%s", seletor);
    setbuf(stdin, NULL);

    Receita* aux;
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

void removeIngredientes(Receita* receita) {
    Ingrediente* auxIngrediente;
    while(receita->listaIngredientes != NULL) {
        auxIngrediente = receita->listaIngredientes;
        receita->listaIngredientes = receita->listaIngredientes->proxIngrediente;
        free(auxIngrediente);
    }
}

Receita* removeReceita(Receita* listaReceitas) {
    if(listaReceitas == NULL) {
        printf("Lista vazia!\n");
        return NULL;
    }

    imprimeReceita(listaReceitas);

    char seletor[50];
    printf("\nDigite o nome da receita que deseja remover: ");
    scanf("%s", seletor);
    setbuf(stdin, NULL);

    if(strcmp(listaReceitas->nome, seletor) == 0) {
        Receita* aux;
        aux = listaReceitas;
        listaReceitas = listaReceitas->proxReceita;
        free(aux);
        printf("Receita removida!\n");
        return listaReceitas;
    }

    Receita* aux1;
    Receita* aux2;
    aux1 = listaReceitas;
    aux2 = listaReceitas->proxReceita;

    while(aux2 != NULL) {
        if(strcmp(aux2->nome, seletor) == 0) {
            aux1->proxReceita = aux2->proxReceita;
            removeIngredientes(aux2);
            free(aux2);
            printf("Receita removida!\n");
            return listaReceitas;
        } else {
            aux1 = aux2;
            aux2 = aux2->proxReceita;
        }
    }
    if(aux2 == NULL) {
        printf("Receita nao encontrada!\n");
        return listaReceitas;
    }
}
