#include "serial.h"
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <stdlib.h>

int open_port(const char *device);
int close_port(int fd);

struct termios saved_attributes;

void reset_terminal_mode (void)
{
	tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

void set_terminal_mode (void)
{
	struct termios tattr;	
	/* Make sure stdin is a terminal. */
	if (!isatty (STDIN_FILENO)) {
		fprintf (stderr, "Not a terminal.\n");
		exit (EXIT_FAILURE);
	}

	/* Save the terminal attributes so we can restore them later. */
	tcgetattr (STDIN_FILENO, &saved_attributes);
	atexit (reset_terminal_mode);

	/* Set the funny terminal modes. */
	tcgetattr (STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}


int config_serial(serial_handler handler, const char * device, long baud, 
				int data_bits, int stop_bits, int parity)
{
	struct termios options;
	//struct sigaction saio;
	int fd;
	long DATABITS, STOPBITS, PARITYON, PARITY;
	/* definition of signal action */
/*	struct sigaction saio;
*/
	fd = open_port (device);
	if (fd < 0)
		return -1;

	/* Install the signal handler before making the device asynchronous */
/*	saio.sa_handler = handler;
	sigemptyset (&saio.sa_mask);
	sigaddset (&saio.sa_mask, SIGINT);
	saio.sa_flags = 0;
	saio.sa_restorer = NULL;
	sigaction (SIGIO, &saio, NULL);
*/
	/* Allow the process to receive SIGIO */
/*	fcntl (fd, F_SETOWN, getpid());
*/
	/* Make the file descriptor asynchronous.
	 * It is not possible to enable SIGIO receiving by specifying
	 * O_ASYNC when calling open (see open man page)  */
/*	fcntl(fd, F_SETFL, O_ASYNC);
*/
	switch (data_bits) {
	case 8 :
	default :
		DATABITS = CS8;
		break;
	case 7 :
		DATABITS = CS7;
		break;
	case 6 :
		DATABITS = CS6;
		break;
	case 5 :
		DATABITS = CS5;
		break;
	}

	switch (stop_bits) {
	case 0 :
	default :
		STOPBITS = 0;
		break;
	case 1 :
		STOPBITS = CSTOPB;
		break;
	}
	
	switch (parity) {
	case 0 :
	default :
		PARITYON = 0;
		PARITY = 0;
		break;
	case 1 :
		PARITYON = PARENB;
		PARITY = PARODD;
		break;
	case 2 :
		PARITYON = PARENB;
		PARITY = 0;
		break;
	}

	/* enable raw output and disable echo */
	options.c_cflag = parse_baudrate(baud) | DATABITS | STOPBITS | PARITYON | PARITY | CLOCAL | CREAD;
	options.c_iflag = IGNBRK;
	options.c_oflag = 0;
	options.c_lflag = 0;
	options.c_cc[VMIN] = 1;
	options.c_cc[VTIME] = 0;
	tcflush (fd, TCIFLUSH);
	tcsetattr (fd, TCSANOW, &options);
	return (fd);
}

int read_char(int fd, char *c)
{
	return (read(fd, c, 255));
}

int write_char(int fd, char c)
{
	return (write(fd, &c, 1));
}

/*
 * 'open_port()' - Open serial port 1.
 *
 * Returns the file descriptor on success or -1 on error.
 */

int open_port(const char *device)
{
	int fd;

	fd = open(device, O_RDWR | O_NOCTTY);// | O_NONBLOCK);

	if (fd < 0) {
		/* Could not open the port */
		perror(device);
	}
	return (fd);
}

int close_port(int fd)
{
	if (close(fd) < 0) {
		/* Could not close the port */
		perror("Error closing port");
	}
	return (fd);
}

unsigned int parse_baudrate(long requested)
{
	int baudrate;

	switch (requested) {

	#ifdef B50
	case 50 :
		baudrate = B50;
		break;
	#endif
	#ifdef B75
	case 75 :
		baudrate = B75;
		break;
	#endif
	#ifdef B110
	case 110 :
		baudrate = B110;
		break;
	#endif
	#ifdef B134
	case 134 :
		baudrate = B134;
		break;
	#endif
	#ifdef B150
	case 150 :
		baudrate = B150;
		break;
	#endif
	#ifdef B200
	case 200 :
		baudrate = B200;
		break;
	#endif
	#ifdef B300
	case 300 :
		baudrate = B300;
		break;
	#endif
	#ifdef B600
	case 600 :
		baudrate = B600;
		break;
	#endif
	#ifdef B1200
	case 1200 :
		baudrate = B1200;
		break;
	#endif
	#ifdef B1800
	case 1800 :
		baudrate = B1800;
		break;
	#endif
	#ifdef B2400
	case 2400 :
		baudrate = B2400;
		break;
	#endif
	#ifdef B4800
	case 4800 :
		baudrate = B4800;
		break;
	#endif
	#ifdef B9600
	case 9600 :
		baudrate = B9600;
		break;
	#endif
	#ifdef B19200
	case 19200 :
		baudrate = B19200;
		break;
	#endif
	#ifdef B38400
	case 38400 :
		baudrate = B38400;
		break;
	#endif
	#ifdef B57600
	case 57600 :
		baudrate = B57600;
		break;
	#endif
	#ifdef B115200
	case 115200 :
		baudrate = B115200;
		break;
	#endif
	#ifdef B230400
	case 230400 :
		baudrate = B230400;
		break;
	#endif
	#ifdef B460800
	case 460800 :
		baudrate = B460800;
		break;
	#endif
	#ifdef B500000
	case 500000 :
		baudrate = B500000;
		break;
	#endif
	#ifdef B576000
	case 576000 :
		baudrate = B576000;
		break;
	#endif
	#ifdef B921600
	case 921600 :
		baudrate = B921600;
		break;
	#endif
	#ifdef B1000000
	case 1000000 :
		baudrate = B1000000;
		break;
	#endif
	#ifdef B1152000
	case 1152000 :
		baudrate = B1152000;
		break;
	#endif
	#ifdef B1500000
	case 1500000 :
		baudrate = B1500000;
		break;
	#endif
	#ifdef B2000000
	case 2000000 :
		baudrate = B2000000;
		break;
	#endif
	#ifdef B2500000
	case 2500000 :
		baudrate = B2500000;
		break;
	#endif
	#ifdef B3000000
	case 3000000 :
		baudrate = B3000000;
		break;
	#endif
	#ifdef B3500000
	case 3500000 :
		baudrate = B3500000;
		break;
	#endif
	#ifdef B4000000
	case 4000000 :
		baudrate = B4000000;
		break;
	#endif
	default :
		baudrate = 0;
	}
	return baudrate;
}

