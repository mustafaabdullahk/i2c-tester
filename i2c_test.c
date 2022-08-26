/*
 * i2c_test.c
 *
 *  Created on: Feb 27, 2020
 *      Author: mustafa
 */
#include "project.h"
#include "i2c_test.h"

I2C_Handle      i2c;
I2C_Params      i2cParams;
I2C_Transaction i2cTransaction;

void i2c_yaz(unsigned char slaveAddr,unsigned char regAddr, const void* txData, int txDataSize)
{
    i2cTransaction.slaveAddress = slaveAddr;
    i2cTransaction.writeBuf=&regAddr;
    i2cTransaction.writeCount = txDataSize;
    i2cTransaction.readBuf = 0;
    i2cTransaction.readCount = 0;
    I2C_transfer(i2c,&i2cTransaction);
}
int i2c_oku(unsigned char slaveAddr, unsigned char regAddr, void* rxData, int rxDataSize)
{
    i2cTransaction.slaveAddress = slaveAddr;
    i2cTransaction.writeBuf=&regAddr;
    i2cTransaction.writeCount=1;
    i2cTransaction.readBuf=rxData;
    i2cTransaction.readCount=rxDataSize;
    if(I2C_transfer(i2c,&i2cTransaction))
    {
        return rxDataSize;
    }
    else
    {
        return 0;
    }
}
void i2c_kurulum()
{
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400kHz;
    i2cParams.transferMode= I2C_MODE_BLOCKING;
    i2c = I2C_open(Board_I2C0, &i2cParams);
    if (i2c == NULL)
    {
        System_abort("I2C kurulamadı!\n");
    }
    else
    {
        System_printf("I2C Kuruldu!\n");
    }
}



