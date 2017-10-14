/*
 * caesar.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Austin Klum
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "vin.h"
#include "caesar.h"

void parseArgs(char **argv, int *isEncrypt, int *isCaesar);
void shift(char *,int key,  int isDecrypt);

int main(int argc, char **argv){
	if (argc < 3){
		exit(-1);
	}
	int isEncrypt;
	int isCaesar;
	parseArgs(argv, &isEncrypt, &isCaesar);

	FILE *fp;
	if(argv[4] != NULL){
		fp = fopen(argv[4],"r");
	}else{
		fp = stdin;
	}

	char *input = NULL;
	char str[52];
	int keyIndex = 0;
	do{
		input = fgets(str, 52, fp);
		if(input != NULL){
			if(isEncrypt){
				if(isCaesar){
					encryptC(atoi(argv[3]), str, 0);
				}else{
					keyIndex = encryptV(argv[3], str, 0, keyIndex);
				}
			}else{
				if(isCaesar){
					decryptC(atoi(argv[3]), str);
				} else {
					keyIndex = decryptV(argv[3], str, keyIndex);
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
			//printf(" large_c = %d : key = %d\n", large_c, key);
			/*These if statement handles jumping the gaps forwards and backwards*/
			if (large_c == 91) {
				large_c = 97;
			} else if (large_c == 64) {
				large_c = 122;
			} else if (large_c == 123) {
				large_c = 65;
			} else if (large_c == 96) {
				large_c = 90;
			}
		}
		*c = large_c;
	}
}




