#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void imprimir_numero(double numero)
{
    if (numero > 0)
        printf("+ ");
    else
        printf("- ");
    printf("%.3lf", fabs(numero));
}

int main()
{
    double *pontos;
    double **delta;
    int qtd_pontos;

    printf("Insira a quantidade de pontos: ");
    scanf("%d", &qtd_pontos);

    pontos = (double *)malloc(sizeof(double) * qtd_pontos);
    delta = (double **)malloc(sizeof(double *) * (qtd_pontos));
    for (int i = 0; i < qtd_pontos; i++)
    {
        delta[i] = (double *)malloc((qtd_pontos - i) * sizeof(double));
        
        printf("Insira o par x e f(x): ");
        scanf("%lf%lf", &pontos[i], &delta[0][i]);
    }

    for (int i = 0; i < qtd_pontos - 1; i++)
    {
        for (int i2 = 0; i2 < qtd_pontos - 1 - i; i2++)
        {
            // printf("%lf - %lf / %lf - %lf\n", delta[i][indice], delta[i][i2], pontos[indice], pontos[i2]);
            delta[i + 1][i2] = (delta[i][i2 + 1] - delta[i][i2]) / (pontos[i2 + 1 + i] - pontos[i2]);
            printf("%lf\n", delta[i + 1][i2]);
        }
    }

    printf("P(x)=");
    // printf("%lf ", pontos[0][1]);
    for (int i = 0; i < qtd_pontos; i++)
    {
        if (i != 0)
            printf(" + ");
        for (int i2 = 0; i2 < i; i2++)
        {
            printf("(x ");
            imprimir_numero(-pontos[i2]);
            printf(")");
        }
        
        printf("(%.3lf)", delta[i][0]);
    }
    
    
    for (int i = 0; i < qtd_pontos; i++)
    {
        free(delta[i]);
    }

    free(delta);
    free(pontos);

    return 0;
}

/*
3
-1 4
0 1
2 -1

4
1 0
3 6
4 24
5 60
*/