/*
  sysfs.c

  Copyright (c) 2014 Mitul Vekariya <vekariya93@gmail.com>
  Copyright (c) 2013 Anuj Deshpande

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

*/

#include "sysfs.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

/* PWM period in nano seconds*/
#define SYSFS_PWM_PERIOD_NS 20000

int sysfs_read(const char *path, const char *filename, char *value)
{
	FILE *fd;
	char buf[MAX_BUF];
	snprintf(buf, sizeof(buf), "%s%s", path, filename);
	fd = fopen(buf, "r");
	if (fd == NULL) {
		perror(buf);
		return -1;
	}
	fscanf(fd, "%s", value);
	if (fclose(fd) != 0)
		perror(buf);
	return 0;
}

int sysfs_write(const char *path, const char *filename, int value)
{
	FILE *fd;
	char buf[MAX_BUF];
	snprintf(buf, sizeof(buf), "%s%s", path, filename);
	fd = fopen(buf, "w");
	if (fd == NULL) {
		perror(buf);
		return -1;
	}
	fprintf(fd, "%d", value);
	if (fclose(fd) != 0)
		perror(buf);
	return 0;
}

void sysfs_gpio_setvalue(uint8_t pin, uint8_t value)
{
	char buf[MAX_BUF];
	snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/", pin);
	sysfs_write(buf, "value", value);
}

int sysfs_gpio_getvalue(uint8_t pin)
{
	char buf[MAX_BUF], value[4];
	snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/", pin);
	sysfs_read(buf, "value", value);
	return atoi(value);
}

/* sysfs_adc_getvalue
 * Gets a value from the sysfs adc entries
 * Returns a value on the scale of (0 to 4095)
 */
uint32_t sysfs_adc_getvalue(uint32_t channel)
{
	char buf[MAX_BUF], channelname[20], value[8];
	snprintf(buf, sizeof(buf), SYSFS_ADC_DIR"/");
	snprintf(channelname, sizeof(channelname), "in_voltage%d_raw", channel);
	sysfs_read(buf, channelname, value);
	return atol(value);
}

void sysfs_led_setvalue(uint8_t led, uint8_t value)
{
	char buf[MAX_BUF];
	snprintf(buf, sizeof(buf), SYSFS_LED_DIR "/beaglebone:green:usr%d/", led);
	sysfs_write(buf, "brightness", value);
}

int gpio_export(uint32_t gpio_pin)
{
	FILE *fd = NULL;
	int ret = 0;
	char export_value[16] = "";
	char fs_path[SYSFS_BUF] = SYSFS_GPIO_DIR "export";
	
	if (NULL == (fd = fopen(fs_path, "ab")))
	{
		//print("GPIO error);
		return -1;
	}
	rewind(fd);
	
	memset(export_value, 0x0, sizeof(export_value));
	snprintf(export_value, sizeof(export_value), "%u", gpio_pin);
	fwrite(&export_value, sizeof(char), sizeof(export_value), fd);
	fclose(fd);

	return ret;
}

int gpio_unexport(uint32_t gpio_pin)
{
	FILE *fd;
	fd = fopen("/sys/class/gpio/unexport", "w");
	if (fd == NULL) {
		fprintf(stderr, "Pin %d: ", gpio_pin);
		perror("/gpio/unexport");
		return -1;
	}
	fprintf(fd, "%d", gpio_pin);
	if (fclose(fd) != 0) {
		fprintf(stderr, "Pin %d: ", gpio_pin);
		perror("/gpio/unexport");
	}
	return gpio_pin;
}

int gpio_setdirection(uint32_t gpio_pin, const char *direction)
{
	FILE *fd;
	char buf[MAX_BUF];
	snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", gpio_pin);
	fd = fopen(buf, "w");
	if (fd == NULL) {
		fprintf(stderr, "Pin %d: ", gpio_pin);
		perror(buf);
		return -1;
	}
	fprintf(fd, "%s", direction);
	if (fclose(fd) != 0) {
		fprintf(stderr, "Pin %d: ", gpio_pin);
		perror(buf);
	}
	return gpio_pin;
}

/*
* Exports PWM to sysfs
* @return
* -1 : If either following directories does not exist: SYSFS_PWM_ROOT,SYSFS_PWM_ROOT pwmx/period
*	SYSFS_PWM_ROOT pwmx/enable, SYSFS_PWM_ROOT pwmx/duty_cycle
* 0 : Success 
* @arguments
* pwm : pwm ID of SoC
* handle_enable : pointer to the file /sys/class/pwm/pwmchip0/pwmx/enable
* handle_duty : pointer to to the file /sys/class/pwm/pwmchip0/pwmx/duty_cycle
*/

int sysfsPwmExport(uint32_t pwm, int *handle_enable, int *handle_duty)
{
	FILE *fp = NULL;
	int ret = 0;
	char export_value[16] = "";
	char fs_path[SYSFS_BUF] = SYSFS_PWM_ROOT "export";

	if (NULL == (fp = fopen(fs_path, "ab"))) {
		return -1;
	}
	rewind(fp);

	memset(export_value, 0x0, sizeof(export_value));
	snprintf(export_value, sizeof(export_value), "%u", pwm);
	fwrite(&export_value, sizeof(char), sizeof(export_value), fp);
	fclose(fp);

	/* Set default frequency */
	memset(fs_path, 0x00, sizeof(fs_path));
	snprintf(fs_path, sizeof(fs_path), SYSFS_PWM_ROOT "pwm%u/period", pwm);
	if (NULL == (fp = fopen(fs_path, "ab"))) {
		return -1;
	}
	rewind(fp);

	memset(export_value, 0x0, sizeof(export_value));
	snprintf(export_value, sizeof(export_value), "%u", SYSFS_PWM_PERIOD_NS);
	fwrite(&export_value, sizeof(char), sizeof(export_value), fp);
	fclose(fp);

	/* Open persistent handle to pwm/enable */
	memset(fs_path, 0x00, sizeof(fs_path));
	snprintf(fs_path, sizeof(fs_path), SYSFS_PWM_ROOT "pwm%u/enable", pwm);
	ret = open(fs_path,  O_RDWR);
	if (ret < 0) {
		return ret;
	}
	*handle_enable = ret;

	/* Open persistent handle to pwm/duty_cycle */
	memset(fs_path, 0x00, sizeof(fs_path));
	snprintf(fs_path, sizeof(fs_path), SYSFS_PWM_ROOT "pwm%u/duty_cycle",
		 pwm);
	ret = open(fs_path,  O_RDWR);
	if (ret < 0) {
		return ret;
	}
	*handle_duty = ret;

	return 0;
}

/* Enable given pwm channel
*  @return
*  -1 : can not write to /sys/class/pwm/pwmchip0/pwmx/enable
*	can not write to the file /sys/class/pwm/pwmchip0/pwmx/duty_cycle
*   0 : success
*  @parameters
*  handler_enable : pointer to the file /sys/class/pwm/pwmchip0/pwmx/enable
*  handle_duty : pointer to the file /sys/class/pwm/pwmchip0/pwmx/duty_cycle
*  ulValue : duty cycle of PWM
*  TODO : handle invalid ulValue
*/
int sysfsPwmEnable(int handle_enable, int handle_duty, unsigned int ulValue)
{
	char value[16] = "";
	char enable = '1';
	int ret = 0;
	unsigned int value_duty = 0;
	
	value_duty = ulValue * SYSFS_PWM_PERIOD_NS;
	value_duty = value_duty / pow(2, 8); // Default resolution set to 8 bits
	
	memset(value, 0x0, sizeof(value));
	snprintf(value, sizeof(value), "%u", value_duty);
	lseek(handle_duty, 0, SEEK_SET);
	ret = write(handle_duty, &value, sizeof(value));
	if (sizeof(value) != ret) {
		return -1;
	}

	lseek(handle_enable, 0, SEEK_SET);
	ret = write(handle_enable, &enable, sizeof(enable));
	if (sizeof(enable) != ret) {
		return -1;
	}

	return 0;
}

int sysfsPwmDisable(int handle_enable)
{
	char enable = '0';
	int ret = 0;

	lseek(handle_enable, 0, SEEK_SET);
	ret = write(handle_enable, &enable, sizeof(enable));
	if (sizeof(enable) != ret) {
		return -1;
	}

	return 0;
}

