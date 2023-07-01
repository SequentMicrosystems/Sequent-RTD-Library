extern "C" {
#include <inttypes.h>
}

#include "Arduino.h"
#include "Wire.h"
#include "SM_RTD.h"

SM_RTD::SM_RTD(uint8_t stack)
{
	if (stack > 7)
		stack = 7;
	_hwAdd = SLAVE_OWN_ADDRESS_BASE + stack;
	_detected = false;
}

bool SM_RTD::begin()
{
	uint8_t value = 0;
	Wire.begin();
	if (0 == readByte(REVISION_MAJOR_MEM_ADD, &value))
	{
		_detected = true;
	}
	return _detected;
}

bool SM_RTD::isAlive()
{
	return _detected;
}

float SM_RTD::readTemp(uint8_t channel)
{
	uint8_t buff[4];
	float val = -1000;
	if (channel > RTD_CHANNEL_NR_MAX || channel == 0)
	{
		return (float)-1000;
	}

	if (OK != readFloat(RTD_VAL1_ADD + sizeof(float) * (channel -1), &val))
	{
		return (float)-1001;
	}
	return val;
}


float SM_RTD::readRes(uint8_t channel)
{
	uint8_t buff[4];
	float val = -1000;
	if (channel > RTD_CHANNEL_NR_MAX || channel == 0)
	{
		return (float)-1;
	}

	if (OK != readFloat(RTD_RES1_ADD + sizeof(float) * (channel -1), &val))
	{
		return (float)-2;
	}
	return val;
}
/*
 ***************** RTD_I2C access functions ****************************
 **********************************************************************
 */
int SM_RTD::writeByte(uint8_t add, uint8_t value)
{
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	Wire.write(value);
	return Wire.endTransmission();
}


int SM_RTD::readByte(uint8_t add, uint8_t *value)
{
	if (0 == value)
	{
		return -1;
	}
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	if (Wire.endTransmission() != 0)
	{
		return -1;
	}
	Wire.requestFrom(_hwAdd, (uint8_t)1);
	if (1 <= Wire.available())
	{
		*value = Wire.read();
	}
	else
	{
		return -1;
	}
	return 0;
}



int SM_RTD::readFloat(uint8_t add, float *value)
{
	uint8_t buff[4];
	int i = 0;

	if (0 == value)
	{
		return -1;
	}
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	if (Wire.endTransmission() != 0)
	{
		return -1;
	}
	Wire.requestFrom(_hwAdd, (uint8_t)4);
	if (4 <= Wire.available())
	{
		for (i = 0; i < 4; i++)
		{
			buff[i] = Wire.read();
		}
	}
	else
	{
		return -1;
	}
	memcpy(value, buff, 4);
	return 0;
}