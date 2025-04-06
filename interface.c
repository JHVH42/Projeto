#include "ortografia.h"

void funcaomodo1(char **words, int tamanhoDicionario, char *dicionario, char *frase, char *fraseCopia, int numeroLinhas, FILE *ficheiroEntrada, int *nPalavrasErradas, char ***palavrasErradas, FILE *ficheiroSaida)
{
    size_t tamanhoFrase = 128;
    frase = (char *)malloc(tamanhoFrase * sizeof(char));
    if (frase == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para frase");
        return;
    }

    if (ficheiroEntrada == NULL) {
        fprintf(stderr, "Erro ao abrir o ficheiro de entrada");
        free(frase);
        return;
    }

    while (getline(&frase, &tamanhoFrase, ficheiroEntrada) != -1)
    {
        numeroLinhas++;
        fraseCopia = strdup(frase);
        if (fraseCopia == NULL)
        {
            fprintf(stderr, "Erro ao alocar memoria para fraseCopia\n");
            free(frase);
            return;
        }
        if (strcmp(frase, "\n") == 0)
        {
            free(fraseCopia);
            break;
        }
        separarPalavras(frase, words, tamanhoDicionario, numeroLinhas, fraseCopia, palavrasErradas, nPalavrasErradas);
        free(fraseCopia);
    }

    
    free(frase);
    frase = NULL;
}


void funcaomodo2(char **words, int tamanhoDicionario, char *dicionario, char *frase, char *fraseCopia, int numeroLinhas, FILE *ficheiroEntrada, int *nPalavrasErradas, char ***palavrasErradas, FILE *ficheiroSaida, offsetPalavrasDicio *dicio, int valorA, int valorN)
{
    funcaomodo1(words, tamanhoDicionario, dicionario, frase, fraseCopia, numeroLinhas, ficheiroEntrada, nPalavrasErradas, palavrasErradas, ficheiroSaida);
    printf("Palavras erradas: %d\n", *nPalavrasErradas);
    if (nPalavrasErradas != 0)
    {
        palavrasAlternativas(*palavrasErradas, words, *nPalavrasErradas, dicio, tamanhoDicionario, valorA, valorN);
    }
    for (int i = 0; i < *nPalavrasErradas; i++)
    {
        free((*palavrasErradas)[i]);
        (*palavrasErradas)[i] = NULL;
    }
    free(*palavrasErradas);
    *palavrasErradas = NULL;

    if (dicio != NULL)
    {
        free(dicio);
        dicio = NULL;
    }
}


void funcaochamafuncao(int valorM, int valorA, int valorN, char **words, int tamanhoDicionario, char *dicionario, char frase[300], char fraseCopia[300], int numeroLinhas, FILE *ficheiroEntrada, int *nPalavrasErradas, offsetPalavrasDicio *dicio, char ***palavrasErradas, FILE *ficheiroSaida)
{
    

    switch (valorM)
    {
    case 1:
        funcaomodo1(words, tamanhoDicionario, dicionario, frase, fraseCopia, numeroLinhas, ficheiroEntrada, nPalavrasErradas, palavrasErradas, ficheiroSaida);
        break;
    case 2:
        funcaomodo2(words, tamanhoDicionario, dicionario, frase, fraseCopia, numeroLinhas, ficheiroEntrada, nPalavrasErradas, palavrasErradas, ficheiroSaida, dicio, valorA, valorN);
        break;
    case 3:
        //funcaomodo3(valorA, valorN);
        break;
    }
}

void ajuda() {
    printf("Uso: ./ortografia [opções]\n");
    printf("Opções:\n");
    printf("  -h, --help    Mostrar esta mensagem de ajuda\n");
    printf("  -m <modo>     Selecionar o modo de funcionamento (1, 2 ou 3)\n");
    printf("  -a <valor>    Definir o valor A\n");
    printf("  -n <valor>    Definir o valor N\n");
}
