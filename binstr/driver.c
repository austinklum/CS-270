/*
 * A simple driver program for processing commands to test binary string
 * functionality. (Do NOT modify this file.)
 *
 * Author: Jason Sauppe
 * Date: 2017-10-31
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binstr.h"

#define BUFFER_SIZE 64

/* Function declarations */
char *str_to_binstr(char *str, char **endptr);

/*
 * A simple read-eval-print loop for testing out binstr functionality.
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
                printf("  hmb <n>           : "
                       "Calls how_many_bits(<n>) and prints result\n");
                printf("  d2b <n>           : "
                       "Calls decimal_to_binary(<n>) and prints result\n");
                printf("  b2d <s>           : "
                       "Calls binary_to_decimal(<s>) and prints result\n");
                printf("  neg <s>           : "
                       "Calls negate(<s>) and prints result\n");
                printf("  sgn <s> <n>       : "
                       "Calls sign_extend(<s>, <n>) and prints result\n");
                printf("  sign-ext <s> <n>  : "
                       "Calls sign_extend(<s>, <n>) and prints result\n");
                printf("  add <s1> <s2>     : "
                       "Calls add(<s1>, <s2>) and prints result\n");
                printf("  add_bin <s1> <s2> : "
                       "Calls add(<s1>, <s2>) and prints result\n");
                printf("  add_dec <n1> <n2> : Converts <n1> and <n2> into "
                       "binary strings <s1> and <s2>\n"
                       "                      using binary_to_decimal and "
                       "then calls add(<s1>, <s2>)\n"
                       "                      and prints result\n");
                printf("  sub <s1> <s2>     : "
                       "Calls sub(<s1>, <s2>) and prints result\n");
                printf("  sub_bin <s1> <s2> : "
                       "Calls sub(<s1>, <s2>) and prints result\n");
                printf("  sub_dec <n1> <n2> : Converts <n1> and <n2> into "
                       "binary strings <s1> and <s2>\n"
                       "                      using binary_to_decimal and "
                       "then calls sub(<s1>, <s2>)\n"
                       "                      and prints result\n");
                printf("  quit              : Quits this program\n");
                printf("  help              : Prints this help message\n");
            } else if (strncmp(buffer, "hmb", 3) == 0) {
                long val = strtol(buffer + 4, NULL, 10);
                printf("%d\n", how_many_bits(val));
            } else if (strncmp(buffer, "d2b", 3) == 0) {
                long val = strtol(buffer + 4, NULL, 10);
                char *result = decimal_to_binary(val);
                printf("%s\n", result);
                free(result);
            } else if (strncmp(buffer, "b2d", 3) == 0) {
                char *input = str_to_binstr(buffer + 4, NULL);
                printf("%d\n", binary_to_decimal(input));
                free(input);
            } else if (strncmp(buffer, "neg", 3) == 0) {
                char *input = str_to_binstr(buffer + 4, NULL);
                char *result = negate(input);
                printf("%s\n", result);
                free(input);
                free(result);
            } else if (strncmp(buffer, "sgn", 3) == 0 ||
                       strncmp(buffer, "sign-ext", 8) == 0) {
                char *endptr = NULL, *input, *result;
                long num_bits;
                if (strncmp(buffer, "sgn", 3) == 0) {
                    input = str_to_binstr(buffer + 4, &endptr);
                } else {
                    input = str_to_binstr(buffer + 9, &endptr);
                }
                num_bits = strtol(endptr, NULL, 10);
                result = sign_extend(input, num_bits);
                printf("%s\n", result);
                free(input);
                free(result);
            } else if (strncmp(buffer, "add", 3) == 0 ||
                       strncmp(buffer, "sub", 3) == 0) {
                char *endptr = NULL;
                char *binstr1, *binstr2, *result;
                if (strncmp(buffer + 3, "_dec", 4) == 0) {
                    binstr1 = decimal_to_binary(strtol(buffer + 8, &endptr, 10));
                    binstr2 = decimal_to_binary(strtol(endptr, NULL, 10));
                } else if (strncmp(buffer + 3, "_bin", 4) == 0) {
                    binstr1 = str_to_binstr(buffer + 8, &endptr);
                    binstr2 = str_to_binstr(endptr, NULL);
                } else { /* Assume just dealing with two binary strings */
                    binstr1 = str_to_binstr(buffer + 4, &endptr);
                    binstr2 = str_to_binstr(endptr, NULL);
                }
                if (strncmp(buffer, "add", 3) == 0) {
                    result = add(binstr1, binstr2);
                } else { /* Assume subtraction */
                    result = sub(binstr1, binstr2);
                }
                printf("%s\n", result);
                free(binstr1);
                free(binstr2);
                free(result);
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
 * Helper function for parsing a binary string out of a larger string.
 */
char *str_to_binstr(char *str, char **endptr) {
    int i, size = 0;
    char *result;
    /* Skip leading spaces */
    while (*str == ' ') {
        ++str;
    }
    while (str[size] == '0' || str[size] == '1') {
        ++size;
    }
    result = malloc((size + 1) * sizeof(char));
    result[size] = '\0';
    for (i = 0; i < size; ++i) { /* Copy over values */
        result[i] = str[i];
    }
    if (endptr != NULL) {
        *endptr = str + size; /* Pointer to end of binary string */
    }
    return result;
}

