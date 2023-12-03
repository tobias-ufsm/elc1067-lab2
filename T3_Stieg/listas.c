#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include "listas.h"

int daysBetweenDates(struct Date date1, struct Date date2)
{
    int days1 = date1.year * 365 + date1.day;
    int days2 = date2.year * 365 + date2.day;

    // Adicionar dias extras para os anos bissextos
    days1 += date1.year / 4 - date1.year / 100 + date1.year / 400;
    days2 += date2.year / 4 - date2.year / 100 + date2.year / 400;

    // Adicionar dias para os meses
    int monthDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (int i = 1; i < date1.month; i++)
    {
        days1 += monthDays[i];
    }
    for (int i = 1; i < date2.month; i++)
    {
        days2 += monthDays[i];
    }

    // Considerar anos bissextos
    if (date1.month <= 2 && (date1.year % 4 == 0 && (date1.year % 100 != 0 || date1.year % 400 == 0)))
    {
        days1--;
    }
    if (date2.month <= 2 && (date2.year % 4 == 0 && (date2.year % 100 != 0 || date2.year % 400 == 0)))
    {
        days2--;
    }

    // Calcular a diferen�a em dias
    int difference = days2 - days1;
    return difference;
}

Veiculo *lst_veiculo_cria(void)
{
    return NULL;
}
Veiculo *lst_veiculo_insere(Veiculo *l, char placa[], char marca[], char modelo[], int ano, int kilometragem, float diaria)
{
    Veiculo *novo = (Veiculo *)malloc(sizeof(Veiculo));
    strcpy(novo->placa, placa);
    strcpy(novo->marca, marca);
    strcpy(novo->modelo, modelo);
    novo->ano = ano;
    novo->kilometragem = kilometragem;
    novo->diaria = diaria;
    novo->disp = 1;
    novo->prox = l;
    return novo;
}
Veiculo *adicionar_veiculo(Veiculo *l)
{
    char placa[100], marca[100], modelo[100];
    int ano, kilometragem;
    float diaria;
    printf("\tVeiculo\n\n");
    printf("Digite a placa: ");
    scanf("%s", placa);
    printf("Digite a marca: ");
    scanf("%s", marca);
    printf("Digite o modelo: ");
    scanf("%s", modelo);
    printf("Digite o ano de fabricacao: ");
    scanf("%d", &ano);
    printf("Digite a kilometragem: ");
    scanf("%d", &kilometragem);
    printf("Digite o valor da diaria: ");
    scanf("%f", &diaria);
    printf("Veiculo adicionado com sucesso\n");
    return (lst_veiculo_insere(l, placa, marca, modelo, ano, kilometragem, diaria));
}
Veiculo *busca_veiculo(Veiculo *l, char placa[])
{
    Veiculo *p = l;
    for (p = l; p != NULL; p = p->prox)
    {
        if (strcmp(placa, p->placa) == 0)
            return p;
    }
    
    
    
    return p;
}
void listar_veiculos(Veiculo *l)
{
    Veiculo *p = l;
    int cont = 1;
    if (p == NULL)
    {
        printf("Nenhum veiculo listado\n\n");
    }
    else
    {
        printf("Informacoes dos Veiculos:\n\n");
        while (p != NULL)
        {
            printf("Informacoes do Veiculo #%d\n\n", cont);
            cont++;
            printf("Placa: %s\n", p->placa);
            printf("Marca: %s\n", p->marca);
            printf("Modelo: %s\n", p->modelo);
            printf("Ano de Fabricacao: %d\n", p->ano);
            printf("Kilometragem: %d\n", p->kilometragem);
            printf("Valor da Diaria: $%.2f\n", p->diaria);
            if (p->disp == true)
            {
                printf("Veiculo Disponivel\n");
            }
            else
            {
                printf("Veiculo Indisponivel\n");
            }
            printf("\n");
            p = p->prox;
        }
    }
}
void devolver_veiculo(Veiculo *veiculo)
{
    // mudei pra void
    Veiculo *v = veiculo;
    char placa[100];
    int kilometragem;
    printf("Informe a placa do veiculo: ");
    scanf("%s", placa);
    printf("Informe a kilometragem do veiculo: ");
    scanf("%d", &kilometragem);
    // Alterei as duas funcoes de busca, estavam dando seg_fault :(
    v = busca_veiculo(veiculo, placa);
    if (v == NULL)
    {
        printf("veiculo nao encontrado\n");
    }
    else if (v->disp == 1)
    {
        printf("O veiculo j� estava disponivel\n");
    }
    else
    {
        printf("veiculo devolvido com sucesso\n");
        // mudei aq
        v->disp = 1;
        v->kilometragem = kilometragem;
    }
}

Cliente *lst_cliente_cria(void)
{
    return NULL;
}
Cliente *lst_cliente_insere(Cliente *l, int cnh, char nome[], int telefone)
{
    Cliente *novo = (Cliente *)malloc(sizeof(Cliente));
    novo->cnh = cnh;
    strcpy(novo->nome, nome);
    novo->telefone = telefone;
    novo->prox = l;
    return novo;
}
Cliente *adicionar_cliente(Cliente *l)
{
    int cnh;
    char nome[100];
    int telefone;
    printf("\tCliente\n\n");
    printf("Digite a CNH: ");
    scanf("%d", &cnh);
    printf("Digite o nome: ");
    scanf("%s", nome);
    printf("Digite o telefone: ");
    scanf("%d", &telefone);
    return lst_cliente_insere(l, cnh, nome, telefone);
}
Cliente *busca_cliente(Cliente *l, int cnh)
{
    Cliente *p = l;
    while (p != NULL && p->cnh != cnh)
    {
        p = p->prox;
    }
    return p;
}
void listar_clientes(Cliente *l)
{
    Cliente *p = l;
    int cont = 1;
    if (p == NULL)
    {
        printf("Nenhum cliente listado\n\n");
    }
    else
    {
        printf("Informacoes dos Clientes:\n\n");
        while (p != NULL)
        {
            printf("Informacoes do Cliente #%d\n\n", cont);
            cont++;
            printf("CNH: %d\n", p->cnh);
            printf("Nome: %s\n", p->nome);
            printf("Telefone: %d\n", p->telefone);
            printf("\n");
            p = p->prox;
        }
    }
}

Locacao *lst_locacao_cria(void)
{
    return NULL;
}
Locacao *lst_locacao_insere(Locacao *l, Veiculo *v, Cliente *c, Date retirada, Date devolucao, float valor)
{

    Locacao *novo = (Locacao *)malloc(sizeof(Locacao));
    v->disp = 0;
    novo->v = v;
    novo->c = c;
    novo->retirada = retirada;
    novo->devolucao = devolucao;
    novo->valor = valor;
    novo->prox = l;
    return novo;
}
Locacao *busca_na_locacao_veiculo(Locacao *locacao, Veiculo *veiculo)
{
    Locacao *l = locacao;
    /*for (l = locacao; l != NULL; l = l->prox)
    {
        if (strcmp(l->v->placa, veiculo->placa) == 0)
            return l;
    }*/
    while (l!=NULL&&strcmp(l->v->placa, veiculo->placa)!=0)
    {
        l=l->prox;
    }


    return l;
    
}
bool verificar_disponibilidade(Locacao *locacao, Veiculo *veiculo, Date retirada, Date devolucao)
{
    if (locacao == NULL)
    {
        return 1;
    }
    Locacao *l = locacao;
    while (l != NULL)
    {
        l = busca_na_locacao_veiculo(l, veiculo);
        if (l==NULL)
        {
            break;
        }
        int dist1, dist2, distTotal;
        dist1 = abs(daysBetweenDates(l->retirada, retirada)) + abs(daysBetweenDates(l->devolucao, retirada));
        dist2 = abs(daysBetweenDates(l->retirada, devolucao)) + abs(daysBetweenDates(l->devolucao, devolucao));
        distTotal = daysBetweenDates(l->retirada, l->devolucao);
        int dist3, dist4, distTotal2;
        dist3 = abs(daysBetweenDates(retirada, l->retirada)) + abs(daysBetweenDates(devolucao, l->retirada));
        dist4 = abs(daysBetweenDates(retirada, l->devolucao)) + abs(daysBetweenDates(devolucao, l->devolucao));
        distTotal2 = daysBetweenDates(retirada, devolucao);
        if (dist1 <= distTotal || dist2 <= distTotal || dist3 <= distTotal2 || dist4 <= distTotal2)
        {
            return 0;
        }

        l = l->prox;
    }
    return 1;
}
Locacao *adicionar_locacao(Locacao *locacao, Cliente *cliente, Veiculo *veiculo)
{
    int cnh;
    Cliente *c = cliente;
    while (c != NULL)
    {
        printf("Digite a sua CNH\n");
        scanf("%d", &cnh);
        c = busca_cliente(cliente, cnh);
        if (c == NULL)
        {
            printf("Cliente nao encontrado na base de dados\n");
            c = cliente;
        }
        else
        {
            break;
        }
    }
    if (c == NULL)
    {
        printf("Nao ha registro de clientes na base de dados\n");
        return locacao;
    }

    char placa[100];
    Veiculo *p = veiculo;
    Date retirada, devolucao;
    while (p != NULL)
    {
        while (1)
        {
            printf("Digite a placa do veiculo\n");
            scanf("%s", placa);
            p = busca_veiculo(veiculo, placa);
            if (p == NULL)
            {
                printf("Veiculo nao encontrado na base de dados\n");
            }
            else
            {
                break;
            }
        }

        while (1)
        {
            printf("Insira a data da retirada(dd/mm/aaaa): ");
            scanf("%d/%d/%d", &retirada.day, &retirada.month, &retirada.year);
            printf("Insira a data da devolucao(dd/mm/aaaa): ");
            scanf("%d/%d/%d", &devolucao.day, &devolucao.month, &devolucao.year);
            if (daysBetweenDates(retirada, devolucao) < 0)
            {
                printf("Datas invalidas, data de devolucao antecede a data de retirada inserida\n");
            }
            else
            {
                break;
            }
        }
        if (!verificar_disponibilidade(locacao, p, retirada, devolucao))
        {
            printf("O veiculo esta indisponivel no periodo solicitado\n");
        }
        else
        {
            int dias = daysBetweenDates(retirada, devolucao);
            float valor = dias * p->diaria;

            printf("Locacao realizada com sucesso\n\n");
            printf("CNH do locador: %d\n", c->cnh);
            printf("Nome do locador: %s\n", c->nome);
            printf("Placa do veiculo: %s\n", p->placa);
            printf("Modelo do veiculo: %s\n", p->modelo);
            printf("Data de retirada %d/%d/%d\n", retirada.day, retirada.month, retirada.year);
            printf("Data de devolucao %d/%d/%d\n", devolucao.day, devolucao.month, devolucao.year);
            printf("Valor total: $%.2f\n", valor);

            return lst_locacao_insere(locacao, p, c, retirada, devolucao, valor);
        }
    }

    if (p == NULL)
    {
        printf("Nao ha nenhum veiculo registrado\n");
        return locacao;
    }
}
void listar_locacoes(Locacao *l)
{
    Locacao *p = l;
    int cont = 1;
    if (p == NULL)
    {
        printf("Nenhuma locacao listada\n\n");
    }
    else
    {
        printf("Informacoes das locacoes:\n");
        while (p != NULL)
        {
            printf("Informacoes da locacao #%d\n\n", cont);
            cont++;
            printf("Locacao realizada com sucesso\n\n");
            printf("CNH do locador: %d\n", p->c->cnh);
            printf("Nome do locador: %s\n", p->c->nome);
            printf("Placa do veiculo: %s\n", p->v->placa);
            printf("Modelo do veiculo: %s\n", p->v->modelo);
            printf("Data de retirada %d/%d/%d\n", p->retirada.day, p->retirada.month, p->retirada.year);
            printf("Data de devolucao %d/%d/%d\n", p->devolucao.day, p->devolucao.month, p->devolucao.year);
            printf("Valor total: $%.2f\n", p->valor);
            printf("\n\n");
            p = p->prox;
        }
    }
}
void listar_locacoes_ativas(Locacao *l)
{
    Locacao *p = l;
    Date data;
    int cont = 0;
    if (p == NULL)
    {
        printf("Nenhuma locacao listada\n\n");
        return;
    }
    else
    {
        printf("Insira a data para verificar as locacoes ativas(dd/mm/aaaa): ");
        scanf("%d/%d/%d", &data.day, &data.month, &data.year);
        while (p != NULL)
        {
            int dist1, distTotal;
            dist1 = abs(daysBetweenDates(p->retirada, data)) + abs(daysBetweenDates(p->devolucao, data));
            distTotal = daysBetweenDates(p->retirada, p->devolucao);
            if (dist1 == distTotal)
            {
                if (cont == 0)
                {
                    printf("Locacoes Ativas:\n\n");
                }
                printf("CNH do locador: %d\n", p->c->cnh);
                printf("Nome do locador: %s\n", p->c->nome);
                printf("Placa do veiculo: %s\n", p->v->placa);
                printf("Modelo do veiculo: %s\n", p->v->modelo);
                printf("Data de retirada %d/%d/%d\n", p->retirada.day, p->retirada.month, p->retirada.year);
                printf("Data de devolucao %d/%d/%d\n", p->devolucao.day, p->devolucao.month, p->devolucao.year);
                printf("Valor total: $%.2f\n", p->valor);
                cont++;
            }
            p = p->prox;
        }
    }
    if (cont == 0)
    {
        printf("Nenhuma locacao ativa\n");
    }
}
void listar_locacao_cliente(Locacao *l)
{
    Locacao *p = l;
    int cnh, cont = 1;
    printf("Infome a CNH do cliente\n");
    scanf("%d", &cnh);
    if (p == NULL)
    {
        printf("Nenhuma locacao listada\n");
    }
    else
    {
        while (p != NULL)
        {
            if (p->c->cnh == cnh)
            {
                printf("Informacoes da locacao %d\n", cont);
                printf("Placa do veiculo: %s\n", p->v->placa);
                printf("Data de retirada: %d/%d/%d\n", p->retirada.day, p->retirada.month, p->retirada.year);
                printf("Data de devolucao: %d/%d/%d\n", p->devolucao.day, p->devolucao.month, p->devolucao.year);
                printf("Valor total: $%.2f\n", p->valor);
                cont++;
            }
            p = p->prox;
        }

        if (cont == 1)
        {
            printf("Esse cliente nao tem nenhuma locacao\n");
        }
    }
}
void faturamento(Locacao *l)
{
    Locacao *p = l;
    int mes;
    float valortotal = 0;
    printf("Digite o mes a ser pesquisado");
    scanf("%d", &mes);
    if (p == NULL)
    {
        printf("Sem locacoes ativas, portando sem faturamento\n");
    }
    while (p != NULL)
    {
        if (p->retirada.month == mes)
        {
            valortotal += p->valor;
        }
        p = p->prox;
    }
    if (valortotal == 0)
    {
        printf("Nenhuma locacao encontrada nesse mes\n");
    }
    else
    {
        printf("O faturamento do mes %d foi de R$%.2f\n", mes, valortotal);
    }
}
void listar_mais_rodados(Veiculo *veiculo)
{
    Veiculo *p = veiculo;
    Veiculo *o = veiculo;
    int primeiroMaior = 0, segundoMaior = 0, terceiroMaior = 0;
    char placa1[100], placa2[100], placa3[100];
    if (p == NULL)
    {
        printf("Nenhum veiculo listado\n\n");
    }
    else
    {
        while (p != NULL)
        {
            if (p->kilometragem > primeiroMaior)
            {
                terceiroMaior = segundoMaior;
                segundoMaior = primeiroMaior;
                primeiroMaior = p->kilometragem;
            }
            else if (p->kilometragem > segundoMaior)
            {
                terceiroMaior = segundoMaior;
                segundoMaior = p->kilometragem;
            }
            else if (p->kilometragem > terceiroMaior)
            {
                terceiroMaior = p->kilometragem;
            }
        }
        if (terceiroMaior != 0)
        {
            while (o != NULL)
            {
                if (o->kilometragem == terceiroMaior)
                {
                    strcpy(placa3, o->placa);
                }
                else if (o->kilometragem == segundoMaior)
                {
                    strcpy(placa2, o->placa);
                }
                else if (o->kilometragem == primeiroMaior)
                {
                    strcpy(placa1, o->placa);
                }
                o = o->prox;
            }
            printf("Os veiculos com maior kilometragem sao:\n");
            printf("Veiculos com maior kilometragem: Placa: %s Kilometragem = %d\n", placa1, primeiroMaior);
            printf("Veiculo com segunda maior kilometragem: Placa: %s Kilometragem = %d\n", placa2, segundoMaior);
            printf("Veiculo com terceira maior kilometragem: Placa: %s Kilometragem = %d\n", placa3, terceiroMaior);
        }
        else if (terceiroMaior == 0 && segundoMaior != 0)
        {
            while (o != NULL)
            {
                if (o->kilometragem == segundoMaior)
                {
                    strcpy(placa2, o->placa);
                }
                else if (o->kilometragem == primeiroMaior)
                {
                    strcpy(placa1, o->placa);
                }
                o = o->prox;
            }
            printf("Os veiculos com maior kilometragem sao:\n");
            printf("Veiculos com maior kilometragem: Placa: %s Kilometragem = %d\n", placa1, primeiroMaior);
            printf("Veiculo com segunda maior kilometragem: Placa: %s Kilometragem = %d\n", placa2, segundoMaior);
        }
        else if (terceiroMaior == 0 && segundoMaior == 0 && primeiroMaior!= 0)
        {
            while (o!= NULL)
            {
                if (o->kilometragem == primeiroMaior)
                {
                    strcpy(placa1, o->placa);
                }
                o = o->prox;
            }
            printf("Veiculos com maior kilometragem: Placa: %s Kilometragem = %d\n", placa1, primeiroMaior);
        }
    }
}
void listar_disponiveis(Veiculo *veiculo)
{
    Veiculo *v = veiculo;
    int cont = 1;
    if (v == NULL)
    {
        printf("Nenhum veiculo listado\n");
    }
    while (v != NULL)
    {
        if (v->disp == true)
        {
            printf("O veiculo de placa %s e modelo %s esta disponivel\n", v->placa, v->modelo);
        }
        v = v->prox;
    }
}
void relatorios(Locacao *locacao, Cliente *cliente, Veiculo *veiculo)
{
    int menu2;
    do
    {
        printf("======MENU DE RELATORIOS=======\n");
        printf("1.  Listar locacoes ativas\n");
        printf("2.  Listar todas as locacoes ja realizadas por um cliente\n");
        printf("3.  Listar o faturamento\n");
        printf("4.  Listar a placa dos 3 veiculos mais rodados\n");
        printf("5.  Listar a placa e o modelo de todos os veiculos disponiveis\n");
        printf("0.  Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf(" %d", &menu2);
        printf("\n");
        switch (menu2)
        {
        case 1:
            listar_locacoes_ativas(locacao);
            break;
        case 2:
            listar_locacao_cliente(locacao);
            break;
        case 3:
            faturamento(locacao);
            break;
        case 4:
            listar_mais_rodados(veiculo);
            break;
        case 5:
            listar_disponiveis(veiculo);
            break;
        default:
            break;
        }
    } while (menu2 != 0);
}