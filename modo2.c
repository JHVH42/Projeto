#include "ortografia.h"

void palavrasAlternativas(char **palavrasErradas, char **words, int nPalavrasErradas, offsetPalavrasDicio *dicio, int TamanhoDicionario) {
    for (int i = 0; i < TamanhoDicionario; i++)  {
        dicio[i].palavraDoDicio = words[i];
        dicio[i].offset = 0;
    }

    for (int i = 0; i < nPalavrasErradas; i++) {
        for (int j = 0; j < TamanhoDicionario; j++) {
            dicio[j].offset = strcspn(palavrasErradas[i], dicio[j].palavraDoDicio);
        }
    }

    int offset = 2;
    for (int i = 0; i < TamanhoDicionario; i++) {
        if (dicio[i].offset == offset) {
            printf("%s ", dicio[i].palavraDoDicio);
        }
    }
}