#include "variant.h"
#include <wordexp.h>
#include <unistd.h>
/*
Arduino Uno format of pins
 * Arduino Pin     |  CFA10036      Header Pin
 * ----------------+----------------------------
 *   0             |  
 *   1             |  
 *   2             |
 *   3             | 
 *   4             | 
 *
 *   5             | 
 *   6             | 
 *   7             | 
 *   8             | 
 *   9             | 
 *  10             | 
 *
 *  11             | 
 *  12             | 
 *  13             | 
 *  14             | 
 *  15             | 
 *  16             | 
 *  17             | 
 *  18             | 
 *  19             | 
 *  20             | 
 *  21             | 
 *  22             | 
 *  23             | 
 *  24             |
 *
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
