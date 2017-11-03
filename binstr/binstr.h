/*
 * Interface for manipulating binary strings (i.e., strings of 'bits').
 * (Do NOT modify this file.)
 *
 * Author: Jason Sauppe
 * Date: 2017-10-25
 */
#ifndef BINSTR_H
#define BINSTR_H

int how_many_bits(int);
char *decimal_to_binary(int);
int binary_to_decimal(char *);
char *negate(char *);
char *sign_extend(char *, int);
char *add(char *, char *);
char *sub(char *, char *);

#endif

