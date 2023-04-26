#include <stdio.h>
#include <stdlib.h>
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
}

void imprimir_equacao(double **matriz, int tamanho)
{
	printf("f(x) = ");
	for (int i = tamanho - 1; i >= 0; i--)
	{
		if(matriz[i][tamanho] > 0)
			printf("+");
		printf("%.3lf", matriz[i][tamanho]);

		if(i != 0)
			printf("x");
		if(i > 1)
			printf("^%d", i);
		printf(" ");
	}
}

int main()
{
    int qtd_pontos;
    double **matriz;
    double x;
    double fx;

    printf("Insira a quantidade de pontos: ");
    scanf("%d", &qtd_pontos);

    matriz = (double **) malloc(qtd_pontos * sizeof(double *));

    for (int i = 0; i < qtd_pontos; i++)
    {
        matriz[i] = (double *) malloc((qtd_pontos + 1) * sizeof(double));
        
        printf("Insira os valores do par x e f(x): ");
		scanf("%lf%lf", &x, &fx);

        matriz[i][0] = 1;
        for (int i2 = 1; i2 < qtd_pontos; i2++)
        {
            matriz[i][i2] = pow(x, i2);
        }
        matriz[i][qtd_pontos] = fx;
    }

	eliminacao_gauss(matriz, qtd_pontos, qtd_pontos + 1);
	imprimir_equacao(matriz, qtd_pontos);

    liberar_matriz(matriz, qtd_pontos);

    return 0;
}

/*
Insira os valores do par x e f(x): -1 3
Insira os valores do par x e f(x): 1 -5
Insira os valores do par x e f(x): 2 10
Insira os valores do par x e f(x): 3 -3
-17.50000 1.08333x 16.50000x^2 -5.08333x^3
*/
