#include <stdio.h>
#include <locale.h>
#include <math.h>

double funcao(double x)
{
	return pow(x, 3) - (9 * x) + 5;
}

double funcao_de_iteracao(double x)
{
	return (pow(x, 3) + 5) / 9;
}

double ponto_fixo(double x, double erro)
{
	double fx = funcao(x);
	int limite_iteracoes = 1000;
	
	while(limite_iteracoes > 0 && fabs(fx) > erro)
	{
		limite_iteracoes -= 1;
		
		x = funcao_de_iteracao(x);
        fx = funcao(x);
	}
	
	return x;
}

int main()
{
    setlocale(LC_ALL, "");
	
	printf("A raiz da função é aproximadamente: %.5lf\n", ponto_fixo(2.66, 0.001));
    
    return 0;
}