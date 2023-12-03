#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz.h"

void horizontal_direta(char word[], char **mat, int rows, int columns, int word_size, int l, int c)
{
    if ((c + word_size) <= columns)
    {
        char copy[3000];
        int k = 0;
        for (int i = c; i < c + word_size; i++)
        {
            copy[k] = mat[l][i];
            k++;
        }
        copy[k] = '\0';
        if (strcmp(copy, word) == 0)
        {
            printf("Palavra '%s' ocorre na horizontal direta, iniciando na posicao [%d,%d] e terminando na posicao [%d,%d]\n", word, l + 1, c + 1, l + 1, c + word_size);
        }
    }
}
void horizontal_reversa(char word[], char **mat, int rows, int columns, int word_size, int l, int c)
{
    if ((c - word_size + 1) >= 0)
    {
        char copy[3000];
        int k = 0;
        for (int i = c; i > c - word_size; i--)
        {
            copy[k] = mat[l][i];
            k++;
        }
        copy[k] = '\0';
        if (strcmp(copy, word) == 0)
        {
            printf("Palavra '%s' ocorre na horizontal reversa, iniciando na posicao [%d,%d] e terminando na posicao [%d,%d]\n", word, l + 1, c + 1, l + 1, c - word_size + 2);
        }
    }
}

void vertical_direta(char word[], char **mat, int rows, int columns, int word_size, int l, int c)
{
    if ((l + word_size) <= rows)
    {
        char copy[3000];
        int k = 0;
        for (int i = l; i < l + word_size; i++)
        {
            copy[k] = mat[i][c];
            k++;
        }
        copy[k] = '\0';
        if (strcmp(copy, word) == 0)
        {
            printf("Palavra '%s' ocorre na vertical direta, iniciando na posicao [%d,%d] e terminando na posicao [%d,%d]\n", word, l + 1, c + 1, l + word_size, c + 1);
        }
    }
}
void vertical_reversa(char word[], char **mat, int rows, int columns, int word_size, int l, int c)
{
    if ((l - word_size + 1) >= 0)
    {
        char copy[3000];
        int k = 0;
        for (int i = l; i > l - word_size; i--)
        {
            copy[k] = mat[i][c];
            k++;
        }
        copy[k] = '\0';
        if (strcmp(copy, word) == 0)
        {
            printf("Palavra '%s' ocorre na vertical reversa, iniciando na posicao [%d,%d] e terminando na posicao [%d,%d]\n", word, l + 1, c + 1, l - word_size + 2, c + 1);
        }
    }
}

void diagonal_principal_direta(char word[], char **mat, int rows, int columns, int word_size, int l, int c)
{
    if ((word_size + c <= columns) && (word_size + l <= rows))
    {
        char copy[3000];
        int k = 0;
        for (int i = 0; i < word_size; i++)
        {
            copy[k] = mat[l + i][c + i];
            k++;
        }
        copy[k] = '\0';
        if (strcmp(copy, word) == 0)
        {
            printf("Palavra '%s' ocorre na diagonal principal direta, iniciando na posicao [%d,%d] e terminando na posicao [%d,%d]\n", word, l + 1, c + 1, l + word_size, c + word_size);
        }
    }
}
void diagonal_principal_reversa(char word[], char **mat, int rows, int columns, int word_size, int l, int c)
{
    if ((c - word_size + 1 >= 0) && (l - word_size + 1 >= 0))
    {
        char copy[3000];
        int k = 0;
        for (int i = 0; i < word_size; i++)
        {
            copy[k] = mat[l - i][c - i];
            k++;
        }
        copy[k] = '\0';
        if (strcmp(copy, word) == 0)
        {
            printf("Palavra '%s' ocorre na diagonal principal reversa, iniciando na posicao [%d,%d] e terminando na posicao [%d,%d]\n", word, l + 1, c + 1, l - word_size + 2, c - word_size + 2);
        }
    }
}

void diagonal_secundaria_direta(char word[], char **mat, int rows, int columns, int word_size, int l, int c)
{
    if ((c - word_size + 1 >= 0) && ((l + word_size) <= rows))
    {
        char copy[3000];
        int k = 0;
        for (int i = 0; i < word_size; i++)
        {
            copy[k] = mat[l + i][c - i];
            k++;
        }
        copy[k] = '\0';
        if (strcmp(copy, word) == 0)
        {
            printf("Palavra '%s' ocorre na diagonal secundaria direta, iniciando na posicao [%d,%d] e terminando na posicao [%d,%d]\n", word, l + 1, c + 1, l + word_size, c - word_size + 2);
        }
    }
}
void diagonal_secundaria_reversa(char word[], char **mat, int rows, int columns, int word_size, int l, int c)
{
    if ((l - word_size + 1 >= 0) && (c + word_size <= columns))
    {
        char copy[3000];
        int k = 0;
        for (int i = 0; i < word_size; i++)
        {
            copy[k] = mat[l - i][c + i];
            k++;
        }
        copy[k] = '\0';
        if (strcmp(copy, word) == 0)
        {
            printf("Palavra '%s' ocorre na diagonal secundaria reversa, iniciando na posicao [%d,%d] e terminando na posicao [%d,%d]\n", word, l + 1, c + 1, l - word_size + 2, c + word_size);
        }
    }
}

void verifica_posicao(char word[], char **mat, int rows, int columns, int word_size, int l, int c)
{
    horizontal_direta(word, mat, rows, columns, word_size, l, c);
    horizontal_reversa(word, mat, rows, columns, word_size, l, c);
    vertical_direta(word, mat, rows, columns, word_size, l, c);
    vertical_reversa(word, mat, rows, columns, word_size, l, c);
    diagonal_principal_direta(word, mat, rows, columns, word_size, l, c);
    diagonal_principal_reversa(word, mat, rows, columns, word_size, l, c);
    diagonal_secundaria_direta(word, mat, rows, columns, word_size, l, c);
    diagonal_secundaria_reversa(word, mat, rows, columns, word_size, l, c);
}

int main()
{
    int rows, columns, word_size, stop=0;
    char word[3000], letter;
    printf("Digite as dimensoes da matriz(linhas e colunas): ");
    scanf("%d %d", &rows, &columns);
    char **mat = (char **)allocate_matrix(rows, columns, sizeof(char));
    printf("Digite um texto: ");
    fill_matrix_without_spaces(mat, rows, columns);
    print_matrix((void **)mat, rows, columns, sizeof(char));

    while (1)
    {
        printf("\nDigite uma palavra: ");
        scanf("%s", word);
        word_size = (int)strlen(word);

        for (int l = 0; l < rows; l++)
        {
            for (int c = 0; c < columns; c++)
            {
                if (mat[l][c] == word[0])
                {
                    verifica_posicao(word, mat, rows, columns, word_size, l, c);
                }
            }
        }
        getchar();
        printf("\nDeseja buscar outra palavra(s/n)?\n");
        letter=getchar();
        if (letter=='n'||letter=='N')
        {
            break;
        }
        else if (letter!='s'&&letter!='S')
        {
            printf("\nPo meuuu, era s ou n\n");
        }
    }
    free_matrix((void **)mat, rows);
}