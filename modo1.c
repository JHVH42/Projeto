#include "ortografia.h"

void formalizarPalavras(char palavras[]) {
    if (palavras == NULL || palavras[0] == '\0')
    {
        return;
    }
    
    int tamanho = strlen(palavras);
    int count = 0;

    while (palavras[count] != '\0' && !isalpha(palavras[count])) {
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
        if ((palavras[i] >= 32 && palavras[i] <= 38) || (palavras[i] >= 40 && palavras[i] <= 64) || (palavras[i] >= 91 && palavras[i] <= 96) || (palavras[i] >= 123 && palavras[i] <= 126)) {
            palavras[i] = '\0';
            tamanho--;
        }
    }
}


int compararPalavras(char palavras[], char **words, int tamanhoDicionario, char ***palavrasErradas, int *nPalavrasErradas) {
    int existe = FALSE;

    for (int i = 0; i < tamanhoDicionario; i++) {
        if (strcasecmp(palavras, words[i]) == 0) {
            existe = TRUE;
            break;
        }
    }

    if (existe == FALSE) {
        *palavrasErradas = realloc(*palavrasErradas, (*nPalavrasErradas + 1) * sizeof(char *));
        
        (*palavrasErradas)[*nPalavrasErradas] = (char *)malloc(strlen(palavras) + 1);
        
        strcpy((*palavrasErradas)[*nPalavrasErradas], palavras);
        (*nPalavrasErradas)++;
        //printf("Palavra errada: %s\n", palavras);
    }
    
    return existe;
}

// Separar as palavras da frase
int separarPalavras(char *frase, char **words, int tamanhoDicionario, int numeroLinhas, char *fraseCopia, char ***palavrasErrada, int *nPalavrasErradas, int modo, offsetPalavrasDicio *dicio, int valorA, int valorN) {
    char sinalSeparação[] = " -\t\r\n/";
    char *palavras = strtok(frase, sinalSeparação);
    int erro = FALSE;

    while (palavras != NULL) {
        formalizarPalavras(palavras); // chama a função para limpar as palavras
        //printf("%s\n", palavras);
        if (compararPalavras(palavras, words, tamanhoDicionario, palavrasErrada, nPalavrasErradas) == FALSE) {
            if (erro == FALSE) {
                printf("%d: %s", numeroLinhas, fraseCopia);
                erro = TRUE;
            }
            printf("Erro na palavra \"%s\"\n", palavras);
            
            
            if (modo == 2) {
                for (int i = 0; i < *nPalavrasErradas; i++) {
                    if (strcasecmp(palavras, (*palavrasErrada)[i]) == 0) {
                        palavrasAlternativas(&((*palavrasErrada)[i]), words, 1, dicio, tamanhoDicionario, valorA, valorN);
                        break;
                    }
                }
            }
        }
        palavras = strtok(NULL, sinalSeparação);
    }
    return erro;
}