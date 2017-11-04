/*
 * binstr.c
 *
 *  Created on: Nov 3, 2017
 *      Author: Austin Klum
 */
#include <stdio.h>
#include <stdlib.h>
#include "binstr.h"

int main(int argc, char **argv){
	int x = -1;
	printf("How many bits for %d : %d\n",x, how_many_bits(x));
	printf("Binary String rep of %d : %s",x,decimal_to_binary(x));
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
		arr[0] = '1';
	}

	return arr;
}
//int binary_to_decimal(char *arr) {
//	/* start at end of array and set base to 1. While not at the start of the array
//	 *  dec_val = dec_val + arr[i] * base
//	 *  base *= 2
//	*/
//}
//char *negate(char *arr) {
//	/* loop through everything if 0 then 1
//	 * else if 1 then 0
// 	 */
//}
//char *sign_extend(char *arr, int) {
//	//Make a new array of length arr + int
//	//If 0 add more 0's
//	//If 1 add more 1's ???
//}
//char *add(char *arr1, char *arr2) {
//	/*  Malloc a new array of size arr1 + arr2
//	 *	 Add arr1[i] + arr2[i] + carry
//	 *	 If greater than 1 set to 0
//	 *	 and set carry to 1
//	 *	 May be an issue if arr1 = 1, arr2 = 1, carry = 1, should set the val to 1 with carry of 1
//	 *	 ?Add carry after the if check??
//	 */
//}
//char *sub(char *arr1, char *arr2) {
//	/*
//	 * Call negate on arr2, add 1
//	 * call add
//	 * */
//
//}
//

