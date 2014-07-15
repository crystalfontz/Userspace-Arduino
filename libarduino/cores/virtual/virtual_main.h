#ifndef virtual_main_h
#define virtual_main_h

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>
#include "sysfs.h"
#include "i2c.h"

#ifdef __cplusplus
extern "C"{
#endif

/* Program start time for millis and micros. Instantiated in main.cpp */
extern struct timespec prog_start_time;
#ifdef __cplusplus
}
#include "HardwareSerial.h"
#include "WMath.h"
#endif


#include "wiring.h"
#include "wiring_digital.h"
#include "wiring_analog.h"
#endif

