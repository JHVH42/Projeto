#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#define TRUE 1
#define FALSE 0


typedef struct {
    char *palavraDoDicio;
    int offset;
} offsetPalavrasDicio;


void abrirDicionario(char ***words, int *tamanhoDicionario, char nomeficheiro[]);

void formalizarPalavras(char palavras[]);

int separarPalavras(char frase[], char **words, int tamanhoDicionario, int numeroLinhas, char fraseCopia[], char ***palavrasErradas, int *nPalavrasErradas);

int compararPalavras(char palavras[], char **words, int tamanhoDicionario, char ***palavrasErradas, int *nPalavrasErradas);


void palavrasAlternativas(char **palavrasErradas, char **words, int nPalavrasErradas, offsetPalavrasDicio *dicio, int TamanhoDicionario);