#include <stdio.h>
#include <locale.h>

double funcao(double x)
{
    double y = x * x;

    return y;
}

double soma_riemann(double inicio_intervalo, double fim_intervalo, int subdivisoes)
{
    double soma = 0;
    double incremento_x = (fim_intervalo - inicio_intervalo) / subdivisoes;
    for(double x = inicio_intervalo; x < fim_intervalo; x += incremento_x)
    {
        soma += funcao(x) * incremento_x;
    }

    return soma;
}

int main()
{
    setlocale(LC_ALL, "");

    double inicio_intervalo;
    double fim_intervalo;
    int subdivisoes;

    printf("Início do intervalo: ");
    scanf("%lf", &inicio_intervalo);
    printf("Fim do intervalo: ");
    scanf("%lf", &fim_intervalo);
    printf("Número de subdivisões: ");
    scanf("%d", &subdivisoes);

    printf("Resultado da Soma de Riemann: %lf\n", soma_riemann(inicio_intervalo, fim_intervalo, subdivisoes));

    return 0;
}