#ifndef _MPU_6050_H_
#define _MPU_6050_H_

#include <core/defs.h>

class mpu_6050
{
public:
	mpu_6050();
	UINT16 AcX, AcY, AcZ, GyX, GyY, GyZ;
	UINT8 accel[6];
	UINT8 gyro[6];

	VOID initialize();
	VOID read_sensor();
};

#endif
