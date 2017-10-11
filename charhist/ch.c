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
void print_row(int *arr);

int main(int argc, char **argv){
	FILE *fp;
	fp = stdin;
	/*fp = fopen("odyssey","r");*/
	char c = 0;
	int arr[27];
	int i;
	 /*Initialize array*/
	for(i = 0; i < 27; i++){
		 arr[i] = 0;
	}
	 /*Gather input. Apparently setting assignment and comparing is allowed in one line*/
	while((c = fgetc(fp)) != EOF){
		/*Scale c to be case insensitive and in order from 0 - 26*/
		int c_scaled = (int)(toupper(c) - 'A');
		/*If in range add to array*/
		if(c_scaled >= 0 && c_scaled <= 26){
			arr[c_scaled]++;
		/*else, if it is not a space and just happens to be some other strange character. Add it to the left over data*/
		}else if(!isspace(c)){
			arr[26]++;
		}

	}
	if(strcmp(argv[0], "c") == 0){
		/*Display results in column mode*/
		print_col(arr);
	}else{
		 /*Display results in row mode*/
		print_row(arr);
	}
	return 0;
}
void print_row(int *arr){
	int i;
	/*Print out the rows up to Z*/
	for(i = 0; i < 26; i++){
		 printf("%c : %d\n", (i + 'A'), arr[i] );
	 }
	/*Print out misc characters*/
	 printf("%c : %d\n", '*', arr[26]);
}

void print_col(int arr[]){
	int i;
	/*Get the max digit count*/
	int maxDigit = max_digit_count(arr) - 1;
	/*Use max digit as the decrementing count to print out the proper chars in each row.*/
	while(maxDigit >= 0){
		/*Print out a row at the current value of maxDigit*/
		for(i = 0; i < 27; i++){
			if(digit_count(arr[i]) <= maxDigit && 0 < maxDigit){
				printf("  ");
			}else{
				printf("%c ", digit_at_pos(arr[i], maxDigit));
			}
		}
		/*Make forward progress and next line*/
		maxDigit--;
		printf("\n");
	}
	/*Print out bottom row*/
	 for(i = 0; i < 26; i++){
		 printf("%c ", (i + 'A') );
	 }
	 printf("%c ", '*');
}

int digit_count(int val){
	/*While the val can be divided more; Keep dividing*/
	int count = 0;
	while(val > 0){
		val /= 10;
		count++;
	}
	return count;
}

char digit_at_pos(int val, int i){
	/*Divide by number of need times*/
	int j;
	for(j = 0; j < i; j++){
		val /= 10;
	}
	/*Return the remainder of digit and add a scaler*/
	return (val % 10) + '0';
}

/*Get the digit of the largest count*/
int max_digit_count(int arr[]){
	int i;
	int max = 0;
	/*Find max*/
	for(i = 0; i < 27; i++){
		if(arr[i] > max){
			max = arr[i];
		}
	}
	/*return digit count of max*/
	return digit_count(max);
}
