#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"

Mesa **allocate_matrix(int rows, int columns)
{
    Mesa **matrix = (Mesa **)malloc(rows * sizeof(Mesa *));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = malloc(columns * sizeof(Mesa));
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[i][j].disponibilidade=true;
            matrix[i][j].pratos=true;
        }
        
    }
    return matrix;
}
Mesa **mesa_insere(Mesa **matriz, int quantidade, int rows, int columns, int *resto)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (quantidade == 0)
            {
                *resto = 0;
                return matriz;
            }
            if (matriz[i][j].disponibilidade == true && matriz[i][j].pratos == true)
            {
                if (quantidade > 3)
                {
                    quantidade -= 4;
                    matriz[i][j].pessoas = 4;
                }
                else
                {
                    matriz[i][j].pessoas = quantidade;
                    quantidade = 0;
                }
                matriz[i][j].comanda = (i * columns) + j + 1;
                matriz[i][j].disponibilidade = false;
            }
        }
    }
    *resto = quantidade;
    return matriz;
}
void free_matrix(Mesa **matrix, int rows)
{
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


Prato* pilha_pratos_cria(void)
{
    return NULL;
}
Prato* prato_insere(Prato* l)
{
    Prato* novo = (Prato*)malloc(sizeof(Prato));
    novo->prox = l;
    return novo;
}
int lst_vazia(Prato *l)
{
    return (l==NULL);
} 
Prato *prato_retira(Prato *l)
{
    if (lst_vazia(l))
    {
        printf("Sem pratos disponiveis\n");
        return l;
    }
    Prato* p;
    p=l->prox;
    free(l);
    return p;
}
int contar_pratos_pilha(Prato* l)
{
    int contador = 0;
    Prato* atual = l;

    while (atual != NULL) {
        contador++;
        atual = atual->prox;
    }

    return contador;
}
void adiciona_pratos_pilha(Prato **p, int quantidade)
{
    for (int i = 0; i < quantidade; i++)
    {
        *p = prato_insere(*p);
    }
}
void adicionar_pratos_mesa(Prato **p)
{
    for (int i = 0; i < 4; i++)
    {
        *p = prato_retira(*p);
    }
}
void verificar_mesas(Mesa **mesas, Prato **pratos, int rows, int columns)
{
    int pratos_pilha = contar_pratos_pilha(*pratos);
    if (pratos_pilha < 4)
    {
        return;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (pratos_pilha > 3)
            {
                if (mesas[i][j].disponibilidade == true)
                {

                    if (mesas[i][j].pratos == false)
                    {
                        adicionar_pratos_mesa(pratos);
                        pratos_pilha -= 4;
                        mesas[i][j].pratos = true;
                        printf("A mesa %d foi arrumada.\n", (i * columns) + j + 1);
                    }
                }
            }
            else
            {
                break;
            }
        }
    }
}
void free_pilha(Prato *l)
{
    while (l != NULL) {
        Prato *temp = l;
        free(temp);
        l = l->prox;
    }
}


Fila *fila_cria(void)
{
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}
void fila_insere(Fila *f, int v, int pswd)
{
    Lista *n = (Lista *)malloc(sizeof(Lista));
    n->senha = pswd;
    n->pessoas = v;        /* armazena informação */
    n->prox = NULL;     /* novo nó passa a ser o último */
    if (f->fim != NULL) /* verifica se lista não estava vazia */
        f->fim->prox = n;
    else /* fila estava vazia */
        f->ini = n;
    f->fim = n; /* fila aponta para novo elemento */
}
int fila_vazia(Fila *f)
{
    return (f->ini == NULL);
}
void fila_retira(Fila *f)
{
    Lista *t;
    //float v;
    if (fila_vazia(f))
    {
        printf("\nFila vazia. Nao ha como remover elementos\n");
        system("pause");
        exit(1);
    } 
    t = f->ini;
    //v = t->senha;
    f->ini = t->prox;
    if (f->ini == NULL) 
        f->fim = NULL;
    free(t);
    //return v;
}
void remove_no(Fila *fila, int pswd)
{
    if (fila->ini == NULL)
    {
        printf("Nao ha ninguem na fila.\n");
        return;
    }

    Lista *anterior = NULL;
    Lista *atual = fila->ini;

    while (atual != NULL)
    {
        if (atual->senha == pswd)
        {
            if (anterior == NULL)
            {
                fila->ini = atual->prox;
            }
            else
            {
                anterior->prox = atual->prox;
            }

            if (atual == fila->fim)
            {
                fila->fim = anterior;
            }

            free(atual);
            return;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("Senha nao encontrada na fila.\n");
}
void free_fila(Fila *fila)
{
    Lista *atual = fila->ini;
    while (atual != NULL) {
        Lista *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    fila->ini = fila->fim = NULL;
}


void disposicao_mesas(Mesa **matriz, int rows, int columns)
{
    int menu;
    printf("1. Consultar uma mesa\n");
    printf("2. Imprimir disposicao de todas as mesas\n");
    scanf(" %d", &menu);
    printf("\n");
    if (menu == 1)
    {
        int mesa;
        printf("Digite o numero de uma mesa de 1 a %d: ", columns * rows);
        scanf(" %d", &mesa);
        int linha = (mesa - 1) / columns, coluna = (mesa - 1) % columns;
        if ((linha >= 0 && linha < rows) && (coluna >= 0 && coluna < columns))
        {
            if (matriz[linha][coluna].pratos == false)
            {
                printf("======\n");
                printf(":Suja:\n");
                printf("======\n");
            }
            else
            {
                if (matriz[linha][coluna].disponibilidade == false)
                {
                    printf("=======\n");
                    printf("Ocup %d\n", matriz[linha][coluna].pessoas);
                    printf("=======\n");
                }
                if (matriz[linha][coluna].disponibilidade == true)
                {
                    printf("======\n");
                    printf(":Disp:\n");
                    printf("======\n");
                }
            }
        }
        else
        {
            printf("Mesa inexistente.\n");
        }
    }
    else if (menu == 2)
    {

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (matriz[i][j].pratos == false)
                {
                    printf(":Suja:\t");
                }
                else
                {
                    if (matriz[i][j].disponibilidade == false)
                    {
                        printf("Ocup %d\t", matriz[i][j].pessoas);
                    }
                    if (matriz[i][j].disponibilidade == true)
                    {
                        printf(":Disp:\t");
                    }
                }
            }
            printf("\n");
        }
    }
    else
    {
        printf("Opcao Inexistente.");
    }
    printf("\n");
}
void disposicao_fila(Fila *fila)
{
    Lista *atual = fila->ini;
    int totalGrupos = 0;
    int totalPessoas = 0;

    while (atual != NULL)
    {
        totalGrupos++;
        totalPessoas += atual->pessoas;
        printf("Grupo %d: %d pessoas\n", atual->senha, atual->pessoas);
        atual = atual->prox;
    }

    printf("\nTotal de grupos: %d\n", totalGrupos);
    printf("Total de pessoas na fila: %d\n", totalPessoas);
}

void print_menu(void)
{
    printf("\t\t==============MENU==============\n\n");
    printf("\t1. Chegar clientes ao restaurante.\n");
    printf("\t2. Finalizar refeicao.\n");
    printf("\t3. Desistir de esperar.\n");
    printf("\t5. Repor pratos.\n");
    printf("\t6. Imprimir pilha de pratos, fila de espera e ocupacao das mesas.\n");
    printf("\t0. Encerrar Programa.\n");
    printf("\nEscolha uma opcao: ");
}
void opcao1(Prato **pratos, Mesa ***mesas, Fila **filaClientes, int rows, int columns, int *senha_fila)
{
    int quantidade, clientes_fila = 0;
    printf("Quantas pessoas integram o grupo: \n");
    scanf("%d", &quantidade);
    if (quantidade > 0)
    {
        *mesas = mesa_insere(*mesas, quantidade, rows, columns, &clientes_fila);
        if (clientes_fila == 0)
        {
            printf("Clientes alocados com sucesso\n");
            int prato = quantidade % 4;
            adiciona_pratos_pilha(pratos, 4 - prato);
            verificar_mesas(*mesas, pratos, rows, columns);
        }
        else
        {
            *senha_fila++;
            printf("Nao ha mesas disponiveis, %d integrantes do grupo foram para fila de espera com senha %d\n", clientes_fila, *senha_fila);
            fila_insere(*filaClientes, clientes_fila, *senha_fila);
            printf("Pessoas no primeiro grupo: %d\n", (*filaClientes)->ini->pessoas);
        }
    }
}
void opcao2(Prato **pratos, Mesa ***mesas, Fila **filaClientes, int rows, int columns)
{
    int comanda;
    printf("Informe a comanda: \n");
    scanf("%d", &comanda);
    if (comanda - 1 < (rows * columns) && comanda - 1 >= 0)
    {
        int linha = (comanda - 1) / columns, coluna = (comanda - 1) % columns;
        if ((*mesas)[linha][coluna].disponibilidade == true)
        {
            printf("Comanda nao esta em uso.\n\n");
        }
        else
        {
            (*mesas)[linha][coluna].disponibilidade = true;
            if (contar_pratos_pilha(*pratos) > 3)
            {
                (*mesas)[linha][coluna].pratos = true;
                adicionar_pratos_mesa(pratos);
                printf("A mesa %d foi arrumada.\n", comanda);
                if (!fila_vazia(*filaClientes))
                {
                    if ((*filaClientes)->ini->pessoas > 3)
                    {
                        printf("4 clientes do grupo com senha %d foram chamados da fila para a mesa %d.\n", (*filaClientes)->ini->senha, comanda);
                        (*filaClientes)->ini->pessoas -= 4;
                        (*mesas)[linha][coluna].pessoas = 4;
                    }
                    else
                    {
                        printf("%d clientes do grupo com senha %d foram chamados da fila para a mesa %d.\n", (*filaClientes)->ini->pessoas, (*filaClientes)->ini->senha, comanda);
                        (*mesas)[linha][coluna].pessoas = (*filaClientes)->ini->pessoas;
                        adiciona_pratos_pilha(pratos, 4 - (*filaClientes)->ini->pessoas);
                        fila_retira(*filaClientes);
                    }
                    (*mesas)[linha][coluna].disponibilidade = false;
                }
            }
            else
            {
                printf("Pratos insuficientes para arrumar a mesa.\n\n");
                (*mesas)[linha][coluna].pratos = false;
            }
        }
    }
    else
    {
        printf("Comanda inexistente.\n");
    }
}
void opcao3(Fila **filaClientes)
{
    int pswd;
    printf("Digite a sua senha: \n");
    scanf("%d", &pswd);
    remove_no(*filaClientes, pswd);
}
void opcao5(Prato **pratos, Mesa ***mesas, Fila **filaClientes, int rows, int columns)
{
    int numero_pratos, pratos_pilha;
    printf("Quantos pratos voce deseja alocar na pilha: \n");
    scanf("%d", &numero_pratos);
    adiciona_pratos_pilha(pratos, numero_pratos);
    pratos_pilha = contar_pratos_pilha(*pratos);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (pratos_pilha > 3)
            {
                if ((*mesas)[i][j].disponibilidade == true)
                {
                    if ((*mesas)[i][j].pratos == false)
                    {
                        adicionar_pratos_mesa(pratos);
                        pratos_pilha -= 4;
                        (*mesas)[i][j].pratos = true;
                        printf("A mesa %d foi arrumada.\n", (i * columns) + j + 1);
                        if (!fila_vazia(*filaClientes))
                        {

                            if ((*filaClientes)->ini->pessoas > 3)
                            {
                                (*filaClientes)->ini->pessoas -= 4;
                                (*mesas)[i][j].pessoas = 4;
                                printf("4 clientes do grupo com senha %d foram chamados da fila para a mesa %d devido a disponibilidade de pratos.\n", (*filaClientes)->ini->senha, (i * columns) + j + 1);
                            }
                            else
                            {
                                (*mesas)[i][j].pessoas = (*filaClientes)->ini->pessoas;
                                printf("%d clientes do grupo com senha %d foram chamados da fila para a mesa %d devido a disponibilidade de pratos.\n", (*filaClientes)->ini->pessoas, (*filaClientes)->ini->senha, (i * columns) + j + 1);
                                adiciona_pratos_pilha(pratos, 4 - (*filaClientes)->ini->pessoas);
                                fila_retira(*filaClientes);
                            }
                            (*mesas)[i][j].disponibilidade = false;
                        }
                    }
                }
            }
            else
            {
                break;
            }
        }
    }
}
void opcao6(Prato **pratos, Mesa ***mesas, Fila **filaClientes, int rows, int columns)
{
    int menu;
    do
    {
        printf("\t\t==============MENU==============\n\n");
        printf("\t1. Ocupacao das mesas.\n");
        printf("\t2. Fila de Espera.\n");
        printf("\t3. Pratos na Pilha.\n");
        printf("\t0. Volta ao menu principal.\n");
        printf("\nEscolha uma opcao: ");
        scanf(" %d", &menu);
        switch (menu)
        {
        case 1:
            disposicao_mesas(*mesas, rows, columns);
            break;
        case 2:
            disposicao_fila(*filaClientes);
            break;
        case 3:
            printf("Tem %d pratos na pilha\n", contar_pratos_pilha(*pratos));
            break;
        case 0:
            break;
        default:
            printf("Opcao Inexsitente\n");
            break;
        }
    } while (menu != 0);
}