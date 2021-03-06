/*
  wiring_digital.c - digital input and output functions
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2013 Parav Nagarsheth
  Copyright (c) 2005-2006 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  Modified 28 September 2010 by Mark Sproul

*/

#include "wiring_digital.h"
#include "linux-virtual.h"
#include "pins_linux.h"
#include "debug.h"

extern PwmDescription g_APwmDescription[];
extern GPIODescription g_AGPIODescription[];
extern uint32_t sizeof_g_APwmDescription;
extern PinState g_APinState[];
extern uint32_t sizeof_g_APinState;
extern uint32_t sizeof_g_APinDescription;
extern uint32_t sizeof_g_AGPIODescription;

int pin2gpiohandle(uint8_t pin)
{
	uint32_t i;

	// Scan mappings
	for (i = 0; i < sizeof_g_AGPIODescription; i++){
		if(g_AGPIODescription[i].ulArduinoId == pin)
			return g_AGPIODescription[i].ulGPIOId;
	}

	// Indicate error
	return -1;
}

void pinMode(uint8_t pin, uint8_t mode)
{
	
	if (isDigital(pin)) {
		if (mode == INPUT) {
			gpio_setdirection(pin2gpiohandle(pin), "in");
			#ifdef DEBUG
			trace_debug("[pinMode] configuring pin %d as INPUT \n", pin);
			#endif
		}
		else if (mode == OUTPUT ) {
			gpio_setdirection(pin2gpiohandle(pin), "out");
			#ifdef DEBUG
			trace_debug("[pinMode] configuring pin %d as OUTPUT \n", pin);
			#endif
		}
		else if (mode == INPUT_PULLUP) {
		    #ifdef DEBUG
			trace_debug("[pinMode] can't set pin %d as INPUT_PULLUP \n", pin);
			#endif
		}
		else {
		    #ifdef DEBUG
			trace_debug("[pinMode] Invalid pinMode %d for pin %d\n", mode, pin);
			#endif
		}
	}
	#ifdef DEBUG
	else
		trace_debug("[pinMode] pin %d is not Digital\n", pin);
	#endif
	return;
}

void digitalWrite(uint8_t pin, uint8_t val)
{
	#ifdef DEBUG
	trace_debug("[digitalWrite] writing %d to pin %d\n", val, pin);
	#endif
	if (isDigital(pin))
		sysfs_gpio_setvalue(pin2gpiohandle(pin), val);
	#ifdef DEBUG
	else
	trace_debug("[digitalWrite] pin %d is not Digital\n", pin);
	#endif
	return;
}

int digitalRead(uint8_t pin)
{
	uint8_t result = 0;
	if (isDigital(pin)) {
		result = sysfs_gpio_getvalue(pin2gpiohandle(pin));
		#ifdef DEBUG
		trace_debug("[digitalRead] Value of pin %d is %d\n", pin, result);
		#endif
		return result;
	}	
	#ifdef DEBUG
	else
		trace_debug("[digitalRead] pin %d is not Digital\n", pin);
	#endif
	return 0;
}

void pinInit(void)
{
	uint16_t i ;
	
	#ifdef DEBUG
	trace_debug("[pinInit] Exporting GPIOs...\n");  
	#endif
	for (i = 0; i < sizeof_g_AGPIODescription; i++) {
		gpio_export(g_AGPIODescription[i].ulGPIOId);
		#ifdef DEBUG
		trace_debug("[pinInit] Exporting GPIO%d\n", g_AGPIODescription[i].ulGPIOId);
		#endif
	}
}

