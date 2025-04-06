#include "ortografia.h"

static int levenshteinDistance(const char *s1, const char *s2)
{
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    // 创建 DP 数组
    int *prev = (int *)malloc((len2 + 1) * sizeof(int));
    int *curr = (int *)malloc((len2 + 1) * sizeof(int));

    if (!prev || !curr)
    {
        fprintf(stderr, "Erro ao alocar memoria para Levenshtein\n");
        free(prev);
        free(curr);
        return len1 > len2 ? len1 : len2; // 应急返回一个较大值
    }

    // 初始化第一行
    for (int j = 0; j <= len2; j++)
    {
        prev[j] = j;
    }

    // 填充 DP
    for (int i = 1; i <= len1; i++)
    {
        curr[0] = i;
        for (int j = 1; j <= len2; j++)
        {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            int del = prev[j] + 1;
            int ins = curr[j - 1] + 1;
            int rep = prev[j - 1] + cost;
            curr[j] = (del < ins ? (del < rep ? del : rep) : (ins < rep ? ins : rep));
        }
        // 交换 row
        int *temp = prev;
        prev = curr;
        curr = temp;
    }

    int distance = prev[len2];
    free(prev);
    free(curr);
    return distance;
}

void palavrasAlternativas(char **palavrasErradas, char **words, int nPalavrasErradas, offsetPalavrasDicio *dicio, int TamanhoDicionario, int valorA, int valorN) {
    int offsetDesejado = valorN;
    int maximoAlternativas = valorA;

    for (int i = 0; i < TamanhoDicionario; i++) {
        dicio[i].palavraDoDicio = words[i];
        dicio[i].offset = 0; }

    for (int i = 0; i < nPalavrasErradas; i++) {
        for (int j = 0; j < TamanhoDicionario; j++) {
            dicio[j].offset = 0; }
            for (int j = 0; j < TamanhoDicionario; j++){
                int offset = levenshteinDistance(palavrasErradas[i], dicio[j].palavraDoDicio);
                dicio[j].offset = offset;
            }
            
            for (int x = 0; x < TamanhoDicionario - 1; x++) {
                for (int y = 0; y < TamanhoDicionario - x - 1; y++) {
                    if (dicio[y].offset > dicio[y + 1].offset || (dicio[y].offset == dicio[y + 1].offset && strcasecmp(dicio[y].palavraDoDicio, dicio[y + 1].palavraDoDicio) > 0))
                    {
                        offsetPalavrasDicio temp = dicio[y];
                        dicio[y] = dicio[y + 1];
                        dicio[y + 1] = temp;
                    }
                }
            }
            int count = 0;
            for (int j = 0; j < TamanhoDicionario; j++){
                if (dicio[j].offset <= offsetDesejado) {
                    printf("%s %d ", dicio[j].palavraDoDicio, dicio[j].offset);

                    count++;
                }
                if (count >= maximoAlternativas) {
                    break;
                }
            }
        }
        printf("\n");
}