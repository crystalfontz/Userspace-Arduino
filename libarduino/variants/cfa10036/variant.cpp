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

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Pins descriptions
 */

GPIODescription g_AGPIODescription[] = {
	{ 102 , 2},
	{ 103 , 4},
	{ 104 , 7},
	{ 105 , 10},
	{ 108 , 11},
	{ 109 , 13}
	
};

uint32_t sizeof_g_AGPIODescription = sizeof(g_AGPIODescription)/sizeof(struct _GPIODescription);

/* Array to match sysfs PWM Id againts Arduino pin no */
PwmDescription g_APwmDescription[] = {
	{ 0,	3,	-1,	-1 },
	{ 1,	5,	-1,	-1 },
	{ 2,	6,	-1,	-1 },
	{ 3,	9,	-1,	-1 },
	{ 4,	10,	-1,	-1 },
	{ 5,	11,	-1,	-1 }

/* Extra PWM pins
	{ 6,	,	-1,	-1 },
	{ 7,	,	-1,	-1 },*/
};

uint32_t sizeof_g_APwmDescription = sizeof(g_APwmDescription)/sizeof(struct _PwmDescription);

PinState g_APinState[]=
{
	/* uCurrentPwm	uCurrentInput		*/
	{ 0,		1 },	/* 0		*/
	{ 0,		1 },	/* 1		*/
	{ 0,		1 },	/* 2		*/
	{ 0,		1 },	/* 3  - PWM	*/
	{ 0,		1 },	/* 4 		*/
	{ 0,		1 },	/* 5  - PWM 	*/
	{ 0,		1 },	/* 6  - PWM	*/
	{ 0,		1 },	/* 7 		*/
	{ 0,		1 },	/* 8 		*/
	{ 0,		1 },	/* 9  - PWM	*/
	{ 0,		1 },	/* 10 - PWM	*/
	{ 0,		1 },	/* 11 - PMW	*/
	{ 0,		1 },	/* 12		*/
	{ 0,		1 },	/* 13		*/
	{ 0,		1 },	/* 14		*/
	{ 0,		1 },	/* 15		*/
	{ 0,		1 },	/* 16		*/
	{ 0,		1 },	/* 17		*/
	{ 0,		1 },	/* 18		*/
	{ 0,		1 } 	/* 19		*/
};

uint32_t sizeof_g_APinState = sizeof(g_APinState)/sizeof(struct _PinState);
#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif



void init( void )
{
 pinInit();
 pwmInit();
}

#ifdef __cplusplus
}
#endif
