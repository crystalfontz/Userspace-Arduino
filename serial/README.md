# Serial

Serial (Also famous as UART) communication is very simple protocol. It has only two pins: TX and RX (There are a few more, but discussion of which is not relevent here).

There are two serial ports used in Userspace-Arduino. One of which is serial over USB and other is ttyAPP3 serial port. Unlike Arduino, you don't have to print values of variables in serial port. You can use ```printf()``` function inside sketch and print them on the remote terminal (accessed by SSH).
