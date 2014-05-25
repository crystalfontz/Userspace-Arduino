# PWM specifications

There are 8 PWM channels available on CFA10036 board.

### Pinout Table

| PWM channel no | Arduino Uno Pin no| Ball no of i.MX28 | Pin no in CFA10037 |
|:--:   |:--:|:--:| :--:  |
| PWM0  | 3  | K7 | P3.16 |
| PWM1  | 5  |L7 | P3.17 |
| PWM2* | 6  | K8 | P3.18 |
| PWM3* | 9  | G7 | P3.20 |
| PWM4* | 10 | E10| P3.29 |
| PWM5* | 11 | F7 | P3.22 |
| PWM6* |  - | E7 | P3.23 |
| PWM7  |  - | E8 | P3.26 |

```* There is an issue with these PWMs.```
```They won't work with Userspace code directly. Work around for that problem is available.```
