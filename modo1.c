#include "ortografia.h"

void formalizarPalavras(char palavras[]) {
    int tamanho = strlen(palavras); // tamanho da palavra

    int count = 0;
    while (palavras[count] != '\0' && !((palavras[count] >= 'a' && palavras[count] <= 'z') || (palavras[count] >= 'A' && palavras[count] <= 'Z'))) {
        count++;
    }

    if (count != 0) {
        int tamanho = strlen(palavras);
        for (int i = 0; i < tamanho; i++) {
            palavras[i] = palavras[i + count];
        }
    }

    while (palavras[0] == '\'') {
        for (int i = 0; i < tamanho; i++) {
            palavras[i] = palavras[i + 1];
        }
        tamanho--;
    }

    while (palavras[tamanho - 1] == '\'') {
        palavras[tamanho - 1] = '\0';
        tamanho--;
    }
/*
    for (int i = 0; palavras[i] != '\0'; i++) {
        // Converte as letras maiusculas para minusculas
        if ((palavras[i] >= 32 && palavras[i] <= 38) || (palavras[i] >= 40 && palavras[i] <= 64) || (palavras[i] >= 91 && palavras[i] <= 96) || (palavras[i] >= 123 && palavras[i] <= 126)) {
            palavras[i] = '\0';
            tamanho--;
        }
    }
        */
}

int compararPalavras(char palavras[], char **words, int tamanhoDicionario, char ***palavrasErradas, int *nPalavrasErradas) {
    int resultado = FALSE;

    for (int i = 0; i < tamanhoDicionario; i++) {
        // Comparar as palavras
    
        //printf("%s %s\n", palavras, words[i]);
        // printf("%s %s\n", palavras, words[1]);
        if (strcasecmp(palavras, words[i]) == 0) {
            resultado = TRUE;
            break;
        }
    }
    
        if (resultado == FALSE) {
            *palavrasErradas = realloc(*palavrasErradas, (*nPalavrasErradas + 1) * sizeof(char *));

            (*palavrasErradas)[*nPalavrasErradas] = (char *)malloc(strlen(palavras) + 1);

            strcpy((*palavrasErradas)[*nPalavrasErradas], palavras);
            (*nPalavrasErradas)++;
            //printf("Palavra errada: %s\n", palavras);
        }
    

    return resultado;
}

// Separar as palavras da frase
int separarPalavras(char frase[], char **words, int tamanhoDicionario, int numeroLinhas, char fraseCopia[], char ***palavrasErrada, int *nPalavrasErradas, int modo, offsetPalavrasDicio *dicio, int valorA, int valorN) {
    char sinalSeparação[] = " -\t\r\n/";
    char *palavras = strtok(frase, sinalSeparação);
    int erro = FALSE;

    while (palavras != NULL) {
        formalizarPalavras(palavras); // chama a função para limpar as palavras
        // printf("%s\n", palavras);
        if (compararPalavras(palavras, words, tamanhoDicionario, palavrasErrada, nPalavrasErradas) == FALSE) {
            if (erro == FALSE) {
                printf("%d: %s", numeroLinhas, fraseCopia);
                erro = TRUE;
            }
            printf("Erro na palavra \"%s\"\n", palavras);

            if (modo == 2) {
                palavrasAlternativas(&((*palavrasErrada)[*nPalavrasErradas - 1]), words, 1, dicio, tamanhoDicionario, valorA, valorN);
            }
        }
        palavras = strtok(NULL, sinalSeparação);
    }
    return erro;
}