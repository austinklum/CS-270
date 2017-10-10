/*
 * ch.c
 *
 *  Created on: Oct 7, 2017
 *      Author: Austin Klum
 */

#include<stdio.h>
#include<ctype.h>
#include<string.h>

int digit_count(int val);
char digit_at_pos(int, int);
int max_digit_count(int *arr);
void print_col(int *arr);

int main(int argc, char **argv){
	FILE *fp;
	fp = fopen("odyssey","r");
	char c = 0;
	int arr[27];
	int i;
	 /*Initalize array*/
	for(i = 0; i < 27; i++){
		 arr[i] = 0;
	}
	 /*Gather input. Apparently setting assignment and comparing is allowed in one line*/
	while((c = fgetc(fp)) != EOF){
		int c_scaled = (int)(toupper(c) - 'A');
		//printf("c = %c : c = %d : cUpper = %d : A = %d :  C_Scaled = %d\n" ,c,(int)c,(int)toupper(c),(int)'A',c_scaled);
		if(c_scaled >= 0 && c_scaled <= 26){
			arr[c_scaled]++;
		}else if(!isspace(c)){
			arr[26]++;
		}

	}
	print_col(arr);
	 /*Display results in row mode*/
	/* for(i = 0; i < 26; i++){
		 printf("%c : %d\n", (i + 'A'), arr[i] );
	 }
	 printf("%c : %d\n", '*', arr[26]);*/
	return 0;
}

void print_col(int arr[]){
	int i;
	int maxDigit = max_digit_count(arr);
	maxDigit--;
	while(maxDigit >= 0){
		for(i = 0; i < 27; i++){
			if(digit_count(arr[i]) < maxDigit && 0 < maxDigit){
				printf("  ");
			}else{
				printf("%c ", digit_at_pos(arr[i], maxDigit));
			}
		}
		maxDigit--;
		printf("\n");
	}
	 for(i = 0; i < 26; i++){
		 printf("%c ", (i + 'A') );
	 }
	 printf("%c ", '*');
}

int digit_count(int val){
	int count = 0;
	while(val > 0){
		val /= 10;
		count++;
	}
	return count;
}

char digit_at_pos(int val, int i){
	int j;
	for(j = 0; j < i; j++){
		val /= 10;
	}
	return (val % 10) + '0';
}

int max_digit_count(int arr[]){
	int i;
	int max = 0;
	for(i = 0; i < 27; i++){
		if(arr[i] > max){
			max = arr[i];
		}
	}
	return digit_count(max);
}
