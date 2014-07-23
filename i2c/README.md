# I2C (wire)

Inter-Integrated Circuit or I2C is a multi-master, multi-slave, 2-wire serial bus. Both lines are pulled-up using resistors of appropriate values.

**Wires**

There are 2 bidirectional lines associated with I2C:

**SDA**(Serial Data): Line to send data from the master to the slave. This line is pulled low to indicate that the device wants to transfer data. It is released again when the transfer is complete.

**SCL**(Serial Clock): Synchronization line for transfer of data. A single high-low pulse indicates transfer of one bit of data.
