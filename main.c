#include "ortografia.h"

int main() {
    int tamanhoDicionario = 0;
    char frase[300];
    char fraseCopia[300];
    char **words = NULL;
    int numeroLinhas = 0;
    char *nomeficheiro = "words";
    char **palavrasErradas = NULL;
    int nPalavrasErradas = 0;
    offsetPalavrasDicio *dicio = NULL;

        abrirDicionario(&words, &tamanhoDicionario, nomeficheiro);
    //printf("%d\n", tamanhoDicionario);
    if(tamanhoDicionario > 0) {
        dicio = malloc(tamanhoDicionario * sizeof(offsetPalavrasDicio));
        if (dicio == NULL) {
            fprintf(stderr, "Erro ao alocar memoria para decio");
            return 1;
        }
    } else {
        fprintf(stderr, "Erro: TamanhoDicionario = 0");
        return 1;
    }

    while (fgets(frase, sizeof(frase), stdin) != NULL) {

        numeroLinhas++;
        if (strcmp(frase, "\n") == 0) {
            break;
        }
        strcpy(fraseCopia, frase);
        separarPalavras(frase, words, tamanhoDicionario, numeroLinhas, fraseCopia, &palavrasErradas, &nPalavrasErradas);
    }

    printf("Palavras erradas: %d\n", nPalavrasErradas);
    for (int i = 0; i < nPalavrasErradas; i++) {
        printf("%s\n", palavrasErradas[i]);
    }

    if (nPalavrasErradas != 0) {
        palavrasAlternativas(palavrasErradas, words, nPalavrasErradas, dicio, tamanhoDicionario);
    }

    free(dicio);
    for (int i = 0; i < tamanhoDicionario; i++) {
        free(words[i]);
    }
    free(words);

    for (int i = 0; i < nPalavrasErradas; i++) {
        free(palavrasErradas[i]);
    }
    free(palavrasErradas);

    return 0;
}