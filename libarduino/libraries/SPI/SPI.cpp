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
#include "debug.h"

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
	    #ifdef DEBUG
	        trace_debug("SPI: Can't open SPI device: %s\n",LINUX_SPIDEV); 
	    #else
		    perror("Can't open SPI device\n");
		#endif
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
    
    #ifdef DEBUG
        trace_debug("SPI : Sending data - %d\n", txData); 
    #endif
    
    if (status < 0) {
        #ifdef DEBUG
            trace_debug("SPI: SPI_IOC_MESSAGE error while sending\n"); 
        #else 
            perror("SPI_IOC_MESSAGE not sent");
        #endif
    }
    else {
    #ifdef DEBUG
        trace_debug("SPI: Received %d\n", rxData); 
    #endif
    }
    return rxData;
}

void SPIClass::setBitOrder(uint8_t bitOrder) {

	uint8_t lsbFirst = 0;
	
	if (bitOrder == LSBFIRST) {
	    #ifdef DEBUG
	        trace_debug("SPI: Bit order is LSBFIRST\n"); 
	    #endif
		lsbFirst = 1;
	}
	else {
	    #ifdef DEBUG
	        trace_debug("SPI: Bit order is MSBFIRST\n"); 
	    #endif
	}

    this->bitOrder = bitOrder;
	if (ioctl (this->fd, SPI_IOC_WR_LSB_FIRST, &lsbFirst) < 0) {
	    #ifdef DEBUG
	        trace_debug("SPI: Can not set bit order - %d\n", bitOrder); 
	    #else
		    perror("Failed to set SPI bit justification\n");
		#endif
	}
	else {
	    #ifdef DEBUG
	        trace_debug("SPI: Bit order set to %d\n", bitOrder); 
	    #endif
    }
	
}

void SPIClass::setDataMode(uint8_t mode) {
	
	uint8_t linuxSpiMode = 0;
    
    #ifdef DEBUG
        trace_debug("SPI: data mode is - %d\n",this->mode); 
    #endif
    
    this->mode = mode;
    
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
	    #ifdef DEBUG
		trace_debug("SPI: Invalid SPI mode %d\n", mode);
		#endif
		return;
	}

	if (ioctl (this->fd, SPI_IOC_WR_MODE, &linuxSpiMode) < 0) {
	    #ifdef DEBUG
	        trace_debug("SPI: Can not set mode - %d\n",mode); 
        #else
		    perror("Failed to set SPI mode\n");
		#endif
	}
	else {
	    #ifdef DEBUG
	        trace_debug("SPI: data mode is - %d\n", mode); 
	    #endif
	}
	
}

void SPIClass::setClockDivider(uint32_t clkDiv) {

	uint32_t maxSpeedHz = SPI_CLK_DEFAULT_HZ;

    #ifdef DEBUG
        trace_debug("SPI: Clock Divider is - %d\n",this->clkDiv); 
    #endif
    
    this->clkDiv = clkDiv;
    
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
	    #ifdef DEBUG
	        trace_debug("SPI: Invalid Clock Divider %d\n", clkDiv);    
	    #endif
	    return;
	}

	if (ioctl (this->fd, SPI_IOC_WR_MAX_SPEED_HZ, &maxSpeedHz) < 0) {
		
		#ifdef DEBUG
		    trace_debug("SPI: Error! Can not set clock divider - %d\n", clkDiv);
		#else
		    perror("Failed to set SPI clock speed\n");
		#endif
		return;
	}
	else {
	    #ifdef DEBUG
            trace_debug("SPI: Clock Divider is - %d\n",this->clkDiv); 
        #endif
    }
 }

void SPIClass::end() {
 
    #ifdef DEBUG 
        trace_debug("SPI: closing SPIDEV %d\n",LINUX_SPIDEV);
    #endif
    close(fd);
}
