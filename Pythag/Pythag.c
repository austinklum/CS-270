/*
 * Pythag.c
 *
 *  Created on: Sep 22, 2017
 *      Author: Austin Klum
 */
#include <stdio.h>
#include <math.h>

int main(){
	int a = 0, b = 0, c = 0, max = 60;
	for (b = 1; b <= max; b++){
		for (a = 1; a < b; a++){
			for(c = 1; c <= 75; c++){
				if(a*a + b*b == c*c)
					printf("triple: %d %d %d\n", a, b, c);
			}
		}
	}

	return 0;
}
