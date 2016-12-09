#include<stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
//#include <linux/i2c-dev.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "dri_i2c.h"

//#define I2C_ADDR=0x1e;


void main()
{
        __u8 I2C_ADD=0x1e;
        int file = open("/dev/i2c-1", O_RDWR);
        set_i2c ( file, I2C_ADD, 0x00, 0x70 );
        char val = get_i2c ( file, I2C_ADD, 0x00  );
        fprintf(stderr, "%x\n",val);
        close(file);
}

