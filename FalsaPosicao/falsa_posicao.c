#include <stdio.h>
#include <locale.h>
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

double falsa_posicao(double inicio_intervalo, double fim_intervalo, double erro, double k)
{
	double funcao_inicio = funcao(inicio_intervalo);
	double funcao_fim = funcao(fim_intervalo);
	
	k = ((inicio_intervalo * funcao_fim) - (fim_intervalo * funcao_inicio)) / (funcao_fim - funcao_inicio);
	
	if(abs(fim_intervalo - inicio_intervalo) < erro || fabs(k) < erro)
		return k;
	
	if(comparar_sinais(inicio_intervalo, k) == -1)
		return falsa_posicao(inicio_intervalo, k, erro, k);
	else
		return falsa_posicao(k, fim_intervalo, erro, k);
}

int main()
{
    setlocale(LC_ALL, "");
	
	printf("A raiz da função é aproximadamente: %.5lf\n", falsa_posicao(1, 2, 0.1, 0));
    
    return 0;
}