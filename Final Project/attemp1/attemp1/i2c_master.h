#ifndef _I2C_MASTER_H_
#define _I2C_MASTER_H_

#include <core/defs.h>

class I2c
{
public:
	//prescaler: 0: 1, 1: 4, 2: 16, 3: 64
	static VOID initialize(UINT32 scl_frequency, UINT8 prescaler);
	
	static BOOL read_register(UINT8 devaddr, UINT8 regaddr, UINT8 *data, UINT16 length);
	static BOOL write_register(UINT8 devaddr, UINT8 regaddr, UINT8 *data, UINT16 length);

private:
	static BOOL start(UINT8 address);
	static VOID stop();
	static BOOL read_ack();
	static BOOL read_nack();
	static BOOL write(UINT8 data);
	static BOOL transmit(UINT8 address, UINT8 *data, UINT16 length);
	static BOOL receive(UINT8 address, UINT8 *data, UINT16 length);
};

#endif
