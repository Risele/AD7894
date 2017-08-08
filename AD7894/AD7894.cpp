#include <AD7894.h > 
	AD7894::AD7894(uint8_t SCLK, uint8_t SDATA, uint8_t BUSY, uint8_t CONVST)
{
	if (
		((SCLK > 0) && (SDATA > 0) && (BUSY > 0) && (CONVST > 0))
		&&
		((SCLK != SDATA) && (SCLK != BUSY) && (SCLK != CONVST))
		&& 
		((SDATA != BUSY) && (SDATA != CONVST))
		&&
		(BUSY != CONVST)
		)
	{
		_Error = noError;
		_SCLK = SCLK;
		_SDATA = SDATA;
		_BUSY = BUSY;
		_CONVST = CONVST;
	}
	else
	{
		_Error = WrongPins;
	}
}
void AD7894::Begin()
{
	pinMode(_SCLK,OUTPUT);
	pinMode(_SDATA,INPUT_PULLUP);
	pinMode(_BUSY,INPUT_PULLUP);
	pinMode(_CONVST,OUTPUT);
	
	digitalWrite(_SCLK,LOW);
	digitalWrite(_CONVST,LOW);
	
	
	//Clear buffer
	delayMicroseconds(100);
	for (uint8_t i = 0; i<16; i++)
	{
		digitalWrite(_SCLK,HIGH);
		//Wait at least 1/16MHz , but this is the maximum oscillator frequency
		digitalWrite(_SCLK,LOW);
	}
	
}

float AD7894::GetVoltage()
{
	if (_Error!=WrongPins)
	{
		//Start convertion at Auto Sleep mode
		
		digitalWrite(_CONVST,HIGH);
		digitalWrite(_CONVST,LOW);
		//Wait before convertion ends
		uint32_t startT = millis();
		while((digitalRead(_BUSY) == HIGH) && ((millis()-startT)<_Timeout))
		{
			//Do nothing, just wait
		}
		if ((millis()-startT)<=_Timeout)
		{
			_Error = noError;
			return ADCread();
		}
		else
		{
			_Error = Timeout;
			return 0.;
		}
	}
	else
	{
		return 0.;
	}
		
}

uint8_t AD7894::GetError()
{
	return (uint8_t)_Error;
}

float AD7894::ADCread();
{
	int16_t RawValue = 0;
	for (uint8_t i = 0; i<16; i++)
	{
		/*
		According to the datasheet, 
		"Serial data is clocked out from the SDATA line on the falling edge
		of this clock and is valid on both the rising and falling edges of SCLK"
		But I found, that there is error if you try to achieve data after SCLK set to LOW.
		*/
		RawValue = RawValue<<1;
		digitalWrite(_SCLK,HIGH);
		if (digitalRead(_SDATA))
		{
			RawValue++;
		}
		digitalWrite(_SCLK,LOW);
	}
	RawValue^=0x2000; //Convert according to twos compliment (recommended at http://community.silabs.com/t5/8-bit-MCU/convert-two-compliment-numbers/td-p/8015)
	return ((float)(RawValue-8192))*0.00122;
}