#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

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

void adicionar_linhas(double **matriz, int linha1, int linha2, int colunas, double escalar)
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
		if(matriz[i][coluna] > maior)
		{
			maior = matriz[i][coluna];
			indice_maior = i;
		}
	}

	return indice_maior;
}

void eliminacao_gauss(double **matriz, int linhas, int colunas)
{
	int pivo_linha = 0;
	int pivo_coluna = 0;

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

			adicionar_linhas(matriz, i, pivo_linha, colunas, -fator);
			matriz[i][pivo_coluna] = 0;
		}

		// imprimir_matriz(matriz, linhas, colunas);
		
		pivo_linha += 1;
		pivo_coluna += 1;
	}
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
		printf("Termo [%d]: ", i);
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
	imprimir_matriz(matriz_aumentada, linhas, colunas + 1);
	
	liberar_matriz(matriz_coeficientes, linhas);
	liberar_matriz(matriz_aumentada, linhas);
	free(termos);
	return 0;
}

/*
3
3
2
1
-1
-3
-1
2
-2
1
2
8
-11
-3
*/