#ifndef serial_h
#define serial_h

#ifdef __cplusplus
extern "C"{
#endif

/* Handler type definition */
typedef void (*serial_handler) (int status);

/* Macros */

#define PARITY_OFF 	0
#define PARITY_ODD 	1
#define PARTIY_EVEN	2

#define DATA_8		8
#define DATA_7		7
#define DATA_6		6
#define DATA_5		5

#define STOP_1		0
#define STOP_2		1
/* Functions */

/* 
 * begin_serial() - Initialize serial device
 * @handler:	Takes a function pointer of type serial_handler
 * @device:	Takes the path of the serial device. Example, "/dev/tty"
 * @baud:	Baudrate. Example, 9600, 38400, 115200
 * @data_bits:	Number of data bits. Example, 8,7,6,5
 * @stop_bits:	Number of stop bits. '0' for 1 stop bit and '1' for 2 stopbits
 * @parity:	Parity and type. 0 for none, 1 for odd and 2 for even.
 * 
 * Sets the above options for the given serial device
 *
 * Return:	Returns the file descriptor for the given device
 */

int config_serial(serial_handler handler, const char * device, long baud, int data_bits, int stop_bits, 
								int parity);
int read_char(int fd, char *c);
int write_char(int fd, char c);
unsigned int parse_baudrate(long requested);

/*
 * set_terminal_mode() - Configure the terminal
 *
 * Configures the terminal for non-canonical and non-echo mode input.
 * Setup to call reset_terminal_mode() when programs exits normally. 
 */

void set_terminal_mode (void);

/*
 * reset_terminal_mode() - Restore the orignial terminal mode settings.
 *
 * Should be called when original settings are to be restored.
 */

void reset_terminal_mode (void);

#ifdef __cplusplus
}
#endif
#endif /* serial_h */

