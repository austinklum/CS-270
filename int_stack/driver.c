///*
// * A simple driver program for processing commands to manipulate a stack of
// * integers. (Do NOT modify this file.)
// *
// * Author: Jason Sauppe
// * Date: 2017-10-17
// */
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include "int_stack.h"
//
//#define BUFFER_SIZE 20
//
//int main(int argc, char **argv) {
//    char buffer[BUFFER_SIZE]; /* Can store reasonably long digits */
//    char *fgets_rtn = NULL;
//    struct int_stack *stk = NULL;
//    int node_capacity = 5;
//
//    /* Create the stack */
//    if (argc >= 2) {
//        node_capacity = strtol(argv[1], NULL, 10);
//    }
//    stk = make_stack(node_capacity);
//
//    do {
//        fgets_rtn = fgets(buffer, BUFFER_SIZE, stdin);
//        if (fgets_rtn != NULL) {
//            if (strncmp(buffer, "push", 4) == 0) {
//                long val = strtol(buffer + 5, NULL, 10);
//                push(stk, val);
//            } else if (strncmp(buffer, "pop", 3) == 0) {
//                printf("%d\n", pop(stk));
//            } else if (strncmp(buffer, "top", 3) == 0) {
//                printf("%d\n", top(stk));
//            } else if (strncmp(buffer, "print", 5) == 0) {
//                print_stack(stk);
//            } else if (strncmp(buffer, "size", 4) == 0) {
//                printf("%zu\n", stk->size);
//            } else if (strncmp(buffer, "reset", 5) == 0) {
//                reset_stack(stk);
//            } else if (strncmp(buffer, "done", 4) == 0 ||
//                       strncmp(buffer, "quit", 4) == 0 ||
//                       strncmp(buffer, "exit", 4) == 0) {
//                break; /* Exit loop, clean up, and terminate */
//            } else {
//                int len = strlen(buffer);
//                if (buffer[len-1] == '\n') {
//                    buffer[len-1] = '\0';
//                    --len;
//                }
//                if (len > 0) { /* Ignores empty lines */
//                    printf("Unrecognized command: [%s]\n", buffer);
//                }
//            }
//        }
//    } while (fgets_rtn != NULL);
//
//    /* Clean-up */
//    free_stack(stk);
//
//    return 0;
//}

