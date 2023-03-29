#include <stdio.h>
#include <locale.h>
#include <math.h>

double funcao(double x)
{
	return pow(x, 3) - 2;
}

double secante(double x0, double x1, double erro)
{
	int limite_iteracoes = 1000;
	double xn = 0;
	
	while(limite_iteracoes > 0 && fabs(x1 - x0) > erro)
	{
		limite_iteracoes -= 1;
		
		double fx0 = funcao(x0);
		double fx1 = funcao(x1);
		
		xn = x1 - (fx1 * (x1 - x0) / (fx1 - fx0));
		x0 = x1;
		x1 = xn;
	}
	
	return xn;
}

int main()
{
    setlocale(LC_ALL, "");
	
	printf("A raiz da função é aproximadamente: %.5lf\n", secante(1, 2, 0.1));
    
    return 0;
}