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

#ifndef _VARIANT_BEAGLEBONE_
#define _VARIANT_BEAGLEBONE_

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "virtual_main.h"
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/* There are two SPI available in cfa10036.
*  You can use either spi, but dont forget to comment unused one!
*/

#define LINUX_SPIDEV	"/dev/spidev32766.0"	// SSP3

typedef struct _PwmDescription
{
	uint32_t		ulPWMId;		// PWM identity in sysfs
	uint32_t		ulArduinoId;		// Arduino pin ID
	int			iHandleEnable;		// Persistent handle
	int			iHandleDuty;		// Persistent handle
} PwmDescription;

typedef struct _GPIODescription
{
	uint32_t		ulGPIOId;		// GPIO identity in sysfs
	uint32_t		ulArduinoId;		// Arduino pin ID
} GPIODescription;

typedef struct _PinState
{
	uint32_t	uCurrentPwm;	/* True if currently used as PWM */
	uint32_t	uCurrentInput;	/* True if currently input */
} PinState;

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

/* Number of pins defined in PinDescription array */
#define PINS_COUNT           (25u)

/* Mapping pins to pin numbers in userspace */

static const uint8_t A0  = 0;
static const uint8_t A1  = 1;
static const uint8_t A2  = 2;
static const uint8_t A3  = 3;
static const uint8_t A4  = 4;
static const uint8_t A5  = 5;
static const uint8_t A6  = 6;

void load_cape(const char *capename);

#ifdef __cplusplus
}
#endif


#endif /* _VARIANT_BEAGLEBONE_ */
