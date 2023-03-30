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

void imprimir_solucao(double **matriz, int linhas, int colunas)
{
	for(int i = 0; i < linhas; i ++)
	{
		if(matriz[i][i] != 0)
			printf("x%d = %.2lf\n", (i + 1), matriz[i][colunas - 1]);
		else
			printf("x%d = indefinido\n", (i + 1));
	}
}

void trocar_linhas(double **matriz, int linha1, int linha2)
{
	double *troca = matriz[linha1];
	matriz[linha1] = matriz[linha2];
	matriz[linha2] = troca;
}

void multiplicar_linha(double **matriz, int linha, int colunas, double escalar)
{
	for (int i = 0; i < colunas; i++)
	{
		matriz[linha][i] *= escalar;
	}
}

void somar_linhas(double **matriz, int linha1, int linha2, int colunas, double escalar)
{
	for (int i = 0; i < colunas; i++)
	{
		matriz[linha1][i] += matriz[linha2][i] * escalar;
	}
}

int indice_maior_elemento_coluna(double **matriz, int linhas, int coluna, int linha_inicial)
{
	int maior = matriz[linha_inicial][coluna];
	int indice_maior = linha_inicial;

	for (int i = linha_inicial + 1; i < linhas; i++)
	{
		if(fabs(matriz[i][coluna]) > maior)
		{
			maior = fabs(matriz[i][coluna]);
			indice_maior = i;
		}
	}

	return indice_maior;
}

void eliminacao_gauss(double **matriz, int linhas, int colunas)
{
	int pivo_linha = 0;
	int pivo_coluna = 0;

	// Método de Gauss
	while(pivo_linha < (linhas - 1) && pivo_coluna < (colunas - 1))
	{
		int indice_maior = indice_maior_elemento_coluna(matriz, linhas, pivo_coluna, pivo_linha);

		if(matriz[indice_maior][pivo_coluna] == 0)
		{
			pivo_coluna += 1;
			continue;
		}

		if(pivo_linha != indice_maior)
			trocar_linhas(matriz, pivo_linha, indice_maior);
		
		for (int i = pivo_linha + 1; i < linhas; i++)
		{
			double fator = matriz[i][pivo_coluna] / matriz[pivo_linha][pivo_coluna];

			somar_linhas(matriz, i, pivo_linha, colunas, -fator);
			matriz[i][pivo_coluna] = 0;
		}

		// imprimir_matriz(matriz, linhas, colunas);
		
		pivo_linha += 1;
		pivo_coluna += 1;
	}
	
	// Back Substitution
	for(int i = linhas - 1; i >= 0; i--)
	{
		if(matriz[i][i] == 0)
		{
			if (matriz[i][colunas - 1] == 0)
			{
				continue;
			}
			
			printf("Sistema impossível\n");
			return;
		}
		
		multiplicar_linha(matriz, i, colunas, (1 / matriz[i][i]));
		matriz[i][i] = 1;
		
		for(int i2 = i - 1; i2 >= 0; i2--)
		{
			double fator = matriz[i2][i];
			somar_linhas(matriz, i2, i, colunas, -fator);
		}
	}
	
	imprimir_matriz(matriz, linhas, colunas);
	imprimir_solucao(matriz, linhas, colunas);
}

int main()
{
	setlocale(LC_ALL, "");

	double **matriz_coeficientes;
	double *termos;
	double **matriz_aumentada;
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

	matriz_aumentada = (double **) malloc(linhas * sizeof(double *));
	for(int i = 0; i < linhas; i++)
	{
		matriz_aumentada[i] = (double *) malloc((colunas + 1) * sizeof(double));
		for (int j = 0; j < colunas; j++)
		{
			matriz_aumentada[i][j] = matriz_coeficientes[i][j];
		}

		matriz_aumentada[i][colunas] = termos[i];
	}

	eliminacao_gauss(matriz_aumentada, linhas, colunas + 1);
	
	liberar_matriz(matriz_coeficientes, linhas);
	liberar_matriz(matriz_aumentada, linhas);
	free(termos);
	return 0;
}

/*
3 3
2 1 -1
-3 -1 2
-2 1 2
8 -11 -3
*/

/*
3 3
1 3 -1
2 1 1
3 -1 1
0 1 3
*/

/*
3 3
2 4 -2
-2 -2 2
5 4 -3
2 1 6
*/