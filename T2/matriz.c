#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matriz.h"

void **allocate_matrix(int rows, int columns, size_t size_type)
{
    void **matrix = (void **)malloc(rows * sizeof(void *));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = malloc(columns * size_type);
    }
    return matrix;
}
void fill_matrix(void **matrix, int rows, int columns, size_t size_type)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (size_type == sizeof(int))
            {
                scanf(" %d", (int *)(matrix[i] + j * size_type));
            }
            else if (size_type == sizeof(float))
            {
                scanf(" %f", (float *)(matrix[i] + j * size_type));
            }
            else if (size_type == sizeof(double))
            {

                scanf(" %lf", (double *)(matrix[i] + j * size_type));
            }
            else if (size_type == sizeof(char))
            {

                scanf(" %c", (char *)(matrix[i] + j * size_type));
            }
        }
    }
}
void print_matrix(void **matrix, int rows, int columns, size_t size_type)
{
    printf("\n  ");
    for (int i = 0; i < columns; i++)
    {
        printf(" %d", i + 1);
    }
    printf("\n");
    for (int i = 0; i < rows; i++)
    {
        printf("%d  ", i + 1);
        for (int j = 0; j < columns; j++)
        {
            if (size_type == sizeof(int))
            {
                printf("%d ", *((int *)(matrix[i] + j * size_type)));
            }
            else if (size_type == sizeof(float))
            {
                printf("%.2f ", *((float *)(matrix[i] + j * size_type)));
            }
            else if (size_type == sizeof(double))
            {
                printf("%.2lf ", *((double *)(matrix[i] + j * size_type)));
            }
            else if (size_type == sizeof(char))
            {
                printf("%c ", *((char *)(matrix[i] + j * size_type)));
            }
        }
        printf("\n");
    }
}

void fill_matrix_without_spaces(char **matrix, int rows, int columns)
{
    getchar();
    int block = 0;
    char letter;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (block == 1)
            {
                matrix[i][j] = ' ';
            }
            else
            {
                letter = getchar();
                while (letter == ' ')
                {
                    letter = getchar();
                    if (letter == '\n')
                    {
                        break;
                    }
                }
                if (letter == '\n')
                {
                    block = 1;
                }
                else
                {
                    matrix[i][j] = letter;
                }
            }
        }
    }
    while (letter != '\n')
    {
        letter = getchar();
    }
}

void free_matrix(void **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}