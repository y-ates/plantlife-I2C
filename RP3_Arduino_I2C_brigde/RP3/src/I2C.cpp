#include <sys/ioctl.h>
#include <errno.h>
#include <stdio.h>      /* Standard I/O functions */
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include "I2C.h"
#include <iostream>


using namespace std;

I2C::I2C(int bus, int address) 
{
	_i2cbus = bus;
	_i2caddr = address;
	snprintf(busfile, sizeof(busfile), "/dev/i2c-%d", bus);
	openfd();
}

I2C::~I2C() 
{
	close(fd);
}

void I2C::read_byte(uint8_t address) 
{

	if (fd != -1) 
	{
	    uint8_t data[5]; // addr , data0, data1, data2,data3
		data[0] = address;
		if (write(fd, data, 1) != 1) 
		{
			cout << "read failed"<< endl;
		}
		if (read(fd, data, 4) != 4) 
		{
			cout << "read failed"<< endl;
		}	
		sensor_data_value[0] = data[0]; // temp sensor
		sensor_data_value[1] = data[1]; // hum sensor
		sensor_data_value[2] = data[2]; // other sensor
		sensor_data_value[3] = data[4]; // other sensor

	} 
	else 
	{
		cout << "Device File not available. Aborting read" << endl;
		return (-1);
	}

}

uint8_t I2C::write_byte(uint8_t address, uint8_t data) 
{
	if (fd != -1) 
	{
		uint8_t buff[2];
		buff[0] = address;
		buff[1] = data;
		if (write(fd, buff, sizeof(buff)) != 2)
		{
			cout<<"Failed to write to I2C Slave 0x%x @ register 0x%x [write_byte():write %d]" << endl;
			return (-1);
		}
		else 
		{
			cout<<	"Wrote to I2C Slave 0x%x @ register 0x%x [0x%x]" << endl;
			return (-1);
		}
	} 
	else 
	{
		cout << "Device File not available. Aborting write" << endl;
		return (-1);
	}
	return 0;
}

//! Open device file for I2C Device
void I2C::openfd() {
	if ((fd = open(busfile, O_RDWR)) < 0) 
	{
		cout << "Couldn't open I2C Bus %d [openfd():open %d]" << endl;
	}
	if (ioctl(fd, I2C_SLAVE, _i2caddr) < 0) 
	{
		cout<<"I2C slave %d failed [openfd():ioctl %d]"<<endl;

	}
}
