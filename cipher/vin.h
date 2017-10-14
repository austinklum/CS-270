/*
 * vin.h
 *
 *  Created on: Oct 12, 2017
 *      Author: Austin Klum
 */

#ifndef VIN_H_
#define VIN_H_

int decryptV(char *key, char *str, int keyIndex);
int encryptV(char *key, char *str, int isDecrypt, int keyIndex);

#endif /* VIN_H_ */
