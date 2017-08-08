/*
	# AD7894
	Arduino library for an Analog Devices ADC AD7894 - 10, 14 bit ADC with ±10V range.
	Do not forget about the reference voltage source (+2.5V). Voltage divider, connected to internal Arduino source provides too much noise.

	This version operates with all 4 data pins at the ADC (3-wire serial + BUSY) without interrupts. If you want to use interrupts (BUSY pin could provide interrupt at the falling edge), than use functions from the private field: BeginConversion() and ADCread();

	Class constructor requires number of pins ADC connected to:
	SCLK, SDATA, BUSY, CONVST. The default values are 5,2,3,4. If you connected your ADC to those pins, you can use just <AD7894 myADC>;

	Only 3 functions are available:
	Begin(); - checks PIN's numbers and set them to I/O modes.
	GetVoltage(); - return float value of voltage at the ADC input in Volts. 
	GetError(); - return the error value. 0 is OK, 1 - timeout, 2 - wrong pins set.


	Created by Risele for everyone's use (profit and non-profit).

	ALL THESE WOR_DS
	ARE YOURS EXCEPT
	RISELE
	ATTEMPT NO
	namechangING THERE
	USE THEM TOGETHER
	USE THEM IN PEACE
*/

#ifndef AD7894_h
#define AD7894_h
//Arduino standart libraries
	#if defined(ARDUINO) && ARDUINO >= 100
		#include "Arduino.h"
		#else
		#include "WProgram.h"
	#endif 
class AD7894
{
	public:
	AD7894(uint8_t SCLK = 5,uint8_t SDATA = 2,uint8_t BUSY = 3, uint8_t CONVST = 4);
	void Begin();
	float GetVoltage();
	enum Errors
	{
		noError 	= 0,
		Timeout 	= 1,
		WrongPins 	= 2
	};
	uint8_t GetError();
	private:
	Errors _Error;
	float ADCRead();
	void BeginConversion();
	uint32_t _Timeout=2; //At real, 15 microseconds are enough, but 2 ms are easy to check. 
	uint8_t _SCLK;
	uint8_t _SDATA;
	uint8_t _BUSY;
	uint8_t _CONVST;
	
};

#endif // AD7894_h
