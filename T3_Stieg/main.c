#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include "listas.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int menu;
    Cliente *c = lst_cliente_cria();
    Veiculo *v = lst_veiculo_cria();
    Locacao *l = lst_locacao_cria();
    do
    {
        printf("======ENTERPRISE RENT A CAR, LIVE A DREAM=======\n");
        printf("1.  Adicionar veiculo\n");
        printf("2.  Listar veiculos\n");
        printf("3.  Adicionar clientes\n");
        printf("4.  Listar clientes\n");
        printf("5.  Realizar locacao\n");
        printf("6.  Devolver veiculo\n");
        printf("7.  Listar locacoes\n");
        printf("9.  Relatorios\n");
        printf("0.  Sair\n");
        printf("Escolha uma opcao: ");
        scanf(" %d", &menu);
        printf("\n");
        switch (menu)
        {
        case 1:
            v = adicionar_veiculo(v);
            break;
        case 2:
            listar_veiculos(v);
            break;
        case 3:
            c = adicionar_cliente(c);
            break;
        case 4:
            listar_clientes(c);
            break;
        case 5:
            l = adicionar_locacao(l, c, v);
            break;
        case 6:
            devolver_veiculo(v);
            break;
        case 7:
            listar_locacoes(l);
            break;
        case 8:
            break;
        case 9:
            relatorios(l, c, v);
            break;
        default:
            break;
        }
        printf("\nPressione enter para continuar...\n\n");
        fflush(stdin);
        getchar();
        getchar();
    } while (menu != 0);
}