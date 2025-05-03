#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "receitas.h"

/* Inicializa uma lista vazia de receitas */
Receita* criaListaDeReceitasVazia() {
    return NULL; // incia a lista de receitas
}

/* Inicializa uma lista vazia de ingredientes */
Ingrediente* criaListaDeIngredientesVazia() {
    return NULL; // incia a lista de ingredientes
}

/* Adiciona um novo ingrediente a lista */
Ingrediente* adicionarIngrediente(Ingrediente* listaIngredientes, char auxNome[]) {
    Ingrediente* novoIngrediente;
    novoIngrediente = (Ingrediente *)malloc(sizeof(Ingrediente));
    strcpy(novoIngrediente->nome, auxNome);

    char e;
    printf("Deseja marcar esse ingrediente como essencial?[s/n]: ");
    scanf("%c", &e);

    if(e == 's') {
        novoIngrediente->essencial = 1; // valor 1 representa que o ingrediente eh essencial
    } else if (e == 'n') {
        novoIngrediente->essencial = 0; 
    } else {
        printf("caractere invalido! ingrediente marcado como nao essencial.\n");
        novoIngrediente->essencial = 0; // assume que n eh favorita
    }

    if(listaIngredientes == NULL) { // lista vazia
        novoIngrediente->proxIngrediente = NULL;
        novoIngrediente->antIngrediente = NULL;
    } else {
        novoIngrediente->proxIngrediente = listaIngredientes;
        listaIngredientes->antIngrediente = novoIngrediente;
    }
    return novoIngrediente;
}

/* Adiciona uma nova receita a lista */
Receita* adicionarReceita(Receita* listaReceitas) { // adiciona uma receita
    Receita* novaReceita;
    novaReceita = (Receita *)malloc(sizeof(Receita));

    char auxNome[100];
    printf("\nDigite o nome da receita: ");
    scanf("%s", auxNome);
    setbuf(stdin, NULL);
    strcpy(novaReceita->nome, auxNome);

    char favorita;
    printf("Gostaria de marca-la como favorita?[s/n]: ");
    scanf("%c", &favorita);
    setbuf(stdin, NULL);
    if (favorita == 's') {
        novaReceita->favorita = 1;
    } else if (favorita == 'n') {
        novaReceita->favorita = 0;
    } else {
        printf("\ncaractere invalido! receita marcada como nao essencial.\n");
        novaReceita->favorita = 0;
    }

    novaReceita->listaIngredientes = criaListaDeIngredientesVazia();
    int numIngredientes;
    printf("Digite o numero de ingredientes: ");
    scanf("%d", &numIngredientes);

    for(int i = 0; i < numIngredientes; i++) { // loop para receber todos os ingredientes 
        char auxNome[200];
        printf("\nDigite o nome do ingrediente: ");
        scanf("%s", auxNome);
        setbuf(stdin, NULL);

        novaReceita->listaIngredientes = adicionarIngrediente(novaReceita->listaIngredientes, auxNome); //adiciona um ingrendiente a receita
        printf("Ingrediente adicionado!\n");
    }
    if(listaReceitas == NULL) {
        novaReceita->proxReceita = NULL;
    } else {
        novaReceita->proxReceita = listaReceitas;
    }
    return novaReceita;
}

/* Imprime a lista de receitas (todas ou apenas favoritas) */
void imprimeReceita(Receita* listaReceitas, int f) {
    if(listaReceitas == NULL) {
        printf("Lista vazia. Adicione receitas na lista e tente novamente!\n\n");
    } else {
        if(f == 1) {
            Receita* aux;
            aux = listaReceitas;

            int c = 0;
            printf("\nReceitas Favoritas:\n");
            while(aux != NULL) {
                if(aux->favorita == 1) { //verifica se tem receitas favoritas e impirme 
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
            while(aux != NULL) { //imprime todas as receitas
                printf("%s\n", aux->nome);
                aux = aux->proxReceita;
            }
        
        }
    }
    
}

/* Imprime os ingredientes de uma receita especifica */
void imprimeIngredientes(Receita* listaReceitas) { 
    imprimeReceita(listaReceitas, 0);
    if(listaReceitas != NULL) {
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
                if(auxIngrediente == NULL) { //verifica se a lista apresenta ingredientes
                    printf("Receita sem ingredientes. Adione e tente novamente!\n\n");
                    break;
                }
                printf("Ingredientes:\n");
                while(auxIngrediente != NULL) {
                    printf("%s\n", auxIngrediente->nome); //imprime o ingrediente
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

/* Remove um ingrediente de uma receita */
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
    // Solicita qual ingrediente remover
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
    
/* Imprime apenas os ingredientes essenciais de uma receita */
void imprimeEssenciais(Receita* receita) {
    if(receita == NULL || receita->listaIngredientes == NULL) {
        printf("Lista vazia!\n");
    } else {
        int c = 0;
        Ingrediente* aux;
        aux = receita->listaIngredientes;
        printf("Ingredientes essenciais: ");
        while(aux != NULL) {
            if(aux->essencial) {
                printf("\n%s", aux->nome);
                c++;
            }
            aux = aux->proxIngrediente;
        }
        if(c == 0) {
            printf("\nReceita sem ingredientes essenciais!\n");
        }
    }
}

/* Remove todos os ingredientes de uma receita (função auxiliar) */
void removeIngredientes(Receita* receita) {
    Ingrediente* auxIngrediente;
    while(receita->listaIngredientes != NULL) {
        auxIngrediente = receita->listaIngredientes;
        receita->listaIngredientes = receita->listaIngredientes->proxIngrediente;
        free(auxIngrediente);
    }
}

/* Remove uma receita da lista */
Receita* removeReceita(Receita* listaReceitas) {
    if(listaReceitas == NULL) {
        printf("Lista vazia. Adicione elementos e tente novamente!\n");
        return NULL;
    }

    imprimeReceita(listaReceitas, 0);

    char seletor[100];
    printf("\nDigite o nome da receita que deseja remover: ");
    scanf("%s", seletor);
    setbuf(stdin, NULL);
    // Caso especial: remover o primeiro elemento
    if(strcmp(listaReceitas->nome, seletor) == 0) {
        Receita* aux;
        aux = listaReceitas;
        listaReceitas = listaReceitas->proxReceita;
        free(aux);
        printf("Receita removida!\n");
        return listaReceitas;
    }
    // Procura a receita na lista
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

/* Modifica o status de favorito de uma receita */
int modificaFavorita(Receita* listaReceitas, int f) {
    imprimeReceita(listaReceitas, !f);

    if(listaReceitas == NULL) {
        return -1;
    }
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

/* Modifica o status de essencial de um ingrediente */
int modificaEssencial(Receita* receita, int e) {
    if(receita == NULL || receita->listaIngredientes == NULL) {
        printf("Lista vazia!\n");
        return -1;
    }

    Ingrediente* atual;
    atual = receita->listaIngredientes;
    if(e == 1) {
        printf("Ingredientes:\n");
        while(atual != NULL) {
            printf("%s\n", atual->nome);
            atual = atual->proxIngrediente;
        }
    } else {
        printf("Ingredientes essenciais: \n");
        while(atual != NULL) {
            if(atual->essencial) {
                printf("%s\n", atual->nome); 
            }
            atual = atual->proxIngrediente;
        }
    }
    
    // Solicita qual ingrediente modificar
    char seletor[200];
    printf("Digite o nome do ingrediente que deseja: ");
    scanf("%s", seletor);
    setbuf(stdin, NULL);

    atual = receita->listaIngredientes;
    // Procura o ingrediente
    while(atual != NULL) {
        if(strcmp(atual->nome, seletor) == 0) {
            break;
        }
        atual = atual->proxIngrediente;
    }
    if(atual == NULL) {
        printf("Ingrediente nao encontrado!\n");
        return -1;
    }
    // Modifica o status
    atual->essencial = e;

    return 0;
}

