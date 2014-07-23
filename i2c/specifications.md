# I2C Specifications

The I2C0 lines in Userspace Arduino are shared with the OLED on CFA10036. That means that any I2C devices with address xx wont work when connected to the lines.

### Pinout Table

| I2C0 Pin | Arduino Uno Pin no | i.MX28 Ball no | CFA10037 Pin no |
| :--: | :--: | :--: |  :--: |
| SDA |  A4  |  H5  | P3.01 |
| SCL |  A5  |  G5  | P3.00 |

