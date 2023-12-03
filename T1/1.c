#include <stdio.h>
#include <stdlib.h>
void calc_esfera (float r, float *area, float *volume)
{
    *area=4*3.14*r*r;
    *volume=(4*3.14*r*r*r)/3;
}
int main()
{
    float raio, area, volume;
    printf("Digite o raio da esfirra esferica: ");
    scanf("%f", &raio);
    calc_esfera(raio, &area, &volume);
    printf("Area:%f  Volume:%f", area, volume);
}