#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>

double funcao_quadratica(double x)
{
	return pow(x, 2);	
}

double funcao_cosseno(double x)
{
	return x - cos(x);
}

double funcao(double x)
{
	return pow(x, 2) - 3;
}

int comparar_sinais(double x1, double x2)
{
	double mult = funcao(x1) * funcao(x2);
	if(mult < 0)
		return -1;
	else
		return 1;
}

double bissecao(double inicio_intervalo, double fim_intervalo, double erro, double k)
{
	k = (inicio_intervalo + fim_intervalo) / 2;
	
	if(abs(fim_intervalo - inicio_intervalo) < erro)
		return k;
	
	if(comparar_sinais(inicio_intervalo, k) == -1)
		return bissecao(inicio_intervalo, k, erro, k);
	else
		return bissecao(k, fim_intervalo, erro, k);
}

int main()
{
    setlocale(LC_ALL, "");
	
	printf("A raiz da função é aproximadamente: %.2lf\n", bissecao(1, 2, 0.1, 0));
    
    return 0;
}