#include "ortografia.h"

void abrirDicionario(char **words, int *tamanhoDicionario, char nomeficheiro[])
{
    FILE *dicionario = fopen(nomeficheiro, "r");
    if (dicionario == NULL)
    {
        printf("Erro ao abrir o dicionário.\n");
        exit(1);
    }

    // Lê o número de palavras no dicionário
    fscanf(dicionario, "%d", tamanhoDicionario);

    // Aloca memória para as palavras do dicionário
    *words = (char **)malloc((*tamanhoDicionario) * sizeof(char *));
    for (int i = 0; i < *tamanhoDicionario; i++)
    {
        (*words)[i] = (char *)malloc(100 * sizeof(char)); // Aloca espaço para cada palavra
        fscanf(dicionario, "%s", (*words)[i]); // Lê cada palavra
    }

    fclose(dicionario);
}