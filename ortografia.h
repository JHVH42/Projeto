#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void abrirDicionario(char ***words, int *tamanhoDicionario, char nomeficheiro[]);

void formalizarPalavras(char palavras[]);
int separarPalavras(char frase[], char **words, int tamanhoDicionario, int numeroLinhas, char fraseCopia[]);
int compararPalavras(char palavras[], char **words, int tamanhoDicionario);
