/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

void setup() {                
  // initialize the digital pin as an output.
  // Pin 15 has an LED connected on Beaglebone Black:
  pinMode(2, OUTPUT);
  digitalWrite(2, 1);
}

void loop() {
  digitalWrite(2, 1);   // set the LED on
  delay(1000);              // wait for a second
  digitalWrite(2, 0);    // set the LED off
  delay(1000);              // wait for a second
}

