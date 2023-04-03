#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

void liberar_matriz(double **matriz, int linhas)
{
	for(int i = 0; i < linhas; i++)
	{
		free(matriz[i]);
	}
	
	free(matriz);
}

void imprimir_matriz(double **matriz, int linhas, int colunas)
{
	for (int i = 0; i < linhas; i++)
	{
		for (int j = 0; j < colunas; j++)
		{
			printf("%.2lf ", matriz[i][j]);
		}
		printf("\n");
	}
}

void imprimir_solucao(double *solucao, int tamanho)
{
	for(int i = 0; i < tamanho; i++)
	{
		printf("x%d = %.2lf\n", (i + 1), solucao[i]);
	}
}

void copiar_solucao(double *origem, double *solucao, int tamanho)
{
	for(int i = 0; i < tamanho; i++)
	{
		solucao[i] = origem[i];
	}
}

double calcular_erro(double *solucao_anterior, double *solucao, int tamanho)
{
	double maior_diferenca = 0;
	for(int i = 0; i < tamanho; i++)
	{
		double diferenca = fabs(solucao[i] - solucao_anterior[i]);
		if (diferenca > maior_diferenca)
			maior_diferenca = diferenca;
	}

	return maior_diferenca;
}

void jacobi(double **matriz, double *termos, int linhas, int colunas)
{
	double erro = 1;
	double tolerancia = 0.01;
	double soma;
	int limite_iteracoes = 10;
	int iteracoes = 0;
	double *solucao = (double *) malloc(colunas * sizeof(double));
	double *solucao_temp = (double *) malloc(colunas * sizeof(double));

	for(int i = 0; i < colunas; i++)
	{
		solucao[i] = 0;
		solucao_temp[i] = 0;
	}
	
	while(iteracoes < limite_iteracoes && erro > tolerancia)
	{
		iteracoes += 1;
		
		for(int i = 0; i < linhas; i++)
		{
			soma = 0;
			for(int j = 0; j < colunas; j++)
			{
				if(i != j)
				{
					soma += (matriz[i][j] * solucao[j]) / matriz[i][i];
				}
				
				solucao_temp[i] = (termos[i] / matriz[i][i]) - soma;
			}
		}
		
		erro = calcular_erro(solucao, solucao_temp, colunas);

		copiar_solucao(solucao_temp, solucao, colunas);
	}
	
	imprimir_solucao(solucao, colunas);

	free(solucao);
	free(solucao_temp);
}

int main()
{
	setlocale(LC_ALL, "");

	double **matriz_coeficientes;
	double *termos;
	int linhas;
	int colunas;
	
	printf("== Matriz de coeficientes ==\n");
	printf("Número de linhas: ");
	scanf("%d", &linhas);
	
	printf("Número de colunas: ");
	scanf("%d", &colunas);
	
	matriz_coeficientes = (double **) malloc(linhas * sizeof(double *));
	for(int i = 0; i < linhas; i++)
	{
		matriz_coeficientes[i] = (double *) malloc(colunas * sizeof(double));
		for (int j = 0; j < colunas; j++)
		{
			printf("a[%d][%d]: \n", (i + 1), (j + 1));
			scanf("%lf", &matriz_coeficientes[i][j]);
		}
	}

	printf("== Termos ==\n");
	termos = (double *) malloc(linhas * sizeof(double));
	for(int i = 0; i < linhas; i++)
	{
		printf("Termo [%d]: ", (i + 1));
		scanf("%lf", &termos[i]);
	}

	jacobi(matriz_coeficientes, termos, linhas, colunas);
	
	liberar_matriz(matriz_coeficientes, linhas);
	free(termos);
	return 0;
}

/*
VALORES PARA TESTE
3 3
2 1 -1
-3 -1 2
-2 1 2
8 -11 -3

3 3
1 3 -1
2 1 1
3 -1 1
0 1 3

3 3
2 4 -2
-2 -2 2
5 4 -3
2 1 6

3 3
8 1 -1
1 -7 2
2 1 9
8 -4 12
*/