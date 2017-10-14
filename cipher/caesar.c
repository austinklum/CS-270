/*
 * caesar.c
 *
 *  Created on: Oct 12, 2017
 *      Author: Austin Klum
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void encryptC(int key, char *str, int isDecrypt){
	int i;
	for(i = 0; i < strlen(str); i++){
		shift(&str[i],key, isDecrypt);
	}
}

void decryptC(int key, char *str){
	encryptC(key, str, 1);
}
