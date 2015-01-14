/**
 * @file   i2crw.c
 * @Author sajin.geo@gmail.com
 * @date   Jan 12th 2015
 * @brief  API for using the repeated start feature of the I2C bus
 *
 * Wraper library to i2c. based on the work of Sean Cross / chumby industries , Copyright (c) 2010, released under BSD licence
 */
#include <stdio.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include "i2crw.h"



int i2c_write(int file,
                            unsigned char addr,
                            unsigned char *obuff,
                            unsigned int len) {
	struct i2c_rdwr_ioctl_data packets;
	struct i2c_msg messages[1];
	
    messages[0].addr  = addr;
    messages[0].flags = 0;
    messages[0].len   = len;
    messages[0].buf   = obuff;
    
    packets.msgs  = messages;
    packets.nmsgs = 1;
    if(ioctl(file, I2C_RDWR, &packets) < 0) {
            perror("Unable to send W data");
            return 1;
    }
    return 0;
}

int i2c_rw(int file,
                            unsigned char addr,
                            unsigned char *obuff,
                            unsigned int olen,
                            unsigned char*ibuff,
                            unsigned int ilen) {
	
		struct i2c_rdwr_ioctl_data packets;
	    struct i2c_msg messages[2];
	    
	    // tx message
	    messages[0].addr  = addr;
	    messages[0].flags = 0;
	    messages[0].len   = olen;
	    messages[0].buf   = obuff;
	    
	    // rx message
	    messages[1].addr  = addr;
	    messages[1].flags = I2C_M_RD/* | I2C_M_NOSTART*/;
	    messages[1].len   = ilen;
	    messages[1].buf   = ibuff;
	    
	    packets.msgs      = messages;
	    packets.nmsgs     = 2;
	    
	    if(ioctl(file, I2C_RDWR, &packets) < 0) {
	            perror("Unable to send RW data");
	            return 1;
	        }
}


int i2c_init()
{
int i2c_file;
if ((i2c_file = open(I2C_FILE_NAME, O_RDWR)) < 0) {
		        perror("Unable to open i2c control file");
		        exit(1);
		    }
}


void i2c_close(int file)
{
	close(file);
}



//int main(int argc, char **argv) {
//	int i2c_file,i=0;
//	unsigned char ottbuff[]={0x00};
//	unsigned char outbuf[]={0x00,0xB8,0x0D,0x1F,0x74};
//	unsigned char ibuffer[248];
//	// Open I2C file
//	i2c_file = i2c_init();
//	
//	
//	
//	 	if(i2c_write(i2c_file,0x60,outbuf,5))
//	 	{
//	 		printf("unable to write to register");
//	 	}
//	 	
//	 	if (i2c_rw(i2c_file,0x50,ottbuff,1,ibuffer,248))
//	 	{
//	 		printf("unable to read from register");
//	 	}
//	 	for (i=0;i<=248;i++)
//	 	{
//	 		printf("%x ",ibuffer[i]);
//	 	}
//	
//	 	i2c_close(i2c_file);
//	    return 0;
//}
