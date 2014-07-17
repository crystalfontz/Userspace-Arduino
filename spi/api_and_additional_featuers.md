# SPI API
----------------------------------------------------------

Userspace-Arduino follows Arduino Uno SPI programming API. It provides following functions to interface with SPI device


**Functions**
* SPI.begin( )
* SPI.end( )
* SPI.setClockDivider( )
* SPI.setDataMode ( )
* SPI.setBitOrder( )

#### Additional features

#### Change default frequency of SPI
Default frequency for spidev is set to 4MHz. To change it, Open following file using your favourite text editor:

```
Userspace-Arduino/libarduino/libraries/SPI.cpp
```
and change the default frequency.

``` cpp
#define SPI_CLK_DEFAULT_HZ 4000000
```

```NOTE: SPI_CLK_DEFAULT_HZ is in Hz```
