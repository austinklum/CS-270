/*
 * caesar.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Austin Klum
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void decryptC(int key, char *str);
void decryptV(char *key, char *str);
void encryptV(char *key, char *str, int isDecrypt);
void parseArgs(char **argv, int *isEncrypt, int *isCaesar);
void encryptC(int key, char *str, int isDecrypt);
void shift(char *,int key,  int isDecrypt);

int main(int argc, char **argv){
	if (argc < 3){
		exit(-1);
	}
	int isEncrypt;
	int isCaesar;
	char str[64];
	parseArgs(argv, &isEncrypt, &isCaesar);
	char *input = NULL;

	do{

		input = fgets(str, 64, stdin);
		if(input != NULL){
			if(isEncrypt){
				if(isCaesar){
					encryptC(atoi(argv[3]), str, 0);
				}else{
					encryptV(argv[3], str, 0);
				}
			}else{
				if(isCaesar){
					decryptC(atoi(argv[3]), str);
				} else {
					decryptV(argv[3], str);
				}
			}
			printf("%s",str);
		}
	}while(input != NULL);

	return 0;
}

void parseArgs(char **argv, int *isEncrypt, int *isCaesar){
	/*Determine if encoding or decoding*/
	if(strcmp(argv[1], "-e") == 0){
		*isEncrypt = 1;
	}else if(strcmp(argv[1],"-d") == 0){
		*isEncrypt = 0;
	}
	/*Determine Type*/
	if (strcmp(argv[2], "-c") == 0){
		*isCaesar = 1;
	} else if (strcmp(argv[2], "-v") == 0) {
		*isCaesar = 0;
	}


}

/*This was suppose to process a file. I got some weird data issues and the time limit was fast approaching*/
/*void processString(char *str, char *path){
	FILE *fp;
	printf("Path = %s\n",path);
	fp = fopen(path,"r");

	char c = 0;
	int length = 0;
	while((c = fgetc(fp)) != EOF){
		length++;
		//Add to string we are building
		str = realloc(str, length * sizeof(char));
		//strcat(str,c);
		str[length-1] = c;
		str[length] = '/0';
	}
	fclose(fp);
}*/


void encryptC(int key, char *str, int isDecrypt){
	int i;
	for(i = 0; i < strlen(str); i++){
		shift(&str[i],key, isDecrypt);
	}
}

void shift(char *c, int key, int isDecrypt){
	if(isalpha(*c)){
		int large_c = *c;
		int i;
		for(i = 0; i < key; i++){
			/*if we are decrypting go right to left*/
			if(isDecrypt){
				large_c--;
			/*if we are encrypting go left to right*/
			}else{
				large_c++;
			}

			/*These switch statement handles jumping the gaps forwards and backwards*/
			switch (large_c) {
				case 91:
					large_c = 97;
					break;
				case 64:
					large_c = 122;
					break;
				case 123:
					large_c = 65;
					break;
				case 96:
					large_c = 90;
					break;
			}

		}
		*c = large_c;
	}
}

void encryptV(char *key, char *str, int isDecrypt){
	int i;
	/*Translate all the chars in the keyword to find the shift value*/
	for(i = 0; i < strlen(key); i++){
		/*When lower case switch it to uppercase to avoid the gap between the 2 good zones*/
		if(islower(key[i]) && isalpha(key[i])){
			/*Translate it down: key[i] - 64 + 26*/
			key[i] = toupper(key[i]) - 38;
		} else {
			/*Translate it down*/
			key[i] = key[i] - 64;
		}
	}
	int keyCount = 0;

	/*Loop through all possible chars in str*/
	for(i = 0; i < strlen(str); i++){
		/*If it is a letter, shift it however many places the key dictates*/
		if(isalpha(str[i])){
			shift(&str[i], key[keyCount], isDecrypt);
			/*Check what the keyword index is at. And either reset the count or add to it*/
			if(keyCount + 1 >= strlen(key)){
				keyCount = 0;
			}else{
				keyCount++;
			}
		}

	} /*End For*/
}

void decryptV(char *key, char *str){
	encryptV(key, str, 1);
}

void decryptC(int key, char *str){
	encryptC(key, str, 1);
}


