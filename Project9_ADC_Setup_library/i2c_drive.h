void i2c_init(char i2c, unsigned short speed_mode);

#define I2C_FM 0x2d //Fast mode speed
#define I2C_SM 0xB4 //Standard mode speed
void I2C_add(char i2c, char address, char RW);
void I2C_write(char i2c, char address, char data[]);
void I2C_data(char i2c, char data);
void I2C_stop(char i2c);