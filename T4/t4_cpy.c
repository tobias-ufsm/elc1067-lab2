#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "funcoes.h"

/*typedef struct Mesa
{
    int comanda;
    bool disponibilidade;
    int pessoas;

} Mesa;

typedef struct Prato
{
    struct Prato *prox;
} Prato;*/
/*
Prato *adiciona_pratos_pilha2(Prato *p, int quantidade)
{
    for (int i = 0; i < quantidade; i++)
    {
        p = prato_insere(p);
    }
    return p;
}
Prato *adicionar_pratos_mesa2(Prato *p)
{
    for (int i = 0; i < 4; i++)
    {
        p = prato_retira(p);
    }
    return p;
}
*/
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

int main()
{
    int rows, columns;
    Prato *pratos = pilha_pratos_cria();
    printf("Informe a distribuicao das mesas(linhas e colunas) do restaurante: ");
    scanf(" %d %d", &rows, &columns);
    Mesa **mesas = allocate_matrix(rows, columns);
    Fila *filaClientes = fila_cria();
    int senha_fila = 0;
    int menu;
    do
    {
        printf("\t\t==============MENU==============\n\n");
        printf("\t1. Chegar clientes ao restaurante.\n");
        printf("\t2. Finalizar refeicao.\n");
        printf("\t3. Desistir de esperar.\n");
        printf("\t5. Repor pratos.\n");
        printf("\t6. Imprimir pilha de pratos, fila de espera e ocupacao das mesas.\n");
        printf("\nEscolha uma opcao: ");
        scanf(" %d", &menu);
        switch (menu)
        {
        case 1:
            int quantidade, clientes_fila = 0;
            printf("Quantas pessoas integram o grupo: \n");
            scanf("%d", &quantidade);
            mesas = mesa_insere(mesas, quantidade, rows, columns, &clientes_fila);
            if (clientes_fila == 0)
            {
                int prato = quantidade % 4;
                adiciona_pratos_pilha(&pratos, prato);
            }
            else
            {
                senha_fila++;
                printf("Nao ha mesas disponiveis, %d integrantes do grupo foram para fila de espera com senha %d\n", clientes_fila, senha_fila);
                fila_insere(filaClientes, clientes_fila, senha_fila);
                printf("Pessoas no primeiro grupo: %d\n", filaClientes->ini->pessoas);
            }
            break;
        case 2:
            int comanda;
            printf("Informe a comanda: \n");
            scanf("%d", &comanda);
            if (comanda - 1 < (rows * columns) && comanda - 1 >= 0)
            {
                int linha = (comanda - 1) / columns, coluna = (comanda - 1) % columns;
                if (mesas[linha][coluna].disponibilidade == true)
                {
                    printf("Comanda nao esta em uso.\n\n");
                }
                else
                {
                    mesas[linha][coluna].disponibilidade = true;
                    if (contar_pratos_pilha(pratos) > 3)
                    {
                        mesas[linha][coluna].pratos = true;
                        adicionar_pratos_mesa(&pratos);
                        printf("A mesa %d foi arrumada.\n", comanda);
                        if (!fila_vazia(filaClientes))
                        {
                            if (filaClientes->ini->pessoas > 3)
                            {
                                printf("4 clientes do grupo com senha %d foram chamados da fila para a mesa %d.\n", filaClientes->ini->senha, comanda);
                                filaClientes->ini->pessoas -= 4;
                                mesas[linha][coluna].pessoas = filaClientes->ini->pessoas;
                            }
                            else
                            {
                                printf("%d clientes do grupo com senha %d foram chamados da fila para a mesa %d.\n", filaClientes->ini->pessoas, filaClientes->ini->senha, comanda);
                                mesas[linha][coluna].pessoas = filaClientes->ini->pessoas;
                                adiciona_pratos_pilha(&pratos, 4 - filaClientes->ini->pessoas);
                                fila_retira(filaClientes);
                            }
                            mesas[linha][coluna].disponibilidade = false;
                        }
                    }
                    else
                    {
                        printf("Pratos insuficientes para arrumar a mesa.\n\n");
                        mesas[linha][coluna].pratos = false;
                    }
                }
            }
            else
            {
                printf("Comanda inexistente.\n");
            }

            break;
        case 3:
            int pswd;
            printf("Digite a sua senha: \n");
            scanf("%d", &pswd);
            remove_no(filaClientes, pswd);
            break;
        case 5:
            int numero_pratos, pratos_pilha;
            printf("Quantos pratos você deseja alocar na pilha: \n");
            scanf("%d", &numero_pratos);
            adiciona_pratos_pilha(&pratos, numero_pratos);
            pratos_pilha = contar_pratos_pilha(pratos);
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < columns; j++)
                {
                    if (pratos_pilha > 3)
                    {
                        if (mesas[i][j].disponibilidade == true)
                        {
                            printf("==0==\n");
                            if (mesas[i][j].pratos == false)
                            {
                                printf("==1==\n");
                                adicionar_pratos_mesa(&pratos);
                                pratos_pilha -= 4;
                                mesas[i][j].pratos = true;
                                printf("A mesa %d foi arrumada.\n", comanda);
                                if (!fila_vazia(filaClientes))
                                {
                                    printf("==2==\n");
                                    
                                    if (filaClientes->ini->pessoas > 3)
                                    {
                                        filaClientes->ini->pessoas -= 4;
                                        mesas[i][j].pessoas = filaClientes->ini->pessoas;
                                        printf("4 clientes do grupo com senha %d foram chamados da fila para a mesa %d devido a disponibilidade de pratos.\n", filaClientes->ini->senha, (i*columns)+j+1);
                                    }
                                    else
                                    {
                                        mesas[i][j].pessoas = filaClientes->ini->pessoas;
                                        printf("%d clientes do grupo com senha %d foram chamados da fila para a mesa %d devido a disponibilidade de pratos.\n", filaClientes->ini->pessoas, filaClientes->ini->senha, (i*columns)+j+1);
                                        adiciona_pratos_pilha(&pratos, 4 - filaClientes->ini->pessoas);
                                        fila_retira(filaClientes);
                                    }
                                    mesas[i][j].disponibilidade = false;
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

            break;
        case 6:

            break;
        default:
            break;
        }
    } while (menu != 0);
}