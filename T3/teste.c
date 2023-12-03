#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


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
    int difference = abs(days2 - days1);
    return difference;
}


int main()
{
    Date o_retirada, o_devolucao, novo_retirada, novo_devolucao;
    o_retirada.day=2;
    o_retirada.month=4;
    o_retirada.year=2004;

    o_devolucao.day=7;
    o_devolucao.month=4;
    o_devolucao.year=2004;

    printf("Diferenca entre datas antigass: %d\n", daysBetweenDates(o_retirada, o_devolucao));
    novo_retirada.day=7;
    novo_retirada.month=4;
    novo_retirada.year=2004;

    printf("Teste: %d\n", daysBetweenDates(o_retirada, novo_retirada)+daysBetweenDates(o_devolucao, novo_retirada));

    novo_devolucao.day=15;
    novo_devolucao.month=4;
    novo_devolucao.year=2004;
    printf("Teste2: %d\n", daysBetweenDates(o_retirada, novo_devolucao)+daysBetweenDates(o_devolucao, novo_devolucao));

    printf("Diferenca entre datas novas: %d\n", daysBetweenDates(novo_retirada, novo_devolucao));
    printf("Teste3: %d\n", daysBetweenDates(novo_retirada, o_retirada)+daysBetweenDates(novo_devolucao, o_retirada));

    printf("Teste4: %d\n", daysBetweenDates(novo_retirada, o_devolucao)+daysBetweenDates(novo_devolucao, o_devolucao));
}