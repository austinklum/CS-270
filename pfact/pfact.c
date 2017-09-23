/*
 * pfact.c
 *
 *  Created on: Sep 23, 2017
 *      Author: Austin Klum
 */
#include <stdio.h>
#include <math.h>

int main(){
	int n = 646969323;

int divisor = 2;
int half_n = n/2;
int check_again = 0;
int prev_val = 0;
int dup_count = 0;
	/* The factors should be found in first half of n */
	while(divisor <= half_n){
		/*Check if the number is divisible by the divisor */
		int counter = 0;
		while(n % divisor == 0){

			printf("%d * ", divisor );
			n = n /divisor;
		}
	divisor++;
	}
}

