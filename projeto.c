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

void ficheiroMemoria(char vetor[][50], int *numPalavras) {
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
    //Calcula o tamanho do ficheiro e volta ao inicio do ficheiro

     //char *vetor = (char *)malloc(ficheiroTamanho + 1);

      
      //Associa uma memoria dinamicamente ao vetor
     //fread(vetor, 1, 104335, ficheiro);

    char palavra[40];
    *numPalavras = 0;
     while (fscanf(ficheiro, "%39s", palavra) == 1)
    {
     strcpy(vetor[*numPalavras], palavra);
    (*numPalavras) ++;
    }
    fclose(ficheiro);
    //Le o ficheiro, coloca o conteudo ao vetor e fecha o ficheiro
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

// Separar as palavras da frase
void separarPalavras(char frase[])
{
    char sinalSeparação[] = " \t\r\n/";
    char *palavras = strtok(frase, sinalSeparação);

    while (palavras != NULL)
    {
        formalizarPalavras(palavras); // chama a função para limpar as palavras
        printf("%s\n", palavras);
        palavras = strtok(NULL, sinalSeparação);
    }
}

void compararPalavras(char palavras[], char vetor[])
{
    for (int i = 0; i < strlen(palavras); i++)
    {
        // Comparar as palavras
        if (palavras[i] != vetor[i])
        {
            printf("As palavras nao são iguais\n");
        }
    }
    // Compara as palavras
}

int main()
{
    int tamanho;
    char frase[300];
    char fraseCopia[300];
    char vetor[104335][50];
    // int numPalavras;
    //char **vetor = read_names_from_file("words", &tamanho);

    ficheiroMemoria(vetor, &tamanho);

    for (int i = 0; i < 20; i++)
    {
        printf("%s\n", vetor[i]);
    }
    printf("Insere a frase\n");
    fgets(frase, sizeof(frase), stdin); // ler a frase

    // printf("%d\n", strlen(frase));
    strcpy(fraseCopia, frase);

    separarPalavras(frase);

    printf("%s\n", fraseCopia);
    // compararPalavras(frase, ficheiroMemoria("word.txt"));

    return 0;
}
