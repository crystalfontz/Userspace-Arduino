# Exceptions & Known Issues

Userspace Arduino occasionaly deviates from the Arduino libraries. Knowing these exceptions maybe helpful in debugging and saving time. If an exception has not been documented, please create an issue on the github page and we'll add it here.


## Hardware Exceptions

These have been documented in more detail in the following chapters.

1. **Analog**: Unlike the Arduino boards, the analog input in i.MX28 is limited to **1.8V**. Anything likely damage the chip/board. Permanently.


## Software Exceptions


1. **Fuction prototypes**: Unlike Arduino, functions need to be declared at the start of sketch (i.e. before they're called). Code will not compile otherwise.
2. **Global Objects**: Class objects declared globally might cause the program to act weirdly. Best way to avoid this is to avoid initialization inside constructors.


