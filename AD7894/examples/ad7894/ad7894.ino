#include <AD7894.h>

AD7894 myADC(5,2,3,4);
void setup() {
myADC.Begin();
Serial.begin(19200);
}

void loop() {
Serial.println(myADC.GetVoltage(),4);
delay(10);
}
