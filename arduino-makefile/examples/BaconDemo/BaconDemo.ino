//
//  BaconDemo
//
//  Copyright (c) 2013 Parav Nagarsheth
//  Push Button Connected to P8_19, Digital Pin 7

int pushButton = 7;
int sliderPot  = A6;
int ledPin = 3;
void setup() {               
  // initialise digital pins as inputs
  pinMode(pushButton, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int sliderState = analogRead(sliderPot);
  analogWrite(ledPin, sliderState/4);
  // print out the state of the button:
  delay(10);        // delay in between reads for stability
}

