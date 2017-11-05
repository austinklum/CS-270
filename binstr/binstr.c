/*
 * binstr.c
 *
 *  Created on: Nov 3, 2017
 *      Author: Austin Klum
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binstr.h"

int main(int argc, char **argv){
	int x = -1;
	char *y = decimal_to_binary(x);
	printf("How many bits for %d : %d\n",x, how_many_bits(x));
	printf("Binary String rep of %d : %s\n",x,y);
	printf("Taking Binary String %s into decimal : %d\n",y,binary_to_decimal(y));
	printf("Negating %s to %s\n",y,negate(y));
	printf("Sign Extending by 3 to %s : %s\n",y,sign_extend(y,3));
	return 0;
}

//Im not sure if this accurately represent a 2's complement bit count
int how_many_bits(int dec) {
	//Divide by 2 until dec is 0. Keep a count of times this was done.
	if (dec == 0) {
		return 1;
	}

	int count = 1;
	while(dec != 0) {
		dec /= 2;
		count++;
	}
	return count;
}
char *decimal_to_binary(int dec) {
	//Mod and divide by 2. Save a record into a malloc array and reverse it
	int size = how_many_bits(dec);
	//Size is n, we can only use 0 - n-1, Be sure to end string with a '\0'
	char *arr = malloc((size + 1) * sizeof(char));
	arr[size] = '\0';
	int i = 0;
	int isNeg = dec < 0;
	if(isNeg){
		dec *= -1;
	}
	/*Put the contents in the array in reverse order add '0' to offset the dec % 2 value*/
	for(i = size - 1; i >= 0; i--){
		arr[i] = (char)(dec % 2) + '0';
		dec /= 2;
	}
	if(isNeg){
		return negate(arr);
	}

	return arr;
}
int binary_to_decimal(char *arr) {
	/* start at end of array and set base to 1. While not at the start of the array
	 *  dec_val = dec_val + arr[i] * base
	 *  base *= 2
	*/
	int dec = 0;
	int size = strlen(arr);
	int i = 0;
	int base = 1;
	/*We should check if arr[0] is 1
	 * If 1 negate the output and do the stuff
	 * */
	int isNeg = arr[0] == '1';
	if (isNeg) {
		arr = negate(arr);
	}
	for(i = size - 1; i >= 0; i--){
		dec += (arr[i] - '0') * base;
		base *= 2;
	}
	if(isNeg) {
		dec *= -1;
	}
	return dec;
}
char *negate(char *oldArr) {
	/* loop through everything
	 * if 0 then 1
	 * else if 1 then 0
 	 */
	int i = 0;
	int size = strlen(oldArr);
	/*Create a new copy of the array to return*/
	char *arr = malloc(size * sizeof(char));
	strcpy(arr,oldArr);
	size--;

	for(i = size; i >= 0; i--) {
		/*Switch to the opposite binary digit*/
		if (arr[i] == '0') {
			arr[i] = '1';
		} else {
			arr[i] = '0';
		}
	}

	int carry = 1;
	while(carry == 1){
		/*Start the end of arr
		 * If arr[i] == 0 change to 1; set carry to 0
		 * If arr[i] == 1 change to 0; set carry to 1
		 * */
		if (arr[size] == '0') {
			arr[size] = '1';
			carry = 0;
		} else {
			arr[size] = '0';
			carry = 1;
		}
		size--;
		if (size == -1){
			break;
		}
	}
	return arr;
}
char *sign_extend(char *oldArr, int ext) {
	//Make a new array of length arr + int
	//If 0 add more 0's
	//If 1 add more 1's ???
	/*Make space for the new extended array*/
	char *arr = malloc((strlen(oldArr) + ext) * sizeof(char));
	int isNeg = oldArr[0] == '1';
	int i = 0;
	/*Build up the padded extension depending on positivity*/
	for (i = ext-1;i >= 0; i--) {
		if (isNeg) {
			arr[i] = '1';
		} else {
			arr[i] = '0';
		}
	}
	/*Return the new extend piece and the old piece combined*/
	return strcat(arr,oldArr);
}
char *add(char *arr1, char *arr2) {
	/*  Malloc a new array of the greater size of arr1 and arr2 ???
	 *	 Add arr1[i] + arr2[i] + carry
	 *	 If greater than 1 set to 0
	 *	 and set carry to 1
	 *	 May be an issue if arr1 = 1, arr2 = 1, carry = 1, should set the val to 1 with carry of 1
	 *	 ?Add carry after the if check??
	 */
	int arr1Size = strlen(arr1);
	int arr2Size = strlen(arr2);
	/*Create two array copies that I can modify without harm*/
	char *binStr1 = malloc(arr1Size * sizeof(char));
	char *binStr2 = malloc(arr2Size * sizeof(char));

	strcpy(binStr1,arr1);
	strcpy(binStr2,arr2);

	if(arr1Size > arr2Size) {
		binStr2 = sign_extend(binStr2);
	} else if (arr1Size < arr2Size) {
		binStr1 = sign_extend(binStr1);
	}
	char *arr = malloc(strlen(binStr1) * sizeof(char));

	int i = 0;
	int carry = 0;
	for(i = strlen(binStr1); i >= 0; i--) {
		arr[i] = ((binStr1 - '0') + (binStr2 - '0') + carry) + '0';
	}

}
//char *sub(char *arr1, char *arr2) {
//	/*
//	 * Call negate on arr2, add 1
//	 * call add
//	 * */
//
//}
//

