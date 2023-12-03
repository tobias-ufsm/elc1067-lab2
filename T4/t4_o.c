#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "funcoes.h"

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
            if (matriz[i][j].disponibilidade == true)
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
    printf("Informe a distribuicao das mesas(linhas e colunas)\n");
    scanf(" %d %d", &rows, &columns);
    Mesa **mesas = allocate_matrix(rows, columns);
    Fila *filaClientes = fila_cria();
    int senha_fila = 0;
    int menu;
    do
    {
        printf("1. Chegar (grupo de) clientes ao restaurante (implica em ocupar mesa se há disponibilidade ou ir pra fila de espera)\n");
        printf("2. Finalizar refeição/liberar mesa (liberar a mesa, chamar clientes da fila de espera (se houver), e arrumar mesa)\n");
        printf("3. Desistir de esperar (sair da fila de espera)\n");
        printf("5. Repor pratos (adicionar pratos na pilha)\n");
        printf("6. Imprimir pilha de pratos, fila de espera e ocupação das mesas.\n");
        scanf(" %d", &menu);
        switch (menu)
        {
        case 1:
            int quantidade, clientes_fila=0;
            printf("Quantas pessoas integram o grupo: \n");
            scanf("%d", &quantidade);
            mesas = mesa_insere(mesas, quantidade, rows, columns, &clientes_fila);
            if (clientes_fila == 0)
            {
                int prato = quantidade % 4;
                //pratos = adiciona_pratos_pilha(pratos, prato);
                adiciona_pratos_pilha(&pratos, prato);

            }
            else
            {
                senha_fila++;
                printf("Nao ha mesas disponiveis, %d integrantes do grupo foram para fila de espera com senha %d\n", clientes_fila, senha_fila);
                fila_insere(filaClientes, clientes_fila, senha_fila);
            }
            break;
        case 2:
            int comanda;
            printf("Informe a comanda: \n");
            scanf("%d", &comanda);
            int linha = (comanda - 1) / columns, coluna = (comanda - 1) % columns;
            mesas[linha][coluna].disponibilidade = true;
            //pratos = adicionar_pratos_mesa(pratos);
            adicionar_pratos_mesa(&pratos);

            if (!fila_vazia(filaClientes))
            {
                if (filaClientes->ini->pessoas > 4)
                {
                    filaClientes->ini->pessoas -= 4;
                    mesas[linha][coluna].pessoas = filaClientes->ini->pessoas;
                }
                else
                {
                    mesas[linha][coluna].pessoas = filaClientes->ini->pessoas;
                    //pratos = adiciona_pratos_pilha(pratos, 4 - filaClientes->ini->pessoas);
                    adiciona_pratos_pilha(&pratos, 4 - filaClientes->ini->pessoas);
                    fila_retira(filaClientes);
                }
                mesas[linha][coluna].disponibilidade = false;
            }
            break;
        case 3:
            int pswd;
            printf("Digite a sua senha: \n");
            scanf("%d", &pswd);
            remove_no(filaClientes, pswd);
            break;
        case 5:
            int numero_pratos;
            printf("Quantos pratos você deseja alocar na pilha: \n");
            scanf("%d", &numero_pratos);
            //pratos = adiciona_pratos_pilha(pratos, numero_pratos);
            adiciona_pratos_pilha(&pratos, numero_pratos);

            break;
        case 6:

            break;
        default:
            break;
        }
    } while (menu != 0);
}