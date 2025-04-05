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

    for (int i = 0; palavras[i] != '\0'; i++) {
        // Converte as letras maiusculas para minusculas
        if ((palavras[i] >= 32 && palavras[i] <= 38) || (palavras[i] >= 40 && palavras[i] <= 64) || (palavras[i] >= 91 && palavras[i] <= 96) || (palavras[i] >= 123 && palavras[i] <= 126)) {
            palavras[i] = '\0';
            tamanho--;
        }
    }
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
        } else if (strcasecmp(palavras, words[i]) != 0) {
            resultado == FALSE;
            //palavrasErradas[i] = palavras[i];
            palavrasErradas[i] = (char *)malloc(strlen(palavras) + 1);
            strcpy(palavrasErradas[i], palavras);
            //printf("Palavra errada: %s\n", palavras);
            *nPalavrasErradas++;
        }
    }

    return resultado;
}

// Separar as palavras da frase
int separarPalavras(char frase[], char **words, int tamanhoDicionario, int numeroLinhas, char fraseCopia[], char ***palavrasErrada, int *nPalavrasErradas) {
    char sinalSeparação[] = " -\t\r\n/";
    char *palavras = strtok(frase, sinalSeparação);
    int erro = FALSE;
    while (palavras != NULL) {
    
        formalizarPalavras(palavras); // chama a função para limpar as palavras
        // printf("%s\n", palavras);
        if (compararPalavras(palavras, words, tamanhoDicionario, &palavrasErradas, &nPalavrasErradas) == 0) {
            if (erro == FALSE) {
                printf("%d: %s", numeroLinhas, fraseCopia);
                erro = TRUE;
            }
            printf("Erro na palavra \"%s\"\n", palavras);
        }
        palavras = strtok(NULL, sinalSeparação);
    }
    return erro;
}