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
	int isEncrypt;
	int isCaesar;
	char *key;
	char *str;
	int size = 0;

	processString(&str, &size, argv[3]);
	parseArgs(argv, &isEncrypt, &isCaesar, &key);

	if(isEncrypt){
		if(isCaesar){
			encryptC((int)key, &str, size);
		}else{
			encryptV((int)key);
		}
	}else{
		if(isCaesar){
			decryptC(key);
		} else {
			decryptV(key);
		}
	}


	return 0;
}

void parseArgs(char **argv, int *isEncrypt, int *isCaesar, char *key){
	if(argv[0] == 'e'){
		*isEncrypt = 1;
	}else if(argv[0] == 'd'){
		*isEncrypt = 0;
	}
	/*Determine Type*/
	if (argv[1] == 'c'){
		*isCaesar = 1;
	} else if (argv[1] == 'v') {
		*isCaesar = 0;
	}else{
		exit(-1);
	}
	*key = (char)argv[2];
}

void encryptC(int key, char *str, int size){
	int i;
	for(i = 0; i < size; i++){
		if(str[i] + key < 128){
			/*Standard case*/
			str[i] += key;
		}else{
			/*Wrap around values*/
			str[i] = str[i] + key - 127;
		}
	}
}

void processString(char *str, int *size, char *path){
	FILE fin = *fOpen(*path,"r");

	/* input + key = new value
	 * if greater than 127
	 * input + key - 127 = new wrapped around value
	 *
	 * */
	char *c = fgetc(fin);
	while(c != EOF){
		//Add to string we are building
		*str += c;
		size++;
		//Get next value
		*c = fgetc(fin);
	}
}
