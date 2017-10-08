/*
 * ch.c
 *
 *  Created on: Oct 7, 2017
 *      Author: Austin Klum
 */
#include<stdio.h>
#include<ctype.h>

int main(int argc, char **argv){
	 char c = fgetc(stdin);
	while(c != EOF){
		printf("Stuff = %c\n", c);
		c = ToUpper(fgetc(stdin));

		if(c == '!'){
			printf("BANG!");
			return 0;
		}
	}
	return 0;
}
