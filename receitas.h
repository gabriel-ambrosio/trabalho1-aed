struct ingrediente {
    char nome[200]; // Nome do ingrediente
    struct ingrediente* proxIngrediente; // Ponteiro para o proximo ingrediente
    struct ingrediente* antIngrediente; // Ponteiro para o ingrediente anterior
    int essencial; // Indicar se eh essencial (1) ou não (0)
};

typedef struct ingrediente Ingrediente;

struct receita {
    char nome[100]; // Nome da receita
    Ingrediente* listaIngredientes; // Ponteiro para a lista de ingredientes
    struct receita *proxReceita; // Ponteiro para a proxima receita
    int favorita; // Indicar se eh favorita (1) ou não (0)
};

typedef struct receita Receita; 

Receita* criaListaDeReceitasVazia();
Ingrediente* criaListaDeIngredientesVazia();
Ingrediente* adicionarIngrediente(Ingrediente* listaIngredientes, char auxNome[]);
Receita* adicionarReceita(Receita* listaReceitas);
void imprimeReceita(Receita* listaReceitas, int f);
void imprimeIngredientes(Receita* listaReceitas);
Receita* removeIngrediente(Receita* receita);
void imprimeEssenciais(Receita* receita);
void removeIngredientes(Receita* receita);
Receita* removeReceita(Receita* listaReceitas);
int modificaFavorita(Receita* listaReceitas, int f);
int modificaEssencial(Receita* receita, int e);
