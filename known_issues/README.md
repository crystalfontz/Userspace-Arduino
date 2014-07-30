# Exceptions & Known Issues

Userspace Arduino occasionaly deviates from the Arduino libraries. Knowing these exceptions maybe helpful in debugging and saving time. If an exception has not been documented, please create an issue on the github page and we'll add it here.


## Hardware Exceptions

These have been documented in more detail in the following chapters.

1. **Analog**: Unlike the Arduino boards, the analog input in i.MX28 is limited to **1.8V**. Anything likely may damage the chip/board. Permanently.
2. Since CFA10036 is using device tree, unlike Arduino, It is not possible to change pin functionality dynamically. That's why, you'll see further in this document, a pin is mapped to an unique function, depending on device tree loaded. Thus, pin configured as GPIO can't substitue PWM and vice versa. SPI, I2C, UART and ADC are no exception. However, you can change functionality of pins by rewriting device tree, but still can't change device tree dynamically.

## Software Exceptions


1. **Fuction prototypes**: Unlike Arduino, functions need to be declared at the start of sketch (i.e. before they're called). Code will not compile otherwise.
2. **Global Objects**: Class objects declared globally might cause the program to act weirdly. Best way to avoid this is to avoid initialization inside constructors.
3. **Global class objects**: If you are using class objects globally, please execute a blank sketch beforehand, if you have not executed any other arduino sketch. When the board powers up, it does not have all pheripherals exported to sysfs. It needs to export them only once after the board powers up. They are exported when the blank arduino sketch is executed.

