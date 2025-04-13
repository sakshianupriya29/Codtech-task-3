#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char keywords[32][10] = {
    "auto","break","case","char","const","continue","default","do","double",
    "else","enum","extern","float","for","goto","if","int","long","register",
    "return","short","signed","sizeof","static","struct","switch","typedef",
    "union","unsigned","void","volatile","while"
};

int isKeyword(char *word) {
    for (int i = 0; i < 32; i++) {
        if (strcmp(keywords[i], word) == 0)
            return 1;
    }
    return 0;
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
            ch == '=' || ch == '<' || ch == '>' || ch == '%');
}

void analyzeFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    char ch, word[100];
    int i;

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\n--- Lexical Analysis Output ---\n");

    while ((ch = fgetc(file)) != EOF) {
        // Skip whitespace
        if (isspace(ch))
            continue;

        // Identifier or Keyword
        if (isalpha(ch)) {
            i = 0;
            word[i++] = ch;
            while ((ch = fgetc(file)) != EOF && (isalnum(ch) || ch == '_'))
                word[i++] = ch;
            word[i] = '\0';
            ungetc(ch, file); // put back the character

            if (isKeyword(word))
                printf("Keyword: %s\n", word);
            else
                printf("Identifier: %s\n", word);
        }
        // Operator
        else if (isOperator(ch)) {
            printf("Operator: %c\n", ch);
        }
        // Numbers (optional enhancement)
        else if (isdigit(ch)) {
            i = 0;
            word[i++] = ch;
            while ((ch = fgetc(file)) != EOF && isdigit(ch))
                word[i++] = ch;
            word[i] = '\0';
            ungetc(ch, file);
            printf("Number: %s\n", word);
        }
    }

    fclose(file);
}
    
int main() {
    char filename[100];

    printf("Enter the name of the input file: ");
    scanf("%s", filename);

    analyzeFile(filename);

    return 0;
}
