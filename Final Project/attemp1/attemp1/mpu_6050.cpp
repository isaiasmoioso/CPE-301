#include <device/mpu_6050.h>
#include <interface/i2c_master.h>

#include <util/delay.h>

mpu_6050::mpu_6050()
{
}

VOID mpu_6050::initialize()
{
	I2c::initialize(100000, 1);

	UINT8 data;

	//xxx00xxx
	data = 0x00;
	I2c::write_register(0x68 << 1, 0x1B, &data, 1);

	//xxx00xxx
	data = 0x00;
	I2c::write_register(0x68 << 1, 0x1C, &data, 1); //2g range

	//x0xxxxx1
	data = 0x01;
	I2c::write_register(0x68 << 1, 0x6B, &data, 1);
}

VOID mpu_6050::read_sensor()
{
	I2c::read_register(0x68 << 1, 0x3b, accel, 6); //ACCEL_XOUT_H
	I2c::read_register(0x68 << 1, 0x43, gyro, 6); //GYRO_XOUT_H

	AcX = accel[0] << 8 | accel[1];
	AcY = accel[2] << 8 | accel[3];
	AcZ = accel[4] << 8 | accel[5];

	GyX = gyro[0] << 8 | gyro[1];
	GyY = gyro[2] << 8 | gyro[3];
	GyZ = gyro[4] << 8 | gyro[5];
}
