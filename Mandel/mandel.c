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
	int h, w;
	double height = 80;
	double width = 21;
	int max = 20;
	double x_scaler = (3 / (height - 1));
	double y_scaler = (2 / (width - 1));
	//printf("x_scaler = %f\n", x_scaler);
	//printf("y_scaler = %f\n", y_scaler);
	for(h = 0; h <= height; h += y_scaler){ //h += scaler
		//printf("%2d ",h);
		//printf("---Outer loop : %d---\n", w);
		double constant_i = 1 - h * y_scaler;
		for(w = 0; w <= width; w += x_scaler){ // w += scaler
			//printf("Inner loop : %d\n", w);
			int iter = 0;
			//int escape_condition = sqrt(zr*zr + zi*zi); /*Or maybe 2?*/
			double constant_r = -2 + w * x_scaler;
			/*Set z = c*/
			double zr = 0;//constant_r;
			double zi = 0;//constant_i;
			print_char(x_scaler, y_scaler);
			/*First peice is the same as the sqrt(a^2 + b^2)*/
//			while(sqrt(zr * zr + zi * zi) <= 2 && iter < max){
			/*	printf("\nIteration : %d\n\n", iter);
				double zi2 = zi * zi; zi^2
				double zr2 = zr * zr;
				double zi_next = 2 * zr * zi + y_scaler; 2abi OR yi
				double zr_next = zr2 - zi2 + x_scaler;
				zi += zi_next;
				zr += zr_next;
				iter++;
			}
			if (iter == 100) {
				printf("*");
			} else {
				printf(" ");
			}*/
		} /*End of row*/
		/*Start next row*/
		printf("\n");
	}

}

void print_char(double x, double y){
	printf("Print Char Function Called!");
	int i;
	double zr = 0, zi = 0;
	for(i = 0; i < 100; i++){
		double zi2 = zi * zi;
		double zr2 = zr * zr;

		double zr_next = zr2 - zi2 + x;
		double zi_next = 2 * zr * zi + y;

		zi = zi_next;
		zr = zr_next;

		if(sqrt(zr * zr + zi * zi) > 2 ){
			printf(" ");
			return;
		}
	}
	printf("*");
}
