#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 5

typedef struct
{
    float nota1;
    float nota2;
    int aulasAssistidas;
    float media;
    char status;
} Aluno;

typedef struct
{
    Aluno alunos[TAM];
    int aulasMinistradas;
} Disciplina;

void calcularMediaEStatus(Aluno *aluno, int aulasMinistradas)
{
    aluno->media = (aluno->nota1 + aluno->nota2) / 2.0;

    float frequencia = (aluno->aulasAssistidas / (float)aulasMinistradas) * 100;

    if (aluno->media >= 6 && frequencia >= 75)
    {
        aluno->status = 'A';
    }
    else
    {
        aluno->status = 'B';
    }
}

int main()
{
    Disciplina disc;
    
    printf("Aulas ministradas: ");
    scanf("%d", &disc.aulasMinistradas);

    for (int i = 0; i < TAM; i++)
    {
        printf("\nAluno %d:\n", i + 1);
        printf("Informe a primeira nota: ");
        scanf("%f", &disc.alunos[i].nota1);
        printf("Informe a segunda nota: ");
        scanf("%f", &disc.alunos[i].nota2);
        printf("Informe o numero de aulas assistidas: ");
        scanf("%d", &disc.alunos[i].aulasAssistidas);

        calcularMediaEStatus(&disc.alunos[i], disc.aulasMinistradas);
    }

    printf("\nRelatorio de Alunos:\n");
    for (int i = 0; i < TAM; i++)
    {
        printf("Aluno %d:\n", i + 1);
        printf("Media: %.2f\n", disc.alunos[i].media);
        printf("Status: %c\n", disc.alunos[i].status);
        printf("\n");
    }
}