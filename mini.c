#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// My own smallest inplemetation of brainfuck in c

void interpret(char* input) {
    unsigned char tape[30000] = {0};
    unsigned char* ptr = tape;
    char currentChar;

    int i;

    for (i = 0; input[i] != 0; i++) {
        currentChar = input[i];

        switch (currentChar) {
            case '>': {
                ptr++;
            } break;
            case '<': {
                ptr--;
            } break;

            case '+': {
                (*ptr)++;
            } break;
            case '-': {
                (*ptr)--;
            } break;

            case '.': {
                putchar(*ptr);
            } break;

            case ',': {
                *ptr = getchar();
            } break;

            //add loops
            case '[': {
                if (*ptr == 0) {
                    size_t openC = 0;

                    for (int j = i; j < strlen(input)-1; j++) {
                        if (input[j] == '[') openC++;
                        if (input[j] == ']') openC--;

                        if (input[j] == ']' && openC == 0) {
                            i = j;
                            break;
                        }
                    }
                }
            } break;

            case ']': {
                if (*ptr != 0) {
                    size_t closeC = 0;

                    for (int j=i; j >= 0; j--) {
                        if (input[j] == ']') closeC++;
                        if (input[j] == '[') closeC--;

                        if (input[j] == '[' && closeC == 0) {
                            i = j;
                            break;
                        }
                    }
                }
            } break;

        }
    }
}

char* readStrFromFp(FILE* fp) {
    char* file = malloc(10);
    size_t bytesRead = 0;
    size_t curSize = 10;

    while (1) {
        char c = fgetc(fp);

        if (c == EOF) break;

        file[bytesRead] = c;
        bytesRead++;

        if (bytesRead + 1 > curSize) {
            curSize += 10;
            file = realloc(file, curSize);
        }
    }

    return file;
}

int main(int argc, char const *argv[]){
    if (argc < 2) return 1;

    // main
    FILE* fp;

    fp = fopen(argv[1], "r");

    char* text = readStrFromFp(fp);

    interpret(text);

    return 0;
}
