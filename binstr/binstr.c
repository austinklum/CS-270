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

//int main(int argc, char **argv){
//	int x = 2;
//	int z = 8;
//	char *y = decimal_to_binary(x);
//	char *w = decimal_to_binary(z);
////	printf("How many bits for %d : %d\n",x, how_many_bits(x));
////	printf("Binary String rep of %d : %s\n",x,y);
////	printf("Taking Binary String %s into decimal : %d\n",y,binary_to_decimal(y));
////	printf("Negating %s to %s\n",y,negate(y));
////	printf("Sign Extending by 3 to %s : %s\n",y,sign_extend(y,3));
////	printf("Adding %d-[%s] and %d-[%s] to get %s : %d\n",x,y,z,w,add(y,w),binary_to_decimal(add(y,w)));
////	printf("Subbing %d-[%s] and %d-[%s] to get %s : %d\n",x,y,z,w,sub(y,w),binary_to_decimal(sub(y,w)));
//	char *l = sign_extend(y,z);
//	printf("\n%d : %s extended by %d = %s\n",x,y,z,l);
//
//	return 0;
//}

//Im not sure if this accurately represent a 2's complement bit count
int how_many_bits(int dec) {
	//Divide by 2 until dec is 0. Keep a count of times this was done.
	if (dec == 0) {
		return 1;
	}
	int count = 1;

	/*Handle negative powers of 2*/
	if(dec < 0 && (dec*-1 & (dec*-1 - 1)) == 0 ) {
		count = 0;
	}
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
		char* tempArr = negate(arr);
		free(arr);
		return tempArr;
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
	char *tempArr = NULL;
	if (isNeg) {
		/*The issue lies here*/
		tempArr = negate(arr);
	} else {
		tempArr = arr;
	}

	for(i = size - 1; i >= 0; i--){
		dec += (tempArr[i] - '0') * base;
		base *= 2;
	}
	if(isNeg) {
		dec *= -1;
		free(tempArr);
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
	char *arr = malloc((size + 1) * sizeof(char));
	arr[size] = '\0';
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
char *sign_extend(char *binStr, int ext) {
	//Make a new array of length arr + int
	//If 0 add more 0's
	//If 1 add more 1's
	/*ext is less than binstr return a copy*/
	if(ext < strlen(binStr)){
		char *arr = malloc((strlen(binStr) + 1 )* sizeof(char));
		arr[strlen(binStr)] = '\0';
		return strcpy(arr,binStr);
	}

	/*Make space for the new extended array*/
	char *newPart = malloc((ext+1) * sizeof(char));
	newPart[ext-strlen(binStr)]='\0';
	int isNeg = binStr[0] == '1';
	int i = 0;
	/*Build up the padded extension depending on positivity*/
	for (i = 0; i < ext - strlen(binStr); i++) {
		if (isNeg) {
			newPart[i] = '1';
		} else {
			newPart[i] = '0';
		}
	}
	/*Return the new extend piece and the old piece combined*/
	return strcat(newPart,binStr);
}
char *add(char *arr1, char *arr2) {
	/*  Malloc a new array of the greater size of arr1 and arr2 ???
	 *	 Add arr1[i] + arr2[i] + carry
	 *	 If greater than 1 set to 0
	 *	 and set carry to 1
	 *	 May be an issue if arr1 = 1, arr2 = 1, carry = 1, should set the val to 1 with carry of 1
	 *	 ?Add carry after the if check??
	 */
	int max = strlen(arr1) < strlen(arr2) ?  strlen(arr2) : strlen(arr1);

	/*Create two array copies that I can modify without harm*/
	char *binStr1 = sign_extend(arr1, max);
	char *binStr2 = sign_extend(arr2, max);

	char *arr = malloc((max+1) * sizeof(char));
	arr[max] = '\0';
	int i = 0;
	int carry = 0;
	for(i = max - 1; i >= 0; i--) {
		/*Get the int rep of adding the binary digits together*/
		int newNum = (binStr1[i] - '0') + (binStr2[i] - '0') + carry;
		if(newNum == 0 || newNum == 1){
			arr[i] = newNum + '0';
			carry = 0;
		/*Number must be 2 or 3*/
		} else {
			/*Subtracting two and adding '0' will shift 2 and 3 to 0 and 1*/
			arr[i] = (newNum - 2) + '0';
			carry = 1;
		}
	}
	free(binStr1);
	free(binStr2);

	/*Handle overflow*/
	if(arr1[0] == arr2[0] && arr[0] != arr1[0]){
		/*Make more space*/
		arr = realloc(arr,(strlen(arr) + 2) * sizeof(char));
		for(i = strlen(arr)+1;i >= 0; i--) {
			arr[i+1] = arr[i];
		}
		arr[0] = '*';
	}
	return arr;

}
char *sub(char *arr1, char *arr2) {
	/*
	 * Call negate on arr2
	 * call add
	 * */
	char *neg = negate(arr2);
	char *res = add(arr1,neg);
	free(neg);
	return res;
}

/* Alternative Method names
 * ************************* */
/*int hmb(int dec) {
	return how_many_bits(dec);
}

char *d2b(int dec) {
	return decimal_to_binary(dec);
}

int b2d(char *bin) {
	return binary_to_decimal(bin);
}

char *neg(char *bin) {
	return negate(bin);
}

char *sgn(char *bin, int ext) {
	return sign_extend(bin,ext);
}

char *sign_ext(char *bin, int ext) {
	return sign_extend(bin,ext);
}

char *add_bin(char *bin1, char *bin2) {
	return add(bin1,bin2);
}

char *add_dec(int n1, int n2){
	return add(binary_to_decimal(n1),binary_to_decimal(n2));
}

char *sub_bin(char *bin1, char *bin2) {
	return sub(bin1,bin2);
}

char *sub_dec(int n1, int n2){
	return sub(binary_to_decimal(n1),binary_to_decimal(n2));
}*/





