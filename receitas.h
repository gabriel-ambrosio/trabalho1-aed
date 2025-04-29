struct ingrediente {
    char nome[200];
    struct ingrediente* proxIngrediente;
    struct ingrediente* antIngrediente;
};

typedef struct ingrediente Ingrediente;

struct receita {
    char nome[100];
    Ingrediente* listaIngredientes;
    struct receita *proxReceita;
    int favorita;
};

typedef struct receita Receita; 

Receita* criaListaDeReceitasVazia();
Ingrediente* criaListaDeIngredientesVazia();
Ingrediente* adicionarIngrediente(Ingrediente* listaIngredientes, char auxNome[]);
Receita* adidionarReceita(Receita* listaReceitas);
void imprimeReceita(Receita* listaReceitas, int f);
void imprimeIngredientes(Receita* listaReceitas);
Receita* removeIngrediente(Receita* receita);
void removeIngredientes(Receita* receita);
Receita* removeReceita(Receita* listaReceitas);
int modificaFavorita(Receita* listaReceitas, int f);
