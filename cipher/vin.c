/*
 * vin.c
 *
 *  Created on: Oct 12, 2017
 *      Author: Austin Klum
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int encryptV(char *key, char *str, int isDecrypt, int keyIndex){
	int i;
	/*Loop through all possible chars in str*/
	for(i = 0; i < strlen(str); i++){
		/*If it is a letter, shift it however many places the key dictates*/
		if(isalpha(str[i])){
			if(islower(key[keyIndex]) && isalpha(key[keyIndex])){
				/*Translate it down: key[i] - 64 + 26*/
				shift(&str[i], toupper(key[keyIndex]) - 38, isDecrypt);
			} else {
				/*Translate it down*/
				shift(&str[i], key[keyIndex]  - 64, isDecrypt);
			}

			/*Check what the keyword index is at. And either reset the count or add to it*/
			if(keyIndex + 1 >= strlen(key)){
				keyIndex = 0;
			}else{
				keyIndex += 1;
			}
		}

	} /*End For*/

	return keyIndex;
}

int decryptV(char *key, char *str, int keyIndex){
	return encryptV(key, str, 1, keyIndex);
}

