/*
  HardwareSerial.cpp - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  
  Modified 30 January 2014 by Parav Nagarsheth
  Modified 23 November 2006 by David A. Mellis
  Modified 28 September 2010 by Mark Sproul
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "wiring.h"

#include "HardwareSerial.h"
#include "serial.h"

#ifdef __cplusplus
extern "C"{
#endif

#include <unistd.h>
#include <sys/ioctl.h>

#ifdef __cplusplus
}
#endif

#define AUART4 "/dev/ttyAPP4"
#define SERIAL_BUFFER_SIZE 1024

volatile int w_flag = 0;
volatile int w_rem = 0;
volatile int r_len = 0;
char buf[255];

struct ring_buffer
{
	unsigned char buffer[SERIAL_BUFFER_SIZE];
	volatile unsigned int head;
	volatile unsigned int tail;
};

ring_buffer rx_buffer  =  { { 0 }, 0, 0 };
ring_buffer tx_buffer  =  { { 0 }, 0, 0 };

inline void store_char(unsigned char c, ring_buffer *buffer)
{
	unsigned int i = (unsigned int)(buffer->head + 1) % SERIAL_BUFFER_SIZE;

	// if we should be storing the received character into the location
	// just before the tail (meaning that the head would advance to the
	// current location of the tail), we're about to overflow the buffer
	// and so we don't write the character or advance the head.
	if (i != buffer->tail) {
		buffer->buffer[buffer->head] = c;
		buffer->head = i;
	}
}

void serialEvent (int status)
{
	int i = 0;	
	ioctl(Serial.serial_fd, TIOCOUTQ, &w_rem);
	ioctl(Serial.serial_fd, TIOCINQ, &r_len);
	if (w_rem == 0)	{
			w_flag = 0;
	}
	if (r_len > 0) {
		r_len = read(Serial.serial_fd, &buf, 255);
		while(i < r_len)	
			store_char(buf[i++], &rx_buffer);
	}
	printf("Inside\n\r");
}

// Constructors ////////////////////////////////////////////////////////////////

HardwareSerial::HardwareSerial(ring_buffer *rx_buffer, ring_buffer *tx_buffer)
{
	_rx_buffer = rx_buffer;
	_tx_buffer = tx_buffer;
}

// Public Methods //////////////////////////////////////////////////////////////

void HardwareSerial::begin(long baud)
{
	serial_fd = config_serial(serialEvent, AUART4, baud, DATA_8, STOP_1, PARITY_OFF);
	set_terminal_mode();
}

void HardwareSerial::end()
{
	/* wait for transmission of outgoing data */
	while (_tx_buffer->head != _tx_buffer->tail); // ??

	/* clear any received data */
	_rx_buffer->head = _rx_buffer->tail;
}

int HardwareSerial::available(void)
{
	int r_length;
	ioctl(serial_fd, TIOCINQ, &r_length);
	return r_length;
}

int HardwareSerial::peek(void)
{
	if (_rx_buffer->head == _rx_buffer->tail) {
		return -1;
	} else {
		return _rx_buffer->buffer[_rx_buffer->tail];
	}
}

int HardwareSerial::read(void)
{
// if the head isn't ahead of the tail, we don't have any characters
	/*if (_rx_buffer->head == _rx_buffer->tail) {
		return -1;
	} else {
		unsigned char c = _rx_buffer->buffer[_rx_buffer->tail];
		_rx_buffer->tail = (unsigned int)(_rx_buffer->tail + 1)
							 % SERIAL_BUFFER_SIZE;
		return c;
	}*/
	unsigned char c;
	::read(serial_fd, &c, 1);	
	return (c);
}

void HardwareSerial::flush()
{
	printf("serial:calling flush()\n");
}

size_t HardwareSerial::write(uint8_t c)
{
/*
	int i = (_tx_buffer->head + 1) % SERIAL_BUFFER_SIZE;
        
	// If the output buffer is full, there's nothing for it other than to 
	// wait for the interrupt handler to empty it a bit
	// ???: return 0 here instead?
	if (i == _tx_buffer->tail)
		return 0;
        
	_tx_buffer->buffer[_tx_buffer->head] = c;
	_tx_buffer->head = i;
*/
	/* Set wait flag to 1 and loop till handler sets it to 0 */
//	w_flag =1;
	::write(serial_fd, &c, 1);
//	while(w_flag);
	return 1;
}

HardwareSerial::operator bool() {
	return true;
}

// Preinstantiate Objects //////////////////////////////////////////////////////
HardwareSerial Serial(&rx_buffer, &tx_buffer);

