#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "funcoes.h"

int main()
{
    int rows, columns;
    printf("Informe a distribuicao das mesas(linhas e colunas) do restaurante: ");
    scanf(" %d %d", &rows, &columns);

    Prato *pratos = pilha_pratos_cria();
    Mesa **mesas = allocate_matrix(rows, columns);
    Fila *filaClientes = fila_cria();

    int senha_fila = 0;
    
    int menu;
    do
    {
        print_menu();
        scanf(" %d", &menu);
        switch (menu)
        {
        case 1:
            opcao1(&pratos, &mesas, &filaClientes, rows, columns, &senha_fila);
            break;
        case 2:
            opcao2(&pratos, &mesas, &filaClientes, rows, columns);
            break;
        case 3:
            opcao3(&filaClientes);
            break;
        case 5:
            opcao5(&pratos, &mesas, &filaClientes, rows, columns);
            break;
        case 6:
            opcao6(&pratos, &mesas, &filaClientes, rows, columns);
            break;

        default:
            break;
        }

    } while (menu != 0);

    free_fila(filaClientes);
    free_matrix(mesas, rows);
    free_pilha(pratos);
}