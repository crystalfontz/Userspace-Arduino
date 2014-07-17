# SPI

Serial Pheripheral Interface (SPI) is a synchronous serial data protocol. It is used for short distance data transfer, generally between microprocessor and sensors.

SPI follows master-slave topology where there is one master and at least one slave.

**Interface**

There are four lines associated with SPI:

**MOSI **(Master Out Slave In): Line to send data to the Slave from the Master

**MISO **(Master In Slave Out): Line to send data to the Master from the Slave

**SCK **(Serial Clock): Line to provide clock signal to the slave

**SS **(Slave Select): Line to enable specific Slave. It is active low pin. So it must be low before communicating with the Master. When it's high, slave simply ignores anything it receives from the Master.


