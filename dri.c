#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "dri_i2c.h"

/*These Functions need to open and close the 
file externally; int file = open("/dev/i2c-1", O_RDWR);
close(file)*/

void                                                                        
set_i2c( int file, __u8 I2C_ADDR,                                           
         __u8 I2C_REG, __u8 I2CDATA )                                       
{                                                                           
	static char buf[2]={0};
	buf[0]=I2C_REG;                                            
	buf[1]=I2CDATA;        
        static const void * ptr = buf;                                                                   
        if (file < 0) { printf("Error opening file: %s\n", strerror(errno));         
                return; }                                                            
                                                                                       
        if (ioctl(file, I2C_SLAVE, I2C_ADDR) < 0) {                                    
                printf("ioctl error: %s\n", strerror(errno));                          
                return;}                                                               
                                                                                       
        if (write(file, ptr, 2) != 2) { fprintf (stderr, "i2c transaction failed\n");  
                return; }                                                              
                                                                                       
        else { fprintf (stderr, "I2C Write 0x%x = 0x%x Succeed!\n",I2C_REG,I2CDATA); }
}


char                                                                                                    
get_i2c( int file, __u8 I2C_ADDR,                                                                        
         __u8 I2C_REG)                                                                                   
{                                                                                                        
        char buf[1]={0};                                                                                 
	char reg[1]={0}; reg[0]=I2C_REG;
	const void * wptr= reg;
	void * rptr = buf;                                                                                                         
        if (file < 0) { printf("Error opening file: %s\n", strerror(errno));                             
                return 1; }                                                                                
                                                                                                         
        if (ioctl(file, I2C_SLAVE, I2C_ADDR) < 0) {                                                      
                printf("ioctl error: %s\n", strerror(errno));                                            
                return 1;}                                                                                 
                                                                                                         
        if (write(file, wptr, 1) != 1) { fprintf (stderr, "i2c can't access the address specified\n");
                return 1; }                                                                                
                                                                                                         
        else { read(file, rptr, 1);                                                                       
                fprintf (stderr, "I2C Read 0x%x = 0x%x Succeed!\n",I2C_REG,buf[0]);                      
                return buf[0]; }                                                                            
} 
