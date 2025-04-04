#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

void tokenize(const char *text, char tokens[][MAX_WORD_LENGTH], int *count) {
    const char *delimiter = " ,.!?;\n";
    char temp[MAX_WORDS * MAX_WORD_LENGTH];
    char *token;

    strcpy(temp, text);
    token = strtok(temp, delimiter);
    *count = 0;

    while (token != NULL) {
        strcpy(tokens[*count], token);
        (*count)++;
        token = strtok(NULL, delimiter);
    }
}

void to_lowercase(char tokens[][MAX_WORD_LENGTH], int count) {
    int i, j;
    for (i = 0; i < count; i++) {
        for (j = 0; tokens[i][j] != '\0'; j++) {
            tokens[i][j] = tolower(tokens[i][j]);
        }
    }
}

int is_stopword(const char *word, const char *stopwords[], int stopword_count) {
    int i;
    for (i = 0; i < stopword_count; i++) {
        if (strcmp(word, stopwords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void remove_stopwords(char tokens[][MAX_WORD_LENGTH], int *count, const char *stopwords[], int stopword_count) {
    int i, new_count = 0;
    for (i = 0; i < *count; i++) {
        if (!is_stopword(tokens[i], stopwords, stopword_count)) {
            strcpy(tokens[new_count], tokens[i]);
            new_count++;
        }
    }
    *count = new_count;
}

void stem_tokens(char tokens[][MAX_WORD_LENGTH], int count) {
    const char *suffixes[] = {"ing", "ed", "s"};
    int suffix_count = sizeof(suffixes) / sizeof(suffixes[0]);
    int i, j;

    for (i = 0; i < count; i++) {
        int len = strlen(tokens[i]);
        for (j = 0; j < suffix_count; j++) {
            int suffix_len = strlen(suffixes[j]);
            if (len > suffix_len && strcmp(&tokens[i][len - suffix_len], suffixes[j]) == 0) {
                tokens[i][len - suffix_len] = '\0';
                break;
            }
        }
    }
}

void generate_ngrams(char tokens[][MAX_WORD_LENGTH], int count, int n, char ngrams[][MAX_WORD_LENGTH], int *ngram_count) {
    int i, j;
    *ngram_count = 0;

    for (i = 0; i <= count - n; i++) {
        char ngram[MAX_WORD_LENGTH * n];
        ngram[0] = '\0';

        for (j = 0; j < n; j++) {
            strcat(ngram, tokens[i + j]);
            if (j < n - 1) {
                strcat(ngram, " ");
            }
        }

        strcpy(ngrams[*ngram_count], ngram);
        (*ngram_count)++;
    }
}

int main() {
    char text[] = "VScode is great, but I am editing in DevC++";
    char tokens[MAX_WORDS][MAX_WORD_LENGTH];
    char ngrams[MAX_WORDS][MAX_WORD_LENGTH];
    const char *stopwords[] = {"is", "but", "can", "be", "too"};
    int stopword_count = sizeof(stopwords) / sizeof(stopwords[0]);
    int token_count, ngram_count, i;

    tokenize(text, tokens, &token_count);
    printf("Tokens:\n");
    for (i = 0; i < token_count; i++) {
        printf("%s ", tokens[i]);
    }
    printf("\n");

    to_lowercase(tokens, token_count);
    printf("\nLowercase Tokens:\n");
    for (i = 0; i < token_count; i++) {
        printf("%s ", tokens[i]);
    }
    printf("\n");

    remove_stopwords(tokens, &token_count, stopwords, stopword_count);
    printf("\nTokens after Stopword Removal:\n");
    for (i = 0; i < token_count; i++) {
        printf("%s ", tokens[i]);
    }
    printf("\n");

    stem_tokens(tokens, token_count);
    printf("\nTokens after Stemming:\n");
    for (i = 0; i < token_count; i++) {
        printf("%s ", tokens[i]);
    }
    printf("\n");

    generate_ngrams(tokens, token_count, 2, ngrams, &ngram_count);
    printf("\nBigrams:\n");
    for (i = 0; i < ngram_count; i++) {
        printf("%s\n", ngrams[i]);
    }

    return 0;
}
