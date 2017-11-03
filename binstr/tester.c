/*
 * An extended testing program for Assignment 04. Allows for easily testing
 * ranges of values. (Do NOT modify this file.)
 *
 * Author: Jason Sauppe
 * Date: 2017-10-31
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binstr.h"

#define BUFFER_SIZE 64

/* Function declarations confined to this source file */
void test_range_how_many_bits(int min, int max);
void test_range_decimal_to_binary(int min, int max);
void test_range_binary_to_decimal(int min, int max, int num_bits);
void test_range_negate(int min, int max, int num_bits);
void test_range_sign_extend(int min, int max, int num_bits);
void test_range_add(int min, int max, int num_bits);
void test_range_sub(int min, int max, int num_bits);

char *decimal_to_binary_n_bits(int val, int num_bits);

/*
 * Runs some extended tests.
 */
int main(int argc, char **argv) {

    char buffer[BUFFER_SIZE];
    char *fgets_rtn = NULL;

    do {
        printf("> ");
        fgets_rtn = fgets(buffer, BUFFER_SIZE, stdin);
        if (fgets_rtn != NULL) {
            if (strncmp(buffer, "help", 4) == 0) {
                printf("Commands:\n");
                printf("  rhmb <min> <max>\n");
                printf("  rd2b <min> <max>\n");
                printf("  rb2d <min> <max> [<n>]\n");
                printf("  rneg <min> <max> [<n>]\n");
                printf("  rsgn <min> <max> [<n>]\n");
                printf("  radd <min> <max> [<n>]\n");
                printf("  rsub <min> <max> [<n>]\n");
                printf("  quit\n");
                printf("  help\n");
            } else if (strncmp(buffer, "rhmb", 4) == 0 ||
                       strncmp(buffer, "rd2b", 4) == 0 ||
                       strncmp(buffer, "rb2d", 4) == 0 ||
                       strncmp(buffer, "rneg", 4) == 0 ||
                       strncmp(buffer, "rsgn", 4) == 0 ||
                       strncmp(buffer, "radd", 4) == 0 ||
                       strncmp(buffer, "rsub", 4) == 0) {
                char *endptr = NULL;
                long min = strtol(buffer + 5, &endptr, 10);
                long max = strtol(endptr, &endptr, 10);
                /* Try to read the optional third number */
                long num_bits = strtol(endptr, NULL, 10);
                /* Figure out which function needs to be run */
                if (strncmp(buffer, "rhmb", 4) == 0) {
                    test_range_how_many_bits(min, max);
                } else if (strncmp(buffer, "rd2b", 4) == 0) {
                    test_range_decimal_to_binary(min, max);
                } else if (strncmp(buffer, "rb2d", 4) == 0) {
                    test_range_binary_to_decimal(min, max, num_bits);
                } else if (strncmp(buffer, "rneg", 4) == 0) {
                    test_range_negate(min, max, num_bits);
                } else if (strncmp(buffer, "rsgn", 4) == 0) {
                    test_range_sign_extend(min, max, num_bits);
                } else if (strncmp(buffer, "radd", 4) == 0) {
                    test_range_add(min, max, num_bits);
                } else {/* strncmp(buffer, "rsub", 4) == 0) */
                    test_range_sub(min, max, num_bits);
                }
            } else if (strncmp(buffer, "done", 4) == 0 ||
                       strncmp(buffer, "quit", 4) == 0 ||
                       strncmp(buffer, "exit", 4) == 0) {
                break; /* Exit loop, clean up, and terminate */
            } else {
                int len = strlen(buffer);
                if (buffer[len-1] == '\n') {
                    buffer[len-1] = '\0';
                    --len;
                }
                if (len > 0) { /* Ignores empty lines */
                    printf("Unrecognized command: [%s]\n", buffer);
                }
            }
        }
    } while (fgets_rtn != NULL);

    return 0;
}

/*
 * Tests how_many_bits for a range of values.
 */
void test_range_how_many_bits(int min, int max) {
    int i;
    printf("Testing how_many_bits [%d, %d]\n", min, max);
    for (i = min; i <= max; ++i) {
        printf("%5d requires %d bits\n", i, how_many_bits(i));
    }
    return;
}

/*
 * Tests decimal_to_binary for a range of values.
 */
void test_range_decimal_to_binary(int min, int max) {
    int i;
    printf("Testing decimal_to_binary [%d, %d]\n", min, max);
    for (i = min; i <= max; ++i) {
        char *binstr = decimal_to_binary(i);
        printf("%5d is encoded as [%s]\n", i, binstr);
        free(binstr);
    }
    return;
}

/*
 * Tests binary_to_decimal for a range of values. If num_bits > 0, the
 * binary strings are sign-extended before being passed into the
 * binary_to_decimal function.
 *
 * NOTE: Assumes that decimal_to_binary (and potentially sign_extend) works
 * properly!
 */
void test_range_binary_to_decimal(int min, int max, int num_bits) {
    int i;
    printf("Testing binary_to_decimal [%d, %d]", min, max);
    if (num_bits > 0) {
        printf(" with %d bits", num_bits);
    }
    printf("\n");
    for (i = min; i <= max; ++i) {
        char *binstr = decimal_to_binary_n_bits(i, num_bits);
        printf("[%s] decodes to %d\n", binstr, binary_to_decimal(binstr));
        free(binstr);
    }
    return;
}

/*
 * Tests negate for a range of values. If num_bits > 0, the binary strings are
 * sign-extended before being passed into the negate function.

 * NOTE: Assumes that decimal_to_binary (and potentially sign_extend) works
 * properly!
 */
void test_range_negate(int min, int max, int num_bits) {
    int i;
    printf("Testing negate [%d, %d]", min, max);
    if (num_bits > 0) {
        printf(" with %d bits", num_bits);
    }
    printf("\n");
    for (i = min; i <= max; ++i) {
        char *binstr = decimal_to_binary_n_bits(i, num_bits);
        char *negstr = negate(binstr);
        printf("Negating [%s] yields [%s]\n", binstr, negstr);
        free(negstr);
        free(binstr);
    }
    return;
}

/*
 * Tests sign_extend for a range of values. If num_bits != 0, the encoding
 * for each number in the range is sign-extended to that number of bits.
 * Otherwise, each number in the range is sign-extended to all possible
 * lengths up to 16 bits.

 * NOTE: Assumes that decimal_to_binary works properly!
 */
void test_range_sign_extend(int min, int max, int num_bits) {
    int i;
    printf("Testing sign_extend [%d, %d]", min, max);
    if (num_bits > 0) {
        printf(" with %d bits", num_bits);
    }
    printf("\n");
    for (i = min; i <= max; ++i) {
        char *binstr = decimal_to_binary(i);
        if (num_bits > 0) {
            char *extstr = sign_extend(binstr, num_bits);
            printf("Sign-extending [%s] to %d bits yields [%s]\n",
                    binstr, num_bits, extstr);
            free(extstr);
        } else {
            int length = strlen(binstr) + 1;
            printf("Sign-extending [%16s]:\n", binstr);
            for ( ; length <= 16; ++length) {
                char *extstr = sign_extend(binstr, length);
                printf("   to %2d bits: [%16s]\n", length, extstr);
                free(extstr);
            }
        }
        free(binstr);
    }
    return;
}

/*
 * Tests add for a range of values. If num_bits > 0, the binary strings are
 * sign-extended before being passed into the add function.

 * NOTE: Assumes that decimal_to_binary (and potentially sign_extend) works
 * properly!
 */
void test_range_add(int min, int max, int num_bits) {
    int i, j;
    printf("Testing add [%d, %d]", min, max);
    if (num_bits > 0) {
        printf(" with %d bits", num_bits);
    }
    printf("\n");
    for (i = min; i <= max; ++i) {
        char *b1 = decimal_to_binary_n_bits(i, num_bits);
        for (j = min; j <= max; ++j) {
            char *b2 = decimal_to_binary_n_bits(j, num_bits);
            char *result = add(b1, b2);
            printf("[%s] + [%s] = [%s]\n", b1, b2, result);
            free(result);
            free(b2);
        }
        free(b1);
    }
    return;
}

/*
 * Tests sub for a range of values. If num_bits > 0, the binary strings are
 * sign-extended before being passed into the sub function.
 *
 * NOTE: Assumes that decimal_to_binary works properly!
 */
void test_range_sub(int min, int max, int num_bits) {
    int i, j;
    printf("Testing sub [%d, %d]", min, max);
    if (num_bits > 0) {
        printf(" with %d bits", num_bits);
    }
    printf("\n");
    for (i = min; i <= max; ++i) {
        char *b1 = decimal_to_binary(i);
        for (j = min; j <= max; ++j) {
            char *b2 = decimal_to_binary_n_bits(j, num_bits);
            char *result = sub(b1, b2);
            printf("[%s] - [%s] = [%s]\n", b1, b2, result);
            free(result);
            free(b2);
        }
        free(b1);
    }
    return;
}

/*
 * Helper method for creating an n-bit binary string for the given number.
 * NOTE: Assumes that decimal_to_binary and sign_extend work properly!
 */
char *decimal_to_binary_n_bits(int val, int num_bits) {
    char *result = decimal_to_binary(val);
    if (strlen(result) < num_bits) {
        char *extstr = sign_extend(result, num_bits);
        free(result);
        result = extstr;
    }
    return result;
}

