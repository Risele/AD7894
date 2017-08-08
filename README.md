# AD7894
Arduino library for an Analog Devices ADC AD7894 - 10, 14 bit ADC with ±10V range.
Do not forget about the reference voltage source (+2.5V). Voltage divider, connected to internal Arduino source provides too much noise.

This version operates with all 4 data pins at the ADC (3-wire serial + BUSY) without interrupts. If you want to use interrupts (BUSY pin could provide interrupt at the falling edge), than use functions from the private field: BeginConversion() and ADCread();

Class constructor requires numbers of pins ADC connected to:
SCLK, SDATA, BUSY, CONVST. The default values are 5,2,3,4. If you connected your ADC to those pins, you can use just \<AD7894 myADC\>;

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
