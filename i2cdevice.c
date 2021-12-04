#include <stdio.h>
//#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

// This function is called by the dotnet core managed world to read from the I2C bus for the given slave address
//  Returns a negative status code if failed. Returns a positive integer of number of bytes read (bufferLength) if failed.
int ReadI2C(const char* device, const int slaveAddress, void *readBuffer, int bufferLength)
{
    int file = open(device, O_RDWR);
	if (file < 0)
	{
		return file;
	}
	
	int ioStatus = ioctl(file, I2C_SLAVE, slaveAddress);
    if (ioStatus < 0)
	{
		close(file);
		return ioStatus;
	}

    int bytesRead =	read(file, readBuffer, bufferLength);
	close(file);
    return bytesRead;
}