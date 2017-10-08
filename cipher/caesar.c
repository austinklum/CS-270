/*
 * caesar.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Austin Klum
 */

#include<stdio.h>
#include<string.h>

int main(int argc, char **argv){

	if (argc < 3){
		exit(-1);
	}
	if(argv[1] == 'c'){
		printf("Caeser!");
	} else if (argv[1] == 'v') {
		printf("Vigenere");
	}

	return 0;
}

