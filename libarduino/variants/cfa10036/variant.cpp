/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "variant.h"
#include <wordexp.h>
#include <unistd.h>
/*
Arduino Uno format of pins
 * Arduino Pin| FUNCTION 1 | HEADER PIN | FUNCTION 2 | HEADER PIN | FUNCTION 3 | HEADER PIN |
 * ------------------------------------------------------------------------------------------
 *   0        |    GPIO    |            |    RX      |            |    -       |            |
 *   1        |    GPIO    |            |    TX      |            |    -       |            |
 *   2        |    GPIO    |            |    -       |            |    -       |            |
 *   3        |    GPIO    |            |    PWM     |            |    -       |            |
 *   4        |    GPIO    |            |    -       |            |    -       |            |
 *   5        |    GPIO    |            |    PWM     |            |    -       |            |
 *   6        |    GPIO    |            |    PWM     |            |    -       |            |
 *   7        |    GPIO    |            |    -       |            |    -       |            |
 *
 *   8        |    GPIO    |            |    -       |            |    -       |            |
 *   9        |    GPIO    |            |    PWM     |            |    -       |            |
 *  10        |    GPIO    |            |    PWM     |            |    SS      |            |
 *  11        |    GPIO    |            |    PWM     |            |    MOSI    |            |
 *  12        |    GPIO    |            |    -       |            |    MISO    |            |
 *  13        |    GPIO    |            |    -       |            |    SCK     |            |
 *  -         |    GND     |            |    -       |            |    -       |            |
 *  -         |    AREF    |            |            |            |    -       |            |
 * 
 *  A0        |    ADC     |            |            |            |    -       |            |
 *  A1        |    ADC     |            |            |            |    -       |            |
 *  A2        |    ADC     |            |            |            |    -       |            |
 *  A3        |    ADC     |            |            |            |    -       |            |
 *  A4        |    ADC     |            |            |            |    -       |            |
 *  A5        |    ADC     |            |            |            |    -       |            |
 * // ADC NOT PART OF ARDUINO UNO R3
 *  A6        |    ADC     |            |            |            |    -       |            |
 *  A7        |    ADC     |            |            |            |            |            |
 */
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Pins descriptions
 */
PinDescription g_APinDescription[]=
{
  // The offsets can be derived from userspace pin numbers defined in the header file
  // 0 .. 13 - Digital pins
  // ----------------------
  // 0/1 - UART (Serial)
  { P9_11,   30,  UART }, // URXD P3_02
  { P9_13,   31,  UART }, // UTXD P3_03

  // 2
  { P3_04,   48,  GPIO }, // PIN2 P3_04
  { P9_14,   31,  PWM  }, // PWM1A P3_05
  { P3_06,   60,  GPIO }, // PIN4 P3_06

  // 5
  { P9_16,   51,  PWM  }, // PWM1B P3_07
  { P9_42A,   7,  PWM  }, // PWM0 P3_08
  { P3_09,   22,  GPIO  }, // PWM2A P3_09

  //8
  { P9_19,   13,  I2C  }, // I2C2_SCL P3_10
  { P9_20,   12,  I2C  }, // I2C2_SDA P3_11

  // 10
  { P3_12,    5,  GPIO  }, // SPI0_CSO P3_12
  { P3_13,    4,  GPIO  }, // MOSI P3_13
  { P9_21,    3,  _SPI   }, // MISO P3_14
  { P3_18,    114,  GPIO  }, // P3_15

  // 14 .. 17 - USR LEDs
  { USR0,    53,  LED  },
  { USR1,    86,  LED  },
  { USR2,    87,  LED  },
  { USR3,    88,  LED  },

  // 18 .. 24 - Analog pins
  // ----------------------
  { AIN4,  ANALOG_PIN,  ANALOG, 4 },
  { AIN6,  ANALOG_PIN,  ANALOG, 6 },
  { AIN5,  ANALOG_PIN,  ANALOG, 5 },
  { AIN2,  ANALOG_PIN,  ANALOG, 2 },
  { AIN3,  ANALOG_PIN,  ANALOG, 3 },
  { AIN0,  ANALOG_PIN,  ANALOG, 0 },
  { AIN1,  ANALOG_PIN,  ANALOG, 1 }
} ;

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

void load_cape(const char* capename)
{
	FILE* fd;
	char* slots;
	wordexp_t wordexp_buf;
	// ask wordexp to expand the filepath for slots
	wordexp("/sys/devices/bone_capemgr*/slots", &wordexp_buf, 0);
	// assume it's the first value
	slots = wordexp_buf.we_wordv[0];
	fd = fopen(slots, "w");
	if (fd == NULL) {
		perror(slots);
		wordfree(&wordexp_buf);
		return;
	}
	fprintf(fd,"%s",capename);
	if (fclose(fd) != 0)
		perror(capename);
	else {
		printf("Cape loaded %s\n", capename);
		sleep(2);
	}
	wordfree(&wordexp_buf);
}

void init( void )
{
  /* Derive the offsets and export the GPIOs */
  for (unsigned int i = 0; i < PINS_COUNT; i += 1) {
	// if(g_APinDescription[i].pinType != ANALOG)
	// 	g_APinDescription[i].pinOffset = g_APinDescription[i].headerPin * 4;
	if(g_APinDescription[i].pinType == GPIO)
		gpio_export(g_APinDescription[i].gpioPin);
	// if(g_APinDescription[i].pinType == PWM)
	//   pwm_export(g_APinDescription[i].gpioPin);
  }
}

#ifdef __cplusplus
}
#endif
