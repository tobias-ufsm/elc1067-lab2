#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int ladoA;
    int ladoB;
    int ladoC;
    char ehTriangulo;
    char tipo[20];
} Triangulo;

void verificaTriangulo (Triangulo *t)
{
    if (t->ladoA>=t->ladoB+t->ladoC)
    {
        t->ehTriangulo='N';
    }
    else if (t->ladoC>=t->ladoA+t->ladoB)
    {
        t->ehTriangulo='N';
    }
    else if (t->ladoB>=t->ladoA+t->ladoC)
    {
        t->ehTriangulo='N';
    }
    else{
        t->ehTriangulo='S';
        if(t->ladoA==t->ladoB&&t->ladoA==t->ladoC)
        {
            strcpy(t->tipo, "Equilatero");
        }
        else if(t->ladoA==t->ladoB||t->ladoA==t->ladoC||t->ladoB==t->ladoC)
        {
            strcpy(t->tipo, "Isosceles");
        }
        else
        {
            strcpy(t->tipo, "Escaleno");
        }
    }

}
int main()
{
    Triangulo triangulo;
    scanf("%d", &triangulo.ladoA);
    scanf("%d", &triangulo.ladoB);
    scanf("%d", &triangulo.ladoC);
    verificaTriangulo(&triangulo);
    printf("%c\n", triangulo.ehTriangulo);
    printf("%s", triangulo.tipo);
}