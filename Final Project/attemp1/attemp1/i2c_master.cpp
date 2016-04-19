#include <avr/io.h>
#include <util/twi.h>
#include <interface/i2c_master.h>

#define READ 0x01
#define WRITE 0x00

VOID I2c::initialize(UINT32 scl_frequency, UINT8 prescaler)
{
	TWBR = (((F_CPU / scl_frequency) - 16) / (2 * (1 << (2 * prescaler))));
	TWSR &= 0xFC;
	TWSR |= prescaler;
}

BOOL I2c::read_register(UINT8 devaddr, UINT8 regaddr, UINT8 *data, UINT16 length)
{
	if(!start(devaddr))
	{
		return FALSE;
	}

	write(regaddr);

	if (!start(devaddr | 0x01))
	{
		return FALSE;
	}

	for (UINT16 i = 0; i < length - 1; i++)
	{
		data[i] = read_ack();
	}
	data[length - 1] = read_nack();

	stop();

	return TRUE;
}

BOOL I2c::write_register(UINT8 devaddr, UINT8 regaddr, UINT8 *data, UINT16 length)
{
	if (!start(devaddr | WRITE))
	{
		return FALSE;
	}

	write(regaddr);

	for (UINT16 i = 0; i < length; i++)
	{
		if (!write(data[i]))
		{
			return FALSE;
		}
	}

	stop();

	return TRUE;
}

BOOL I2c::read_ack()
{
	//start TWI module and acknowledge data after reception
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

	//wait for end of transmission
	while(!(TWCR & (1 << TWINT)));

	//return received data from TWDR
	return TWDR;
}

BOOL I2c::read_nack()
{
	//start receiving without acknowledging reception
	TWCR = (1 << TWINT) | (1 << TWEN);

	//wait for end of transmission
	while(!(TWCR & (1 << TWINT)));

	//return received data from TWDR
	return TWDR;
}

BOOL I2c::write(UINT8 data)
{
	//load data into data register
	TWDR = data;

	//start transmission of data
	TWCR = (1 << TWINT) | (1 << TWEN);

	//wait for end of transmission
	while(!(TWCR & (1 << TWINT)));

	if((TWSR & 0xF8) != TW_MT_DATA_ACK)
	{
		return FALSE;
	}
	
	return TRUE;
}

BOOL I2c::transmit(UINT8 address, UINT8 *data, UINT16 length)
{
	if (!start(address | WRITE))
	{
		return FALSE;
	}
	
	for (UINT16 i = 0; i < length; i++)
	{
		if (!write(data[i]))
		{
			return FALSE;
		}
	}
	
	stop();
	
	return TRUE;
}

BOOL I2c::receive(UINT8 address, UINT8 *data, UINT16 length)
{
	if (!start(address | READ))
	{
		return FALSE;
	}
	
	for (UINT16 i = 0; i < length - 1; i++)
	{
		data[i] = read_ack();
	}
	data[length - 1] = read_nack();
	
	stop();
	
	return TRUE;
}

BOOL I2c::start(UINT8 address)
{
	//reset TWI control register
	TWCR = 0;

	//transmit START condition
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	//wait for end of transmission
	while(!(TWCR & (1 << TWINT)));

	//check if the start condition was successfully transmitted
	if((TWSR & 0xF8) != TW_START)
	{
		return FALSE;
	}

	//load slave address into data register
	TWDR = address;

	//start transmission of address
	TWCR = (1 << TWINT) | (1 << TWEN);

	//wait for end of transmission
	while(!(TWCR & (1 << TWINT)));

	//check if the device has acknowledged the READ / WRITE mode
	UINT8 twst = TW_STATUS & 0xF8;
	if ((twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK))
	{
		return FALSE;
	}
	
	return TRUE;
}

VOID I2c::stop()
{
	//transmit STOP condition
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}