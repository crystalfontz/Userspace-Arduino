/*
  SPI 7Segment with shift register

  created 29 Dec 2013
  by Siddharth Bharat Purohit
*/

#include<SPI.h>

#define SS 4

void setup()
{
  pinMode(SS,OUTPUT);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV4);		
  SPI.setDataMode(SPI_MODE0);			
  SPI.setBitOrder(MSBFIRST);
}
void loop()
{
  byte b ;
  
  b = SPI.transfer(~0x3F);
  delay(1000);
  b = SPI.transfer(~0x06);
  delay(1000);
  b = SPI.transfer(~0x5B);
  delay(1000);
  b = SPI.transfer(~0x4F);
  delay(1000);
  b = SPI.transfer(~0x66);
  delay(1000);
  b = SPI.transfer(~0x6D);
  delay(1000);
  b = SPI.transfer(~0x7D);
  delay(1000);
  b = SPI.transfer(~0x07);
  delay(1000);
  b = SPI.transfer(~0x7F);
  delay(1000);
  b = SPI.transfer(~0x6F);
  delay(1000);
  b = SPI.transfer(~0x77);
  delay(1000);
  b = SPI.transfer(~0x7C);
  delay(1000);
  b = SPI.transfer(~0x39);
  delay(1000);
  b = SPI.transfer(~0x5E);
  delay(1000);
  b = SPI.transfer(~0x79);
  delay(1000);
  b = SPI.transfer(~0x71);
  delay(1000);
}
