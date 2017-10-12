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
void parseArgs(char **argv, int *isEncrypt, int *isCaesar);
void encryptC(int key, char *str, int size);
void processString(char *str, int *size, char *path);
int getKey(int index, char *key, int *repeatCount);
void shift(char *,int);
int getKey(int index, char *key, int *repeatCount);


int main(int argc, char **argv){
	if (argc < 3){
		exit(-1);
	}
	int isEncrypt;
	int isCaesar;
	//int shift = atoi(argv[3]);
	//printf("shift si valued at = %d\n", shift);
	//char *key = calloc(shift, sizeof(char));
	char *str = calloc(0, sizeof(char));
	int size = 0;
	printf("Processing string\n");
	processString(str, &size, argv[4]);
	printf("size = %d\n str = %s\n", size, str);
	printf("Parsing Args\n");
	parseArgs(argv, &isEncrypt, &isCaesar);
	printf("Criteria Includes:  Is Encrypt: %d , Is Caesar: %d , Key : %s \n", isEncrypt, isCaesar, argv[3]);
	if(isEncrypt){
		if(isCaesar){
			encryptC(atoi(argv[3]), str, size);
		}else{
			encryptV(argv[3], str, size);
		}
	}else{
		if(isCaesar){
			//decryptC(key);
		} else {
			//decryptV(key);
		}
	}
	printf("Encrypted String is :\n %s", str);

	return 0;
}

void parseArgs(char **argv, int *isEncrypt, int *isCaesar){
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

}


void processString(char *str, int *size, char *path){
	FILE *fp;
	printf("Path = %s\n",path);
	fp = fopen(path,"r");

	 /*input + key = new value
	 * if greater than 127
	 * input + key - 127 = new wrapped around value
	 *
	 * */
	char c = 0;
	while((c = fgetc(fp)) != EOF){
		//Add to string we are building
		str = realloc(str,(*size) * sizeof(char));
		str[(*size)] = c;
		(*size)++;
		str[(*size)] = '\0';
		//printf("%c\n",c);
	}
}


void encryptC(int key, char *str, int size){
	printf("Inner function print str : %s\n", str);
	int i;
	for(i = 0; i < size; i++){
		shift(&str[i],key);
	}
}

void shift(char *c, int key){
	if(isalpha(*c)){
		*c += key;
		if(*c > 90 && *c < 97){
			/*Wrap around problems*/
			 int diff = *c - 90;
			 *c = 90 + diff;
		}
		if(*c > 122){
			int diff = *c - 122;
			*c = 64 + diff;
		}
	}
}

void encryptV(char *key, char *str, int size){
	int i;
	int keyCount = 0;
	printf("Size of key = %d\n" , strlen(key));
	for(i = 0; i < size; i++){
		shift(&str[i], (key[keyCount] - 'A' + 1));
		printf("Looking at index : %d\n" + keyCount);
		printf("Key = %c : Key - A = %d : Key in char form = %c\n", key[keyCount], key[keyCount] - 'A' + 1, key[keyCount] - 'A' + 1);
		if(keyCount + 1 >= strlen(key)){
			printf("Reset\n");
			keyCount = 0;
		}else{
			keyCount++;
		}
	}
}

/*Split up key string into its peices and do str[i] += key[j] - 'a'
or for wrapping do str[i] = str[i] + (key[j] - 'a') - 127*/
/*void encryptV(char *key, char *str, int strSize){
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
}*/
/* Will do index until it hits \0
 * After that it will subtract the length of the string from the index
 * to give the proper peiece of the passkey.
 *
 * if it repeats more than once multiply the size of whats being subtracted
 *
 **/
int getKey(int index, char *key, int *repeatCount){
	if(key[index] == '\0'){
		(*repeatCount)++;
	}

	//(strlen(key) * (*repeatCount))
	/*calculates how far to move back for repeating values
	 * the - 'a' does the ascii math to give the integer to shift
	 * */

	return (int)(key[index - (strlen(key) * (*repeatCount))] - 'a');
}

