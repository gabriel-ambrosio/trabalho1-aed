#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "receitas.h"

int main() {
    Receita* listaReceitas;         // Ponteiro para a lista de receitas
    listaReceitas = criaListaDeReceitasVazia(); // Inicializa lista vazia
    int menu = 1;                   // Variavel para controle do menu
    int c = 0;                      // Contador auxiliar
    char auxNome[100];              // Buffer para nomes de receitas
    char nomeIngrediente[200];      // Buffer para nomes de ingredientes
    char medidaIngrediente[200];    // buffer para a quantidade de ingredientes
    Receita* auxReceita;            // Ponteiro auxiliar para navegar nas receitas


    while(menu) {
        printf("\n\n-----------------------------------------------");
        printf("\nMENU");
        printf("\n-----------------------------------------------\n\n");

        printf("1.  Adicionar Receita\n2.  Adicionar Ingrediente\n3.  Ver Todas as Receitas\n4.  Ver Receitas Favoritas\n5.  Ver Ingredientes de Uma Receita\n6.  Ver Ingredientes Essenciais de Uma Receita");
        printf("\n7.  Adicionar Receita as Favoritas\n8.  Retirar Receita das Favoritas\n9.  Adicionar Ingrediente aos Essenciais\n10. Retirar Ingrediente dos Essenciais\n11. Remover Receita\n12. Remover Ingrediente\n13. Buscar Ingrediente em Todas as Receitas\n14. Carregar lista de Exemplo\n15. Sair");
        printf("\n\nEscolha sua opcao: ");
        scanf("%d", &menu);

        switch(menu){

            case 1:
                listaReceitas = adicionarReceita(listaReceitas);
                printf("\nReceita adicionada com sucesso!");
                break;

            case 2:
                imprimeReceita(listaReceitas, 0);
                if(listaReceitas == NULL) {
                    break;
                }
                printf("Digite o nome da receita desejada: ");
                scanf(" %[^\n]", auxNome);
                setbuf(stdin, NULL);

                printf("Digite o nome do ingrediente a ser adicionado: ");
                scanf(" %[^\n]", nomeIngrediente);
                setbuf(stdin, NULL);

                printf("Digite a quantidade e medida do ingrediente a ser adicionado: ");
                scanf(" %[^\n]", medidaIngrediente);
                setbuf(stdin, NULL);

                auxReceita = listaReceitas;
                while(auxReceita != NULL) {
                    if(strcmp(auxReceita->nome, auxNome) == 0) {
                        auxReceita->listaIngredientes = adicionarIngrediente(auxReceita->listaIngredientes, nomeIngrediente, medidaIngrediente);
                        c++;
                        break;
                    }
                    auxReceita = auxReceita->proxReceita;
                }

                if(c == 0) {
                    printf("Receita nao encontrada!");
                } else {
                    c = 0;
                }
                break;


            case 3:
                imprimeReceita(listaReceitas, 0);
                break;
            
            case 4:
                imprimeReceita(listaReceitas, 1);
                break;

            case 5:
                imprimeIngredientes(listaReceitas);
                break;

            case 6:
                imprimeReceita(listaReceitas, 0);
                if(listaReceitas == NULL) {
                    break;
                }
                printf("Digite o nome da receita desejada: ");
                scanf(" %[^\n]", auxNome);
                setbuf(stdin, NULL);

                auxReceita = listaReceitas;
                while(auxReceita != NULL) {
                    if(strcmp(auxReceita->nome, auxNome) == 0) {
                        imprimeEssenciais(auxReceita);
                        c++;
                        break;
                    }
                    auxReceita = auxReceita->proxReceita;
                }
                if (c == 0) {
                    printf("\nReceita nao encontrada!");
                } else {
                    c = 0;
                }

                break;

            case 7:
                c = modificaFavorita(listaReceitas, 1);
                if(c == 0) {
                    printf("Receita favoritada com sucesso!");
                }
                break;

            case 8:
                c = modificaFavorita(listaReceitas, 0);
                printf("Receita desfavoritada com sucesso!");

                break;

            case 9:
                imprimeReceita(listaReceitas, 0);
                if(listaReceitas == NULL) {
                    break;
                }
                printf("Digite o nome da receita desejada: ");
                scanf(" %[^\n]", auxNome);
                setbuf(stdin, NULL);

                auxReceita = listaReceitas;
                while(auxReceita != NULL) {
                    if(strcmp(auxReceita->nome, auxNome) == 0) {
                        c = modificaEssencial(auxReceita, 1);
                        break;
                    }
                    auxReceita = auxReceita->proxReceita;
                }
                if(c == 0) {
                    printf("Ingrediente adicionado aos essenciais!\n");
                }
                break;
            
            case 10:
                imprimeReceita(listaReceitas, 0);
                if(listaReceitas == NULL) {
                    break;
                }
                printf("Digite o nome da receita desejada: ");
                scanf(" %[^\n]", auxNome);
                setbuf(stdin, NULL);

                auxReceita = listaReceitas;
                while(auxReceita != NULL) {
                    if(strcmp(auxReceita->nome, auxNome) == 0) {
                        c = modificaEssencial(auxReceita, 0);
                        break;
                    }
                    auxReceita = auxReceita->proxReceita;
                }
                printf("Ingrediente removido dos essenciais!\n");

                break;

            case 11:
                listaReceitas = removeReceita(listaReceitas);
                break;
            
            case 12:
                imprimeReceita(listaReceitas, 0);
                if(listaReceitas == NULL) {
                    break;
                }
                printf("Digite o nome da receita desejada: ");
                scanf(" %[^\n]", auxNome);
                setbuf(stdin, NULL);

                auxReceita = listaReceitas;
                while(auxReceita != NULL) {
                    if(strcmp(auxReceita->nome, auxNome) == 0) {
                        auxReceita = removeIngrediente(auxReceita);
                        break;
                    }
                    auxReceita = auxReceita->proxReceita;
                }
                break;

            case 13:
                c = buscarTodosIngredientes(listaReceitas);
                break;

            case 14:
                listaReceitas = listaExemplo(listaReceitas);
                printf("Lista carregada!\n");
                break;

            case 15:
                printf("Ate mais!");
                menu = 0;
                break;

            default:
                printf("Opcao nao encontrada! Tente novamente!\n\n");
                break;
        }

    }
    

    return 0;
}
