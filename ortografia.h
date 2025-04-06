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


void palavrasAlternativas(char **palavrasErradas, char **words, int nPalavrasErradas, offsetPalavrasDicio *dicio, int TamanhoDicionario, int valorA, int valorN);

void funcaochamafuncao(int valorM, int valorA, int valorN, char **words, int tamanhoDicionario, char *dicionario, char *frase, char *fraseCopia, int numeroLinhas, FILE *ficheiroEntrada, int *nPalavrasErradas, offsetPalavrasDicio *dicio, char ***palavrasErradas, FILE *ficheiroSaida);
/*Esta função deve chamar a função de modo de funcionamento 1
2 ou 3 dependendo do qual input de valorM for*/

void funcaomodo1(char **words, int tamanhoDicionario, char *dicionario, char frase[300], char fraseCopia[300], int numeroLinhas, FILE *ficheiroEntrada, int *nPalavrasErradas, char ***palavrasErradas, FILE *ficheiroSaida);
/*Esta função recebe os parametros e usa os para fazer o modo
de funcionamento 1*/

void funcaomodo2(char **words, int tamanhoDicionario, char *dicionario, char *frase, char *fraseCopia, int numeroLinhas, FILE *ficheiroEntrada, int *nPalavrasErradas, char ***palavrasErradas, FILE *ficheiroSaida, offsetPalavrasDicio *dicio, int valorA, int valorN);
/*Esta função recebe os valorA e valorN e usa para se fazer o
modo de funcionamento 2*/

void ajuda();