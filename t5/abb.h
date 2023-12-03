#include <stdbool.h>
struct lista{
    char nome[25];
    int matricula;
    int ano;
    struct lista* prox;
}; typedef struct lista Lista;

struct curso{
    char nome[30];
    struct lista* alunos;
}; typedef struct curso Curso;

struct arv {
int cod;
struct arv* esq;
struct arv* dir;
struct curso* curso;
};
typedef struct arv Arv;

Arv* abb_insere(Arv* a, int v);
void abb_imprime(Arv* a);
bool codIndisponivel(Arv* a, int cod);
Arv* achaCod(Arv* arvore, int codCurso);
Lista* insereListaAluno(Arv* arvore, int codCurso, char nomeAluno[], int matricula, int anoIngresso);
Lista* excluiAlunoLista(Arv* arvore, int mat);
Arv* abb_retira (Arv* r, int v);