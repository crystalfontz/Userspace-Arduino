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

#### Additional features
CFA10036 has plentiful of GPIOs, while Arduino Uno has six.
By default only six pins are enabled (to maintain the compability with Arduino Uno). Do the following to use extra GPIOs.

#### Enable extra GPIOs

Open following file using your favourite text editor:

```
Userspace-Arduino/libarduino/variants/cfa10036/variant.cpp
```

Before adding GPIO pin(s) make sure that the pin(s) is configured as GPIO only in the device tree.

Add ```{sysfs_gpio_no, Uno_pin_no}``` in g_AGPIODescription structure. where **sysfs_gpio_no** is gpio associated with sysfs and **Uno_pin_no** is an extra pin no assigned by you.

For example to use **P3.14** in Userspace-Arduino,

```cpp
GPIODescription g_AGPIODescription[] = {
	{ 102 , 2},
	{ 103 , 4},
	{ 104 , 7},
	{ 105 , 10},
	{ 108 , 11},
	{ 109 , 13},
	{ 110 , 15}         // added GPIO pin P3.14

};
```
For P3.14 sysfs gpio no will be 32*3 + 14

Formula to calculate PX.Y sysfs gpio no = (32*X + Y)

```NOTE: You must assign Uno_pin_no greater than 15. Pin 0 to 13 are reserved for Arduino Uno board. For more details refer Arduino Uno pin functions```
