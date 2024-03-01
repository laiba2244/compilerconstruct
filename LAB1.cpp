#include <string.h>
#include <ctype.h>
#include <stdio.h>

void classifyToken(char str[10]) {
    if (strcmp("for", str) == 0 || strcmp("while", str) == 0 || strcmp("do", str) == 0 ||
        strcmp("int", str) == 0 || strcmp("float", str) == 0 || strcmp("char", str) == 0 ||
        strcmp("double", str) == 0 || strcmp("static", str) == 0 || strcmp("switch", str) == 0 ||
        strcmp("case", str) == 0) {
        printf("| %-10s | Keyword          |\n", str);
    } else {
        printf("| %-10s | Identifier       |\n", str);
    }
}

void classifyOperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
        printf("| %-10c | Arithmetic Op.   |\n", c);
    } else if (c == '=' || c == '<' || c == '>') {
        char nextChar = getchar();
        if (nextChar == '=') {
            printf("| %-10c%c | Relational Op.   |\n", c, nextChar);
        } else {
            printf("| %-10c | Assignment Op.   |\n", c);
            ungetc(nextChar, stdin);
        }
    } else if (c == '&' || c == '|') {
        char nextChar = getchar();
        if (nextChar == c) {
            printf("| %-10c%c | Logical Op.      |\n", c, nextChar);
        } else {
            printf("| %-10c | Invalid Operator |\n", c);
            ungetc(nextChar, stdin);
        }
    }
}

int main() {
    char c;
    char str[10];
    int num[100], lineno = 0, tokenvalue = 0, i = 0, j = 0, k = 0;
    int inComment = 0;

    printf("Enter the C program:\n");

    printf("\n| Token     | Classification   |\n");
    printf("|-----------|-------------------|\n");

    while ((c = getchar()) != EOF) {
        // Ignore comments
        if (c == '/' && (c = getchar()) == '*') {
            inComment = 1;
            continue;
        } else if (c == '*' && (c = getchar()) == '/') {
            inComment = 0;
            continue;
        }

        if (inComment) {
            continue; // Skip characters inside comments
        }

        if (isalnum(c) || c == '_') {
            k = 0;
            str[k++] = c;

            while ((c = getchar()) && (isalnum(c) || c == '_') && k < 10 - 1) {
                str[k++] = c;
            }
            str[k] = '\0';
            ungetc(c, stdin);

            classifyToken(str);
        } else if (isdigit(c)) {
            tokenvalue = c - '0';
            c = getchar();
            while (isdigit(c)) {
                tokenvalue = tokenvalue * 10 + c - '0';
                c = getchar();
            }
            num[i++] = tokenvalue;
            ungetc(c, stdin);
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=' || c == '<' || c == '>') {
            classifyOperator(c);
        } else if (c == '&' || c == '|') {
            classifyOperator(c);
        } else if (c == ' ' || c == '\t') {
            // Skip spaces and tabs
        } else if (c == '\n') {
            lineno++;
        } else {
            printf("| %-10c | Special Character |\n", c);
        }
    }

    printf("\n| The no's in the program are");
    for (j = 0; j < i; j++)
        printf("%d ", num[j]);

    printf("\n| Total no. of lines are: %d\n", lineno);

    return 0;
}

