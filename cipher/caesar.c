/*
 * caesar.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Austin Klum
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void encryptV(char *key, char *str, int strSize);
void parseArgs(char **argv, int *isEncrypt, int *isCaesar, char *key);
void encryptC(int key, char *str, int size);
void processString(char *str, int *size, char *path);
int getKey(int index, char *key, int *repeatCount);


int main(int argc, char **argv){
	printf("What?\nThe!");
	printf("Errors!?");
	if (argc < 3){
		exit(-1);
	}
	int isEncrypt;
	int isCaesar;
	char *key = calloc(argv[3], sizeof(char));
	char *str = calloc(3, sizeof(*str));
	int size = 0;
	printf("Processing string\n");
	processString(&str, &size, argv[4]);
	printf("Parsing Args\n");
	parseArgs(argv, &isEncrypt, &isCaesar, &key);
	printf("Criteria Includes:  Is Encrypt: %d , Is Caesar: %d , Key : %s \n", isEncrypt, isCaesar, argv[3]);
	if(isEncrypt){
		if(isCaesar){
			//encryptC((argv[3], &str, size);
		}else{
			//encryptV(argv[3], &str, size);
		}
	}else{
		if(isCaesar){
			//decryptC(key);
		} else {
			//decryptV(key);
		}
	}
	printf("Encrypted String is :\n %s", key);

	return 0;
}

void parseArgs(char **argv, int *isEncrypt, int *isCaesar, char *key){
	printf("%s",argv[1]);
	if(strcmp(argv[1], "e") == 0){
		*isEncrypt = 1;
	}else if(strcmp(argv[1],"d") == 0){
		*isEncrypt = 0;
	}
	/*Determine Type*/
	if (strcmp(argv[2], "c") == 0){
		*isCaesar = 1;
	} else if (strcmp(argv[2], "v") == 0) {
		*isCaesar = 0;
	}else{
		printf("Something went wrong!\n");
		//exit(-1);
	}
	//*key = realloc(*key,strlen(key) + strlen(argv[3]));

}


void processString(char *str, int *size, char *path){
	FILE *fin;
	fin = fopen(path,"r");

	 /*input + key = new value
	 * if greater than 127
	 * input + key - 127 = new wrapped around value
	 *
	 * */
	char c = fgetc(fin);
	while(c != EOF){
		//Add to string we are building
		*str = realloc(str, (strlen(*str) + 1) * sizeof(*str));
		strcat(*str, (char)c);
		size++;
		//Get next value
		c = fgetc(fin);
	}
}

/*
void encryptC(int key, char *str, int size){
	int i;
	for(i = 0; i < size; i++){
		if(str[i] + key < 128){
			Standard case
			str[i] += key;
		}else{
			Wrap around values
			str[i] = str[i] + key - 127;
		}
	}
}

Split up key string into its peices and do str[i] += key[j] - 'a'
or for wrapping do str[i] = str[i] + (key[j] - 'a') - 127
void encryptV(char *key, char *str, int strSize){
	int i = 0;
	int repeatCount = 0;

	for(i = 0; i < strSize; i++){
		char nextKey = getKey(i, key, &repeatCount);
		if(str[i] + nextKey < 128){
			Standard case
			str[i] += nextKey;
		}else{
			Wrap around values
			str[i] = str[i] + nextKey - 127;
		}
	}
}
 Will do index until it hits \0
 * After that it will subtract the length of the string from the index
 * to give the proper peiece of the passkey.
 *
 * if it repeats more than once multiply the size of whats being subtracted
 *
 *
int getKey(int index, char *key, int *repeatCount){
	if(key[index] == '\0'){
		(*repeatCount)++;
	}

	(strlen(key) * (*repeatCount)) calculates how far to move back for repeating values
	 * the - 'a' does the ascii math to give the integer to shift
	 *
	return (int)(key[index - (strlen(key) * (*repeatCount))] - 'a');
}*/
