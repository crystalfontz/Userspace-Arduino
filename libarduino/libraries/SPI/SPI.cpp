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
#include <fcntl.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "SPI.h"
#include "linux-virtual.h"
#include "variant.h"


/* For Arduino default clock rate is 4MHz */
#define SPI_CLK_DEFAULT_HZ 4000000

SPIClass SPI;
SPIClass::SPIClass() {
 	this->mode = SPI_MODE0;
	this->bitOrder = MSBFIRST;
	this->clkDiv = SPI_CLOCK_DIV4;
}
void SPIClass::begin(){

	this->fd=open(LINUX_SPIDEV,O_RDWR);
	if(fd < 0){
		perror("Can't open SPI device\n");
		abort();
 	}

	this->setDataMode(this->mode);
	this->setClockDivider(this->clkDiv);
	this->setBitOrder(this->bitOrder);
	
}

uint8_t SPIClass::transfer(uint8_t txData) {
	
	int status;
	byte rxData = 0xFF;
    	xfer.tx_buf = (__u64) &txData;
    	xfer.rx_buf = (__u64) &rxData;
    	xfer.len = sizeof(byte);
    
    	status = ioctl(fd, SPI_IOC_MESSAGE(1), &xfer);
    
    	if (status < 0)
    	    perror("SPI_IOC_MESSAGE not sent");

    	return rxData;
}

void SPIClass::setBitOrder(uint8_t bitOrder) {

	uint8_t lsbFirst = 0;
	
	if (bitOrder == LSBFIRST) {
		lsbFirst = 1;
	}

	if (ioctl (this->fd, SPI_IOC_WR_LSB_FIRST, &lsbFirst) < 0) {
		perror("Failed to set SPI bit justification\n");
	}

	this->bitOrder = bitOrder;
}

void SPIClass::setDataMode(uint8_t mode) {
	
	uint8_t linuxSpiMode = 0;

	switch(mode) {
	case SPI_MODE0:
		linuxSpiMode = SPI_MODE_0;
		break;
	case SPI_MODE1:
		linuxSpiMode = SPI_MODE_1;
		break;
	case SPI_MODE2:
		linuxSpiMode = SPI_MODE_2;
		break;
	case SPI_MODE3:
		linuxSpiMode = SPI_MODE_3;
		break;
	default:
		printf("Invalid SPI mode specified\n");
		return;
	}

	if (ioctl (this->fd, SPI_IOC_WR_MODE, &linuxSpiMode) < 0) {
		perror("Failed to set SPI mode\n");
	}
	
	this->mode = mode;
}

void SPIClass::setClockDivider(uint32_t clkDiv) {

	uint32_t maxSpeedHz = SPI_CLK_DEFAULT_HZ;

	switch(clkDiv)
	{
	case SPI_CLOCK_DIV2:
		maxSpeedHz = SPI_CLK_DEFAULT_HZ << 1;
		break;
	case SPI_CLOCK_DIV4:
		break;
	case SPI_CLOCK_DIV8:
		maxSpeedHz = SPI_CLK_DEFAULT_HZ >> 1;
		break;
	case SPI_CLOCK_DIV16:
		maxSpeedHz = SPI_CLK_DEFAULT_HZ >> 2;
		break;
	case SPI_CLOCK_DIV32:
		maxSpeedHz = SPI_CLK_DEFAULT_HZ >> 3;
		break;
	case SPI_CLOCK_DIV64:
		maxSpeedHz = SPI_CLK_DEFAULT_HZ >> 4;
		break;
	case SPI_CLOCK_DIV128:
		maxSpeedHz = SPI_CLK_DEFAULT_HZ >> 5;
		break;
	default:
		printf("Invalid SPI clock\n");
		return;
	}

	if (ioctl (this->fd, SPI_IOC_WR_MAX_SPEED_HZ, &maxSpeedHz) < 0) {
		perror("Failed to set SPI clock speed\n");
		return;
	}

	this->clkDiv = clkDiv;
 }

void SPIClass::end() {
  close(fd);
}
