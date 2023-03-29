#include <stdio.h>
#include <locale.h>
#include <math.h>

double funcao(double x)
{
	return pow(x, 3) - (9 * x) + 5;
}

double funcao_derivada(double x)
{
	return (3 * pow(x, 2)) - 9;
}

void imprimir_valores(int indice_x, double x, double fx, double f_derivada)
{
	printf("x%d = %.5lf\n", indice_x, x);
	printf("f(x) = %.5lf\n", fx);
	printf("f'(x) = %.5lf\n", f_derivada);
	printf("---------------------\n");
}

double newton_raphson(double x, double erro)
{
	int limite_iteracoes = 1000;
	int indice_x = 0;
	double fx = funcao(x);
	double f_derivada = funcao_derivada(x);
	
	while(indice_x < limite_iteracoes && fabs(fx) > erro)
	{
		imprimir_valores(indice_x, x, fx, f_derivada);

		x = x - (fx / f_derivada);
		fx = funcao(x);
		f_derivada = funcao_derivada(x);
		indice_x += 1;
	}

	imprimir_valores(indice_x, x, fx, f_derivada);

	return x;
}

int main()
{
    setlocale(LC_ALL, "");
	
	// Raízes: -3.274, 0.577, 2.670
	// Valores pra teste: -30, 30, 1, 3, -2
	printf("A raiz da função é aproximadamente: %.5lf\n", newton_raphson(1, 0.01));
    
    return 0;
}