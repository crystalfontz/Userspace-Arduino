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

PinDescription g_APinDescriptionp[]=
  {
  };

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
  /* Load capes here */
  // load_cape("BB-BONE-BACONE");
  /* Derive the offsets and export the GPIOs */
  for (unsigned int i = 0; i < PINS_COUNT; i += 1) {
	if(g_APinDescription[i].pinType != ANALOG)
		g_APinDescription[i].pinOffset = g_APinDescription[i].headerPin * 4;
	if(g_APinDescription[i].pinType == GPIO)
		gpio_export(g_APinDescription[i].gpioPin);
	if(g_APinDescription[i].pinType == PWM)
	  pwm_export(g_APinDescription[i].gpioPin);
  }
}

#ifdef __cplusplus
}
#endif
