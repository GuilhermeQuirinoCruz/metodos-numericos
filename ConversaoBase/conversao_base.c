#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>

int bits_necessarios(int numero)
{
    return floor(log2(numero)) + 1;
}

int *converter_decimal_binario(int decimal)
{
    int tamanho = bits_necessarios(decimal);
    int *binario = (int *) malloc(sizeof(int) * tamanho);

    for(int i = tamanho - 1; i >= 0; i--)
    {
        binario[i] = decimal % 2;
        decimal /= 2;
    }

    return binario;
}

void imprimir_binario(int *numero, int tamanho)
{
    for(int i = 0; i < tamanho; i++)
    {
        printf("%d", numero[i]);
    }

    printf("\n");
}

int converter_binario_decimal(int *binario, int tamanho)
{
    int decimal = 0;

    for(int i = 0; i < tamanho; i++)
    {
        decimal += binario[tamanho - 1 - i] * pow(2, i);
    }

    return decimal;
}

int main()
{
    setlocale(LC_ALL, "");

    int *numero_binario = converter_decimal_binario(10);
    imprimir_binario(numero_binario, bits_necessarios(10));
    printf("%d\n", converter_binario_decimal(numero_binario, bits_necessarios(10)));

    free(numero_binario);
    return 0;
}