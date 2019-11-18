/*
 * Step by step boore's moore with checking
 * Please only run on CSE (it will work on any posix system -- probably)
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearScreen(void) { system("clear"); }

void printFailure(int failure[], char *pattern) {
    for (int i = 0; i < (int)strlen(pattern); i++) printf("| % 2d ", i);
    printf("|\n");
    for (int i = 0; i < (int)strlen(pattern); i++) {
        printf("| '%c'", pattern[i]);
    }
    printf("|\n");
    for (int i = 0; i < (int)strlen(pattern); i++) {
        printf("| % 2d ", failure[i]);
    }
    printf("|\n");
}

void printState(char *text, char *pattern, int i, int j) {
    printf("T: ");
    int diff = i - j;
    if (diff < 0)
        for (int k = 0; k < -diff; k++) putchar(' ');
    puts(text);
    int end = 3 + i;
    if (diff < 0) end += -diff;
    for (int k = 0; k < end; k++) putchar(' ');
    printf("^i\n");

    printf("P: ");
    if (diff > 0)
        for (int k = 0; k < diff; k++) putchar(' ');
    puts(pattern);
    end = 3 + j;
    if (diff > 0) end += diff;
    for (int k = 0; k < end; k++) putchar(' ');
    printf("^j\n");
}

int buildFailure(char *pattern, int *failure) {
    int i = 1;
    int len = 0;
    int compares = 0;

    memset(failure, 0, sizeof(int) * strlen(pattern));
    while (i < (int)strlen(pattern)) {
        compares++;
        if (pattern[i] == pattern[len]) {
            len++;
            failure[i] = len;
            i++;
        } else {
            // tricky case i.e. for ABCAAB
            // we try to match the ABC to AAB but fail
            // so instead we back the 2 length AB to AB!
            if (len != 0) {
                len = failure[len - 1];
            } else {
                failure[i] = 0;
                i++;
            }
        }
    }

    return compares;
}

// lower case alphabet of a-z
// returns starting index of match or -1 if no match
int kmp(char *text, char *pattern) {
    int failure[strlen(pattern)];
    int buildCmps = buildFailure(pattern, failure);
    int i = 0;
    int j = 0;
    int numCompares = 0;

    while (i < (int)strlen(text)) {
        clearScreen();
        printf("Comparing text[%d] '%c' to pattern[%d] '%c'\n", i, text[i], j,
               pattern[j]);
        printFailure(failure, pattern);
        printState(text, pattern, i, j);
        printf("Press enter to continue: ");
        getchar();
        numCompares++;

        if (text[i] == pattern[j]) {
            // we found a character match
            if (j == (int)strlen(pattern) - 1) {
                // no more pattern to look for
                printf("Total number of comparisons is %d and build compares "
                       "is %d\n",
                       numCompares, buildCmps);
                // found match
                return i - j;
            } else {
                // we still have pattern to match
                i++;
                j++;
            }
        } else {
            // failure state
            if (j > 0) {
                // we don't have to reset j all the way back
                // since we know this F[0..F[j - 1]] will match
                j = failure[j - 1];
            } else {
                i++;
            }
        }
    };

    printf("Total number of comparisons is %d and build compares is % d\n ",
           numCompares, buildCmps);
    return -1;
}

void convertToLower(char *str) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 'a' - 'A';
        } else if (str[i] < 'a' || str[i] > 'z') {
            fprintf(stderr, "Not a valid string must be between a-z");
            exit(1);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(
            stderr,
            "Need to give pattern and text as ./boyer_moore <text> <pattern>");
        return 1;
    }

    convertToLower(argv[1]);
    convertToLower(argv[2]);

    int substring = kmp(argv[1], argv[2]);
    if (substring == -1) {
        printf("No match\n");
    } else {
        printf("Match starting at %d\n", substring);
    }

    return 0;
}
