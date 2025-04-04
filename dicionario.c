#include "ortografia.h"

void abrirDicionario(char ***words, int *tamanhoDicionario, char nomeficheiro[]) {

    FILE *ficheiro = fopen(nomeficheiro, "r");
    if (!ficheiro) {
        printf("O ficheiro '%s' nao foi encontrado.\n", nomeficheiro);
        return;
    }

    char palavra[50];
    while (fscanf(ficheiro, "%s", palavra) == 1) {
        //printf("%s %d\n", palavra, *tamanhoDicionario);
        char **temp = (char **)realloc(*words, (*tamanhoDicionario + 1) * sizeof(char *));
        if (temp == NULL) {
            printf("Erro ao alocar memoria.\n");
            fclose(ficheiro);
            return;
        }
        *words = temp;
        (*words)[*tamanhoDicionario] = (char *)malloc(strlen(palavra) + 1);
        strcpy((*words)[*tamanhoDicionario], palavra);
        (*tamanhoDicionario)++;
    }
    fclose(ficheiro);
}