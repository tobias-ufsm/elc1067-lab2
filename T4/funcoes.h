#define _funcoes_h_
#include <stdbool.h>

#include <stdio.h>

typedef struct Mesa
{
    int comanda;
    bool disponibilidade;
    bool pratos;
    int pessoas;

}Mesa;
Mesa **allocate_matrix(int rows, int columns);
Mesa **mesa_insere(Mesa **matriz, int quantidade, int rows, int columns, int *resto);
void free_matrix(Mesa **matrix, int rows);

typedef struct Prato
{
    struct Prato *prox;
}Prato;
Prato* pilha_pratos_cria(void);
Prato* prato_insere(Prato* l);
int lst_vazia(Prato *l);
Prato* prato_retira(Prato *l);
int contar_pratos_pilha(Prato* l);
void adiciona_pratos_pilha(Prato **p, int quantidade);
void adicionar_pratos_mesa(Prato **p);
void verificar_mesas(Mesa **mesas, Prato **pratos, int rows, int columns);
void free_pilha(Prato *l);



struct lista
{
    int senha;
    int pessoas;
    struct lista *prox;
};
typedef struct lista Lista;
struct fila
{
    Lista *ini;
    Lista *fim;
};
typedef struct fila Fila;
Fila* fila_cria(void);
void fila_insere(Fila *f, int v, int pswd);
int fila_vazia(Fila *f);
void fila_retira(Fila *f);
void remove_no(Fila *fila, int pswd);
void free_fila(Fila *fila);

void disposicao_mesas(Mesa **matriz, int rows, int columns);
void disposicao_fila(Fila *fila);

void print_menu(void);
void opcao1(Prato **pratos, Mesa ***mesas, Fila **filaClientes, int rows, int columns, int *senha_fila);
void opcao2(Prato **pratos, Mesa ***mesas, Fila **filaClientes, int rows, int columns);
void opcao3(Fila **filaClientes);
void opcao5(Prato **pratos, Mesa ***mesas, Fila **filaClientes, int rows, int columns);
void opcao6(Prato **pratos, Mesa ***mesas, Fila **filaClientes, int rows, int columns);