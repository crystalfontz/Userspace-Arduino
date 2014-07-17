/*
 * wiring_analog.c - analog input and output
 * Part of Arduino - http://www.arduino.cc/
 *
 * Copyright (c) 2014 Mitul Vekariya <vekariya93@gmail.com>
 * Copyright (c) 2013 Parav Nagarsheth
 * Copyright (c) 2005-2006 David A. Mellis
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA  02111-1307  USA
 */

#include "wiring_analog.h"
#include "virtual_main.h"
#include "sysfs.h"
#include "pins_linux.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

#ifdef __cplusplus
extern "C" {
#endif

uint32_t _readResolution = 10;
uint32_t _writeResolution = 8;

extern PwmDescription g_APwmDescription[];
extern GPIODescription g_AGPIODescription[];
extern uint32_t sizeof_g_APwmDescription;
extern PinState g_APinState[];
extern uint32_t sizeof_g_APinState;
extern uint32_t sizeof_g_APinDescription;
extern uint32_t sizeof_g_AGPIODescription;

void analogReadResolution(uint32_t res)
{
	#ifdef DEBUG
	trace_debug("[analogReadResolution] Read resolution is set to %d from %d \n", res, _readResolution);
	#endif
	_readResolution = res;
}

void analogWriteResolution(uint32_t res)
{	
	#ifdef DEBUG
	trace_debug("[analogWriteResolution] Write resolution is to from %d from %d \n", res, _writeResolution);
	#endif
	
	_writeResolution = res;
}

int pin2pwmhandle_enable(uint8_t pin)
{
	uint32_t i;

	// Scan mappings
	for (i = 0; i < sizeof_g_APwmDescription; i++){
		if(g_APwmDescription[i].ulArduinoId == pin)
			return g_APwmDescription[i].iHandleEnable;
	}

	// Indicate error
	return -1;
}

static int pin2pwmhandle_duty(uint8_t pin)
{
	uint32_t i;

	// Scan mappings
	for (i = 0; i < sizeof_g_APwmDescription; i++){
		if(g_APwmDescription[i].ulArduinoId == pin)
			return g_APwmDescription[i].iHandleDuty;
	}

	// Indicate error
	return -1;
}

uint32_t analogRead(uint32_t pin)
{
	uint32_t value;
	if (isAnalog(pin)) {
		value = sysfs_adc_getvalue(pin);
		/* Scale 12 bit ADC value as per _readResolution */
		if (_readResolution < 12) {
			value = (value << _readResolution) - value;
			value = value / 4095;
			#ifdef DEBUG
			trace_debug("[analogRead] value of pin %d is %d\n", pin, value);
			#endif
			return value;
		} else {
			value = value << (_readResolution - 12);
			#ifdef DEBUG
			trace_debug("[analogRead] value of pin %d is %d\n", pin, value);
			#endif
			return value;
		}
	} 
	#ifdef DEBUG
	else
		trace_debug("[analogRead] Pin%u is not Analog", pin);
	#endif
  
	return 0;
	
}

void analogWrite(uint32_t ulPin, uint32_t ulValue)
{
	int ret = 0;

	if (! digitalPinHasPWM(ulPin))
	{	
		#ifdef DEBUG
		trace_debug("[analogWrite] pin %d has no pwm\n", ulPin);
		#endif
		return;
	}
	
	#ifdef DEBUG
	trace_debug("[analogWrite] Writing %d to PWM%d \n",ulValue, ulPin);	
	#endif
	
	ret = sysfsPwmEnable(pin2pwmhandle_enable(ulPin),
				 pin2pwmhandle_duty(ulPin),
				 ulValue);
	if(ret < 0) {
		#ifndef DEBUG
		trace_debug("Something wrong with PWM%d. For more details try \"make CFG=debug upload \" \n",ulPin);
		#endif
	}
	
}

/* Initialise all PWM channels - 0 to 7
*  @return : none
*  @arguments : none
*/
void pwmInit(void)
{
	int i = 0;
	int ret = 0;

	#ifdef DEBUG
	trace_debug("[pwmInit] Exporting PWM... \n");
	#endif
	
	for (i = 0; i < sizeof_g_APwmDescription; i++) {
	
		#ifdef DEBUG
		trace_debug("[pwmInit] Exporting PWM %d \n",i);
		#endif
		
		ret = sysfsPwmExport(g_APwmDescription[i].ulPWMId,
					 &g_APwmDescription[i].iHandleEnable,
					 &g_APwmDescription[i].iHandleDuty);
		if (ret < 0) {
			#ifndef DEBUG
			trace_debug("[pwmInit] unable to open pwm%d \n",
					g_APwmDescription[i].ulPWMId);
			#endif		
		}
		
		/* Disable PWM if necessary in test
		 ret = sysfsPwmDisable(g_APwmDescription[i].iHandleEnable);
		
		if (ret < 0) {
			#ifndef DEBUG
			printf("unable to disable pwm%d \n",
					g_APwmDescription[i].ulPWMId);
			#endif
		}*/

	}

//	return 0;
}

#ifdef __cplusplus
}
#endif
