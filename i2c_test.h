/*
 * i2c_test_.h
 *
 *  Created on: Feb 27, 2020
 *      Author: mustafa
 */

#ifndef I2C_TEST_H_
#define I2C_TEST_H_

void i2c_yaz(unsigned char slaveAddr,unsigned char regAddr, const void* txData, int txDataSize);
int i2c_oku(unsigned char slaveAddr, unsigned char regAddr, void* rxData, int rxDataSize);
void i2c_kurulum();

#endif /* I2C_TEST_H_ */
