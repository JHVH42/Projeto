#include "ortografia.h"

int main(int argc, char *argv[]) {
    int tamanhoDicionario = 0;
    char *frase = NULL;
    char *fraseCopia = NULL;
    char **words = NULL;
    int numeroLinhas = 0;
    char *nomeficheiro = "words";
    char **palavrasErradas = NULL;
    int nPalavrasErradas = 0;
    offsetPalavrasDicio *dicio = NULL;
    ssize_t tamanhoFrase = 0;
/*
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

    while (getline(&frase, &tamanhoFrase, stdin) != -1) {
        numeroLinhas++;
        fraseCopia = strdup(frase);
        if (fraseCopia == NULL) {
            fprintf(stderr, "Erro ao alocar memoria para fraseCopia");
            free(frase);
            free(dicio);
            return 1;
        }
        if (strcmp(frase, "\n") == 0) {
            free(fraseCopia);
            break;
        }
        separarPalavras(frase, words, tamanhoDicionario, numeroLinhas, fraseCopia, &palavrasErradas, &nPalavrasErradas);
        free(fraseCopia);
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
    free(frase);
*/

    FILE *ficheiroEntrada = stdin;
    FILE *ficheiroSaida = stdout;
    char *dicionario = "words";
    int valorA = 10, valorN = 2, valorM = 1;

    int opt;

    abrirDicionario(&words, &tamanhoDicionario, dicionario);
    if (tamanhoDicionario > 0)
    {
        dicio = malloc(tamanhoDicionario * sizeof(offsetPalavrasDicio));
        if (dicio == NULL)
        {
            fprintf(stderr, "Erro ao alocar memoria para decio");
            return 1;
        }
    }
    else
    {
        fprintf(stderr, "Erro: TamanhoDicionario = 0");
        return 1;
    }

    if (argc == 1) {
        funcaochamafuncao(valorM, valorA, valorN, words, tamanhoDicionario, dicionario, frase, fraseCopia, numeroLinhas, ficheiroEntrada, &nPalavrasErradas, dicio, &palavrasErradas, ficheiroSaida);
    }
    /*Edge case para quando nao houver argumentos
    por exemplo "./ortografia.c"*/

    while ((opt = getopt(argc, argv, ":h:i:o:d:a:n:m:")) != -1) {
        switch (opt) {
            case 'h':
                ajuda();
                break;
            case 'i':
            // Nome do ficheiro de entrada, em alternativa a stdin (frases de input de comando)
                ficheiroEntrada = fopen(optarg, "r");
                if (ficheiroEntrada == NULL)
                {
                    return EXIT_FAILURE;
                }
                break;
            case 'o':
            // Nome do ficheiro de saida, em alternativa a stdout (correcoes output)
                ficheiroSaida = fopen(optarg, "w+");
                if (ficheiroSaida == NULL)
                {
                    return EXIT_FAILURE;
                }
                break;
            case 'd':
            // Nome do ficheiro de dicionario
                dicionario = optarg;
                break;
            case 'a':
            

            // O nr maximo de alternativas com cada erro ortografico
                valorA = atoi(optarg);
                if (valorA < 0)
                {
                    return EXIT_FAILURE;
                }
                break;
            case 'n':
            
            // O nr maximo de diferencas com cada erro ortografico
                valorN = atoi(optarg);
                if (valorN < 0)
                {
                    return EXIT_FAILURE;
                }
                break;
            case 'm':
            // O modo de funcionamento 1, 2 ou 3
                valorM = atoi(optarg);
                if (valorM < 1 || valorM > 3)
                {
                    return EXIT_FAILURE;
                }
                break;
            default:
                return EXIT_FAILURE;
            }
        }

    funcaochamafuncao(valorM, valorA, valorN, words, tamanhoDicionario, dicionario, frase, fraseCopia, numeroLinhas, ficheiroEntrada, &nPalavrasErradas, dicio, &palavrasErradas, ficheiroSaida);

    fclose(ficheiroEntrada);
    fclose(ficheiroSaida);

    for (int i = 0; i < nPalavrasErradas; i++)
    {
        free((palavrasErradas)[i]);
        (palavrasErradas)[i] = NULL;
    }
    if (palavrasErradas != NULL)
    {
        free(palavrasErradas);
    }

    if (dicio != NULL)
    {
        free(dicio);
        dicio = NULL;
    }
    free(frase);
    free(fraseCopia);

    for (int i = 0; i < tamanhoDicionario; i++)
    {
        free(words[i]);
    }
    free(words);

    return 0;
}