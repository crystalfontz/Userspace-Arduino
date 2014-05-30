# GPIO API
---------------------------------------------------

**syntax**

* pinMode (pin,mode)
* digitalRead (pin)
* digitalWrite (pin, value)

**parameters**

* **pin:** pin no of digital pin as per Arduino Uno board
* **mode:** INPUT or OUTPUT (INPUT_PULLUP is not available)
* **value:** HIGH or LOW

```
NOTE:
* Do not connect more than 3.3V source to Digital pins
* Digital pin provides maximum 3.3V output only
* Do not use PWM and Analog pins as GPIO pins
```


