#include "ortografia.h"

void abrirDicionario(char **words, int *tamanhoDicionario) {

    FILE *ficheiro = fopen("words", "r");
    if (!ficheiro)
    {
        printf("O ficheiro '%s' nao foi encontrado.\n", "words");
        return;
    }

    char palavra[50];
    while (fscanf(ficheiro, "%s", palavra) == 1)
    {
        words[*tamanhoDicionario] = (char *)malloc(strlen(palavra) + 1);
        strcpy(words[*tamanhoDicionario], palavra);
        (*tamanhoDicionario)++;
    }
    fclose(ficheiro);
}