#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

typedef struct Date
{
    int day;
    int month;
    int year;
} Date;
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

    // Calcular a diferença em dias
    int difference = days2 - days1;
    return difference;
}

typedef struct Cliente
{
    int cnh;
    char nome[100];
    int telefone;
    struct Cliente *prox;
} Cliente;
typedef struct Veiculo
{
    char placa[100];
    char marca[100];
    char modelo[100];
    int ano;
    int kilometragem;
    float diaria;
    Date retirada;
    Date devolucao;
    float valor;
    struct Locacao *prox;
} Locacao;

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
        printf("Nenhum veículo listado\n\n");
    }
    else
    {
        printf("Informações dos Veiculos:\n");
        while (p != NULL)
        {
            printf("Informações do Veiculo #%d\n\n", cont);
            cont++;
            printf("Placa: %s\n", p->placa);
            printf("Marca: %s\n", p->marca);
            printf("Modelo: %s\n", p->modelo);
            printf("Ano de Fabricação: %d\n", p->ano);
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
            printf("\n\n");
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
    printf("Informe a placa do veículo: ");
    scanf("%s", placa);
    printf("Informe a kilometragem do veiculo: ");
    scanf("%d", &kilometragem);
    // Alterei as duas funcoes de busca, estavam dando seg_fault :(
    v = busca_veiculo(veiculo, placa);
    if (v == NULL)
    {
        printf("Veículo não encontrado\n");
    }
    else if (v->disp == 1)
    {
        printf("O veiculo já estava disponivel\n");
    }
    else
    {
        printf("Veículo devolvido com sucesso\n");
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
    printf("CLIENTE\n\n");
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
        printf("Informações dos Clientes:\n");
        while (p != NULL)
        {
            printf("Informações do Cliente #%d\n\n", cont);
            cont++;
            printf("CNH: %d\n", p->cnh);
            printf("Nome: %s\n", p->nome);
            printf("Telefone: %d\n", p->telefone);
            printf("\n\n");
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
    while (l != NULL && strcmp(l->v->placa, veiculo->placa) != 0)
    {
        l = l->prox;
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
            printf("Cliente não encontrado na base de dados\n");
            c = cliente;
        }
        else
        {
            break;
        }
    }
    if (c == NULL)
    {
        printf("Não há registro de clientes na base de dados\n");
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
                printf("Veiculo não encontrado na base de dados\n");
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
            printf("O veiculo esta indisponivel no periodo solicitado");
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
        printf("Nao há nenhum veiculo registrado\n");
        return locacao;
    }
}
void listar_locacoes(Locacao *l)
{
    Locacao *p = l;
    int cont = 1;
    if (p == NULL)
    {
        printf("Nenhuma locação listada\n\n");
    }
    else
    {
        printf("Informações das Locações:\n");
        while (p != NULL)
        {
            printf("Informações da Locação #%d\n\n", cont);
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
        printf("Nenhuma locação listada\n\n");
        return;
    }
    else
    {
        printf("Insira a data para verificar as locações ativas(dd/mm/aaaa): ");
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
                    printf("Locações Ativas:\n\n");
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
    if (cont==0)
    {
        printf("Nenhuma locação ativa\n");
    }
    
}

// Tem que deixar essa funcao nos trinquess ainda
void listar_locacao_cliente(Locacao *l)
{
    Locacao *p = l;
    int cnh, cont = 1;
    printf("Infome a CNH do cliente\n");
    scanf("%d", &cnh);
    if (p == NULL)
    {
        printf("Nenhum locacao listada\n");
    }
    else
    {
        while (p != NULL)
        {
            if (p->c->cnh == cnh)
            {
                printf("Informações da locação %d\n", cont);
                printf("Placa do veículo: %s\n", p->v->placa);
                printf("Data de retirada: %d/%d/%d\n", p->retirada.day, p->retirada.month, p->retirada.year);
                printf("Data de devoluçãoo: %d/%d/%d\n", p->devolucao.day, p->devolucao.month, p->devolucao.year);
                printf("Valor total: $%.2f\n", p->valor);
                cont++;
            }
            p = p->prox;
        }
    }
}

/*
Falta fazer os relatorios, R3, R4, R5
*/
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
        printf("1.  Adicionar veículos\n");
        printf("2.  Listar veículos\n");
        printf("3.  Adicionar clientes\n");
        printf("4.  Listar clientes\n");
        printf("5.  Realizar locação\n");
        printf("6.  Devolver veículo\n");
        printf("7.  Listar locações\n");
        printf("9.  Relatórios\n");
        printf("0.  Sair\n");
        printf("Escolha uma opção: ");
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
            //teste
            listar_locacoes_ativas(l);
            break;
        case 9:
            /* code */
            break;
        default:
            break;
        }
        fflush(stdin);
    } while (menu!=0);
}