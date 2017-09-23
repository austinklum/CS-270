/*
 * pfact.c  A program to find prime factorizations of an input.
 *
 *  Created on: Sep 23, 2017
 *      Author: Austin Klum
 */
#include <stdio.h>
#include <math.h>

int main(int argc , char **argv){
	int n = atoi(argv[1]);

int divisor = 2;
int half_n = n/2;
int first_iter = 1;
	/* The factors should be found in first half of n */
	while(divisor <= half_n){
		/*Check if the number is divisible by the divisor */
		/*&& check added to stop possible infinite loop...*/
		int counter = 0;
		while(n % divisor == 0 && n != 1){
			/*Counter is used to count the number of repeats*/
			counter++;
			n = n /divisor;
		}
		/*On the first iteration through display the number = */
		if(first_iter == 1 && counter > 0){
			printf("%d = ", (half_n*2));
			first_iter = 0;
		}else if(counter > 0){
			/*Prepend a * if there is a value */
			printf(" * ");
		}
		/*Display the number if there was one*/
		if (counter > 1){
			/*Repeated case*/
			printf("%d^%d", divisor, counter);
		}else if (counter == 1){
			/*Individual case*/
			printf("%d", divisor );
		}
	divisor++;
	}
}

