#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// abrir o diciionario e guardar as palavras no vetor
void abrirDicionario(char **words, int *tamanhoDicionario) {

    FILE *ficheiro = fopen("words", "r");
    if (!ficheiro) {
        printf("O ficheiro '%s' nao foi encontrado.\n", "words");
        return;
    }

    char palavra[50];
    while (fscanf(ficheiro, "%s", palavra) == 1) {
        words[*tamanhoDicionario] = (char *)malloc(strlen(palavra) + 1);
        strcpy(words[*tamanhoDicionario], palavra);
        (*tamanhoDicionario)++;
    }
    fclose(ficheiro);

    // Le o ficheiro, coloca o conteudo ao vetor e fecha o ficheiro
}

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
    /*
    for (int i = 0, count = 1; !(palavras[i] >= 'a' && palavras[i] <= 'z'); i++, count++) 
        printf("%d\n", count);

    for (int i = 0; palavras[i] != '\0'; i++) {
        for (int j = 0; j != count; j++) {
            palavras[j] = palavras[j + 1];
        }
        //palavras[i] = palavras[i + count];

    }

    tamanho -= count;
    */
    //printf("%s\n", palavras);
    
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
        
        if ((palavras[i] >= 32 && palavras[i] <= 38) || (palavras[i] >= 40 && palavras[i] <= 64) ||(palavras[i]  >= 91 && palavras[i] <= 96) || (palavras[i] >= 123 && palavras[i] <= 126)) {
            palavras[i] = '\0';
            tamanho--;
        }
    }
}



int compararPalavras(char palavras[], char **words, int tamanhoDicionario) {
    int resultado = 0;

    for (int i = 0; i < tamanhoDicionario; i++) {
        // Comparar as palavras
        if (strcasecmp(palavras, words[i]) == 0) {
            resultado = 1;
            break;
        }
    }

    if (resultado == 0) {
        // printf("A palavra %s nao existe no dicionario\n", palavras);
        resultado = 0;
    }
    // Compara as palavras
    return resultado;
}

// Separar as palavras da frase
int separarPalavras(char frase[], char **words, int tamanhoDicionario, int numeroLinhas, char fraseCopia[]) {
    char sinalSeparação[] = " -\t\r\n/";
    char *palavras = strtok(frase, sinalSeparação);
    int erro = 0;

    while (palavras != NULL) {
        formalizarPalavras(palavras); // chama a função para limpar as palavras
        // printf("%s\n", palavras);
        if (compararPalavras(palavras, words, tamanhoDicionario) == 0) {
            if (erro == 0) {
                printf("%d: %s", numeroLinhas, fraseCopia);
                erro = 1;
            }
            printf("Erro na palavra \"%s\"\n", palavras);
        }
        palavras = strtok(NULL, sinalSeparação);
    }
    return erro;
}

int main() {
    int *tamanhoDicionario = (int *)malloc(sizeof(int));
    char frase[300];
    char fraseCopia[300];
    char **words = (char **)malloc(104335 * sizeof(char *));
    int numeroLinhas = 0;

    *tamanhoDicionario = 0;

    abrirDicionario(words, tamanhoDicionario);

    // verificar se todas as palavras do dicionario estao no words
    // é para retirar no final!!!!!
    /*
    for (int i = 0; i < 1; i++) {
        printf("%d %s\n", i + 1, words[i]);
    }
    */
    //printf("Insere a frase\n");
    
    
    while (fgets(frase, sizeof(frase), stdin) != NULL) {
        
        numeroLinhas++;
        if (strcmp(frase, "\n") == 0)
        {
            break;
        }
        strcpy(fraseCopia, frase);
        //printf("%d: %s", numeroLinhas, fraseCopia);
        separarPalavras(frase, words, *tamanhoDicionario, numeroLinhas, fraseCopia);
    }


    /*
    if (fgets(frase, sizeof(frase), stdin) == NULL) {
        return 0;
    }
    */


    

    for (int i = 0; i < *tamanhoDicionario; i++) {
        free(words[i]);
    }
    free(words);
    free(tamanhoDicionario);

    return 0;
}
