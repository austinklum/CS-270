/*
 * caesar.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Austin Klum
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>



void encryptV(char *key, char *str);
void parseArgs(char **argv, int *isEncrypt, int *isCaesar);
void encryptC(int key, char *str);
void processString(char *str, int *size, char *path);
int getKey(int index, char *key, int *repeatCount);
void shift(char *,int);


int main(int argc, char **argv){
	if (argc < 3){
		exit(-1);
	}
	int isEncrypt;
	int isCaesar;
	//int shift = atoi(argv[3]);
	//printf("shift si valued at = %d\n", shift);
	//char *key = calloc(shift, sizeof(char));
	char *str = calloc(strlen(argv[4]), sizeof(char));
	strcpy(str,argv[4]);
	int size = 0;
	printf("Processing string\n");
	//processString(str, &size, argv[4]);
	printf("Starting str = %s\n", str);
	printf("Parsing Args\n");
	parseArgs(argv, &isEncrypt, &isCaesar);
	printf("Criteria Includes:  Is Encrypt: %d , Is Caesar: %d , Key : %s \n", isEncrypt, isCaesar, argv[3]);
	if(isEncrypt){
		if(isCaesar){
			encryptC(atoi(argv[3]), str);
		}else{
			encryptV(argv[3], str);
		}
	}else{
		if(isCaesar){
			decryptC(atoi(argv[3]), str);
		} else {
			decryptV(argv[3], str);
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
		printf("String = %s : Size = %d\n", str,strlen(str));
		str = realloc(str,strlen(str) + 1 * sizeof(char));
		str[strlen(str)] = c;
		//(*size)++;
		//str[strlen(str) + 1] = '\0';
		//printf("%c\n",c);
	}
	str = realloc(str,strlen(str) + 1 * sizeof(char));
	str[strlen(str)] = '\0';
	printf("String = %s", str);
}


void encryptC(int key, char *str){
	printf("Inner function print str : %s\n", str);
	int i;
	for(i = 0; i < strlen(str); i++){
		shift(&str[i],key);
	}
}

void shift(char *c, int key){
	if(isalpha(*c)){
		//printf("Before: %c, %d | Diff: %c, %d  |  After: %c, %d\n",*c,*c,*c+key,*c+key, 64 + (*c+key)-122,64 + (*c+key)-122);
		/*This sanitizes our shift so it cannot shift into a bad value*/
		/*while(key > 25){
			key -= 25;
		}*/
		/*large_c is the value of *c but without the overflow problems of a char*/
		//int large_c= *c + key;
		//*c += key;
		//normalizeShift(c,large_c);
		//printf("In range = %d\n", (*c >= 65 && *c <= 90 && *c >= 97 && *c <= 122));
		/*int checkAgain = 1;
		while(checkAgain){
			printf("Check again = false\n");
			checkAgain = 0;
			if(large_c > 90 && large_c < 97){
				//Wrap around problems
				 int diff = large_c - 90;
				 large_c = 96 + diff;
				 checkAgain = 1;
				 printf("First case! check again  = true\n");
			}else if(large_c > 122){
				//printf("C before difference = %c : %d\n",*c,*c);
				int diff = large_c - 122;
				//printf("Diff = %d\n", diff);
				large_c = 64 + diff;
				checkAgain = 1;
				printf("second case! check again  = true\n");
			}
		}
		*c = large_c;*/
			//printf("Character = %c : %d\n",*c,*c);
		int large_c = *c;
		int i;
		for(i = 0; i < key; i++){
			large_c++;
			if(large_c == 91){
				large_c = 97;
			}
			 else if (large_c == 123){
				large_c = 65;
			}
		}
		*c = large_c;
		/*int checkAgain = 1;
		int large_c = *c + key;
		while(checkAgain){
			checkAgain = 0;
			if(large_c > 90){
				if(large_c < 97){
					int diff = large_c - 90;
					large_c = 96 + diff;
					checkAgain = 1;
				}else if (large_c > 122){
					int diff = large_c - 122;
					large_c = 64 + diff;
					checkAgain = 1;
				}
			}
		}
		*c = large_c;*/
	}
}

/*int inRange(char c){
	printf("In range = ", (c >= 65 && c <= 90 && c >= 97 && c <= 122))
	return 0;
}*/

void normalizeShift(char *c, int large_c){
	if(*c == large_c){
		return;
	}
	if(large_c > 90 && large_c < 97){
		/*Wrap around problems*/
		 int diff = large_c - 90;
		 *c = 96 + diff;
	}
	if(large_c > 122){
		//printf("C before difference = %c : %d\n",*c,*c);
		int diff = large_c - 122;
		//printf("Diff = %d\n", diff);
		*c = 64 + diff;
	}
	//normalizeShift(c,large_c);

}

void encryptV(char *key, char *str){
	int i;
	for(i = 0; i < strlen(key); i++){

	}
	int keyCount = 0;
	printf("Size of key = %d\n" , strlen(key));
	for(i = 0; i < strlen(str); i++){
		int newKey = 0;
		if(isalpha(str[i])){
			newKey = key[keyCount] - 64;
			if(str[i] > 90){
				printf("Hit me baby!\n");
					newKey -= 5;
			}
		}
		printf("str[i] = %c, %d",str[i],str[i]);
		printf(" : %d : Key = %c : Key - A = %c, %d : ",keyCount, key[keyCount], newKey, newKey);
		shift(&str[i], newKey);
		printf("New str[i] = %c, %d\n", str[i], str[i]);
		//printf("Looking at index : %d\n" + keyCount);

		if(keyCount + 1 >= strlen(key)){
			printf("Reset\n");
			keyCount = 0;
		}else{
			keyCount++;
		}
	}
}

void decryptV(char *key, char *str){
	int i;
	/*Make the reverse key*/
	for(i = 0; i < strlen(key); i++){
		printf("Key before: %d : %c\n", key[i],key[i]);
		key[i] *= -1;
		printf("Key After: %d : %c\n", key[i],key[i]);
	}
	encryptV( key,  str);
}

void decryptC(int key, char *str){
	encryptC( 52-key,  str);
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

