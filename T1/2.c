#include <stdio.h>
#include <stdlib.h>

#define TAM 5

typedef struct
{
    float base;
    float altura;
    float perimetro;
    float area;
} Retangulo;

void preenche_base_altura(Retangulo ret[])
{
    for (int i = 0; i < 5; i++)
    {
        printf("Digite a base do retangulo %d\n", i + 1);
        scanf("%f", &ret[i].base);
        printf("Digite a altura do retangulo %d\n", i + 1);
        scanf("%f", &ret[i].altura);
    }
}

void calculaPeriArea(Retangulo ret, int i)
{
    ret.perimetro = (ret.base * 2) + (ret.altura * 2);
    ret.area = (ret.base * ret.altura);
    printf("Retangulo %d - Perimetro:%f    Area:%f\n", i + 1, ret.perimetro, ret.area);
}

int main()
{
    Retangulo retangulo[TAM];
    preenche_base_altura(retangulo);
    for (int i = 0; i < TAM; i++)
    {
        calculaPeriArea(retangulo[i], i);
    }
}