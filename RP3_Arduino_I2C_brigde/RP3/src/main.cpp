void main()
{
	// in order to find bus , please check on rasberry terminal
	// i2cdetect -y 1 or i2cdetect -y 2
	// then define bus value 
	// Address data should be the same of which is defined on Arduino
	
	int bus =2;
	int addr= 0x10;  // SLAVE_ADDR 0x10
	I2c i2c = new I2C(bus,address); 
	
	// From this point i need to check registers lies in 0x10 by typing i2cdump -y 2 0x10
	i2c->write_byte(addr,0);
	i2c->read_byte(0x10);
	
}