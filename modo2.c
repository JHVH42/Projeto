#include "ortografia.h"

void palavrasAlternativas(char **palavrasErradas, char **words, int nPalavrasErradas, offsetPalavrasDicio *dicio, int TamanhoDicionario) {
    for (int i = 0; i < TamanhoDicionario; i++)  {
        dicio[i].palavraDoDicio = words[i];
        dicio[i].offset = 0;
    }

    for (int i = 0; i < nPalavrasErradas; i++) {
        for (int j = 0; j < TamanhoDicionario; j++) {
            //int k = 0;
            int offset = 0;

            for (int k = 0; palavrasErradas[i][k] != '\0' && dicio[j].palavraDoDicio[k] != '\0'; k++) {
                if (palavrasErradas[i][k] != dicio[j].palavraDoDicio[k]) {
                    offset++;
                }
    
            }
            offset += abs(strlen(palavrasErradas[i]) - strlen(dicio[j].palavraDoDicio));
            dicio[j].offset = offset;
        }
    }

    int offsetDesejado = 2;
    for (int i = 0; i < TamanhoDicionario; i++) {
        //printf("%s %d\n", dicio[i].palavraDoDicio, dicio[i].offset);
        if (dicio[i].offset == offsetDesejado) {
            printf("%s ", dicio[i].palavraDoDicio);
        }
    }
}