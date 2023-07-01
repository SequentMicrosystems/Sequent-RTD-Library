/*!
 * @file SM_RTD.h
 * 
 * Designed specifically to work with the Sequent Microsysatems 
 * RTD Data Acquisition 8-Layer Stackable HAT for Raspberry Pi
 * 
 * ----> https://sequentmicrosystems.com/products/rtd-data-acquisition-card-for-rpi
 * 
 *   This card use I2C to communicate.
 *   
 *   Written by Alexandru Burcea for Sequent Microsystems
 * 
 *   Software License Agreement (BSD License)
 *
 *  Copyright (c) 2023, Sequent Microsystems 
 *  
 */
#ifndef __SM_RTD__
#define __SM_RTD__

#define RTD_CHANNEL_NR_MIN		1
#define RTD_CHANNEL_NR_MAX		8

#define OK 0

#define SLAVE_OWN_ADDRESS_BASE 0x40

enum
{
	RTD_VAL1_ADD = 0,
	RTD_VAL2_ADD = RTD_VAL1_ADD + 4,
	RTD_VAL3_ADD = RTD_VAL2_ADD + 4,
	RTD_VAL4_ADD = RTD_VAL3_ADD + 4,
	RTD_VAL5_ADD = RTD_VAL4_ADD + 4,
	RTD_VAL6_ADD = RTD_VAL5_ADD + 4,
	RTD_VAL7_ADD = RTD_VAL6_ADD + 4,
	RTD_VAL8_ADD = RTD_VAL7_ADD + 4,
	DIAG_TEMPERATURE_MEM_ADD = RTD_VAL8_ADD + 4,
	DIAG_5V_MEM_ADD,
	I2C_MEM_WDT_RESET_ADD = DIAG_5V_MEM_ADD + 2,
	I2C_MEM_WDT_INTERVAL_SET_ADD,
	I2C_MEM_WDT_INTERVAL_GET_ADD = I2C_MEM_WDT_INTERVAL_SET_ADD + 2,
	I2C_MEM_WDT_INIT_INTERVAL_SET_ADD = I2C_MEM_WDT_INTERVAL_GET_ADD + 2,
	I2C_MEM_WDT_INIT_INTERVAL_GET_ADD = I2C_MEM_WDT_INIT_INTERVAL_SET_ADD + 2,
	I2C_MEM_WDT_RESET_COUNT_ADD = I2C_MEM_WDT_INIT_INTERVAL_GET_ADD + 2,
	I2C_MEM_WDT_CLEAR_RESET_COUNT_ADD = I2C_MEM_WDT_RESET_COUNT_ADD + 2,
	I2C_MEM_WDT_POWER_OFF_INTERVAL_SET_ADD,
	I2C_MEM_WDT_POWER_OFF_INTERVAL_GET_ADD = I2C_MEM_WDT_POWER_OFF_INTERVAL_SET_ADD + 4,
	REVISION_HW_MAJOR_MEM_ADD  = I2C_MEM_WDT_POWER_OFF_INTERVAL_GET_ADD + 4,
	REVISION_HW_MINOR_MEM_ADD,
	REVISION_MAJOR_MEM_ADD,
	REVISION_MINOR_MEM_ADD,

	RTD_RES1_ADD,
	RTD_RES2_ADD = RTD_RES1_ADD + 4,
	RTD_RES3_ADD = RTD_RES2_ADD + 4,
	RTD_RES4_ADD = RTD_RES3_ADD + 4,
	RTD_RES5_ADD = RTD_RES4_ADD + 4,
	RTD_RES6_ADD = RTD_RES5_ADD + 4,
	RTD_RES7_ADD = RTD_RES6_ADD + 4,
	RTD_RES8_ADD = RTD_RES7_ADD + 4,
	RTD_REINIT_COUNT = RTD_RES8_ADD + 4,
	RTD_SPS1_ADD = RTD_REINIT_COUNT + 4,
	RTD_SPS2_ADD = RTD_SPS1_ADD + 2,
	RTD_CARD_TYPE = RTD_SPS2_ADD+2,
	RTD_RASP_VOLT,
	I2C_MODBUS_SETINGS_ADD = RTD_RASP_VOLT + 2, //5 bytes
	RTD_LEDS_FUNC = I2C_MODBUS_SETINGS_ADD + 5, //2 bytes
	RTD_LED_THRESHOLD1 = RTD_LEDS_FUNC + 2,
	RTD_LED_THRESHOLD2 = RTD_LED_THRESHOLD1 + 2,
	RTD_LED_THRESHOLD3 = RTD_LED_THRESHOLD2 + 2,
	RTD_LED_THRESHOLD4 = RTD_LED_THRESHOLD3 + 2,
	RTD_LED_THRESHOLD5 = RTD_LED_THRESHOLD4 + 2,
	RTD_LED_THRESHOLD6 = RTD_LED_THRESHOLD5 + 2,
	RTD_LED_THRESHOLD7 = RTD_LED_THRESHOLD6 + 2,
	RTD_LED_THRESHOLD8 = RTD_LED_THRESHOLD7 + 2,
	I2C_CALIB_RES = RTD_LED_THRESHOLD8 + 2,//float
	I2C_CALIB_CH = I2C_CALIB_RES + 4,//u8
	I2C_SENSORS_TYPE,
	I2C_MEM_ADS_SAMPLE_SWITCH,//u16

	SLAVE_BUFF_SIZE = 0xff

};


/*!
 * @brief SM_RTD class
 */
class SM_RTD
{
public:
	/*!
	 * @brief Class constructor.
	 */
	SM_RTD(uint8_t stack = 0);

	/*!
	 * @brief Check card presence
	 * @return Returns true is successful
	 */
	bool begin();

	/*!
	 * @brief Return card existance status
	 * @return Returns true if card is present
	 */
	bool isAlive();

	
	/*!
	 * @brief Get one RTD channel temperature in deg Celsious
	 * @param channel - the desired channel 1..8
	 * @return Returns the temperature
	 */
	float readTemp(uint8_t channel);
	
	
	/*!
	 * @brief Get one RTD channel sensor resistance
	 * @param channel - the desired channel 1..8
	 * @return Returns the resistance in ohms
	 */
	float readRes(uint8_t channel);

private:
	uint8_t _hwAdd;
	bool _detected;
	int writeByte(uint8_t add, uint8_t value);
	int readByte(uint8_t add, uint8_t* value);
	int readFloat(uint8_t add, float *value);
};

#endif //__SM_BAS__
