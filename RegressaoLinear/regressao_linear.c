#include <stdio.h>
#include <stdlib.h>

int main()
{
    int qtd_pontos;
    double x;
    double y;
    double somatorio_x = 0;
    double somatorio_x2 = 0;
    double somatorio_y = 0;
    double somatorio_xy = 0;
    double a;
    double b;

    printf("Insira a quantidade de pontos: ");
    scanf("%d", &qtd_pontos);
    
    for (int i = 0; i < qtd_pontos; i++)
    {
        printf("Insira o par x e f(x): ");
        scanf("%lf%lf", &x, &y);

        somatorio_x += x;
        somatorio_y += y;
        somatorio_x2 += x * x;
        somatorio_xy += x * y;
    }

    b = ((qtd_pontos * somatorio_xy) - (somatorio_x * somatorio_y)) / ((qtd_pontos * somatorio_x2) - (somatorio_x * somatorio_x));
    a = (somatorio_y - (b * somatorio_x)) / qtd_pontos;

    printf("f(x) = %.3lfx ", b);
    if (a >= 0)
        printf("+ ");
    printf("%.3lf", a);

    return 0;
}

/*
4
1 1
2 3
-1 2
0 -1

4
100 50
200 70
400 100
500 120

6
1 80.5
2 81.6
3 82.1
4 83.7
5 83.9
6 85
*/