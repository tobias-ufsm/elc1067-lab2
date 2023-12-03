#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 50

typedef struct
{
    char sexo;
    int idade;
    int qtdade;
} Usuario;

void leVetor(int tamanho, Usuario *vet)
{
    for (int i = 0; i < tamanho; i++)
    {
        printf("Usuario %d\n", i + 1);
        printf("Sexo (M/F): ");
        scanf(" %c", &vet[i].sexo);
        printf("Idade: ");
        scanf("%d", &vet[i].idade);
        printf("Quantidade de livros lidos: ");
        scanf("%d", &vet[i].qtdade);
    }
}

int calculaQtidadeLivros(int tamanho, Usuario *vet)
{
    int livros = 0;
    for (int i = 0; i < tamanho; i++)
    {
        if (vet[i].idade < 10)
        {
            livros += vet[i].qtdade;
        }
    }
    return livros;
}

int calculaQtidadeMulheres(int tamanho, Usuario *vet)
{
    int mulheres = 0;
    for (int i = 0; i < tamanho; i++)
    {
        if (vet[i].sexo == 'F' && vet[i].qtdade >= 5)
        {
            mulheres++;
        }
    }
    return mulheres;
}

int main()
{
    Usuario usuarios[TAM];
    leVetor(TAM, usuarios);
    printf("\nLivros lidos por menores de 10 anos: %d\n", calculaQtidadeLivros(TAM, usuarios));
    printf("Mulheres que leram 5 livros ou mais: %d\n", calculaQtidadeMulheres(TAM, usuarios));
}