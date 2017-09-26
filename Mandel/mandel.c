/*
 * mandel.c
 *
 *  Created on: Sep 22, 2017
 *      Author: Austin Klum
 */

#include <stdio.h>
#include <math.h>

void print_char(double x, double y);

int main(int argc , char **argv){
	double x, y;
	double height = 80;
	double width = 21;
	double x_scaler = 3 / (height - 1);
	double y_scaler = 2 / (width - 1);
	for(y = -1; y <= 1; y += y_scaler){
		for(x = -2; x <= 1; x += x_scaler){
			print_char(x, y);
		} /*End of row*/
		/*Start next row*/
		printf("\n");
	}


}

void print_char(double x, double y){
	int i;
	double zr = 0, zi = 0;
	for(i = 0; i < 100; i++){
		double zi2 = zi * zi;
		double zr2 = zr * zr;

		double zr_next = zr2 - zi2 + x;
		double zi_next = 2 * zr * zi + y;

		zi = zi_next;
		zr = zr_next;

		zr2 = zr * zr;
		zi2 = zi * zi;

		if(sqrt(zr2 + zi2) > 2 ){
			break;
		}
	}
	if(i == 100){
		printf("*");
	}else{
		printf(" ");
	}
}
