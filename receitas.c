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

    char auxNome[100];
    printf("\nDigite o nome da receita: ");
    scanf("%s", auxNome);
    setbuf(stdin, NULL);
    strcpy(novaReceita->nome, auxNome);

    char favorita;
    printf("Gostaria de marca-la como favorita?[s/n]\n");
    scanf("%c", &favorita);
    setbuf(stdin, NULL);
    if (favorita == 's') {
        novaReceita->favorita = 1;
    } else {
        novaReceita->favorita = 0;
    }

    novaReceita->listaIngredientes = criaListaDeIngredientesVazia();
    int numIngredientes;
    printf("\nDigite o numero de ingredientes: ");
    scanf("%d", &numIngredientes);

    for(int i = 0; i < numIngredientes; i++) {
        char auxNome[200];
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

void imprimeReceita(Receita* listaReceitas, int f) {
    if(listaReceitas == NULL) {
        printf("Lista vazia!\n");
    } else {
        if(f == 1) {
            Receita* aux;
            aux = listaReceitas;

            int c = 0;
            printf("\nReceitas Favoritas:\n");
            while(aux != NULL) {
                if(aux->favorita == 1) {
                    printf("%s\n", aux->nome);
                    c++;
                }
                aux = aux->proxReceita;
            }
            if(c == 0) {
                printf("Lista de favoritas vazia!\n");
            }
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
    
}

void imprimeIngredientes(Receita* listaReceitas) {
    imprimeReceita(listaReceitas, 0);

    char seletor[100];
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


Receita* removeIngrediente(Receita* receita) {
    if(receita == NULL || receita->listaIngredientes == NULL) {
        printf("Lista vazia!\n");
        return receita;
    }
    Ingrediente* atual;
    atual = receita->listaIngredientes;
    printf("Ingredientes:\n");
    while(atual != NULL) {
        printf("%s\n", atual->nome);
        atual = atual->proxIngrediente;
    }
    
    char seletor[200];
    printf("Digite o nome do ingrediente: ");
    scanf("%s", seletor);
    setbuf(stdin, NULL);

    atual = receita->listaIngredientes;
    if(strcmp(atual->nome, seletor) == 0) {
        receita->listaIngredientes = receita->listaIngredientes->proxIngrediente;
        receita->listaIngredientes->antIngrediente = NULL;
        free(atual);
        return receita;
    } else {
        while(atual != NULL) {
            if(strcmp(atual->nome, seletor) == 0) {
                atual->antIngrediente->proxIngrediente = atual->proxIngrediente;
                atual->proxIngrediente->antIngrediente = atual->antIngrediente;
                free(atual);
                return receita; 
            } else {
                atual = atual->proxIngrediente;
            }
        }
    }
    printf("Ingrediente nao encontrado!\n");
    return receita;
    
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

    imprimeReceita(listaReceitas, 0);

    char seletor[100];
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

int modificaFavorita(Receita* listaReceitas, int f) {
    imprimeReceita(listaReceitas, !f);

    char seletor[100];
    printf("Digite o nome da receita que deseja: ");
    scanf("%s", seletor);
    setbuf(stdin, NULL);

    Receita* aux;
    aux = listaReceitas;

    while(aux != NULL) {
        if(strcmp(aux->nome, seletor) == 0) {
            break;
        }
        aux = aux->proxReceita;
    }
    if(aux == NULL) {
        printf("Receita nao encontrada!\n");
        return -1;
    }

    aux->favorita = f;

    return 0;
}

