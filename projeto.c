#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LENGTH 100 // Maximum length of each name
#define INITIAL_SIZE 10     // Initial vector size

/*void ficheiroLimpar(const char *ficheiroLocalizacao)
{
    FILE *ficheiro = fopen(ficheiroLocalizacao, "r");
    if (!ficheiro)
    {
        printf("O ficheiro '%s' nao foi encontrado.\n", ficheiroLocalizacao);
        return;
    }
    // Abre o ficheiro

    FILE *temporario = fopen("temporario.txt", "w");
    if (!temporario)
    {
        printf("Nao foi possivel criar o ficheiro.\n");
        fclose(ficheiro);
        return;
    }
    // Cria um ficheiro temporario

    char linha[1024];
    while (fgets(linha, sizeof(linha), ficheiro))
    {
        size_t len = strlen(linha);
        while (len > 0 && (linha[len - 1] == ' ' || linha[len - 1] == '\t' || linha[len - 1] == '/'))
        {
            linha[--len] = '\0';
        }
        fprintf(temporario, "%s\n", linha);
    }
    // Procura nas palavras e remove os espacos, tabs e barras

    fclose(ficheiro);
    fclose(temporario);
    // Fecha os ficheiros

    remove(ficheiroLocalizacao);
    rename("temporario.txt", ficheiroLocalizacao);
    // Substitui o ficheiro original pelo corrigido
} */

void ficheiroMemoria(char **vetor, int *numPalavras)
{

    FILE *ficheiro = fopen("words", "r");
    if (!ficheiro)
    {
        printf("O ficheiro '%s' nao foi encontrado.\n", "words");
        return;
    }
    // Abre o ficheiro
    /*
    fseek(ficheiro, 0, SEEK_END);
    long ficheiroTamanho = ftell(ficheiro);
    rewind(ficheiro);
    */
    // char **vetor = (char *)realloc(ficheiroTamanho + 1);

    //*char=char[]
    //**char=*char[]=char[][]
    // Calcula o tamanho do ficheiro e volta ao inicio do ficheiro

    // char *vetor = (char *)malloc(ficheiroTamanho + 1);

    // Associa uma memoria dinamicamente ao vetor
    // fread(vetor, 1, 104335, ficheiro);

    printf("num %d\n", *numPalavras);
    char palavra[50];
    while (fscanf(ficheiro, "%49s", palavra) == 1)
    {
        vetor[*numPalavras] = (char *)malloc(strlen(palavra) + 1);
        strcpy(vetor[*numPalavras], palavra);
        (*numPalavras)++;
    }
    fclose(ficheiro);

    // Le o ficheiro, coloca o conteudo ao vetor e fecha o ficheiro
}
/*
char **read_names_from_file(const char *filename, int *count)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file");
        return NULL;
    }

    // Allocate initial memory for the vector

    char **vector = malloc(INITIAL_SIZE * sizeof(char *));
    if (!vector)
    {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    int capacity = INITIAL_SIZE;
    *count = 0;
    char buffer[MAX_NAME_LENGTH];

    // Read names from the file
    while (fgets(buffer, MAX_NAME_LENGTH, file))
    {
        // Remove newline character if present
        buffer[strcspn(buffer, "\n")] = '\0';

        // Resize array if needed
        if (*count >= capacity)
        {
            capacity *= 2;
            vector = realloc(vector, capacity * sizeof(char *));
            if (!vector)
            {
                perror("Memory reallocation failed");
                fclose(file);
                return NULL;
            }
        }

        // Allocate memory for the name and store it
        vector[*count] = malloc(strlen(buffer) + 1);
        if (!vector[*count])
        {
            perror("Memory allocation for name failed");
            fclose(file);
            return NULL;
        }
        strcpy(vector[*count], buffer);
        (*count)++;
    }

    fclose(file);
    return vector;
}
*/
void formalizarPalavras(char palavras[])
{
    int tamanho = strlen(palavras);

    while (palavras[0] == '\'')
    {
        for (int i = 0; i < tamanho; i++)
        {
            palavras[i] = palavras[i + 1];
        }
        tamanho--;
    }

    while (palavras[tamanho - 2] == '\'')
    {
        palavras[tamanho - 2] = '\0';
        tamanho--;
    }

    for (int i = 0; i < tamanho; i++)
    {
        // Converte as letras maiusculas para minusculas
        if (palavras[i] >= 'A' && palavras[i] <= 'Z')
        {
            palavras[i] += 32;
        }
        if ((palavras[i] >= 32 && palavras[i] <= 38) || (palavras[i] >= 40 && palavras[i] <= 96) || (palavras[i] >= 123 && palavras[i] <= 126))
        {
            palavras[i] = '\0';
        }
    }
}

void formalizarDicionario(char **vetor, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        char *palavras = vetor[i];
        while (*palavras)
        {
            if (*palavras >= 'A' && *palavras <= 'Z')
            {
                *palavras += 32;
            }
            palavras++;
        }
    }
}

void compararPalavras(char palavras[], char **vetor, int numPalavras)
{
    int resultado = 0;

    printf("我看看 %d\n", numPalavras);
    for (int i = 0; i < numPalavras; i++)
    {
        // printf("hello\n");
        // printf("%s\n", palavras);
    }

    for (int i = 0; i < numPalavras; i++)
    {
        // Comparar as palavras
        if (strcasecmp(palavras, vetor[i]) == 0)
        {
            resultado = 1;
            break;
        }
    }

    if (resultado == 1)
    {
        printf("A palavra existe no dicionario\n");
    }
    else
    {
        printf("A palavra %s nao existe no dicionario\n", palavras);
    }
    // Compara as palavras
}

// Separar as palavras da frase
void separarPalavras(char frase[], char **vetor, int tamanho)
{
    char sinalSeparação[] = " \t\r\n/";
    char *palavras = strtok(frase, sinalSeparação);

    while (palavras != NULL)
    {
        formalizarPalavras(palavras); // chama a função para limpar as palavras
        // printf("%s\n", palavras);
        printf("让我看看 %s", palavras);
        compararPalavras(palavras, vetor, tamanho);
        palavras = strtok(NULL, sinalSeparação);
    }
}

int main()
{
    int *tamanho;
    char frase[300];
    char fraseCopia[300];
    char **vetor = (char **)malloc(104335 * sizeof(char *));

    *tamanho = 0;

    ficheiroMemoria(vetor, tamanho);

    for (int i = 0; i < 1; i++)
    {
        printf("%d %s\n", i + 1, vetor[i]);
    }

    printf("Insere a frase\n");
    fgets(frase, sizeof(frase), stdin); // ler a frase

    strcpy(fraseCopia, frase);

    printf("separar zhiqian %d\n", *tamanho);
    separarPalavras(frase, vetor, *tamanho);

    // printf("%s\n", fraseCopia);
    //  compararPalavras(frase, ficheiroMemoria("word.txt"));

    // compararPalavras(frase, vetor, tamanho);

    for (int i = 0; i < *tamanho; i++)
    {
        free(vetor[i]);
    }
    free(vetor);
    return 0;
}

