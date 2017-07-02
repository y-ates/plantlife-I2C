
#ifndef I2C_H_
#define I2C_H_
#include <inttypes.h>

class I2C 
{
public:
	I2C(int, int);
	virtual ~I2C();
	void read_byte(uint8_t);
	uint8_t write_byte(uint8_t, uint8_t);

private:
	int _i2caddr;
	int _i2cbus;
	void openfd();
	char busfile[64];
	uint8_t sensor_data_value[4];
	int fd;
};

#endif /* I2C_H_ */
