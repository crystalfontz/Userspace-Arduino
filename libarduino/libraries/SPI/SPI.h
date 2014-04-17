/*
 * Copyright (c) 2014 by Mitul Vekariya <vekariya93@gmail.com>
 * Copyright (c) 2013 by Anuj Deshpande <anujdeshpande92@gmail.com>
 * SPI Library for Userspace Arduino
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */
#ifndef _SPI_H
#define _SPI_H
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "linux-virtual.h"

#define SPI_CLOCK_DIV4 0x00
#define SPI_CLOCK_DIV16 0x01
#define SPI_CLOCK_DIV64 0x02
#define SPI_CLOCK_DIV128 0x03
#define SPI_CLOCK_DIV2 0x04
#define SPI_CLOCK_DIV8 0x05
#define SPI_CLOCK_DIV32 0x06

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

#define LSBFIRST 0
#define MSBFIRST 1

class SPIClass {
		int fd;
		uint8_t mode;
		int bitOrder;
		uint8_t clkDiv;
public:
		SPIClass();
		unsigned char transfer(byte _data);
		void begin();
		void end();
		void setBitOrder(uint8_t);
		void setDataMode(uint8_t);
		void setClockDivider(uint32_t);
};
extern SPIClass SPI;
#endif
