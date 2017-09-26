/*
 * mandel.c Prints out a ASCII Art style Mandelbrot set.
 *
 *  Created on: Sep 22, 2017
 *      Author: Austin Klum
 */

#include <stdio.h>
#include <math.h>

/*Print a character at a specific point*/
void print_char(double x, double y);

int main(int argc , char **argv){
	double x, y;
	double height = 80;
	double width = 21;

	/*Scale the (x,y) coordinates to fit inside the bounds*/
	double x_scaler = 3 / (height - 1);
	double y_scaler = 2 / (width - 1);

	/*Loop through each point on the grid*/
	for(y = -1; y <= 1; y += y_scaler){
		for(x = -2; x <= 1; x += x_scaler){
			/*Print a character at a specific point*/
			print_char(x, y);
		} /*End of row*/
		/*Start next row*/
		printf("\n");
	}


}
/*Print a character at a specific point*/
void print_char(double x, double y){
	int i, max_i = 100;
	double zr = 0, zi = 0;

	/*Test weather or not the sequence coverage or diverges*/
	for(i = 0; i < max_i; i++){
		double zi2 = zi * zi;
		double zr2 = zr * zr;

		/*Compute the next real piece and next imaginary piece*/
		double zr_next = zr2 - zi2 + x;
		double zi_next = 2 * zr * zi + y;

		/*Set the values to the next values*/
		zi = zi_next;
		zr = zr_next;

		zr2 = zr * zr;
		zi2 = zi * zi;

		/*The sequence diverges*/
		if(sqrt(zr2 + zi2) > 2 ){
			break;
		}
	}
	/*If it converges print a * */
	if(i == max_i){
		printf("*");
	}else{
		printf(" ");
	}
}
