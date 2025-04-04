#include "ortografia.h"


int main() {
    int tamanhoDicionario = 0;
    char frase[300];
    char fraseCopia[300];
    char **words = (char **)malloc(100 * sizeof(char *));
    int numeroLinhas = 0;
    char nomeficheiro[50] = "words";


    abrirDicionario(&words, &tamanhoDicionario, nomeficheiro);

    while (fgets(frase, sizeof(frase), stdin) != NULL) {

        numeroLinhas++;
        if (strcmp(frase, "\n") == 0) {
            break;
        }
        strcpy(fraseCopia, frase);
        separarPalavras(frase, words, tamanhoDicionario, numeroLinhas, fraseCopia);
    }
    
    for (int i = 0; i < tamanhoDicionario; i++) {
        free(words[i]);
    }
    free(words);
    
    return 0;
}