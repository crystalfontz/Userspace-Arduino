# Demo

**Example**
Check the PWM output using LED

``` cpp
int ledPin = 3; // LED is connected to P3.16 (see Pinout table)

void setup()
{
  pinMode(ledPin, OUTPUT);  // sets the pin as output
}

void loop()
{
    analogWrite(ledPin, 128);
}

```

**Exercise**

---
use PWM to demonstrate fading effect in LED
``` js
// Write your code here :)
```

``` cpp
int ledPin = 5;    // LED connected to P3.17

void setup()  {
  // nothing happens in setup
}

void loop()  {
  // fade in from min to max in increments of 5 points:
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}
```

``` js

```
---

Output of above:

[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/bATbqSoX-gE/0.jpg)](https://www.youtube.com/watch?v=bATbqSoX-gE)
