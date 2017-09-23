/*
 * Pythag.c A program to find the first 60 Pythagorean triples
 *
 *  Created on: Sep 22, 2017
 *      Author: Austin Klum
 */
#include <stdio.h>
#include <math.h>

int main(int argc , char **argv){
	int a = 0, b = 0, c = 0, max = 60;
	/*Loop through all possible b values*/
	for (b = 1; b <= max; b++){
		/*Loop through all possible a values when a is less than b*/
		for (a = 1; a < b; a++){
			/*Loop through all possible c values. In this case 75*/
			for(c = 1; c <= 75; c++){
				/*Logic to see if a^2 + b^2 = c^2*/
				if(a*a + b*b == c*c){
					printf("triple: %d %d %d\n", a, b, c);
				}
			}
		}
	}

	return 0;
}
