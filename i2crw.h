#ifndef I2CRW
#define I2CRW

// for intel edison i2c breakout board from spakfun.com
#define I2C_FILE_NAME "/dev/i2c-1"



/**
 *  Perform a simple I2C write
 *	@param addr address of the slave device
 *	@param *obuff array of bytes to be writen to the slave device
 *	@param len length / number of bytes to be writen to the slave device
 *  @return 1 for pass 0 fail, prints error on STDOUT
 */
int i2c_write(int file,
                            unsigned char addr,
                            unsigned char *obuff,
                            unsigned int len);

/**
 * Performs a mixed transaction I2C, START | WRITE | REPEATED START | READ
 * @param addr address of the slave device
 * @param *obuff array of bytes to be writen to the slave device
 * @param olen length / number of bytes to be writen to the slave device
 * @param *ibuff array to store the received bytes
 * @param ilen length / number of bytes to receive
 * @return 1 for pass 0 fail, prints error on STDOUT
 */
int i2c_rw(int file,
                            unsigned char addr,
                            unsigned char *obuff,
                            unsigned int olen,
                            unsigned char*ibuff,
                            unsigned int ilen);

/**
 * Initilize the I2C interface and returns a number for the file system handle
 */

int i2c_init();

/**
 * close / release resource for the I2C bus
 * @param file the file system handle for the initilazed I2C
 */
void i2c_close(int file);




#endif
