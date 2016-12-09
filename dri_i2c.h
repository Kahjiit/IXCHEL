#ifndef DRI_I2C_H_
#define DRI_I2C_H_
#include <asm/types.h>

void set_i2c(int file,__u8 I2C_ADDR,__u8 I2C_REG,__u8 I2CDATA);
char get_i2c(int file,__u8 I2C_ADDR,__u8 I2C_REG);

#endif
