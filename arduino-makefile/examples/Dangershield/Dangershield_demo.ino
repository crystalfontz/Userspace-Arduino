/***************************************************************************************
  Dangershield Demo
  For testing with CFA10036
  created 10 Sep 2014
  by Mitul Vekariya <vekariya93@gmail.com>

* CONNECTIONS:
-----------------------------
Dangershield    |  CFA10037 |
-----------------------------
SERIAL_IN       |   P0.28   |
LATCH           |   P0.17   |
CLOCK           |   P0.24   |
D5              |   P3.16   |
D6              |   P3.07   |
A0              |   LRADC0  |
-----------------------------

NOTE: * Use voltage divider circuit before applying output from A0(slider) to LRADC0.
        (5V to 1.8V conversion)
      * Maximum value for LRADC0 is 1.8V
      
* Expected Output:
    * Intensity of D5 will change as per Slider A0 value
    * Time period for D6 (LED) blinking is 1 sec
    * seven segment display will update every 1 sec
    
***************************************************************************************/
#include <SPI.h>

#define LED0    3       // PWM
#define LED1    4       // GPIO

#define SLIDER0 A0      // ADC

uint8_t sevenSegmentData[] = {~0x3F, ~0x06, ~0x5B, ~0x4F, ~0x66, ~0x6D, ~0x7D, ~0x07, \
                        ~0x7F, ~0x6F, ~0x77, ~0x7C, ~0x39, ~0x5E, ~0x79, ~0x71};

void setup()
{
  pinMode(LED1, OUTPUT);                    // set LED1 pin as OUTPUT
  
  SPI.begin();                              // Initialize SPI
  SPI.setClockDivider(SPI_CLOCK_DIV4);		// Set clock divider
  SPI.setDataMode(SPI_MODE0);			    // Set mode to MODE0
  SPI.setBitOrder(MSBFIRST);                // Set MSBFIRST bit order
}
void loop()
{
  static char index = 0;
  static unsigned int sliderValue = 0;
  
  SPI.transfer(sevenSegmentData[index%16]);
  index++;
  sliderValue = analogRead(SLIDER0);
  
  digitalWrite(LED1, index%2);
  analogWrite(LED0, sliderValue/8);
  
  delay(1000);
}
