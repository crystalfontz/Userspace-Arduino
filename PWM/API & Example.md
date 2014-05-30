# PWM API
-------------------------------------------------

**syntax**

analogWrite (pin, value)

**parameters**

*pin*: pin no of Arduino Uno (0 to 5 only)

*value*: duty cycle 0(min) to 255(max)

#### change resolution of analogWrite( )

Use following function in sketch before using analogWrite() to change default resolution (8-bit):

**analogWriteResolution (bits)**

for example, add following line in existing sketch to change PWM resolution to 12 bit (0 to 4096).
```
analogWriteResolution(12)
```

#### Additional features that Arduino doesn't provide
CFA10036 has eight PWM channels, while Arduino Uno has only six. This is a good thing who wants to use two extra channels. Right now only six channels are enabled (to maintain the compability with Arduino Uno), but who wants to enjoy an extra scoop can follow mentioned procedure.


#### Enable extra PWMs

Open following file using your favourite text editor:

```
Userspace-Arduino/libarduino/variants/cfa10036/variant.cpp
```
Uncomment the last two lines and give appropriate pin name (second column) to enable PWM6 and PWM7.
``` cpp
/* Array to match sysfs PWM Id againts Arduino pin no */
PwmDescription g_APwmDescription[] = {
	{ 0,	3,	-1,	-1 },
	{ 1,	5,	-1,	-1 },
	{ 2,	6,	-1,	-1 },
	{ 3,	9,	-1,	-1 },
	{ 4,	10,	-1,	-1 },
	{ 5,	11,	-1,	-1 },

/* Extra PWM pins
	{ 6,	,	-1,	-1 },
	{ 7,	,	-1,	-1 },*/
};

```
#### Change default frequency of PWM

You can't change frequency of PWM in case of Arduino Uno. We don't have that kind of restriction here. Default frequency for CFA10036 is set to 20 &#181;s.

Open following file in your favourite text editor:

```
Userspace-Arduino/libarduino/cores/virtual/sysfs.c
```
modify following line

``` cpp
/* PWM period in nano seconds*/
#define SYSFS_PWM_PERIOD_NS 20000
```
```NOTE: write period in term of nano seconds only.```
